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

### Захватчик
Лямбда-функция, которая выполняется при нажатии на существо. 

Ограничено расстоянием между игроком и существом.
```cpp
virtual void setHandler(std::function<void()> new_handler) = 0;
```

### Событие
Лямбда-функция, которая выполняется каждый кадр. 

Можно использовать в качестве сценария поведения существа.
```cpp
virtual void setEvent(std::function<void()> new_event) = 0;
```

Если сделать явное приведение, то у вас появляются дополнительные функции для манипуляции со сущностью:

### Текстуры

```cpp
sf::Texture& getTextureIDLE() const;
```

```cpp
sf::Texture& getTextureMoveVertical() const;
```

```cpp
sf::Texture& getTextureMoveHorizontal() const;
```

### Спрайта

```cpp
sf::Sprite& getSprite() const;
```

### Фиксированная дельта

```cpp
float getDelta() const;
```


## Player

Сущность, которым может управляет игрок.

### Методы

#### Передвижение
Передвижение игрока, используется стандартное управление. 

Невозможно изменить, вызывается из функции `render`. 
| Кнопка |     Действие     |
| ------ | ---------------- |
| W      | Движение вверх   |
| A      | Движение влево   |
| S      | Движение вниз    |
| D      | Движение вправо  |
| Shift  | Бег              |

```cpp
void movement(const float delta);
```

#### Предметы
Персонаж может носить с собой только один предмет. 

Установленный предмет появиться над головой персонажа, а также измениться анимация и скорость передвижения.

```cpp
void setSelectedItem(uint8_t new_item, Items& items);
```

Возвращает текущий предмет.
```cpp
uint8_t getSelectedItem() const;
```

####

## NPC
Неигровой персонаж. Для написания логики используйте методы `setHandler`, `setEvent`. Имеет те же самые методы, что и `Player`.

### Методы

#### Заказы
Позволяет получить или поменять `id` заказа сущности.
```cpp
void setOrder(uint8_t);
```

```cpp
uint8_t getOrder();
```

## Build

Постройка. Взаимодействие происходит через метод `handler()`. Ограниченно расстоянием от игрока до сущности. 