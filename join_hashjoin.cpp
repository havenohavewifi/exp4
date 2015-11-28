#include <cstdlib>
#include <cstring>
#include <iostream>

#include "join_Hashjoin.h"
#include "cursorForTmptable.h"
#include "datadictionary.h"

#define BUFFER_SIZE                 (1* 1024 * 1024)
#define VALUE_SIZE                  1024
#define HASH_TABLE_BUCKET_COUNT     32
#define TUPLE_COUNT_PER_BUCKET      8
#define OUTPUT_INIT_CAPACITY        (1 * 1024)
using namespace std;

class Buffer
{
    public:
        Buffer(size_t size)
        :   size_(size),
            next_(nullptr)
        {
            pos_ = data_ = new char[size];
        }

        ~Buffer()
        {
            if (next_ != nullptr)
                delete next_;
            delete data_;
        }

        Buffer* getNext()
        {
            return next_;
        }

        void setNext(Buffer* next)
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
        Buffer* next_;
};

class BufferManager
{
    public:
        BufferManager()
        :   current_(new Buffer(BUFFER_SIZE))
        {}

        ~BufferManager()
        {
            delete current_;
        }

        char* allocate(size_t size)
        {
            if (size > BUFFER_SIZE)
            {
                Buffer* extra = new Buffer(size);
                extra->setNext(current_->getNext());
                current_->setNext(extra);

                return extra->allocate(size);
            }
            else if (size > current_->getAvailable())
            {
                Buffer* new_buffer = new Buffer(BUFFER_SIZE);
                new_buffer->setNext(current_);
                current_ = new_buffer;

                return current_->allocate(size);
            }
            else
                return current_->allocate(size);
        }

    private:
        Buffer* current_;
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
        InputRelation(BufferManager& buffer_manager, int tuple_num_)
        :   input_tuples_(nullptr),
            input_tuple_count_(0),
            input_tuple_capacity_(tuple_num_),
            buffer_manager_(buffer_manager)
        {
            input_tuples_ = (InputTuple *) buffer_manager_.allocate(                     input_tuple_capacity_ * sizeof(InputTuple));
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
        BufferManager& buffer_manager_;
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
        OutputRelation(BufferManager& buffer_manager)
        :   output_tuples_(nullptr),
            output_tuple_count_(0),
            output_tuple_capacity_(0),
            buffer_manager_(buffer_manager)
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

                output_tuples_ = (OutputTuple *) buffer_manager_.allocate(
                        output_tuple_capacity_ * sizeof(OutputTuple));

                memcpy(output_tuples_,
                        old_output_tuples,
                        old_output_tuple_capacity * sizeof(OutputTuple));
            }

            output_tuples_[output_tuple_count_ ++] = output_tuple;
        }

    private:
        OutputTuple* output_tuples_;
        int output_tuple_count_;
        int output_tuple_capacity_;
        BufferManager& buffer_manager_;
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
        HashTable(BufferManager& buffer_manager)
        :   input_tuple_count_(0),
            bucket_count_(HASH_TABLE_BUCKET_COUNT),
            buffer_manager_(buffer_manager)
        {
            buckets_ = (HeapInputTuple **) buffer_manager_.allocate(
                    HASH_TABLE_BUCKET_COUNT * sizeof(HeapInputTuple *));
            for (int i = 0; i < bucket_count_; i ++)
                buckets_[i] = nullptr;
        }

        ~HashTable()
        {}

        void insert(InputTuple& input_tuple)
        {
            HeapInputTuple* heap_input_tuple = (HeapInputTuple *)
                    buffer_manager_.allocate(sizeof(HeapInputTuple));
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

            buckets_ = (HeapInputTuple **) buffer_manager_.allocate(
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
        BufferManager& buffer_manager_;
};

class HashJoin
{
    public:
        HashJoin(InputView& left_view,
                InputView& right_view,
                OutputRelation& output_relation,
                BufferManager& buffer_manager)
        :   left_view_(left_view),
            right_view_(right_view),
            hash_table_(buffer_manager),
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

void hashjoin(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name){
    int original_rec_length1 = temp_datadic1->getRecordLength(); //record_length in original table*
    int original_rec_length2 = temp_datadic2->getRecordLength();
    int original_attribute_length1=temp_datadic1->getAttributeNum();
    int original_attribute_length2=temp_datadic2->getAttributeNum();
    int new_rec_length = result->getRecordLength();   //each record length in new temp table, in case SPJ use
    //look up which buffer is empty
    int buffer_id_;
    int i;
    for (i = 0; i < 3; i++) {
        if (head->buff[i].emptyOrnot == true) {
            buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
            std::cout << "bufferID: " << i << std::endl;
            break;
        }
    }
    if (i == 3) {
        cout << "No Buffer Can be Used!" << endl;
    }
    else{
        int start1, start2, k1, k2;
        
        char * one_Row_1 = (char *)malloc(sizeof(char) * original_rec_length1);
        char * one_Row_2 = (char *)malloc(sizeof(char) * original_rec_length2);
        char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
//        Buffer t(head, -2); //to avoid positive number, no meaning

        
        BufferManager* buffer_manager = new BufferManager();
        InputRelation* left_relation = new InputRelation(*buffer_manager, temp_datadic1->getRecordNum());
        InputRelation* right_relation = new InputRelation(*buffer_manager, temp_datadic2->getRecordNum());
        
        //creat <key, pos> pair
        RecordCursorTmp scanTable1(head, temp_datadic1->fileID, original_rec_length1, -temp_datadic1->fileID, temp_datadic1->getRecordNum());
        while (true == scanTable1.getNextRecord(one_Row_1)) { //only scan
            for(int i=0;i<original_attribute_length1;i++){
                if(strcmp(temp_datadic1->getAttributeByNo(i).getName(),name)==0){
                    start1=temp_datadic1->getAttributeByNo(i).getRecordDeviation();
                    k1=*((int*)(one_Row_1+start1));
                    left_relation->addInputTuple(k1,one_Row_1);
                    break;
                }
            }
        }
        RecordCursorTmp scanTable2(head, temp_datadic2->fileID, original_rec_length1, -temp_datadic2->fileID, temp_datadic2->getRecordNum());
        while (true == scanTable2.getNextRecord(one_Row_2)){
            for(int i=0;i<original_attribute_length2;i++){
                if(strcmp(temp_datadic2->getAttributeByNo(i).getName(),name)==0){
                    start2=temp_datadic2->getAttributeByNo(i).getRecordDeviation();
                    k2=*((int*)(one_Row_2+start2));
                    right_relation->addInputTuple(k2,one_Row_2);
                    break;
                }
            }
        }
        InputView* left_view = new InputView(*left_relation);
        InputView* right_view = new InputView(*right_relation);
        OutputRelation* output_relation = new OutputRelation(*buffer_manager);
               
        HashJoin* hash_join = new HashJoin(*left_view,
                                                  *right_view,
                                                  *output_relation,
                                                  *buffer_manager);
               
        hash_join->build();
        hash_join->probe();
               
        cout << "matches: " << output_relation->getOutputTupleCount() << "." << endl;
        delete hash_join;
        delete output_relation;
        delete left_view;
        delete right_view;
        delete left_relation;
        delete right_relation;
        }
}

