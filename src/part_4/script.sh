#!/bin/bash

service nginx start
nginx -s reload
gcc /home/server.c -lfcgi -o server
./server
