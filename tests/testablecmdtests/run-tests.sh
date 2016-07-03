#!/bin/bash

#set -v
set -e
SRCDIR=`dirname $0`

compare() {
ARG=$*
OUTPUT=`echo $ARG | sed "s/[  :]//g"`
if [ -z "$ARG" ]
then
OUTPUT="default"
fi

echo "testable $ARG"
./testablecmdtests $ARG | grep Totals > $OUTPUT.out 2>&1
diff -uN $SRCDIR/$OUTPUT.expected $OUTPUT.out
}

compare
compare test1 test2
compare DummyTests2
compare QuickTests::test_dummy1
