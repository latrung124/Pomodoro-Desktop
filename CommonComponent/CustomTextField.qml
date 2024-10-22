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

import QtQuick.Controls.Basic
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

TextField {
    id: root

	// Change this to textfieldstyle because warning of line 43
	// QML Rectangle: The current style does not support customization of this control

    property int textSize: 15
    property int backgroundRadius: 6
    property string textFont: "Roboto"
    property color backgroundColor: "#F2F2F2"
    property bool isShowPassword: false
    property alias isPassword: showPwRect.visible
    property alias backgroundText: placeHolderText.text
    property alias borderColor: backgroundRect.border.color

    Layout.fillWidth: true
    implicitHeight: 48

    verticalAlignment: Text.AlignVCenter

    font.family: root.textFont
    font.pixelSize: root.textSize

    echoMode: isShowPassword ? TextInput.Normal : TextInput.Password

    background: Rectangle {
        id: backgroundRect

        color: root.backgroundColor
        radius: root.backgroundRadius
        border.color: "#E5E5E5"
        border.width: 1

        Item {
            id: placeHolderItem

            visible: !root.text.length

            implicitHeight: root.textSize
            implicitWidth: parent.width - internal.contentMargin * 2
            anchors {
                left: parent.left
                leftMargin: internal.contentMargin
                verticalCenter: parent.verticalCenter
            }

            Text {
                id: placeHolderText

                text: qsTr("Place Holder Text")
                font.family: root.textFont
                font.pixelSize: root.textSize
                opacity: internal.placeHolderOpacity
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    Item {
        id: showPwRect

        visible: false
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        width: 32
        height: 32

        Image {
            id: showPwImage

            source: `Resources/show-pw-icon.png`
            fillMode: Image.PreserveAspectFit
            anchors.fill: parent
            anchors.margins: 8
        }

        ColorOverlay {
            visible: isShowPassword
            anchors.fill: showPwImage
            source: showPwImage
            color: "#007AFF"
        }

        MouseArea {
            id: showPwArea

            anchors.fill: parent
            cursorShape: Qt.ArrowCursor
            onClicked: {
                isShowPassword = !isShowPassword;
            }
        }
    }

    QtObject {
        id: internal

        property int contentMargin: 16
        property double placeHolderOpacity: 0.5
    }
}
