#!/bin/bash
if [ "$#" -eq  "1" ] 
	then
mkdir triangle
javac -cp $PGX_HOME/lib/common/*:$PGX_HOME/lib/yarn/*:$PGX_HOME/lib/embedded/*:$PGX_HOME/lib/client/*:$PGX_HOME/third-party/* triangleCounting.java -d triangle/
java -Dlog4j.configuration=file:$PGX_HOME/conf/log4j.xml -cp $PGX_HOME/lib/common/*:$PGX_HOME/lib/yarn/*:$PGX_HOME/lib/embedded/*:$PGX_HOME/lib/client/*:$PGX_HOME/third-party/*:triangle triangleCounting $1
rm -r triangle
else
echo "usage: triangleCounting <graph config path>"
fi
