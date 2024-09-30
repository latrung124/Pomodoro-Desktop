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
                id: panelContainer

                Layout.alignment: Qt.AlignRight
                width: 488
                height: 650

                LoginPanel {
                    id: loginPanel

                    objectName: "LoginPanel"
                    anchors.fill: parent

                    onOpenPanel: function(name) {
                        internal.handleOpenPanel(name);
                    }
                }

                Loader {
                    id: panelLoader

                    anchors.fill: parent
                    source: ""

                    onLoaded: {
                        panelLoader.item.panelAppearTrans();
                        internal.connectionEstablished(panelLoader.item);
                    }
                }
            }
        }
    }

    QtObject {
        id: internal

        property string defaultBgColor: "#FFFFFF"
        property var pageList: ["UserRegistrationPanel", "ForgotPasswordPanel"]

        function handleClosePanel() {
            panelLoader.source = "";
        }

        function connectionEstablished(obj) {
            if (obj.objectName === pageList[0]) {
                panelLoader.item.closePanel.connect(internal.handleClosePanel);
                console.log("Connection " + pageList[0] + " established!");
            }
        }

        function handleOpenPanel(name) {
            console.log("handle Sign Up!")
            panelLoader.source = name + ".qml";
        }
    }
}
