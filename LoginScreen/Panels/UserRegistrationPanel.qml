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
import QtQuick.Controls.Basic

import CommonComponent

Item {
    id: root

    implicitWidth: 488
    implicitHeight: 650

    objectName: "UserRegistrationPanel"

    signal closePanel()
    signal responseSignUp()

    function panelAppearTrans() {
        console.log("pageAppearTrans() x: " + x + " y: " + y);
        pageAppearAnim.start();
    }

    function panelDisappearTrans() {
        console.log("pageDisappearTrans() x: " + x + " y: " + y);
        pageDisappearAnim.start();
    }

    onResponseSignUp: function() {
        console.log("UserRegistrationPanel onResponseSignUp()");
        if (pageStack.currentItem.objectName === "PasswordPage") {
            pageStack.currentItem.responseSignUp();
        } else {
            console.log("pageStack.currentItem is not PasswordPage: " + pageStack.currentItem.objectName);
        }
    }

    StackView {
        id: pageStack

        signal nextPage(string pageName)
        signal closePanel()
        
        anchors.fill: parent

        initialItem: AccountPage {
            id: accountPage

            StackView.visible: true
            parent: pageStack
            objectName: "AccountPage"
        }

        onNextPage: function(pageName) {
            internal.pushPage(pageName);
        }

        pushEnter: pushEnterTransition
        pushExit: pushExitTransition
        popEnter: popEnterTransition
        popExit: popExitTransition
    }

    Button {
        id: backButton

        implicitWidth: 40
        implicitHeight: 40
        anchors {
            left: parent.left
            leftMargin: 14
            top: parent.top
            topMargin: 14
        }

        background: Rectangle {
            color: "transparent"
        }

        icon.source: `Resources/arrow-left-large.png`
        icon.width: 40
        icon.height: 40

        onClicked: {
            internal.popPage();
        }
    }

    Transition {
        id: pushEnterTransition

        ParallelAnimation {
            PropertyAnimation {
                property: "x"
                from: pageStack.width
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

        PropertyAction {
            property: "x"
            value: 0
        }

        PropertyAction {
            property: "y"
            value: 0
        }
    }

    Transition {
        id: popEnterTransition

        PropertyAction {
            property: "x"
            value: 0
        }
        PropertyAction {
            property: "y"
            value: 0
        }
    }

    Transition {
        id: popExitTransition

        ParallelAnimation {
            PropertyAnimation {
                property: "x"
                from: 0
                to: pageStack.width
                duration: 250
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                property: "opacity"
                from: 1; to: 0
                duration: 250
                easing.type: Easing.OutCubic
            }
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

    ParallelAnimation {
        id: pageDisappearAnim

        NumberAnimation {
            target: root
            properties: "x"
            from: 0
            to: 488
            duration: 250
            easing.type: Easing.InOutQuad
        }

        NumberAnimation {
            target: root
            properties: "opacity"
            from: 1
            to: 0
            duration: 250
            easing.type: Easing.OutCubic
        }

        onStopped: {
            closePanel();
        }
    }

    Connections {
        target: pageStack

        function onClosePanel() {
            panelDisappearTrans();
        }
    }
    
    QtObject {
        id: internal

        property var pageList: ["AccountPage", "PasswordPage", "ThankyouPage"]

        function pushPage(pageName) {
            console.log("pushPage: " + pageName);
            var component = Qt.createComponent(pageName + ".qml");
            if (component.status === Component.Ready) {
                var page = component.createObject(pageStack, {parent:pageStack, objectName: pageName});
                pageStack.push(page);
            } else {
                console.log("Error loading component:", component.errorString());
            }
        }

        function popPage() {
            if (pageStack.depth > 1) {
                pageStack.pop();
            } else {
                panelDisappearTrans();
            }
        }
    }
}
