#!/bin/bash

loc=$(dirname "$0")
run-clang-tidy -p ${loc}/build
