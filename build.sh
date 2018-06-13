#!/usr/bin/env bash
cd build
rm -rf ./*
sdcc -c ../src/workers/workers.c
sdcc -c ../src/dispatcher/dispatcher.c
sdcc ../src/entry.c workers.rel dispatcher.rel
