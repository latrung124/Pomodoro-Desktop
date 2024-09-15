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

TextField {
    id: root

    property int textSize: 15
    property int backgroundRadius: 6
    property string textFont: "Roboto"
    property color backgroundColor: "#F2F2F2"
    property alias backgroundText: placeHolderText.text
    property alias borderColor: backgroundRect.border.color

    Layout.fillWidth: true
    implicitHeight: 48

    verticalAlignment: Text.AlignVCenter

    font.family: root.textFont
    font.pixelSize: root.textSize

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

    QtObject {
        id: internal

        property int contentMargin: 16
        property double placeHolderOpacity: 0.5
    }
}
