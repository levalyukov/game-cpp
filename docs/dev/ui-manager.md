# Класс `UIManager`

Позволяет отрисовывать UI-элементы, наследующие класс `UIElement`, для создания целостного игрового UI.

Тест: [tests/ui-manager.cpp](../../src/engine/tests/ui-manager.cpp)

## Методы

Позволяет добавлять UI-элемент в хранилище для отрисовки. 

Возвращает `true` при успешном добавлении.
```cpp
inline bool addElement(const std::string& name, std::unique_ptr<UIElement> element);
```

Возвращает сырой указатель на существующий UI-элемент. 

Вернет `nullptr` если такого элемента нету.
```cpp
inline UIElement* getElement(const std::string& name);
```

Удаляет существующий UI-элемент из хранилища. 

Возвращает `true` при успешном удалении.
```cpp
inline bool removeElement(const std::string& name)
```

Отрисовка элементов в окне. Вызывается каждый кадр.

```cpp
inline void update(sf::RenderWindow& window, sf::Event& event)
```

### Интерфейс `UIElement`

Вызывается в методе `update()` класса `UIManager`.
```cpp
virtual void update(sf::RenderWindow& window, sf::Event& event) = 0;
```

Установить новую Z-координату UI-элемента.
```cpp
virtual void setDepth(const uint8_t depth) = 0;
```

Возвращает 8-ми битное Z-координату UI-элемента.
```cpp
virtual uint8_t getDepth(void) const = 0;
```