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
import QtQuick.Controls.Basic
import QtQuick.Layouts
import App.Enums 1.0

import CommonComponent

Item {
    id: root

    objectName: "LoginPanel"

    implicitWidth: 488
    implicitHeight: 650

    property font loginRegularFont: themeConfig ? themeConfig.fontPalette.layer3 : internal.defaultFont
    property font loginGreetingFont: themeConfig ? themeConfig.fontPalette.layer2 : internal.defaultFont
    property QtObject userModel: null

    signal openPanel(string name)

    Rectangle {
        id: backgroundRect

        anchors.fill: parent
        color: "#FFFFFF"
    }

    LoadingAnimation {
        id: loadingAnimation

        anchors.centerIn: parent
        visible: false
        width: 50
        height: 50
    }
    
    ColumnLayout {
        id: panelLayout

        anchors.margins: internal.contentMargin
        anchors.fill: parent

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

                            Text {
                                id: errorLoginText

                                text: qsTr("*Invalid login or password")
                                visible: false
                                anchors.left: emailTitleText.right
                                anchors.leftMargin: 10
                                anchors.verticalCenter: parent.verticalCenter
                                verticalAlignment: Text.AlignVCenter
                                color: "red"
                                font.family: loginRegularFont.family
                                font.pixelSize: loginRegularFont.pixelSize
                                font.letterSpacing: 0.3
                                lineHeightMode: Text.FixedHeight
                                lineHeight: 12
                            }
                        }

                        CustomTextField {
                            id: emailTextField

                            echoMode: TextInput.Normal
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

                            Text {
                                id: errorPwText

                                text: qsTr("*Invalid login or password")
                                visible: false
                                anchors.left: pwTitleText.right
                                anchors.leftMargin: 10
                                anchors.verticalCenter: parent.verticalCenter
                                verticalAlignment: Text.AlignVCenter
                                color: "red"
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
                            isPassword: true
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
                                    root.openPanel("ForgotPasswordPanel");
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
            height: internal.footerLayoutHeight
            spacing: 0

            ColumnLayout {
                id: signInBtnLayout

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                Layout.preferredHeight: internal.btnLayoutHeight

                Item {
                    id: signInBtnItem

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignBottom
                    Layout.preferredHeight: internal.buttonHeight

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

                        onClicked: {
                            console.log("Sign In Button clicked");
                            internal.startLoadingAnimation();
                            // internal.signInButtonClicked();
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

                        onClicked: function() {
                            console.log("Sign in with Google Button clicked");
                            loginModuleController.onSignIn(AuthenticationType.Google, "", "");
                        }
                    }
                }
            }

            ColumnLayout {
                id: signUpLayout

                Layout.fillWidth: true
                Layout.preferredHeight: 43.5

                Item {
                    id: signUpItem
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    RowLayout {
                        id: signUpTxtLayout

                        implicitWidth: 250
                        height: parent.height
                        anchors.horizontalCenter: parent.horizontalCenter

                        Item {
                            id: dontHaveAccountRect

                            height: 20
                            width: 170
                            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom

                            Text {
                                id: signUpText

                                text: qsTr("Don't have an account?")
                                anchors {
                                    bottom: parent.bottom
                                    left: parent.left
                                }
                                verticalAlignment: Text.AlignBottom
                                horizontalAlignment: Text.AlignLeft
                                anchors.leftMargin: 0
                                font.family: loginRegularFont.family
                                font.pixelSize: loginRegularFont.pixelSize
                                font.letterSpacing: 0.3
                                lineHeightMode: Text.FixedHeight
                                lineHeight: 12
                            }
                        }

                        Item {
                            id: signUpNowRect

                            height: 20
                            width: 80
                            Layout.alignment: Qt.AlignRight | Qt.AlignBottom

                            Text {
                                id: signUpNowText

                                text: qsTr("Sign up now")
                                anchors {
                                    bottom: parent.bottom
                                    left: parent.left
                                }
                                verticalAlignment: Text.AlignBottom
                                horizontalAlignment: Text.AlignLeft
                                anchors.leftMargin: 0
                                font.family: loginRegularFont.family
                                font.pixelSize: loginRegularFont.pixelSize
                                font.letterSpacing: 0.3
                                lineHeightMode: Text.FixedHeight
                                lineHeight: 12
                                font.underline: true
                                color: internal.blueColor
                            }

                            MouseArea {
                                id: signUpNowMouseArea

                                anchors.fill: signUpNowText
                                cursorShape: Qt.PointingHandCursor

                                onClicked: function() {
                                    console.log("Sign Up Now Button clicked");
                                    root.openPanel("UserRegistrationPanel");
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Timer {
        id: loadingTimer

        interval: 10000
        running: false
        repeat: false

        onTriggered: {
            internal.endLoadingAnimation();
        }
    }

    QtObject {
        id: internal

        property int contentMargin: 48
        property font defaultFont: ({ family: "Helvetica", pointSize: 13, bold: true})
        property color blueColor: "#007AFF"
        property int buttonHeight: 40
        property int btnLayoutHeight: 72
        property double footerLayoutHeight: 220.5
        property int headerLayoutHeight: 80
        property int contentLayoutHeight: 244
        property bool isLoading: false

        function startLoadingAnimation() {
            loadingAnimation.visible = true;
            loadingAnimation.isRunning = true;
            panelLayout.visible = false;
            loadingTimer.start();
        }

        function endLoadingAnimation() {
            loadingAnimation.visible = false;
            loadingAnimation.isRunning = false;
            panelLayout.visible = true;
        }

        function isValidEmail(email) {
            var emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
            return emailPattern.test(email);
        }

        function isValidPassword(password) {
            // Example: Password must be at least 6 characters long
            return password.length >= 6;
        }

        function signInButtonClicked() {
            var isValidLoginAndPassword = internal.isValidEmail(emailTextField.text) && internal.isValidPassword(pwTextField.text);
            errorLoginText.visible = !isValidLoginAndPassword;
            errorPwText.visible = !isValidLoginAndPassword;
            if (isValidLoginAndPassword) {
                loginModuleController.onSignIn(AuthenticationType.EmailAndPassword,
                                               emailTextField.text, pwTextField.text);
            } else {
                console.log("Invalid login or password");
            }
        }
    }
}
