#!/bin/bash

./afl-2.52b/afl-fuzz -i ./inputs -o findings_dir -- ./demo @@
