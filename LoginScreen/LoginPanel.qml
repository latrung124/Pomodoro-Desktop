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
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import CommonComponent

Item {
    id: root

    implicitWidth: 488
    implicitHeight: 650

    property font gFont: themeConfig.loginTextFont

    onGFontChanged: {
        console.log("family: ", gFont.family)
    }

    Rectangle {
        id: backgroundRect

        anchors.fill: parent
        color: "#FFFFFF"
    }
    
    Rectangle {
        id: contentRect

        anchors.margins: internal.contentMargin
        anchors.fill: parent

        ColumnLayout {
            id: contentLayout

            anchors.fill: parent

            spacing: 0

            Rectangle {
                id: greetTextItem

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                implicitHeight: 32

                Text {
                    id: greetText

                    text: qsTr("Nice to see you again")
                    font.family: gFont.family
                    font.pixelSize: 20
                    font.bold: true
                }
            }

            ColumnLayout {
                id: loginFillLayout

                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true
                implicitHeight: 192
                spacing: 16

                Item {
                    id: emailFillItem

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop
                    implicitHeight: 68

                    ColumnLayout {
                        id: emailFillLayout

                        anchors.fill: parent
                        spacing: 8

                        Item {
                            id: emailTitleItem

                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignTop
                            Layout.leftMargin: 16
                            implicitHeight: 12

                            Text {
                                id: emailTitleText
                                text: qsTr("Login")
                                font.family: "Inter"
                                font.pixelSize: 11
                            }
                        }

                        CustomTextField {
                            id: emailTextField

                            backgroundText: qsTr("Email or phone number")
                            Layout.alignment: Qt.AlignTop
                        }
                    }
                }

                Item {
                    id: passwordFillItem

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop
                    implicitHeight: 68

                    ColumnLayout {
                        id: pwFillLayout

                        anchors.fill: parent
                        spacing: 8

                        Item {
                            id: pwTitleItem

                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignTop
                            Layout.leftMargin: 16
                            implicitHeight: 12

                            Text {
                                id: pwTitleText
                                text: qsTr("Password")
                                font.family: "Inter"
                                font.pixelSize: 11
                            }
                        }

                        CustomTextField {
                            id: pwTextField

                            backgroundText: qsTr("Password")
                            Layout.alignment: Qt.AlignTop
                        }
                    }
                }

                Item {
                    id: rememberItem

                    Layout.fillWidth: true
                    implicitHeight: 20

                    CustomToggle {
                        id: rememberToggle
                    }
                }
            }
        }
    }

    QtObject {
        id: internal

        property int contentMargin: 48
    }
}
