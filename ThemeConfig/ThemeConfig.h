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

#include <memory>
#include <functional>

#include <QObject>
#include <QString>
#include <QColor>
#include <QFont>
#include <QStringList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFontDatabase>

class FontPalette;
class ColorPalette;

class ThemeConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)

    Q_PROPERTY(QObject *colorPalette READ colorPalette NOTIFY colorPaletteChanged)
    Q_PROPERTY(QObject *fontPalette READ fontPalette NOTIFY fontPaletteChanged)

public:

    explicit ThemeConfig(QObject *parent = nullptr);
    ~ThemeConfig();

    void initialize();

    enum Theme {
        Light,
        Dark,
        Matcha
    };Q_ENUM(Theme)

    void fontRegistry();
    void colorRegistry();
    void startConnection();

    QString theme() const;

    QObject *colorPalette() const;
    QObject *fontPalette() const;

    void setTheme(const QString &theme);

    Q_INVOKABLE bool loadConfig(const QString &filePath);
    Theme currentTheme() const;

signals:
    void themeChanged();

    void colorPaletteChanged();
    void fontPaletteChanged();

private:
    void parseConfig(Theme theme);
    void parseThemeProperties(const QJsonObject &themeObject);
    void convertTheme(const QString &theme);
    void parseFont(const QJsonObject &fontObject, QFont &font);

    QString m_theme;
    Theme m_currentTheme;

    QStringList m_themeProperties;

    QScopedPointer<ColorPalette> m_colorPalette;
    QScopedPointer<FontPalette> m_fontPalette;

    QMap<QString, std::function<void(const QColor&)>> m_colorLayerSetters;
    QMap<QString, std::function<void(const QFont&)>> m_fontLayerSetters;

    QJsonDocument m_jsonDocument;
    std::shared_ptr<QFontDatabase> m_fontDatabase;
};
