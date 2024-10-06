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

    objectName: "EnterYourEmailPage"

    implicitWidth: 488
    implicitHeight: 650

    StackView.visible: true

    property font loginRegularFont: themeConfig ? themeConfig.loginRegularFont : internal.defaultFont
    property font loginGreetingFont: themeConfig ? themeConfig.loginGreetingFont : internal.defaultFont

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

                    text: qsTr("Enter your email")
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
                                text: qsTr("Email*")
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
                            id: nicknameTextField

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
                            pageStack.nextPage("OTPVerificationPage");
                        }
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

        count: 4
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
        console.log(objectName + " onDestruction!");
    }

    Component.onCompleted: function() {
        console.log(objectName + " onCompleted!");
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
