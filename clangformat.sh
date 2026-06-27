#!/bin/bash

find . -type d \( -path ./build -o -path ./cmake \) -prune -false -o -iname *.cpp -o -iname *.cppm -o -iname *.h | xargs clang-format -style=file -i

