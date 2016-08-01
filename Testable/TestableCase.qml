import QtQuick 2.0
import Testable 1.0

QtObject {
    property string name

    property bool hasError: false

    function wait(timeout) {
        TestableUtils.wait(timeout);
    }

    function compare(actual, expected) {
        if (actual !== expected) {
            hasError = true;
            var message = "Compared values are not the same\n";
            message += "  Actual: " + actual + "\n";
            message += "  Expected: " + expected;
            throw new Error(message);
        }
    }

    function findChild(parent, objectName) {
        return TestableUtils.findChild(parent, objectName);
    }

}
