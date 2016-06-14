import QtQuick 2.0

QtObject {
    property string name

    property bool hasError: false

    function compare(actual, expected) {
        if (actual !== expected) {
            console.trace();
            hasError = true;
            var message = "Compared values are not the same\n";
            message += "  Actual: " + actual + "\n";
            message += "  Expected: " + expected + "\n";
            throw new Error(message);
        }
    }

}
