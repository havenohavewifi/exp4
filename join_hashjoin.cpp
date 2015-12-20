#include <cstdlib>
#include <cstring>
#include <iostream>

#include "join_Hashjoin.h"
#include "cursorForTmptable.h"
#include "dataDictionary.h"
#include "Buffer.h"
#include <sys/time.h>
#include <sys/wait.h>
#include "getaRecordbyCursor.h"
#define nullptr 0
#define hashjoinBuffer_SIZE                 (1* 1024 * 1024)
#define VALUE_SIZE                  1024
#define HASH_TABLE_BUCKET_COUNT     32
#define TUPLE_COUNT_PER_BUCKET      8
#define OUTPUT_INIT_CAPACITY        (1 * 1024)
using namespace std;

class hashjoinBuffer
{
    public:
        hashjoinBuffer(size_t size)
        :   size_(size),
            next_(nullptr)
        {
            pos_ = data_ = new char[size];
        }

        ~hashjoinBuffer()
        {
            if (next_ != nullptr)
                delete next_;
            delete data_;
        }

        hashjoinBuffer* getNext()
        {
            return next_;
        }

        void setNext(hashjoinBuffer* next)
        {
            next_ = next;
        }

        char* allocate(size_t size)
        {
            char* pos = pos_;
            pos_ += size;

            return pos;
        }

        size_t getAvailable()
        {
            return data_ + size_ - pos_;
        }

    private:
        char* data_;
        char* pos_;
        size_t size_;
        hashjoinBuffer* next_;
};

class hashjoinBufferManager
{
    public:
        hashjoinBufferManager()
        :   current_(new hashjoinBuffer(hashjoinBuffer_SIZE))
        {}

        ~hashjoinBufferManager()
        {
            delete current_;
        }

        char* allocate(size_t size)
        {
            if (size > hashjoinBuffer_SIZE)
            {
                hashjoinBuffer* extra = new hashjoinBuffer(size);
                extra->setNext(current_->getNext());
                current_->setNext(extra);

                return extra->allocate(size);
            }
            else if (size > current_->getAvailable())
            {
                hashjoinBuffer* new_hashjoinBuffer = new hashjoinBuffer(hashjoinBuffer_SIZE);
                new_hashjoinBuffer->setNext(current_);
                current_ = new_hashjoinBuffer;

                return current_->allocate(size);
            }
            else
                return current_->allocate(size);
        }

    private:
        hashjoinBuffer* current_;
};

class InputTuple
{
    public:
        int key;
        char value[VALUE_SIZE];
};

class InputRelation
{
    public:
        InputRelation(hashjoinBufferManager& hashjoinBuffer_manager, int tuple_num_)
        :   input_tuples_(nullptr),
            input_tuple_count_(0),
            input_tuple_capacity_(tuple_num_),
            hashjoinBuffer_manager_(hashjoinBuffer_manager)
        {
            input_tuples_ = (InputTuple *) hashjoinBuffer_manager_.allocate(                     input_tuple_capacity_ * sizeof(InputTuple));
        }

        ~InputRelation()
        {}

        void addInputTuple(int key, const char * itsvalue)
        {
            input_tuples_[input_tuple_count_].key = key;
            memcpy(input_tuples_[input_tuple_count_ ++].value, itsvalue, VALUE_SIZE);
        }

        InputTuple* getInputTuples()
        {
            return input_tuples_;
        }

        int getInputTupleCount()
        {
            return input_tuple_count_;
        }

    private:
        InputTuple* input_tuples_;
        int input_tuple_count_;
        int input_tuple_capacity_;
        hashjoinBufferManager& hashjoinBuffer_manager_;
};

class InputView
{
    public:
        InputView(InputRelation& input_relation)
        :   input_tuples_(input_relation.getInputTuples()),
            input_tuple_count_(input_relation.getInputTupleCount())
        {}

        ~InputView()
        {}

        InputTuple* getInputTuples()
        {
            return input_tuples_;
        }

        int getInputTupleCount()
        {
            return input_tuple_count_;
        }

    private:
        InputTuple* input_tuples_;
        int input_tuple_count_;
};

class OutputTuple
{
    public:
        int key;
        char left_value[VALUE_SIZE];
        char right_value[VALUE_SIZE];
};

class OutputRelation
{
    public:
        OutputRelation(hashjoinBufferManager& hashjoinBuffer_manager)
        :   output_tuples_(nullptr),
            output_tuple_count_(0),
            output_tuple_capacity_(0),
            hashjoinBuffer_manager_(hashjoinBuffer_manager)
        {}

        ~OutputRelation()
        {}

        int getOutputTupleCount()
        {
            return output_tuple_count_;
        }

