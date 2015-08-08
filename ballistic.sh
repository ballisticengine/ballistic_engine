#!/usr/bin/env bash
ulimit -c unlimited 
ulimit -a 
export LD_LIBRARY_PATH="/home/maciek/ballistic_engine/python_build/boost/stage/lib:/home/maciek/ballistic_engine/python/lib"
echo $LD_LIBRARY_PATH
./bin/ballistic