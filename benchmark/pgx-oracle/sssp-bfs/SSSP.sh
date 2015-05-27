#!/bin/bash
if [ "$#" -eq  "4" ] 
	then
mkdir sssp
javac -cp $PGX_HOME/lib/common/*:$PGX_HOME/lib/yarn/*:$PGX_HOME/lib/embedded/*:$PGX_HOME/lib/client/*:$PGX_HOME/third-party/* SSSP.java -d sssp/
java -Dlog4j.configuration=file:$PGX_HOME/conf/log4j.xml -cp $PGX_HOME/lib/common/*:$PGX_HOME/lib/yarn/*:$PGX_HOME/lib/embedded/*:$PGX_HOME/lib/client/*:$PGX_HOME/third-party/*:sssp SSSP $1 $2 $3 $4
rm -r sssp
else
echo "usage: ./SSSP.sh <graph config path> <costPropName in the .json file> <src node name> <dest node name>"
fi
