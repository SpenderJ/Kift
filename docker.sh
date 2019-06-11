#!/usr/bin/env bash

docker build --target kift .
docker run --name rick --volume $PWD:/home --port 6060 -dt kift
