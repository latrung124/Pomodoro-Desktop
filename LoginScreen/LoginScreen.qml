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

pragma Singleton

import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root

    width: 1366
    height: 780

    visible: true

    title: qsTr("Pomodoro")

    property string bgColor: themeConfig ? themeConfig.loginBgColor : internal.defaultBgColor

    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }

    Component {
        id: actPanelComponent

        AccountPanel {
            id: accountPanel

            Component.onDestruction: function() {
                console.log("AccountPanel destroyed");
            }

            Component.onCompleted: function() {
                console.log("AccountPanel completed");
            }
        }
    }

    Rectangle {
        id: background

        anchors.fill: parent
        color: bgColor

        MouseArea {
            id: backgroundMA

            anchors.fill: parent
        }

        RowLayout {
            id: rowLayout

            spacing: 58
            width: parent.width - 120
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter


            Rectangle {
                id: imageRect

                implicitWidth: 700
                implicitHeight: 650
                Layout.alignment: Qt.AlignLeft
                color: "transparent"

                Image {
                    id: image

                    source: `Resources/showcase-image.png`
                    fillMode: Image.PreserveAspectCrop
                    width: parent.width
                    height: parent.height
                }
            }

            Item {
                id: stackViewItem

                Layout.alignment: Qt.AlignLeft
                implicitWidth: 488
                implicitHeight: 650

                StackView {
                    id: stackView

                    anchors.fill: parent

                    initialItem: LoginPanel {
                        id: loginPanel

                        Component.onDestruction: function() {
                            console.log("LoginPanel destroyed");
                        }

                        Component.onCompleted: function() {
                            console.log("LoginPanel completed")
                        }
                    }

                    pushEnter: pushEnterTransition
                    pushExit: pushExitTransition
                }
            }
        }
    }

    Transition {
        id: pushEnterTransition

        ParallelAnimation {
            PropertyAnimation {
                property: "x"
                from: stackView.width
                to: 0
                duration: 300
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                property: "opacity"
                from: 0; to: 1
                duration: 200
                easing.type: Easing.OutCubic
            }
        }
    }

    Transition {
        id: pushExitTransition

        ParallelAnimation {
            PropertyAnimation {
                property: "x"
                from: 0
                to: 0
                duration: 300
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                property: "opacity"
                from: 1
                to: 0
                duration: 450
                easing.type: Easing.OutCubic
            }
        }
    }

    Connections {
        target: loginPanel

        function onSignUp(pageName) {
            console.log("onSignUp!");
            internal.pushPage(pageName);
        }
    }

    QtObject {
        id: internal

        property string defaultBgColor: "#FFFFFF"

        function pushPage(pageName) {
            var component = Qt.createComponent(pageName + ".qml");
            if (component.status === Component.Ready) {
                var page = component.createObject(stackView);
                stackView.push(page);
            } else {
                console.log("Error loading component:", component.errorString());
            }
        }
    }
}
