# Instructions

After having Hadoop all setup and running,

Put the input file in the hdfs

```
$HADOOP_PREFIX/bin/hadoop dfs -put <pathToInputFile/file.txt>[eg:/sampa/home/user/bfs/input.txt] <pathForHDFSdirectory>[eg:/user/username]
```$HADOOP_PREFIX

Compile the java code

```
javac -cp $( $HADOOP_PREFIX/bin/hadoop classpath ) -Xlint SearchMapper.java SearchReducer.java Node.java Main.java TSVPreProcessor.java
```

Make jar file and run

```
cd ..
jar -cvf bfs.jar bfs/* 
$HADOOP_PREFIX/bin/hadoop jar bfs.jar bfs/Main /user/username/input.txt tempDirectory outputDirectory
```

### Usage for Main.java

```
Usage: <input file> <intermediate directory name> <output directory name>
```

## Reference
This directory contains a Hadoop implementation of BFS.

The code is based on the code from This code is based on Deepika Mohan's SSSPJob:
http://hadooptutorial.wikispaces.com/file/view/SSSPJob.java 

Also reference to:
http://www.johnandcailin.com/blog/cailin/breadth-first-graph-search-using-iterative-map-reduce-algorithm
