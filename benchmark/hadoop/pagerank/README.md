# Instructions

After having Hadoop all setup and running,

Put the input file in the hdfs

```
$HADOOP_PREFIX/bin/hadoop dfs -put <pathToInputFile/file.txt>[eg:/sampa/home/user/bfs/input.txt] <pathForHDFSdirectory>[eg:/user/username]
```

Compile the java code

```
javac -cp $( $HADOOP_PREFIX/bin/hadoop classpath ) -Xlint InitPRPreProcessor.java Map.java TSVPreProcessor.java Main.java Node.java Reduce.java
```

Make jar file and run

```
cd ..
jar -cvf pagerank.jar pagerank/*
$HADOOP_PREFIX/bin/hadoop jar pagerank.jar pagerank/Main /user/username/input.txt second third result 10
```

### Usage for Main.java

```
Usage: <input file> <intermediate folder1> <intermediate folder2> <result folder> <max number of iter>
```
## Reference

Pagerank Hadoop Code based on the book "Hadoop in Practice" from Alex Holmes in chapter 7. 

link: https://github.com/alexholmes/hadoop-book/tree/master/src/main/java/com/manning/hip/ch7/pagerank


