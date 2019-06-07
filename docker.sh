#!/usr/bin/env bash

docker-machine env rick
eval $(docker-machine env rick)
docker start rick
docker exec -it rick bash
