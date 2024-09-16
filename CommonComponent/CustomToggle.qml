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

Item {
    id: root

    property alias radius: backgroundRect.radius

    property bool checked: false
    property int aniDuration: 200
    property color backgroundColor: "#F2F2F2"
    property color checkedColor: "#2196F3"
    property color borderBgColor: "#E5E5E5"
    property color toggleColor: "#FFFFFF"

    implicitWidth: 40
    implicitHeight: 20

    Rectangle {
        id: backgroundRect

        anchors.fill: parent
        color: checked ? checkedColor : backgroundColor
        radius: 36.5
        border.color: borderBgColor
        border.width: 1

        Behavior on color {
            ColorAnimation {
                duration: aniDuration
            }
        }
    }

    Rectangle {
        id: circleRect

        anchors.verticalCenter: parent.verticalCenter
        x: 0

        width: root.height
        height: root.height
        color: "transparent"

        Rectangle {
            anchors.centerIn: parent
            width: parent.width/5 * 4
            height: parent.height/5 * 4
            radius: parent.height/5 * 4 / 2
            color: toggleColor
            border.color: borderBgColor
            border.width: 1
        }

        Behavior on x {
            NumberAnimation {
                duration: aniDuration
            }
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onClicked: function() {
            checked = !checked;
            circleRect.x = checked ? (root.width - circleRect.width) : 0;
        }
    }
}
