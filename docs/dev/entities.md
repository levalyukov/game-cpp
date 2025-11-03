# Система существ

Класс `EntityManager` управляет сущностями, наследующие класс `Entity`.

## Методы

### Добавление сущности
```cpp
void addEntity(const std::string entity_name, std::unique_ptr<Entity>&& entity);
```

### Получение сущности
Если сущности нет - возвращает nullptr.
```cpp
Entity* getEntity(const std::string entity_name);
```

### Удаление сущности
```cpp
void removeEntity(const std::string entity_name);
```

### Отрисовка сущностей
Отрисовки происходит путем полиморфизма, включает в себя также сортировку по Y-координате:
```cpp
void render(const float delta_time, sf::View& game_camera);
```

### Вычисление расстояния
Получить расстояние между сущностями используя формулу: $\sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$
```cpp
int getDistance(const sf::Sprite first_entity, const sf::Sprite secondary_entity);
```

# Класс `Entity`

Класс, который наследуется для других существ.

### Установка захватчика
```cpp
virtual void setHandler(std::function<void()> new_handler) = 0;
```

### Установка ивента
Выполняется каждый кадр
```cpp
virtual void setEvent(std::function<void()> new_event) = 0;
```

## Player

Сущность, которым может управляет игрок.

### Методы

#### Передвижение
Используется стандартное управление:
| Кнопка |     Действие     |
| ------ | ---------------- |
| W      | Движение вверх   |
| A      | Движение влево   |
| S      | Движение вниз    |
| D      | Движение вправо  |
| Shift  | Бег              |

```cpp
void movement(float deltaTime);
```

## NPC

## Build