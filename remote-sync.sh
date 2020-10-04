#!/bin/bash

echo "starting synchronization (only src dir)..."

rsync -r -a -v -e ssh --delete ../src pi@$REMOTE_HOST:$REMOTE_PATH

echo "synchronization finish!"