        void addOutputTuple(OutputTuple& output_tuple)
        {
            if (output_tuple_capacity_ == output_tuple_count_)
            {
                OutputTuple* old_output_tuples = output_tuples_;
                int old_output_tuple_capacity = output_tuple_capacity_;

                if (output_tuple_capacity_ == 0)
                    output_tuple_capacity_ = OUTPUT_INIT_CAPACITY;
                else
                    output_tuple_capacity_ <<= 1;

                output_tuples_ = (OutputTuple *) hashjoinBuffer_manager_.allocate(
                        output_tuple_capacity_ * sizeof(OutputTuple));

                memcpy(output_tuples_,
                        old_output_tuples,
                        old_output_tuple_capacity * sizeof(OutputTuple));
            }

            output_tuples_[output_tuple_count_ ++] = output_tuple;
        }

    public:
        OutputTuple* output_tuples_;
    private:
        int output_tuple_count_;
        int output_tuple_capacity_;
        hashjoinBufferManager& hashjoinBuffer_manager_;
};

class HeapInputTuple
{
    public:
        InputTuple input_tuple;
        HeapInputTuple* next;
};

class HashTable
{
    public:
        HashTable(hashjoinBufferManager& hashjoinBuffer_manager)
        :   input_tuple_count_(0),
            bucket_count_(HASH_TABLE_BUCKET_COUNT),
            hashjoinBuffer_manager_(hashjoinBuffer_manager)
        {
            buckets_ = (HeapInputTuple **) hashjoinBuffer_manager_.allocate(
                    HASH_TABLE_BUCKET_COUNT * sizeof(HeapInputTuple *));
            for (int i = 0; i < bucket_count_; i ++)
                buckets_[i] = nullptr;
        }

        ~HashTable()
        {}

        void insert(InputTuple& input_tuple)
        {
            HeapInputTuple* heap_input_tuple = (HeapInputTuple *)
                    hashjoinBuffer_manager_.allocate(sizeof(HeapInputTuple));
            heap_input_tuple->input_tuple = input_tuple;

            int index = hash(input_tuple.key);

            heap_input_tuple->next = buckets_[index];
            buckets_[index] = heap_input_tuple;

            input_tuple_count_ ++;

            if (bucket_count_ * TUPLE_COUNT_PER_BUCKET < input_tuple_count_)
                adjust();
        }

        bool find(InputTuple& left_input_tuple,
                HeapInputTuple& right_heap_input_tuple,
                bool& first)
        {
            HeapInputTuple* heap_input_tuple;

            if (first == true)
            {
                int index = hash(left_input_tuple.key);
                heap_input_tuple = buckets_[index];
                first = false;
            }
            else
                heap_input_tuple = right_heap_input_tuple.next;

            while (heap_input_tuple != nullptr)
            {
                if (left_input_tuple.key == heap_input_tuple->input_tuple.key)
                {
                    right_heap_input_tuple = *heap_input_tuple;
                    return true;
                }
                heap_input_tuple = heap_input_tuple->next;
            }

            return false;
        }

    private:
        int hash(int key)
        {
            return key & (bucket_count_ - 1);
        }

        void adjust()
        {
            int old_bucket_count = bucket_count_;
            HeapInputTuple** old_buckets = buckets_;
            while (bucket_count_ * TUPLE_COUNT_PER_BUCKET < input_tuple_count_)
                bucket_count_ <<= 1;

            buckets_ = (HeapInputTuple **) hashjoinBuffer_manager_.allocate(
                    bucket_count_ * sizeof(HeapInputTuple *));
            for (int i = 0; i < bucket_count_; i ++)
                buckets_[i] = nullptr;

            for (int i = 0; i < old_bucket_count; i ++)
            {
                while (old_buckets[i] != nullptr)
                {
                    HeapInputTuple* heap_input_tuple = old_buckets[i];
                    old_buckets[i] = heap_input_tuple->next;

                    int index = hash(heap_input_tuple->input_tuple.key);
                    heap_input_tuple->next = buckets_[index];
                    buckets_[index] = heap_input_tuple;
                }
            }
        }

        int input_tuple_count_;
        HeapInputTuple** buckets_;
        int bucket_count_;
        hashjoinBufferManager& hashjoinBuffer_manager_;
};

class HashJoin
{
    public:
        HashJoin(InputView& left_view,
                InputView& right_view,
                OutputRelation& output_relation,
                hashjoinBufferManager& hashjoinBuffer_manager)
        :   left_view_(left_view),
            right_view_(right_view),
            hash_table_(hashjoinBuffer_manager),
            output_relation_(output_relation)
        {}

        ~HashJoin()
        {}

        void build()
        {
            InputTuple* input_tuples = right_view_.getInputTuples();
            int input_tuple_count = right_view_.getInputTupleCount();

            for (int i = 0; i < input_tuple_count; i ++)
                hash_table_.insert(input_tuples[i]);
        }

