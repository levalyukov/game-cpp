# Класс `EntityManager`

Позволяет хранить, манипулировать и удалять сущностей с наследуемым абстрактным классом `Entity`.

Тест: [tests/entity-manager.cpp](../../tests/entity-manager.cpp)

## Методы

Добавляет новую сущность с уникальным идентификатором. Не добавляет, если сущность с таким же идентификатором уже существует. 

Возвращает `true` при успешном добавлении.
```cpp
bool addEntity(const std::string& name, std::unique_ptr<Entity> entity);
```

Возвращает сырой указатель на `Entity` из контейнера `map`.
```cpp
Entity* getEntity(const std::string& name);
```

Удаляет `Entity` из контейнера. Возвращает `true` при успешном .
```cpp
bool removeEntity(const std::string& name);
```

Отрисовывает спрайты `Entity` методом полиморфизма.
```cpp
void update(sf::RenderWindow& window, sf::Event& event) const;
```