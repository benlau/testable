#!/bin/bash

export DISPLAY=:99.0
set -v
set -e
pushd tests/testableunittests/
qmake
make
ls
./testableunittests
popd

pushd tests/testablecmdtests
qmake
make
bash ./run-tests.sh
popd