        void probe()
        {
            InputTuple* input_tuples = left_view_.getInputTuples();
            int input_tuple_count = left_view_.getInputTupleCount();
            HeapInputTuple heap_input_tuple;
            OutputTuple output_tuple;
            bool first;

            for (int i = 0; i < input_tuple_count; i ++)
            {
                first = true;
                while (hash_table_.find(input_tuples[i], heap_input_tuple, first))
                {
                    output_tuple.key = input_tuples[i].key;
                    memcpy(output_tuple.left_value, input_tuples[i].value, VALUE_SIZE);
                    memcpy(output_tuple.right_value,
                            heap_input_tuple.input_tuple.value,
                            VALUE_SIZE);

                    output_relation_.addOutputTuple(output_tuple);
                }
            }
        }

    private:
        InputView left_view_;
        InputView right_view_;
        HashTable hash_table_;
        OutputRelation& output_relation_;
};

int hashjoin(struct dbSysHead *head, relation *temp_datadic,int old_relation_1, int old_relation_2, const char *name){
    //find empty temp_datadic
    int new_relation;
    for (int i = 0; i < MAX_FILE_NUM; i++) {
        if (strcmp(temp_datadic[i].getRelationName(),"") == 0) {
            new_relation = i;
            cout<<"new relation id: "<<new_relation<<endl;
            temp_datadic[new_relation].init("temp_datadict","XXX");
            break;
        }
    }
    if (new_relation == MAX_FILE_NUM) {
        cout<<"no temp datadict for use!"<<endl;
        return -3;
    }
    //input error control
    int flag = -1;
    for (int i = 0; i < temp_datadic[old_relation_1].getAttributeNum(); i++) {
        if (strcmp(name, temp_datadic[old_relation_1].getAttributeByNo(i).getName()) == 0)
            flag ++;
         
    }
    for (int i = 0; i < temp_datadic[old_relation_2].getAttributeNum(); i++) {
        if (strcmp(name, temp_datadic[old_relation_2].getAttributeByNo(i).getName()) == 0)
            flag ++;
        
    }
    if (flag != 1) {
        cout<<"input attributes error!"<<endl;
        return -1;
    }
    
    int original_rec_length1 = temp_datadic[old_relation_1].getRecordLength();
    int original_rec_length2 = temp_datadic[old_relation_2].getRecordLength();
    int original_attribute_length1=temp_datadic[old_relation_1].getAttributeNum();
    int original_attribute_length2=temp_datadic[old_relation_2].getAttributeNum();

    //look up which buffer is empty
    int buffer_id_;
    int i;
    for (i = 0; i < BUFF_NUM; i++) {
        if (head->buff[i].emptyOrnot == true) {
            buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
            std::cout << "BufferID: " << i << std::endl;
            break;
        }
    }
    if (i == BUFF_NUM) {
        cout << "No Buffer Can be Used!" << endl;
        return -2;
    }
    else{
        int start1, start2, k1, k2;
        char * one_Row_1 = (char *)malloc(sizeof(char) * original_rec_length1);
        char * one_Row_2 = (char *)malloc(sizeof(char) * original_rec_length2);
        
        hashjoinBufferManager* hashjoinBuffer_manager = new hashjoinBufferManager();
        InputRelation* left_relation = new InputRelation(*hashjoinBuffer_manager, temp_datadic[old_relation_1].getRecordNum());
        InputRelation* right_relation = new InputRelation(*hashjoinBuffer_manager, temp_datadic[old_relation_2].getRecordNum());
        cout<<"left relation num :"<<temp_datadic[old_relation_1].getRecordNum() << "  right relation num :"<<temp_datadic[old_relation_2].getRecordNum() <<endl;
        //creat <key, pos> pair
        RecordCursorTmp scanTable1(head, temp_datadic[old_relation_1].fileID, original_rec_length1, -temp_datadic[old_relation_1].fileID, temp_datadic[old_relation_1].getRecordNum());
        while (true == scanTable1.getNextRecord(one_Row_1)) {
            for(int i=0;i<original_attribute_length1;i++){
                if(strcmp(temp_datadic[old_relation_1].getAttributeByNo(i).getName(),name)==0){
                    start1=temp_datadic[old_relation_1].getAttributeByNo(i).getRecordDeviation();
                    k1=*((int*)(one_Row_1+start1));  //debug for key
         //           cout<<k1<<endl;
                    left_relation->addInputTuple(k1,one_Row_1);
                    break;
                }
            }
        }
        RecordCursorTmp scanTable2(head, temp_datadic[old_relation_2].fileID, original_rec_length2, -temp_datadic[old_relation_2].fileID, temp_datadic[old_relation_2].getRecordNum());
        while (true == scanTable2.getNextRecord(one_Row_2)){
            for(int i=0;i<original_attribute_length2;i++){
                if(strcmp(temp_datadic[old_relation_2].getAttributeByNo(i).getName(),name)==0){
                    start2=temp_datadic[old_relation_2].getAttributeByNo(i).getRecordDeviation();
                    k2=*((int*)(one_Row_2+start2));  //debug for key
          //          cout<<k2<<endl;
                    right_relation->addInputTuple(k2,one_Row_2);
                    break;
                }
            }
        }
        InputView* left_view = new InputView(*left_relation);
        InputView* right_view = new InputView(*right_relation);
        OutputRelation* output_relation = new OutputRelation(*hashjoinBuffer_manager);
               
        HashJoin* hash_join = new HashJoin(*left_view,
                                                  *right_view,
                                                  *output_relation,
                                                  *hashjoinBuffer_manager);
               
        hash_join->build();
        hash_join->probe();
               
        cout << "matches: " << output_relation->getOutputTupleCount() << "." << endl;
        temp_datadic[new_relation].fileID = -buffer_id_;
        for (int i = 0; i < original_attribute_length1; i++) {
            temp_datadic[new_relation].insertAttribute( temp_datadic[old_relation_1].getAttributeByNo(i).getName(),  temp_datadic[old_relation_1].getAttributeByNo(i).getType(),  temp_datadic[old_relation_1].getAttributeByNo(i).getLength()) ;
        }
        for (int i = 0; i < original_attribute_length2; i++) {
            temp_datadic[new_relation].insertAttribute( temp_datadic[old_relation_2].getAttributeByNo(i).getName(),  temp_datadic[old_relation_2].getAttributeByNo(i).getType(),  temp_datadic[old_relation_2].getAttributeByNo(i).getLength()) ;
        }
        
        Buffer t(head, -2); //to avoid positive number, no meaning
        int new_rec_length = original_rec_length1 + original_rec_length2;
        char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
        for (int i = 0; i< output_relation->getOutputTupleCount(); i++) {
            memcpy(new_Row_, output_relation->output_tuples_[i].left_value,original_rec_length1);
            memcpy(new_Row_ + original_rec_length1, output_relation->output_tuples_[i].right_value,original_rec_length2);
            /*
            for(int j=0;j<original_rec_length1;j++)
            new_Row_[j]=output_relation->output_tuples_[i].left_value[j];
            for(int j=0;j<original_rec_length2;j++)
            new_Row_[j+original_rec_length1]=output_relation->output_tuples_[i].right_value[j];
            */
             //cout<<new_Row_<<endl;
            //cout<<new_Row_[4]<<new_Row_[5]<<endl;
            //cout<<"~~~~"<<endl;
            //getOneRecord(new_Row_,&temp_datadic[new_relation]);
            //delay(10);
            //if more than one page, write to file and reset Buffer t
            if (false == t.AppendBuffer(new_Row_, new_rec_length))
            {
                t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
                t.pageID++;
                if (t.pageID == SIZE_BUFF) {
                    std::cout << "this buffer full" << std::endl;
                    break;
                }
                memset(t.data_, 0, SIZE_PER_PAGE);
                memcpy(t.data_, new_Row_, new_rec_length);
                t.pointer_ = t.data_ + new_rec_length;
                t.current_size_ = new_rec_length;
            }
        }
        //write remainder
        t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
        free(new_Row_);
        /*
        temp_datadic[new_relation].fileID = -buffer_id_;
        for (int i = 0; i < original_attribute_length1; i++) {
            temp_datadic[new_relation].insertAttribute( temp_datadic[old_relation_1].getAttributeByNo(i).getName(),  temp_datadic[old_relation_1].getAttributeByNo(i).getType(),  temp_datadic[old_relation_1].getAttributeByNo(i).getLength()) ;
        }
        for (int i = 0; i < original_attribute_length2; i++) {
            temp_datadic[new_relation].insertAttribute( temp_datadic[old_relation_2].getAttributeByNo(i).getName(),  temp_datadic[old_relation_2].getAttributeByNo(i).getType(),  temp_datadic[old_relation_2].getAttributeByNo(i).getLength()) ;
        }
         */
        //Attention!!!
        temp_datadic[new_relation].changeRecordNum(output_relation->getOutputTupleCount());
        //delete old relation
        strcpy(temp_datadic[old_relation_1].getRelationName(),"");
        strcpy(temp_datadic[old_relation_2].getRelationName(),"");
        head->buff[-temp_datadic[old_relation_1].fileID].emptyOrnot = true;
        head->buff[-temp_datadic[old_relation_2].fileID].emptyOrnot = true;
        
            
        delete hash_join;
        delete output_relation;
        delete left_view;
        delete right_view;
        delete left_relation;
        delete right_relation;
        std::cout << new_relation<< std::endl;
//        return new_relation;
        }
    return new_relation;
}

