# screen_loader — кастомный экран загрузки для GTA San Andreas

Плагин для GTA San Andreas (ASI), заменяет стандартный экран загрузки на свою картинку и плавную полосу прогресса внизу экрана.

## Возможности

- Собственная картинка загрузки (на всю область экрана).
- Полоса прогресса внизу экрана (full width, без надписей), плавное заполнение.
- Сборка в Visual Studio, стандартный C++ (C++17), без Qt.

## Сборка

1. Откройте **Visual Studio** (2017, 2019 или 2022).
2. **Файл → Открыть → Решение/проект** → выберите `screen_loader.sln`.
3. Конфигурация: **Release**, **Win32** (x86).
4. **Сборка → Собрать решение** (F7).

В папке `bin\Release\` появится **screen_loader.asi**.

## Требования

- Windows, платформа **x86 (Win32)**.
- **DirectX SDK (June 2010)** — заголовки `d3dx9.h` / `d3dx9core.h`:
  - [Microsoft DirectX SDK - June 2010](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
  - Установка по умолчанию: `C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\`
  - Либо переменная **DXSDK_DIR** (тогда в проекте используются `$(DXSDK_DIR)Include` и `$(DXSDK_DIR)Lib\x86`).

## Установка

1. Скопируйте **screen_loader.asi** в папку с GTA San Andreas (рядом с `gta_sa.exe`).
2. Положите картинку загрузки **screen_loader.png** в ту же папку.
3. Нужен ASI Loader (например, CLEO или другой загрузчик .asi).

При сборке: если в корне проекта лежит **screen_loader.png**, он копируется в `bin\Release\` (рядом с .asi).

## Структура проекта

- `source/screen_loader.cpp`, `source/screen_loader.h` — логика экрана загрузки и полосы прогресса.
- `source/loader.cpp`, `source/loader.h` — точка входа DLL, хуки, имя плагина.
- `d3d9/` — обёртка Direct3D 9, текстуры, примитивы.
- `llmo/` — хуки вызовов.
- `CGame/` — заголовки/типы игры.

Лицензия и авторство — по вашему репозиторию.
