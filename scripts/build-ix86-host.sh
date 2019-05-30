#!/bin/sh
cd ../
make build-ix86-host && make link-ix86-host
./iso-ix86.sh
