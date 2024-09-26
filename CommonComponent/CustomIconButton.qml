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

AbstractButton {
    id: root

    property alias contentText: contentText.text
    property alias textColor: contentText.color
    property alias textSize: contentText.font.pixelSize
    property alias backgroundColor: backgroundRect.color
    property alias backgroundRadius: backgroundRect.radius
    property alias iconBtnSource: iconImage.source

    property int iconSize: 20

    implicitHeight: 40
    implicitWidth: 392
    topPadding: Math.floor((root.height - contentLayout.height) / 2)
    bottomPadding: Math.floor((root.height - contentLayout.height) / 2)
    leftPadding: Math.floor((root.width - (contentLayout.width)) / 2)
    rightPadding: Math.floor((root.width - contentLayout.width) / 2)
    topInset: 0
    leftInset: 0
    rightInset: 0
    bottomInset: 0

    enum MouseState {
        Pressed,
        Hovered,
        Entered,
        Exited,
        Released
    }

    background: Rectangle {
        id: backgroundRect

        color: internal.defaultBgColor
        radius: 6
    }

    contentItem: Item {
        id: contentItem

        RowLayout {
            id: contentLayout

            Item {
                id: iconItem

                Layout.preferredHeight: internal.preferIconSize
                Layout.preferredWidth: internal.preferIconSize
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                visible: iconBtnSource !== ""

                Image {
                    id: iconImage
                    source: ""
                    fillMode: Image.PreserveAspectFit
                    anchors.fill: parent
                }
            }

            Item {
                id: textItem

                Layout.preferredWidth: internal.defaultBtnWidth
                Layout.preferredHeight: internal.defaultBtnHeight
                Layout.alignment: Qt.AlignVCenter

                Text {
                    id: contentText
                    text: qsTr("Button")
                    color: "white"
                    font.pixelSize: 16
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }

    QtObject {
        id: internal

        property color defaultBgColor: "#007AFF"
        property int preferIconSize: (iconSize < root.height && iconSize < root.width) ? iconSize : 20
        property int defaultBtnWidth: 140
        property int defaultBtnHeight: 20
    }
}
