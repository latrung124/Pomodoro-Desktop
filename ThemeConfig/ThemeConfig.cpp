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

#include "FontPalette.h"
#include "ColorPalette.h"

#include <QFile>
#include <QDebug>
#include <QList>
#include <QJsonArray>
#include <QMetaObject>
#include <QMetaMethod>

ThemeConfig::ThemeConfig(QObject *parent)
    : QObject(parent),
      m_fontDatabase(std::make_shared<QFontDatabase>()),
      m_colorPalette(new ColorPalette(this)),
      m_fontPalette(new FontPalette(this))
{
    initialize();
    loadConfig(ThemeConfigSpace::kThemePath);

    setTheme("matcha");
}

ThemeConfig::~ThemeConfig()
{
    qDebug() << Q_FUNC_INFO;
}

void ThemeConfig::initialize()
{
    m_themeProperties = {
        "colors",
        "fonts"
    };

    colorRegistry();
    fontRegistry();
}

void ThemeConfig::startConnection()
{
    connect(this, &ThemeConfig::themeChanged, m_fontPalette.get(), &FontPalette::slotThemeChanged);
    connect(this, &ThemeConfig::themeChanged, m_colorPalette.get(), &ColorPalette::slotThemeChanged);
}

void ThemeConfig::fontRegistry()
{
    for (int i = 0; i < m_fontPalette->layerList().size(); ++i)
    {
        auto layer = m_fontPalette->layerList().at(i);
        QByteArray methodName = QString("setLayer%1").arg(i + 1).toUtf8(); // Avoid repeated string conversion

        m_fontLayerSetters[layer] = [this, methodName](const QFont &font) {
            if (!QMetaObject::invokeMethod(m_fontPalette.get(),
                                      methodName.constData(),
                                           Q_ARG(QFont, font))) {
                qWarning() << "Failed to registry font method: " << methodName;
            } else {
                qDebug() << "Registry successfully font method:" << methodName;
            }
        };
    }
}

void ThemeConfig::colorRegistry()
{
    for (int i = 0; i < m_colorPalette->layerList().size(); ++i)
    {
        auto layer = m_colorPalette->layerList().at(i);
        QByteArray methodName = QString("setLayer%1").arg(i + 1).toUtf8(); // Avoid repeated string conversion

        m_colorLayerSetters[layer] = [this, methodName](const QColor &color) {
            if(!QMetaObject::invokeMethod(m_colorPalette.get(),
                                      methodName.constData(),
                                      Q_ARG(QColor, color))) {
                qWarning() << "Failed to registry font method: " << methodName;
            } else {
                qDebug() << "Registry successfully font method: " << methodName;
            }
        };
    }
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
    convertTheme(theme);
    parseConfig(m_currentTheme);

    emit themeChanged();
}

QObject *ThemeConfig::colorPalette() const
{
    return m_colorPalette.get();
}

QObject *ThemeConfig::fontPalette() const
{
    return m_fontPalette.get();
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

void ThemeConfig::parseThemeProperties(const QJsonObject &themeObject)
{
    for (const auto &property : m_themeProperties)
    {
        if (themeObject.contains(property))
        {
            QJsonObject propertyObject = themeObject[property].toObject();
            if (property == "colors")
            {
                for (auto it = m_colorLayerSetters.begin(); it != m_colorLayerSetters.end(); ++it)
                {
                    if (propertyObject.contains(it.key()))
                    {
                        it.value()(QColor(propertyObject[it.key()].toString()));
                    }
                }
            }
            else if (property == "fonts")
            {
                for (auto it = m_fontLayerSetters.begin(); it != m_fontLayerSetters.end(); ++it)
                {
                    if (propertyObject.contains(it.key()))
                    {
                        QFont font;
                        parseFont(propertyObject[it.key()].toObject(), font);
                        it.value()(font);
                    }
                }
            }
        }
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
            parseThemeProperties(themeObject);
        }
    }

    qDebug() << "Theme parsed successfully";
}
