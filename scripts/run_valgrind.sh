#!/bin/bash

export BINDIR=./bin/linux/Debug
./scripts/buildPMS.sh
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $BINDIR/PMS

