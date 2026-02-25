# Класс `SceneManager`

Позволяет хранить и перемещаться между уровнями.

Тест: [tests/scene-manager.cpp](../../src/engine/tests/scene-manager.cpp)

## Методы
Добавляет новую карту, которая наследует класс `Scene`, в хралищие карт. 

Возвращает `true` при успешном добавлении.
```cpp
inline bool addScene(const std::string& name, std::unique_ptr<Scene> scene)
```

Возвращает сырой указатель при условии, что указанная карта существует в хранилище карт.
```cpp
inline Scene* getScene(const std::string& name)
```

Удаляет существующую карту из хранилища. Если указатель был ранее на этой карте - указатель становится nullptr.

Возвращает `true` при успешном удалении.

```cpp
inline bool removeScene(const std::string& name)
```

Устанавливает указатель на новую карту. Возвращает `true` при успешной смене. 
```cpp
inline bool setPointer(const std::string& name)
```

Отрисовывает каждый кадр выбранную локацию.
```cpp
inline void update(sf::RenderWindow& window, sf::Event& event)
```

### Пример кода

scene1.hpp:
```cpp
#pragma once

#include <scenes/scene.hpp>

class GameMap1 : public Scene {
  public:
    inline void update(sf::RenderWindow& window, sf::Event& event) override {
      window.clear(sf::Color(255, 105, 180));
      window.display();
    };
};
```
game.cpp:
```cpp
#include "game.hpp"
#include "scene1.hpp"

void Game::init(void) {
  if (scene->addScene("scene1", std::make_unique<GameMap1>())) {
    scene->setScene("scene1");
  };
};
```
**Результат**:

![screenshot_scene](assets/scene-manager.png)
