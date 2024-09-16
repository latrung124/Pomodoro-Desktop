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
#include <QString>
#include <QColor>
#include <QFont>
#include <QJsonObject>
#include <QJsonDocument>

class ThemeConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)

    Q_PROPERTY(QColor homeBgColor READ homeBgColor NOTIFY homeBgColorChanged)
    Q_PROPERTY(QColor textColor READ textColor NOTIFY textColorChanged)
    Q_PROPERTY(QFont homeTextFont READ homeTextFont NOTIFY homeTextFontChanged)

    Q_PROPERTY(QColor loginBgColor READ loginBgColor NOTIFY loginBgColorChanged)
    Q_PROPERTY(QColor loginTextColor READ loginTextColor NOTIFY loginTextColorChanged)
    Q_PROPERTY(QFont loginTextFont READ loginTextFont NOTIFY loginTextFontChanged)

public:

    explicit ThemeConfig(const QString &configPath, QObject *parent = nullptr);

    enum Theme {
        Light,
        Dark,
        Matcha
    };Q_ENUM(Theme)

    QString theme() const;

    QColor homeBgColor() const;
    QColor textColor() const;
    QFont homeTextFont() const;

    QColor loginBgColor() const;
    QColor loginTextColor() const;
    QFont loginTextFont() const;

    void setTheme(const QString &theme);

    Q_INVOKABLE bool loadConfig(const QString &filePath);
    Theme currentTheme() const;

signals:
    void themeChanged();

    void homeBgColorChanged();
    void textColorChanged();
    void homeTextFontChanged();
    
    void loginBgColorChanged();
    void loginTextColorChanged();
    void loginTextFontChanged();

private:
    void parseConfig(Theme theme);
    void convertTheme(const QString &theme);

    QColor m_homeBgColor;
    QColor m_textColor;
    QFont m_homeTextFont;
    QString m_theme;
    Theme m_currentTheme;

    QColor m_loginBgColor;
    QColor m_loginTextColor;
    QFont m_loginTextFont;

    QJsonDocument m_jsonDocument;
};
