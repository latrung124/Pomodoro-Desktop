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

#include "ThemeConfig.h"

#include <QFile>
#include <QDebug>
#include <QJsonArray>

ThemeConfig::ThemeConfig(const QString &configPath,QObject *parent)
    : QObject(parent)
{
    loadConfig(configPath);

    setTheme("matcha");
}

QString ThemeConfig::theme() const
{
    return m_theme;
}

void ThemeConfig::setTheme(const QString &theme)
{
    if (m_theme == theme)
        return;

    m_theme = theme;
    emit themeChanged();
    convertTheme(theme);

    parseConfig(m_currentTheme);
}

QColor ThemeConfig::homeBgColor() const
{
    return m_homeBgColor;
}

QColor ThemeConfig::textColor() const
{
    return m_textColor;
}

QFont ThemeConfig::homeTextFont() const
{
    return m_homeTextFont;
}

QColor ThemeConfig::loginBgColor() const
{
    return m_loginBgColor;
}

QColor ThemeConfig::loginTextColor() const
{
    return m_loginTextColor;
}

QFont ThemeConfig::loginTextFont() const
{
    return m_loginTextFont;
}

void ThemeConfig::convertTheme(const QString &theme)
{
    if (theme == "light") {
        m_currentTheme = Light;
    } else if (theme == "dark") {
        m_currentTheme = Dark;
    } else if (theme == "matcha") {
        m_currentTheme = Matcha;
    }
}

bool ThemeConfig::loadConfig(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Unable to open file:" << filePath;
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    m_jsonDocument = QJsonDocument::fromJson(jsonData);
    
    return true;
}

void ThemeConfig::parseConfig(Theme theme) {
    if (m_jsonDocument.isNull() || m_jsonDocument.isEmpty() || !m_jsonDocument.isObject()) {
        qWarning() << "Invalid JSON data, cant parse config after set theme";
        return;
    }

    QJsonObject jsonObject = m_jsonDocument.object();

    if (jsonObject.contains("themes") && jsonObject["themes"].isObject()) {
        QJsonObject themesObject = jsonObject["themes"].toObject();

        QString selectedTheme = m_theme;  // Determine selected theme

        if (themesObject.contains(selectedTheme)) {

            QJsonObject themeObject = themesObject[selectedTheme].toObject();

            if (themeObject.contains("homescreen")) {
                QJsonObject homeScreenObject = themeObject["homescreen"].toObject();
                m_homeBgColor = QColor(homeScreenObject["backgroundColor"].toString());
                emit homeBgColorChanged();

                if (homeScreenObject.contains("font")) {
                    QJsonObject fontObject = homeScreenObject["font"].toObject();
                    QString family = fontObject["family"].toString();
                    int pixelSize = fontObject["pixelSize"].toInt();
                    m_homeTextFont = QFont(family, pixelSize);
                    emit homeTextFontChanged();
                }
            }

            if (themeObject.contains("loginscreen")) {
                QJsonObject loginScreenObject = themeObject["loginscreen"].toObject();
                m_loginBgColor = QColor(loginScreenObject["backgroundColor"].toString());
                emit loginBgColorChanged();

                if (loginScreenObject.contains("font")) {
                    QJsonObject fontObject = loginScreenObject["font"].toObject();

                    QString family = fontObject["family"].toString();
                    QString fontPath = ThemeConfigSpace::kFontPath + family + ".ttf";
                    int id = QFontDatabase::addApplicationFont(fontPath);

                    if (id == -1) {
                        return;
                    }

                    int pixelSize = fontObject["pixelSize"].toInt();

                    m_loginTextFont = QFont(family, pixelSize);
                    emit loginTextFontChanged();
                }
            }
        }
    }

    qDebug() << "Theme parsed successfully";
}
