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

#include "ColorPalette.h"

ColorPalette::ColorPalette(QObject *parent)
    : QObject(parent)
{
    m_layer1 = QColor(255, 255, 255);
    m_layer2 = QColor(0, 0, 0);
    m_layer3 = QColor(18, 18, 18);
    m_layer4 = QColor(51, 51, 51);
    m_layer5 = QColor(240, 240, 240);
    m_layer6 = QColor(232, 234, 224);
    m_layer7 = QColor(128, 128, 128);

    m_layerList = {"layer1",
                   "layer2",
                   "layer3",
                   "layer4",
                   "layer5",
                   "layer6",
                   "layer7"};
}

ColorPalette::~ColorPalette()
{
}

QColor ColorPalette::layer1() const
{
    return m_layer1;
}

QColor ColorPalette::layer2() const
{
    return m_layer2;
}

QColor ColorPalette::layer3() const
{
    return m_layer3;
}

QColor ColorPalette::layer4() const
{
    return m_layer4;
}

QColor ColorPalette::layer5() const
{
    return m_layer5;
}

QColor ColorPalette::layer6() const
{
    return m_layer6;
}

QColor ColorPalette::layer7() const
{
    return m_layer7;
}

QStringList ColorPalette::layerList() const
{
    return m_layerList;
}

void ColorPalette::setLayer1(const QColor &color)
{
    if (m_layer1 == color)
        return;

    m_layer1 = color;
}

void ColorPalette::setLayer2(const QColor &color)
{
    if (m_layer2 == color)
        return;

    m_layer2 = color;
}

void ColorPalette::setLayer3(const QColor &color)
{
    if (m_layer3 == color)
        return;

    m_layer3 = color;
}

void ColorPalette::setLayer4(const QColor &color)
{
    if (m_layer4 == color)
        return;

    m_layer4 = color;
}

void ColorPalette::setLayer5(const QColor &color)
{
    if (m_layer5 == color)
        return;

    m_layer5 = color;
}

void ColorPalette::setLayer6(const QColor &color)
{
    if (m_layer6 == color)
        return;

    m_layer6 = color;
}

void ColorPalette::setLayer7(const QColor &color)
{
    if (m_layer7 == color)
        return;

    m_layer7 = color;
}

void ColorPalette::slotThemeChanged()
{
    emit layer1Changed();
    emit layer2Changed();
    emit layer3Changed();
    emit layer4Changed();
    emit layer5Changed();
    emit layer6Changed();
    emit layer7Changed();
}
