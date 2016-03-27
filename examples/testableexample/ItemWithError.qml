import QtQuick 2.0

Item {

    Component.onCompleted: {
        // It will throw error
        global = 123;
    }
}
