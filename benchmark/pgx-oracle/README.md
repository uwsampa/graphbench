
# Instruction
## Installation
Download Oracle PGX and Groovy (2.4.0 is a hard require)

http://www.oracle.com/technetwork/oracle-labs/parallel-graph-analytics/downloads/index.html

http://dl.bintray.com/groovy/maven/groovy-binary-2.4.0.zip [the newest version is 2.4.3 right now]

Unzip the files and set PGX_HOME and GROOVY_HOME to the correct directory. 

## Test
cd $PGX_HOME

./bin/pgx

## More Details
check the original documentation from Oracle

https://docs.oracle.com/cd/E56133_01/index.html

More tutorial after installation:

https://docs.oracle.com/cd/E56133_01/tutorials/index.html


# Notice
Keep all the .java and .sh file in the same directory. 

Run the .sh file, pass in the correct parameters and the output will measure the processing time for the particular algorithm.   

For now, only the pgx-oracle framework is included. We will update when other frameworks are available.

