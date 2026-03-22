#!/bin/sh
mkdir -p testdata/c/new
HOME=$PWD ./mailcheck testdata a b c
