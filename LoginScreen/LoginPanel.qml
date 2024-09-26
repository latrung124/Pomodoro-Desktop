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

    property font loginRegularFont: themeConfig ? themeConfig.loginRegularFont : internal.defaultFont
    property font loginGreetingFont: themeConfig ? themeConfig.loginGreetingFont : internal.defaultFont

    Rectangle {
        id: backgroundRect

        anchors.fill: parent
        color: "#FFFFFF"
    }
    
    ColumnLayout {
        id: panelLayout

        anchors.margins: internal.contentMargin
        anchors.fill: parent

        ColumnLayout {
            id: headerLayout

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            height: 80
        }

        ColumnLayout {
            id: contentLayout

            Layout.fillWidth: true
            height: 244
            spacing: 24

            Rectangle {
                id: greetTextItem

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                implicitHeight: 28

                Text {
                    id: greetText

                    text: qsTr("Nice to see you again")
                    font.family: loginGreetingFont.family
                    font.pixelSize: loginGreetingFont.pixelSize
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
                            implicitHeight: 12

                            Text {
                                id: emailTitleText
                                text: qsTr("Login")
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
                            id: emailTextField

                            backgroundText: qsTr("Email or phone number")
                            Layout.alignment: Qt.AlignTop
                        }
                    }
                }

                Item {
                    id: passwordFillItem

                    Layout.fillWidth: true
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
                                text: qsTr("Password")
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
                            id: pwTextField

                            backgroundText: qsTr("Password")
                            Layout.alignment: Qt.AlignTop
                        }
                    }
                }

                RowLayout {
                    id: rememberLayout

                    Layout.fillWidth: true
                    Layout.topMargin: 4
                    implicitHeight: 20

                    RowLayout {
                        id: rememberToggleLayout

                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignLeft
                        implicitWidth: 188
                        spacing: 8

                        Item {
                            id: rememberItem

                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignLeft
                            implicitWidth: 40

                            CustomToggle {
                                id: rememberToggle

                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }

                        Item {
                            id: rememberTextItem

                            Layout.fillHeight: true
                            implicitWidth: 140
                            
                            Text {
                                id: rememberText

                                text: qsTr("Remember me")
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                verticalAlignment: Text.AlignVCenter
                                anchors.leftMargin: 8
                                font.family: loginRegularFont.family
                                font.pixelSize: loginRegularFont.pixelSize
                                font.letterSpacing: 0.3
                                lineHeightMode: Text.FixedHeight
                                lineHeight: 12
                            }
                        }
                    }

                    RowLayout {
                        id: forgotLayout

                        Layout.fillHeight: true
                        // Layout.alignment: Qt.AlignRight
                        implicitWidth: 204

                        Item {
                            id: forgotItem

                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignRight

                            Text {
                                id: forgotText

                                text: qsTr("Forgot password?")
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                verticalAlignment: Text.AlignVCenter
                                anchors.rightMargin: 0
                                font.family: loginRegularFont.family
                                font.pixelSize: loginRegularFont.pixelSize
                                font.letterSpacing: 0.3
                                lineHeightMode: Text.FixedHeight
                                lineHeight: 12
                                font.underline: true
                                color: internal.blueColor
                                
                            }

                            MouseArea {
                                id: forgotMouseArea

                                anchors.fill: forgotText
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    console.log("Forgot password clicked")
                                }
                            }
                        }
                    }
                }
            }
        }



        ColumnLayout {
            id: footerLayout

            Layout.fillWidth: true
            height: 220.5

            ColumnLayout {
                id: signInBtnLayout

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                Layout.preferredHeight: 72

                Item {
                    id: signInBtnItem

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignBottom
                    Layout.preferredHeight: 40

                    Button {
                        id: signInBtn

                        anchors.fill: parent

                        background: Rectangle {
                            color: "#007AFF"
                            radius: 6
                        }

                        contentItem: Item {
                            Text {
                                text: qsTr("Sign in")
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

            ColumnLayout {
                id: googleSignInBtnLayout

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                Layout.preferredHeight: 72

                Item {
                    id: googleSignInBtnItem

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignBottom
                    Layout.preferredHeight: 40

                    CustomIconButton {
                        id: googleSignInIconBtn

                        contentText: qsTr("Sign in with Google")
                        iconBtnSource: `Resources/google-logo-1040x1040.png`
                        iconSize: 20
                        Layout.fillWidth: true
                        backgroundColor: "#333333"
                    }
                }
            }

            ColumnLayout {
                id: signUpLayout

                Layout.fillWidth: true
                
            }
        }
    }

    QtObject {
        id: internal

        property int contentMargin: 48
        property font defaultFont: ({ family: "Helvetica", pointSize: 13, bold: true})
        property color blueColor: "#007AFF"
        property int buttonHeight: 40
    }
}
