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

    objectName: "AccountPage"

    implicitWidth: 488
    implicitHeight: 650

    property font loginRegularFont: themeConfig ? themeConfig.fontPalette.layer3 : internal.defaultFont
    property font loginGreetingFont: themeConfig ? themeConfig.fontPalette.layer2 : internal.defaultFont

    property bool isNicknameValid: true
    property bool isEmailValid: true

    Rectangle {
        id: backgroundRect

        anchors.fill: parent
        color: "#FFFFFF"
    }
    
    ColumnLayout {
        id: panelLayout

        anchors {
            fill: parent
            leftMargin: internal.contentMargin
            rightMargin: internal.contentMargin
            topMargin: internal.contentMargin
            bottomMargin: internal.contentBotMargin
        }

        RowLayout {
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
                id: greetTextItem

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                implicitHeight: 28

                Text {
                    id: greetText

                    text: qsTr("Your details")
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
                id: detailFillLayout

                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true
                implicitHeight: 192
                spacing: 16

                Item {
                    id: nicknameFillItem

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop
                    implicitHeight: 68

                    ColumnLayout {
                        id: nicknameFillLayout

                        anchors.fill: parent
                        spacing: 8

                        Item {
                            id: nicknameTitleItem

                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignTop
                            implicitHeight: 12

                            Text {
                                id: nicknameTitleText
                                text: qsTr("Nickname*")
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

                            Text {
                                id: nicknameTitleErrorText

                                text: qsTr("Nickname is invalid")
                                anchors.verticalCenter: parent.verticalCenter
                                verticalAlignment: Text.AlignVCenter
                                anchors.left: nicknameTitleText.right
                                anchors.leftMargin: 10
                                color: "red"
                                font.family: loginRegularFont.family
                                font.pixelSize: loginRegularFont.pixelSize
                                font.letterSpacing: 0.3
                                lineHeightMode: Text.FixedHeight
                                lineHeight: 12
                                visible: !isNicknameValid
                            }
                        }

                        CustomTextField {
                            id: nicknameTextField

                            backgroundText: qsTr("Your nickname - No contain special characters")
                            Layout.alignment: Qt.AlignTop
                        }
                    }
                }

                Item {
                    id: emailFillItem

                    Layout.fillWidth: true
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
                                text: qsTr("Email*")
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

                            Text {
                                id: emailTitleErrorText

                                text: qsTr("Email is invalid")
                                anchors.verticalCenter: parent.verticalCenter
                                verticalAlignment: Text.AlignVCenter
                                anchors.left: emailTitleText.right
                                anchors.leftMargin: 10
                                color: "red"
                                font.family: loginRegularFont.family
                                font.pixelSize: loginRegularFont.pixelSize
                                font.letterSpacing: 0.3
                                lineHeightMode: Text.FixedHeight
                                lineHeight: 12
                                visible: !isEmailValid
                            }
                        }

                        CustomTextField {
                            id: pwTextField

                            backgroundText: qsTr("Your email")
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
                                text: qsTr("Continue")
                                color: "white"
                                font.pixelSize: 16
                                font.family: loginRegularFont.family
                                font.bold: true
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }

                        onClicked: function() {
                            pageStack.nextPage("PasswordPage");
                        }
                    }
                }
            }

            ColumnLayout {
                id: lineLayout

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignBottom
                Layout.preferredHeight: 32

                Rectangle {
                    id: lineRect

                    Layout.fillWidth: true
                    implicitHeight: 0.5
                    Layout.alignment: Qt.AlignBottom
                    color: "#E5E5E5"
                }
            }

            ColumnLayout {
                id: googleSignUpBtnLayout

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                Layout.preferredHeight: 72

                Item {
                    id: googleSignUpBtnItem

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignBottom
                    Layout.preferredHeight: 40

                    CustomIconButton {
                        id: googleSignInIconBtn

                        contentText: qsTr("Sign up with Google")
                        iconBtnSource: `Resources/google-logo-1040x1040.png`
                        iconSize: 20
                        Layout.fillWidth: true
                        backgroundColor: "#333333"
                    }
                }
            }
        }
    }

    PageIndicator {
        id: pageIndicator

        anchors {
            bottom: parent.bottom
            bottomMargin: 48
            horizontalCenter: parent.horizontalCenter
        }

        count: 3
        currentIndex: 0

        delegate: Component {
            id: pageIndicatorDelegate

            Rectangle {
                id: pageIndicatorRect

                property bool isHighlight: index === 0

                width: 20
                height: 10
                color: "transparent"

                Rectangle {
                    id: circleIndicatorRect

                    width: isHighlight ? 20 : 8
                    height: 8
                    anchors.centerIn: parent
                    color: isHighlight ? "#007AFF" : "#D9D9D9"
                    radius: isHighlight ? 4 : circleIndicatorRect.width*0.5
                }
            }
        }
    }

    Component.onDestruction: function() {
        console.log("Account Page onDestruction!");
    }

    Component.onCompleted: function() {
        console.log("Account Page onCompleted!");
    }

    QtObject {
        id: internal

        property int contentMargin: 48
        property int contentBotMargin: 117
        property font defaultFont: ({ family: "Helvetica", pointSize: 13, bold: true})
        property color blueColor: "#007AFF"
        property int buttonHeight: 40
        property int btnLayoutHeight: 72
        property double footerLayoutHeight: 220.5
        property int headerLayoutHeight: 80
        property int contentLayoutHeight: 244
    }
}
