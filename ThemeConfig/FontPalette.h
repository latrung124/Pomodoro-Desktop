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

#pragma once

#include <QObject>
#include <QFont>
#include <QStringList>

class FontPalette : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QFont layer1 READ layer1 NOTIFY layer1Changed)
    Q_PROPERTY(QFont layer2 READ layer2 NOTIFY layer2Changed)
    Q_PROPERTY(QFont layer3 READ layer3 NOTIFY layer3Changed)
    Q_PROPERTY(QFont layer4 READ layer4 NOTIFY layer4Changed)

public:
    explicit FontPalette(QObject *parent = nullptr);
    ~FontPalette();

    QFont layer1() const;
    QFont layer2() const;
    QFont layer3() const;
    QFont layer4() const;

    QStringList layerList() const;

signals:
    void layer1Changed();
    void layer2Changed();
    void layer3Changed();
    void layer4Changed();

public slots:
    void slotThemeChanged();

private:
    QFont m_layer1;
    QFont m_layer2;
    QFont m_layer3;
    QFont m_layer4;

    QStringList m_layerList;
};
