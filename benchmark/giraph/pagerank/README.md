# Instructions

After setting up giraph (or using the docker image by running: ``` srun-docker run -ti --rm -v /sampa/home:/home -v /sampa/share:/share -v /shared:/shared uwsampa/giraph-docker /etc/giraph-bootstrap.sh -bash ```)

Compile with jar file and update the jar file

```
cd /home/yx0618/test4/graphbench/benchmark/giraph/pagerank

javac -cp $GIRAPH_HOME/giraph-examples/target/giraph-examples-1.1.0-SNAPSHOT-for-hadoop-2.4.1-jar-with-dependencies.jar:$($HADOOP_HOME/bin/hadoop classpath) PRComputation.java

cp $GIRAPH_HOME/giraph-examples/target/giraph-examples-1.1.0-SNAPSHOT-for-hadoop-2.4.1-jar-with-dependencies.jar ./myjar.jar

jar uf myjar.jar PRComputation.class
```

Put the input file in the hdfs, run Giraph and check the output (make sure you have the correct directory in hdfs, eg: ```$HADOOP_HOME/bin/hdfs dfs -mkdir user``` to create user directory)

```
$HADOOP_HOME/bin/hdfs dfs -put tiny-graph.txt user/tiny-graph.txt

$HADOOP_HOME/bin/hadoop jar myjar.jar org.apache.giraph.GiraphRunner PRComputation --yarnjars myjar.jar --workers 1 --vertexInputFormat org.apache.giraph.io.formats.JsonLongDoubleFloatDoubleVertexInputFormat --vertexInputPath user/yx0618/tiny-graph.txt -vertexOutputFormat org.apache.giraph.io.formats.IdWithValueTextOutputFormat --outputPath user/output

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

