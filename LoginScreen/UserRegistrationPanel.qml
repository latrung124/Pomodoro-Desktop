/*
 * Copyright (C) 2024 La Trung
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file is part of a desktop application based on the Qt framework.
 *
 * Author: La Trung
 */

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import CommonComponent

Item {
    id: root

    implicitWidth: 488
    implicitHeight: 650
    opacity: 0

    objectName: "UserRegistrationPanel"

    function pageAppearTrans() {
        console.log("pageAppearTrans() x: " + x + " y: " + y);
        pageAppearAnim.start();
    }

    StackView {
        id: pageStack

        anchors.fill: parent

        initialItem: AccountPanel {
            id: accountPanel
        }

        Component.onCompleted: {
            console.log("AccountPanel loaded completely");
        }

        Component.onDestruction: {
            console.log("AccountPanel destroyed");
        }

        pushEnter: pushEnterTransition
        pushExit: pushExitTransition
    }

    Transition {
        id: pushEnterTransition

        ParallelAnimation {
            PropertyAnimation {
                property: "x"
                from: stackView.width
                to: 0
                duration: 250
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                property: "opacity"
                from: 0; to: 1
                duration: 250
                easing.type: Easing.OutCubic
            }
        }
    }

    Transition {
        id: pushExitTransition

        NumberAnimation {
            property: "opacity"
            from: 1
            to: 0
            duration: 250
            easing.type: Easing.OutCubic
        }
    }

    ParallelAnimation {
        id: pageAppearAnim

        NumberAnimation {
            target: root
            properties: "x"
            from: 488
            to: 0
            duration: 250
            easing.type: Easing.InOutQuad
        }

        NumberAnimation {
            target: root
            properties: "opacity"
            from: 0
            to: 1
            duration: 250
            easing.type: Easing.OutCubic
        }
    }

    QtObject {
        id: internal

        function pushPage(pageName) {
            var component = Qt.createComponent(pageName + ".qml");
            if (component.status === Component.Ready) {
                var page = component.createObject(pageStack);
                pageStack.push(page);
            } else {
                console.log("Error loading component:", component.errorString());
            }
        }

        function popPage() {
            pageStack.pop();
        }
    }
}
