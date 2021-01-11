#!/bin/bash

process=$1
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PID_FILE="$DIR/ax.pid"
case $process in
    start)
        echo "STARTING Ax server" > /dev/stderr
        python3 $DIR/main.py &
        echo $! > $PID_FILE
        ;;

    stop)
        kill -9 $(cat $PID_FILE)
        rm $PID_FILE
        ;;

    *)
        echo "INVALID OPTION"
        ;;
esac
