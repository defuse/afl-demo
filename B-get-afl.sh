#!/bin/bash

wget http://lcamtuf.coredump.cx/afl/releases/afl-latest.tgz
tar xvf afl-latest.tgz
rm afl-latest.tgz
cd afl-*
make
