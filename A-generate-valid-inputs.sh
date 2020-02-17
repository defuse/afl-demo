#!/bin/bash

mkdir -p inputs

# Single string record.
echo -n -e '\x41\x00\x05abcde' > inputs/single-string
# Single int record.
echo -n -e '\x01\x00\x02\xDE\xAD' > inputs/single-int
# String then int.
echo -n -e '\x41\x00\x05abcde\x01\x00\x02\xDE\xAD' > inputs/string-then-int
