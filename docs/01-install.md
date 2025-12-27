# Установка и запуск

Чтобы запустить игру, можно использовать два способа:

1. Собрать игру самостоятельно
2. Загрузить собранную игру с [VK Play](http://vkplay.ru/play/game/delicious-soup/) или [GameJolt]().

Игра поддерживает: Windows, Linux, MacOS

## Сборка проекта

Для сборки понадобится следующие инструменты:
- [Git](https://git-scm.com/install)
- [CMake](https://cmake.org/download) (версия 3.15 и выше) 
- [GCC](https://gcc.gnu.org/install/download.html)

#### 1. Склонируйте репозиторий
```bash
git clone https://github.com/levalyukov/game-cpp.git
cd game-cpp
```

#### 2. Установите все зависимости проекта

```bash
git submodule update --init
```

#### 3. Создайте папку для сборки и начните сборку
```bash
mkdir build
cd build

cmake ..
make
```

#### 4. Запустите собранный проект
``` bash
./main
```