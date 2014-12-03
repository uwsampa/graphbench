#!/bin/bash
if [ "$#" -eq  "1" ] 
	then
mkdir triangle
javac -cp $PGX_HOME/lib/*:$PGX_HOME/third-party/* triangleCounting.java -d triangle/
java -Dlog4j.configuration=file:$PGX_HOME/conf/log4j.xml -cp $PGX_HOME/lib/*:$PGX_HOME/third-party/*:triangle triangleCounting $1
else
echo "usage: triangleCounting <graph config path>"
fi
