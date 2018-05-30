#!/usr/bin/env bash
cd build
rm -rf ./*
sdcc -c ../src/dispatcher/dispatcher.c --model-large
sdcc ../src/entry.c dispatcher.rel --model-large
