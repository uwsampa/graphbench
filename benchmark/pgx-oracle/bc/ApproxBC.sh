#!/bin/bash
if [ "$#" -eq  "2" ] 
	then
mkdir BC
javac -cp $PGX_HOME/lib/common/*:$PGX_HOME/lib/yarn/*:$PGX_HOME/lib/embedded/*:$PGX_HOME/lib/client/*:$PGX_HOME/third-party/* ApproximateBC.java -d BC/
java -Dlog4j.configuration=file:$PGX_HOME/conf/log4j.xml -cp $PGX_HOME/lib/common/*:$PGX_HOME/lib/yarn/*:$PGX_HOME/lib/embedded/*:$PGX_HOME/lib/client/*:$PGX_HOME/third-party/*:BC ApproximateBC $1 $2
rm -r BC
else
	echo "usage: BC <graph config path> <number of random selected seed nodes to use>"
fi
