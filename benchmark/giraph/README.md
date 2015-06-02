# Instructions

Check each directories for details

# Input format

Standard giraph input

```
JSONArray(<vertex id>, <vertex value>, JSONArray(JSONArray(<dest vertex id>, <edge value>), ...))
```

## TSVProcessor.java
This program can convert the standard TSV format to the one required by giraph.

```
Usage: <Program> <input file>
```

## sample output

```
[0,0,[[1,1],[3,3]]]
[1,0,[[0,1],[2,2],[3,1]]]
[2,0,[[1,2],[4,4]]]
[3,0,[[0,3],[1,1],[4,4]]]
[4,0,[[3,4],[2,4]]]
```

# Docker image

This Docker image has Hadoop and Giraph pre-configured:
https://registry.hub.docker.com/u/uwsampa/giraph-docker
