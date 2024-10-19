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

#include "FontPalette.h"

FontPalette::FontPalette(QObject *parent)
    : QObject(parent)
{
    m_layer1 = QFont("Arial", 12);
    m_layer2 = QFont("Arial", 12);
    m_layer3 = QFont("Arial", 12);
    m_layer4 = QFont("Arial", 12);

    m_layerList = {"layer1",
                   "layer2",
                   "layer3",
                   "layer4"};
}

FontPalette::~FontPalette()
{
}

QFont FontPalette::layer1() const
{
    return m_layer1;
}

QFont FontPalette::layer2() const
{
    return m_layer2;
}

QFont FontPalette::layer3() const
{
    return m_layer3;
}

QFont FontPalette::layer4() const
{
    return m_layer4;
}

QStringList FontPalette::layerList() const
{
    return m_layerList;
}

void FontPalette::setLayer1(const QFont &font)
{
    if (m_layer1 != font)
    {
        m_layer1 = font;
    }
}

void FontPalette::setLayer2(const QFont &font)
{
    if (m_layer2 != font)
    {
        m_layer2 = font;
    }
}

void FontPalette::setLayer3(const QFont &font)
{
    if (m_layer3 != font)
    {
        m_layer3 = font;
    }
}

void FontPalette::setLayer4(const QFont &font)
{
    if (m_layer4 != font)
    {
        m_layer4 = font;
    }
}

void FontPalette::slotThemeChanged()
{
    emit layer1Changed();
    emit layer2Changed();
    emit layer3Changed();
    emit layer4Changed();
}
