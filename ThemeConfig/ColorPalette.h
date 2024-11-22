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
#include <QColor>
#include <QStringList>

class ColorPalette : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor layer1 READ layer1 WRITE setLayer1 NOTIFY layer1Changed)
    Q_PROPERTY(QColor layer2 READ layer2 WRITE setLayer2 NOTIFY layer2Changed)
    Q_PROPERTY(QColor layer3 READ layer3 WRITE setLayer3 NOTIFY layer3Changed)
    Q_PROPERTY(QColor layer4 READ layer4 WRITE setLayer4 NOTIFY layer4Changed)
    Q_PROPERTY(QColor layer5 READ layer5 WRITE setLayer5 NOTIFY layer5Changed)
    Q_PROPERTY(QColor layer6 READ layer6 WRITE setLayer6 NOTIFY layer6Changed)
    Q_PROPERTY(QColor layer7 READ layer7 WRITE setLayer7 NOTIFY layer7Changed)

public:
    explicit ColorPalette(QObject *parent = nullptr);
    ~ColorPalette();

    QColor layer1() const;
    QColor layer2() const;
    QColor layer3() const;
    QColor layer4() const;
    QColor layer5() const;
    QColor layer6() const;
    QColor layer7() const;

    QStringList layerList() const;

signals:
    void layer1Changed();
    void layer2Changed();
    void layer3Changed();
    void layer4Changed();
    void layer5Changed();
    void layer6Changed();
    void layer7Changed();

public slots:
    void slotThemeChanged();

    void setLayer1(const QColor &color);
    void setLayer2(const QColor &color);
    void setLayer3(const QColor &color);
    void setLayer4(const QColor &color);
    void setLayer5(const QColor &color);
    void setLayer6(const QColor &color);
    void setLayer7(const QColor &color);

private:
    QColor m_layer1;
    QColor m_layer2;
    QColor m_layer3;
    QColor m_layer4;
    QColor m_layer5;
    QColor m_layer6;
    QColor m_layer7;

    QStringList m_layerList;
};
