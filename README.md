# exp4
customer.tbl 和nation.tbl 更改为10行和行，因为目前nestloopjoin的结果会溢出，如果不需要调用nestloopjoin可以用原来的数据，否则要重新下载两个表。            
createTable里调用createFileSpace函数，创建文件空间，创建数组字典。
deleteTable按表名删除表文件，回收相应的外存空间。
