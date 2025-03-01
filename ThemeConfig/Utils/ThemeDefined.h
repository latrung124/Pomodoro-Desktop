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

#include <QString>
namespace ThemeConfigSpace {

Q_NAMESPACE

    const QString kFontPath = ":/Resources/Fonts/";
    const QString kThemePath = ":/Resources/theme.json";

    enum ThemeError {
        InvalidFont = -1
    };

namespace Color {

Q_NAMESPACE

    enum ColorLayer {
        Layer1,
        Layer2,
        Layer3,
        Layer4,
        Layer5,
        Layer6,
        Layer7
    };
    Q_ENUM_NS(ColorLayer)
} // namespace Color

namespace Font {

Q_NAMESPACE

    enum FontLayer {
        Layer1,
        Layer2,
        Layer3,
        Layer4
    };
    Q_ENUM_NS(FontLayer)
} // namespace Font
}; // namespace ThemeConfigSpace
