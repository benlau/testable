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
xvfb-run --auto-servernum ./testablecmdtests $ARG | grep Totals | sed 's/, [[:digit:]]\+ms//g' > $OUTPUT.out 2>&1
diff -uN $SRCDIR/$OUTPUT.expected $OUTPUT.out
}

compare
compare test1 test2
compare DummyTests2
compare QuickTests::test_dummy1
