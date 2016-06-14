import QtQuick 2.0
import Testable 1.0

Item {

    TestableCase {
        id: testCase

        function test_abc() {
            console.log("Exec test_abc");
            compare(1,1);
        }
    }

}
