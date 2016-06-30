import QtQuick 2.0
import Testable 1.0
import QtQuick.Window 2.0

Window {

    TestableCase {
        id: testCase
        objectName: "testCase"

        property int executedCount: 0

        function test_compare_fail() {
            console.log("Expected fail test case:");
            compare(1,0);
        }

        function test_exception() {
            // it should throw exception
            t = 123;
        }


    }

}
