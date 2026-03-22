#!/bin/sh
mkdir -p testdata/c/new
./build.sh
HOME=$PWD ./mailcheck testdata a b c
