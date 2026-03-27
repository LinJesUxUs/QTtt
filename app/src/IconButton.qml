// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.impl

Item {
    id: root
    Layout.fillHeight: true
    Layout.fillWidth: true
    property alias button: button
    property alias source: img.source
    IconImage {
        id: img
        height: Math.min(parent.width, parent.height)
        width: height
        fillMode: Image.PreserveAspectFit
        anchors.centerIn: root
        antialiasing: true
        color: Material.foreground
        Button {
            id: button
            anchors.fill: img
            flat: true
            opacity: 0.5
        }
    }
}
