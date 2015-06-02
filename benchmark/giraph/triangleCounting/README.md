# Instructions

After setting up giraph (or using the docker image by running: ``` srun-docker run -ti --rm -v /sampa/home:/home -v /sampa/share:/share -v /shared:/shared uwsampa/giraph-docker /etc/giraph-bootstrap.sh -bash ```)

Copy the new format for triangleCounting into the right directory and compile

```
cd graphbench/benchmark/giraph/triangleCounting

cp JsonDoubleDoubleFloatDoubleVertexInputFormat.java $GIRAPH_HOME/giraph-core/src/main/java/org/apache/giraph/io/formats

cd $GIRAPH_HOME/giraph-core/src/main/java/org/apache/giraph/io/formats

javac -cp $GIRAPH_HOME/giraph-examples/target/giraph-examples-1.1.0-SNAPSHOT-for-hadoop-2.4.1-jar-with-dependencies.jar:$($HADOOP_HOME/bin/hadoop classpath) JsonDoubleDoubleFloatDoubleVertexInputFormat.java
```

Update the jar file and compile the algorithm 

```
cd $GIRAPH_HOME/giraph-core/src/main/java/

jar uf $GIRAPH_HOME/giraph-examples/target/giraph-examples-1.1.0-SNAPSHOT-for-hadoop-2.4.1-jar-with-dependencies.jar org/apache/giraph/io/formats/JsonDoubleDoubleFloatDoubleVertexInputFormat.class org/apache/giraph/io/formats/JsonDoubleDoubleFloatDoubleVertexInputFormat\$JsonDoubleDoubleFloatDoubleVertexReader.class

cd graphbench/benchmark/giraph/triangleCounting

javac -cp $GIRAPH_HOME/giraph-examples/target/giraph-examples-1.1.0-SNAPSHOT-for-hadoop-2.4.1-jar-with-dependencies.jar:$($HADOOP_HOME/bin/hadoop classpath) TriangleCounting.java

cp $GIRAPH_HOME/giraph-examples/target/giraph-examples-1.1.0-SNAPSHOT-for-hadoop-2.4.1-jar-with-dependencies.jar ./myjar.jar

jar uf myjar.jar TriangleCounting.class
```

Put the input file in the hdfs, run Giraph and check the output (make sure you have the correct directory in hdfs, eg: ```$HADOOP_HOME/bin/hdfs dfs -mkdir /home/<user>``` to create user directory)

```
$HADOOP_HOME/bin/hdfs dfs -put tiny-graph.txt tiny-graph.txt

$HADOOP_HOME/bin/hadoop jar myjar.jar org.apache.giraph.GiraphRunner TriangleCounting --yarnjars myjar.jar --workers 1 --vertexInputFormat org.apache.giraph.io.formats.JsonDoubleDoubleFloatDoubleVertexInputFormat --vertexInputPath tiny-graph.txt -vertexOutputFormat org.apache.giraph.io.formats.IdWithValueTextOutputFormat --outputPath output

$HADOOP_HOME/bin/hdfs dfs -cat user/output/part-m-00001
```

## Notice

tiny-graph.txt
```
[0,0,[[1,1],[3,3]]]
[1,0,[[0,1],[2,2],[3,1]]]
[2,0,[[1,2],[4,4]]]
[3,0,[[0,3],[1,1],[4,4]]]
[4,0,[[3,4],[2,4]]]
```
