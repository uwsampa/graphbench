# Instructions

After having Hadoop all setup and running,

Put the input file in the hdfs

```
$HADOOP_PREFIX/bin/hadoop dfs -put <pathToInputFile/file.txt>[eg:/sampa/home/user/bfs/input.txt] <pathForHDFSdirectory>[eg:/user/username]
```

Compile the java code

```
javac -cp $( $HADOOP_PREFIX/bin/hadoop classpath ) -Xlint TriangleCounter.java
```

Make jar file and run

```
cd ..
jar -cvf triangleCounting.jar triangleCounting/*
$HADOOP_PREFIX/bin/hadoop jar triangleCounting.jar triangleCounting/TriangleCounter /user/username/input.txt result
```

### Usage for TriangleCounter.java

```
Usage: <input file> <output directory name>
```

## Reference
The code is based on Stephen Walkauskas's code for Counting Triangle. 
We changed some parts to fit out input as well as removed some map 
classes and the last reduce class.

reference: http://www.vertica.com/2011/09/21/counting-triangles/

github link for the code: https://github.com/vertica/Graph-Analytics----Triangle-
