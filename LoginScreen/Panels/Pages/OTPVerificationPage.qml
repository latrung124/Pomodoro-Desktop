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
import QtQml.Models

import CommonComponent

Item {
    id: root

    objectName: "OTPVerificationPage"

    implicitWidth: 488
    implicitHeight: 650
    StackView.visible: true

    property font loginRegularFont: themeConfig ? themeConfig.fontPalette.layer3 : internal.defaultFont
    property font loginGreetingFont: themeConfig ? themeConfig.fontPalette.layer2 : internal.defaultFont

    property bool isOTPValid: true

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
        spacing: 0

        ColumnLayout {
            id: contentLayout

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.maximumHeight: 250

            spacing: 30

            ColumnLayout {
                id: headerTextLayout

                Layout.alignment: Qt.AlignTop
                Layout.topMargin: 23
                Layout.leftMargin: 16
                Layout.rightMargin: 16
                Layout.preferredHeight: 68

                spacing: 0

                Item {
                    id: headerTextRect

                    Layout.fillWidth: true
                    Layout.preferredHeight: 28

                    Text {
                        id: headerText

                        text: qsTr("OTP Verification")
                        font: loginGreetingFont
                        color: "black"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Item {
                    id: headerExTextRect

                    Layout.fillWidth: true
                    Layout.preferredHeight: 28

                    Text {
                        id: headerExText

                        text: qsTr("Check your email to see the verification code")
                        font: loginRegularFont
                        color: "#1A1A1A"
                        opacity: 0.7
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Item {
                    id: errorNotificationRect

                    Layout.fillWidth: true
                    Layout.preferredHeight: 12

                    Text {
                        id: errorNotificationText

                        text: qsTr("*Invalid OTP code")
                        font: loginRegularFont
                        color: "red"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        visible: !isOTPValid
                    }
                }
            }

            ColumnLayout {
                id: otpLayout

                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true
                height: 152

                Item {
                    id: otpFillItem

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop
                    Layout.leftMargin: 120
                    Layout.rightMargin: 120
                    implicitHeight: 50

                    TextField {
                        anchors.fill: parent

                        background: Rectangle {
                            color: "#E5E5E5"
                            opacity: 0.8
                            radius: 4
                        }

                        text: ""
                        maximumLength: 6
                        font.pixelSize: 25
                        font.capitalization: Font.AllUppercase
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        inputMethodHints: Qt.ImhDigitsOnly
                    }
                }

                Item {
                    id: continueButtonItem

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop
                    implicitHeight: 68

                    Button {
                        id: continueBtn

                        width: parent.width
                        height: internal.buttonHeight
                        anchors.centerIn: parent

                        background: Rectangle {
                            color: internal.blueColor
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
                            pageStack.nextPage("ResetPasswordPage");
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

                property bool isHighlight: index === 1

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
    }
}
