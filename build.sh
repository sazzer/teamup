#!/bin/sh

set -e

TOP=`dirname $0`
pushd $TOP
mkdir -p output
cd output
cmake ..
make
if ! make test; then
    cat Testing/Temporary/LastTest.log
    exit 1
fi
popd
