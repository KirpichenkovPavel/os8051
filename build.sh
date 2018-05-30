#!/usr/bin/env bash
cd build
rm -rf ./*
sdcc -c ../src/dispatcher/dispatcher.c
sdcc ../src/entry.c dispatcher.rel
