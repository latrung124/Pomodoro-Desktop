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

#include <QObject>
#include <QString>
#include <QColor>
#include <QFont>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFontDatabase>

class ThemeConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)

    Q_PROPERTY(QColor homeBgColor READ homeBgColor NOTIFY homeBgColorChanged)
    Q_PROPERTY(QColor textColor READ textColor NOTIFY textColorChanged)
    Q_PROPERTY(QFont homeTextFont READ homeTextFont NOTIFY homeTextFontChanged)

    Q_PROPERTY(QColor loginBgColor READ loginBgColor NOTIFY loginBgColorChanged)
    Q_PROPERTY(QColor loginGreetingColor READ loginGreetingColor NOTIFY loginGreetingColorChanged)
    Q_PROPERTY(QFont loginGreetingFont READ loginGreetingFont NOTIFY loginGreetingFontChanged)
    Q_PROPERTY(QColor loginButtonColor READ loginButtonColor NOTIFY loginButtonColorChanged)
    Q_PROPERTY(QFont loginButtonFont READ loginButtonFont NOTIFY loginButtonFontChanged)
    Q_PROPERTY(QColor loginRegularColor READ loginRegularColor NOTIFY loginRegularColorChanged)
    Q_PROPERTY(QFont loginRegularFont READ loginRegularFont NOTIFY loginRegularFontChanged)
    Q_PROPERTY(QColor loginPlaceholderColor READ loginPlaceholderColor NOTIFY loginPlaceholderColorChanged)
    Q_PROPERTY(QFont loginPlaceholderFont READ loginPlaceholderFont NOTIFY loginPlaceholderFontChanged)

public:

    explicit ThemeConfig(QObject *parent = nullptr);
    ~ThemeConfig();

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
    QColor loginGreetingColor() const;
    QFont loginGreetingFont() const;
    QColor loginButtonColor() const;
    QFont loginButtonFont() const;
    QColor loginRegularColor() const;
    QFont loginRegularFont() const;
    QColor loginPlaceholderColor() const;
    QFont loginPlaceholderFont() const;

    void setTheme(const QString &theme);

    Q_INVOKABLE bool loadConfig(const QString &filePath);
    Theme currentTheme() const;

signals:
    void themeChanged();

    void homeBgColorChanged();
    void textColorChanged();
    void homeTextFontChanged();
    
    void loginBgColorChanged();
    void loginGreetingColorChanged();
    void loginGreetingFontChanged();
    void loginButtonColorChanged();
    void loginButtonFontChanged();
    void loginRegularColorChanged();
    void loginRegularFontChanged();
    void loginPlaceholderColorChanged();
    void loginPlaceholderFontChanged();

private:
    void parseConfig(Theme theme);
    void convertTheme(const QString &theme);
    void parseFont(const QJsonObject &fontObject, QFont &font);

    QColor m_homeBgColor;
    QColor m_textColor;
    QFont m_homeTextFont;
    QString m_theme;
    Theme m_currentTheme;

    QColor m_loginBgColor;
    QColor m_loginGreetingColor;
    QFont m_loginGreetingFont;
    QColor m_loginButtonColor;
    QFont m_loginButtonFont;
    QColor m_loginRegularColor;
    QFont m_loginRegularFont;
    QColor m_loginPlaceholderColor;
    QFont m_loginPlaceholderFont;

    QJsonDocument m_jsonDocument;
    std::shared_ptr<QFontDatabase> m_fontDatabase;
};
