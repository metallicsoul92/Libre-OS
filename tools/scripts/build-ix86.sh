#!/bin/sh
cd ../
make build-ix86 && make link-ix86
./iso-ix86.sh
