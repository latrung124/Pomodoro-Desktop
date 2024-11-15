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
#include "Utils/ThemeDefined.h"

#include <QFile>
#include <QDebug>
#include <QJsonArray>

ThemeConfig::ThemeConfig(QObject *parent)
    : QObject(parent), m_fontDatabase(std::make_shared<QFontDatabase>())
{
    loadConfig(ThemeConfigSpace::kThemePath);

    setTheme("matcha");
}

ThemeConfig::~ThemeConfig()
{
    qDebug() << Q_FUNC_INFO;
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

QColor ThemeConfig::loginGreetingColor() const
{
    return m_loginGreetingColor;
}

QFont ThemeConfig::loginGreetingFont() const
{
    return m_loginGreetingFont;
}

QColor ThemeConfig::loginButtonColor() const
{
    return m_loginButtonColor;
}

QFont ThemeConfig::loginButtonFont() const
{
    return m_loginButtonFont;
}

QColor ThemeConfig::loginRegularColor() const
{
    return m_loginRegularColor;
}

QFont ThemeConfig::loginRegularFont() const
{
    return m_loginRegularFont;
}

QColor ThemeConfig::loginPlaceholderColor() const
{
    return m_loginPlaceholderColor;
}

QFont ThemeConfig::loginPlaceholderFont() const
{
    return m_loginPlaceholderFont;
}

void ThemeConfig::convertTheme(const QString &theme)
{
    if (theme == "light")
    {
        m_currentTheme = Light;
    }
    else if (theme == "dark")
    {
        m_currentTheme = Dark;
    }
    else if (theme == "matcha")
    {
        m_currentTheme = Matcha;
    }
}

bool ThemeConfig::loadConfig(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Unable to open file:" << filePath;
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    m_jsonDocument = QJsonDocument::fromJson(jsonData);

    return true;
}

void ThemeConfig::parseFont(const QJsonObject &fontObject, QFont &font)
{
    QString family = fontObject["family"].toString();
    int id = m_fontDatabase->addApplicationFont(ThemeConfigSpace::kFontPath + family + ".ttf");
    if (id == ThemeConfigSpace::ThemeError::InvalidFont)
    {
        qWarning() << "Failed to load the font!";
    }
    else
    {
        QStringList loadedFonts = QFontDatabase::applicationFontFamilies(id);
        qDebug() << "Loaded font:" << loadedFonts;
        int pixelSize = fontObject["pixelSize"].toInt();
        font = QFont(loadedFonts, pixelSize);
    }
}

void ThemeConfig::parseConfig(Theme theme)
{
    if (m_jsonDocument.isNull() || m_jsonDocument.isEmpty() || !m_jsonDocument.isObject())
    {
        qWarning() << "Invalid JSON data, cant parse config after set theme";
        return;
    }

    QJsonObject jsonObject = m_jsonDocument.object();

    if (jsonObject.contains("themes") && jsonObject["themes"].isObject())
    {
        QJsonObject themesObject = jsonObject["themes"].toObject();

        QString selectedTheme = m_theme; // Determine selected theme

        if (themesObject.contains(selectedTheme))
        {

            QJsonObject themeObject = themesObject[selectedTheme].toObject();

            if (themeObject.contains("homescreen"))
            {
                QJsonObject homeScreenObject = themeObject["homescreen"].toObject();
                m_homeBgColor = QColor(homeScreenObject["backgroundColor"].toString());
                emit homeBgColorChanged();

                if (homeScreenObject.contains("font"))
                {
                    QJsonObject fontObject = homeScreenObject["font"].toObject();
                    QString family = fontObject["family"].toString();
                    int pixelSize = fontObject["pixelSize"].toInt();
                    m_homeTextFont = QFont(family, pixelSize);
                    emit homeTextFontChanged();
                }
            }

            if (themeObject.contains("loginscreen"))
            {
                QJsonObject loginScreenObject = themeObject["loginscreen"].toObject();
                m_loginBgColor = QColor(loginScreenObject["backgroundColor"].toString());
                emit loginBgColorChanged();

                QJsonObject textObject = loginScreenObject["text"].toObject();

                QJsonObject greetingObject = textObject["greeting"].toObject();
                m_loginGreetingColor = QColor(greetingObject["color"].toString());
                emit loginGreetingColorChanged();
                parseFont(greetingObject["font"].toObject(), m_loginGreetingFont);
                emit loginGreetingFontChanged();

                QJsonObject buttonObject = textObject["button"].toObject();
                m_loginButtonColor = QColor(buttonObject["color"].toString());
                emit loginButtonColorChanged();
                parseFont(buttonObject["font"].toObject(), m_loginButtonFont);
                emit loginButtonFontChanged();

                QJsonObject regularObject = textObject["regular"].toObject();
                m_loginRegularColor = QColor(regularObject["color"].toString());
                emit loginRegularColorChanged();
                parseFont(regularObject["font"].toObject(), m_loginRegularFont);
                emit loginRegularFontChanged();

                QJsonObject placeholderObject = textObject["placeholder"].toObject();
                m_loginPlaceholderColor = QColor(placeholderObject["color"].toString());
                emit loginPlaceholderColorChanged();
                parseFont(placeholderObject["font"].toObject(), m_loginPlaceholderFont);
                emit loginPlaceholderFontChanged();
            }
        }
    }

    qDebug() << "Theme parsed successfully";
}
