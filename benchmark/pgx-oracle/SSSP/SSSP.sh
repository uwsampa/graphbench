#!/bin/bash
if [ "$#" -eq  "4" ] 
	then
mkdir sssp
javac -cp $PGX_HOME/lib/*:$PGX_HOME/third-party/* SSSP.java -d sssp/
java -Dlog4j.configuration=file:$PGX_HOME/conf/log4j.xml -cp $PGX_HOME/lib/*:$PGX_HOME/third-party/*:sssp SSSP $1 $2 $3 $4
rm -r sssp
else
echo "usage: pagerank <graph config path> <costPropName in the .json file> <src node name> <dest node name>"
fi
