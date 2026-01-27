# Класс `EventManager`

Позволяет выполнять лямбды-функции через заданное время.

Тест: [tests/event-manager.cpp](../../src/engine/tests/event-manager.cpp)

### Структура `Event_t`

```cpp
struct Event_t {
  std::function<void()> lambda;
  uint32_t frequency;
  bool repeat = false;
  uint32_t time = 0;
  bool performed = false;
};
```

- `lambda` - лямбда-функция, которая будет выполнена по достижение время;
- `frequency` - частота, раз сколько времени будет выполняться событие;
- `repeat` - флаг, повторяется ли событие или нет;
- `time` - счетчик времени, по достижение 0 - лямбда-функция выполняется;
- `performed ` - флаг, отмечает выполнилось ли событие или нет.

Конструктор функции-члена: 
```cpp
Event_t(std::function<void()> _lambda, uint32_t _frequency, bool _repeat);
```

### Методы

Добавление события. 

Возвращает `true` при успешном добавлении.
```cpp
bool addEvent(const std::string& name, std::unique_ptr<Event_t> event);
```

Возвращает сырой указатель на событие, при его отсутствии возвращает `nullptr`.
```cpp
Event_t* getEvent(const std::string& name) const;
```

Удаляет событие. 

Возвращает `true` при успешном удалении.
```cpp
bool removeEvent(const std::string& name);
```

Обработка событий, вызывается каждый кадр.
```cpp
void update(void);
```

### Пример кода

level1.hpp
```cpp
#pragma once

#include <memory>
#include <levels/level.hpp>
#include <levels/level-manager.hpp>

class GameMap1 : public Level {
  public:
    inline void update(sf::RenderWindow& window, sf::Event& event) override {
      if (events) events->update();

      window.clear(sf::Color(255, 105, 180));
      window.display();
    };

  private:
    std::unique_ptr<EventManager> events = std::make_unique<EventManager>();

    void init(void);
};
```

level1.cpp
```cpp
#include "level1.hpp"

void GameMap1::init(void) {
  if (events) {
    events->addEvent("event1", std::make_unique<Event_t>(
      []() {std::cout << "- Hello!\n\t" << std::endl; }, 1, true));
  };
};
```

Результат:
```text
- Hello!

- Hello!

- Hello!
```