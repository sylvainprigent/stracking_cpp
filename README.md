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