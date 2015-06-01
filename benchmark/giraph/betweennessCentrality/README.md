# Instructions

After setting up giraph (or using the docker image by running: ``` srun-docker run -ti --rm -v /sampa/home:/home -v /sampa/share:/share -v /shared:/shared uwsampa/giraph-docker /etc/giraph-bootstrap.sh -bash ```)

Copy the new format for BC into the right directory and compile

```
cd graphbench/benchmark/giraph/betweennessCentrality

cp BCNode.java $GIRAPH_HOME/giraph-core/src/main/java/org/apache/giraph/io/formats

cp BCMessage.java $GIRAPH_HOME/giraph-core/src/main/java/org/apache/giraph/io/formats

cp JsonLongBCNodeFloatBCMessageVertexInputFormat.java $GIRAPH_HOME/giraph-core/src/main/java/org/apache/giraph/io/formats

cd $GIRAPH_HOME/giraph-core/src/main/java/org/apache/giraph/io/formats

javac -cp $GIRAPH_HOME/giraph-examples/target/giraph-examples-1.1.0-SNAPSHOT-for-hadoop-2.4.1-jar-with-dependencies.jar:$($HADOOP_HOME/bin/hadoop classpath) JsonLongBCNodeFloatBCMessageVertexInputFormat.java BCNode.java BCMessage.java
```

Update the jar file and compile the algorithm 

```
cd $GIRAPH_HOME/giraph-core/src/main/java/

jar uf $GIRAPH_HOME/giraph-examples/target/giraph-examples-1.1.0-SNAPSHOT-for-hadoop-2.4.1-jar-with-dependencies.jar org/apache/giraph/io/formats/JsonLongBCNodeFloatBCMessageVertexInputFormat.class org/apache/giraph/io/formats/JsonLongBCNodeFloatBCMessageVertexInputFormat\$JsonLongDoubleFloatDoubleVertexReader.class org/apache/giraph/io/formats/BCNode.class org/apache/giraph/io/formats/BCMessage.class

cd /home/yx0618/test4/graphbench/benchmark/giraph/betweennessCentrality

javac -cp $GIRAPH_HOME/giraph-examples/target/giraph-examples-1.1.0-SNAPSHOT-for-hadoop-2.4.1-jar-with-dependencies.jar:$($HADOOP_HOME/bin/hadoop classpath) BCComputation.java

cp $GIRAPH_HOME/giraph-examples/target/giraph-examples-1.1.0-SNAPSHOT-for-hadoop-2.4.1-jar-with-dependencies.jar ./myjar.jar

jar uf myjar.jar BCComputation.class BCComputation\$Master.class
```

Run the Giraph and check the output

```
$HADOOP_HOME/bin/hdfs dfs -put tiny-graph.txt user/yx0618/tiny-graph.txt

$HADOOP_HOME/bin/hadoop jar myjar.jar org.apache.giraph.GiraphRunner BCComputation --yarnjars myjar.jar --workers 1 -mc BCComputation\$Master --vertexInputFormat org.apache.giraph.io.formats.JsonLongBCNodeFloatBCMessageVertexInputFormat --vertexInputPath user/yx0618/tiny-graph.txt -vertexOutputFormat org.apache.giraph.io.formats.IdWithValueTextOutputFormat --outputPath user/yx0618/output

$HADOOP_HOME/bin/hdfs dfs -cat user/yx0618/output/part-m-00001
```

## Notice

tiny-graph
```
[0,0,[[1,1],[3,3]]]
[1,0,[[0,1],[2,2],[3,1]]]
[2,0,[[1,2],[4,4]]]
[3,0,[[0,3],[1,1],[4,4]]]
[4,0,[[3,4],[2,4]]]
```
