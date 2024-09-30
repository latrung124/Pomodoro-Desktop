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

    objectName: "PasswordPanel"

    implicitWidth: 488
    implicitHeight: 650

    property font loginRegularFont: themeConfig ? themeConfig.loginRegularFont : internal.defaultFont
    property font loginGreetingFont: themeConfig ? themeConfig.loginGreetingFont : internal.defaultFont

    signal nextPage(string name)

    Rectangle {
        id: backgroundRect

        anchors.fill: parent
        color: "#FFFFFF"
    }
    
    ColumnLayout {
        id: panelLayout

        height: 308.5
        anchors {
            left: parent.left
            leftMargin: internal.contentMargin
            right: parent.right
            rightMargin: internal.contentMargin
            top: parent.top
            topMargin: internal.contentMargin
        }

        ColumnLayout {
            id: headerLayout

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            height: internal.headerLayoutHeight
        }

        ColumnLayout {
            id: contentLayout

            Layout.fillWidth: true
            height: internal.contentLayoutHeight
            spacing: 24

            Rectangle {
                id: passwordTextItem

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                implicitHeight: 28

                Text {
                    id: greetText

                    text: qsTr("Your password")
                    font.family: loginGreetingFont.family
                    font.pixelSize: loginGreetingFont.pixelSize
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            ColumnLayout {
                id: pwLayout

                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true
                implicitHeight: 192
                spacing: 16

                Item {
                    id: pwFillItem

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
                            implicitHeight: 12

                            Text {
                                id: pwTitleText
                                text: qsTr("Password*")
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                verticalAlignment: Text.AlignVCenter
                                anchors.leftMargin: 16
                                font.family: loginRegularFont.family
                                font.pixelSize: loginRegularFont.pixelSize
                                font.letterSpacing: 0.3
                                lineHeightMode:Text.FixedHeight
                                lineHeight: 12
                            }
                        }

                        CustomTextField {
                            id: pwTextField

                            backgroundText: qsTr("Your password")
                            Layout.alignment: Qt.AlignTop
                        }
                    }
                }

                Item {
                    id: confirmPwFillItem

                    Layout.fillWidth: true
                    implicitHeight: 68

                    ColumnLayout {
                        id: confirmPwFillLayout

                        anchors.fill: parent
                        spacing: 8

                        Item {
                            id: confirmPwTitleItem

                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignTop
                            implicitHeight: 12

                            Text {
                                id: confirmPwTitleText
                                text: qsTr("Confirm password*")
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                verticalAlignment: Text.AlignVCenter
                                anchors.leftMargin: 16
                                font.family: loginRegularFont.family
                                font.pixelSize: loginRegularFont.pixelSize
                                font.letterSpacing: 0.3
                                lineHeightMode: Text.FixedHeight
                                lineHeight: 12
                            }
                        }

                        CustomTextField {
                            id: confirmPwTextField

                            backgroundText: qsTr("Confirm your password")
                            Layout.alignment: Qt.AlignTop
                        }
                    }
                }
            }
        }

        ColumnLayout {
            id: footerLayout

            Layout.fillWidth: true
            height: internal.footerLayoutHeight
            spacing: 0

            ColumnLayout {
                id: signInBtnLayout

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                Layout.preferredHeight: internal.btnLayoutHeight

                Item {
                    id: continueBtnItem

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignBottom
                    Layout.preferredHeight: internal.buttonHeight

                    Button {
                        id: continueBtn

                        anchors.fill: parent

                        background: Rectangle {
                            color: "#007AFF"
                            radius: 6
                        }

                        contentItem: Item {
                            Text {
                                text: qsTr("Sign up")
                                color: "white"
                                font.pixelSize: 16
                                font.family: loginRegularFont.family
                                font.bold: true
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                    }
                }
            }
        }
    }
    
    QtObject {
        id: internal

        property int contentMargin: 48
        property font defaultFont: ({ family: "Helvetica", pointSize: 13, bold: true})
        property color blueColor: "#007AFF"
        property int buttonHeight: 40
        property int btnLayoutHeight: 72
        property double footerLayoutHeight: 116
        property int headerLayoutHeight: 80
        property int contentLayoutHeight: 244
    }
}
