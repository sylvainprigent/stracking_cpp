# STraking

Set of algorithm to track spot like structures for bio-imaging

## Compile


```
cd stracking
mkdir build
cmake ..
make
```

## Library usage

Here is an example how to run a process on an image

```
#include <stracking>
// todo

```

## Command line tools

```
// todo
...
```

# Docker

This repository contains a Dockerfile to run STracking in a container. We highly recommend using a `docker-compose.yml` to run your containers. Here is an example of docker-compose file content:

```yaml
version: "3"
    services:
        spartion:
            container_name: stracking
            build:
            context: ./spartion
            dockerfile: Dockerfile
            volumes:
                - './data:/app/data/' 
```


# test command

```
./bin/AssociationTracker -i ./bin/frames.txt -d ./bin/detections.txt -t ./bin/out.txt -v ./bin/outdir/ -p ./bin/param.json

./bin/AssociationTracker -i ./bin/frames.txt -d ./bin/detections.txt -t ./bin/out_graph.txt -v ./bin/outdir_graph/ -p ./bin/param_graph.json
```