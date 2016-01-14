import QtQuick 2.0
import QtQuick.Window 2.0

Window {
    id: window
    objectName: "SampleWindow";

    width: 480
    height: 640
    visible: true

    Item {
        id: dummy
        objectName: "DummyItem";
    }

    Repeater {
        delegate: Item {
            objectName: "RepeaterItem"
        }

        model: 5
    }

    ListView {
        delegate: Item {
            objectName: "ListViewItem"
        }

        model: 3
    }

}

