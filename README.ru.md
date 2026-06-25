# Сапёр на C++

## Языки README

- [Английский](https://github.com/Senyos/minesweeper-cpp-raylib/blob/main/README.md)
- [Русский](https://github.com/Senyos/minesweeper-cpp-raylib/blob/main/README.ru.md)

## Содержание

* [Скриншоты](#скриншоты)
* [Быстрый старт](#быстрый-старт)
* [Описание](#описание)
* [Как играть](#как-играть)

## Скриншоты

![Игровой скриншот 1](./1_screenshot.png "Игровой скриншот 1")

![Игровой скриншот 2](./2_screenshot.png "Игровой скриншот 2")

![Игровой скриншот 3](./3_screenshot.png "Игровой скриншот 3")

![Игровой скриншот 4](./4_screenshot.png "Игровой скриншот 4")

## Быстрый старт

### Зависимости

Вам понадобится установить зависимости в корневую директорию проекта:

1. Raylib релиз для целевой ОС: <https://github.com/raysan5/raylib/releases>.
2. Raylib C++ бинды: <https://github.com/RobLoach/raylib-cpp/releases>.

А также Вам понадобится компилятор. В проекте был использован `g++` компилятор на _Linux_ и `mingw64` на _Windows_; также Вы можете скомпилировать _Windows_ запускаемый файл будучи на _Linux_, если Вы установите компилятор `mingw64`: <https://www.mingw-w64.org/downloads/>.

Для _Windows_ выберите тот, который с: `x86_64-*.*.*-release-win32-seh-msvcrt-rt_v*-rev*.7z` _win32_ и _msvcrt_ (Microsoft Visual Compiler Runtime): <https://github.com/niXman/mingw-builds-binaries/releases>.

### Компиляция

Сперва, Вам понадобится настроить Makefile немного в случае различия наименований:

```makefile
CCLIN=g++                                                 # Linux compiler
CCWIN=x86_64-w64-mingw32-g++                              # Windows compiler

RAYLIBCPP_INCLUDE=-I./raylib-cpp/include/                 # raylib cpp bindings include

RAYLIBLIN_INCLUDE=-I./raylib-6.0_linux_amd64/include/     # raylib for Linux include
RAYLIBLIN_LIB=-L./raylib-6.0_linux_amd64/lib              # raylib for Linux lib

RAYLIBWIN_INCLUDE=-I./raylib-6.0_win64_mingw-w64/include/ # raylib for Windows include
RAYLIBWIN_LIB=-L./raylib-6.0_win64_mingw-w64/lib/         # raylib for Windows lib
```

Компиляция под _Linux_:

```sh
make lin
```

Компиляция под _Windows_:

```sh
make win
```

Компиляция под _Linux_ и _Windows_:

```sh
make all
```

или

```sh
make
```

Скомпилированные запускаемые файлы будут храниться в директории `build/`.

## Описание

Полнофункциональная игра Сапёр выполненная с помощью библиотеки raylib (<https://www.raylib.com/>) на C++. Были использованы бинды raylib-cpp (<https://github.com/RobLoach/raylib-cpp>).

## Как играть

В главном меню можно выбрать уровень нажав на кнопку "FIELD" несколько раз. Кнопка "START" начинает игру на выбранном поле.

На поле Левую Кнопку Мыши (ЛКМ) для открытия ячейки, Правую Кнопку Мыши (ПКМ) для того, чтобы поставить флажок.

Нажать R во время проигрыша, чтобы переиграть. Нажать ESC во время проигрыша, чтобы выйти в главное меню. Нажать ESC в главном меню, чтобы покинуть игру.
