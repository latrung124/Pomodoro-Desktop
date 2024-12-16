/*
* LoadingAnimation.qml
* Author: La Trung
* Date: 2024-12-16
* Description: This file contains the implementation of the LoadingAnimation component.
*/

import QtQuick
import QtQuick.Controls

Rectangle {
    id: loadingContainer
    anchors.centerIn: parent
    width: 80
    height: 80
    color: "transparent"
    property double startRadian: 0
    property double endRadian: Math.PI/2
    property bool isRunning: false

    Canvas {
        id: spinnerCanvas
        anchors.fill: parent
        property bool isIncrease: true
        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);
            // Draw spinning arc
            ctx.beginPath();
            ctx.arc(width / 2, height / 2, width/2 - 4, startRadian, endRadian, false);
            ctx.lineWidth = 6;
            ctx.strokeStyle = "#4285F4"; // Google Blue
            ctx.lineCap = "round";
            ctx.stroke();
        }
    }

    Timer {
        interval: 16 // ~60 FPS
        running: isRunning
        repeat: true
        onTriggered: {
            spinnerCanvas.rotation += 5;
            if (spinnerCanvas.rotation >= 360) {
                spinnerCanvas.rotation = 0;
            }
            spinnerCanvas.requestPaint();
        }
    }
}