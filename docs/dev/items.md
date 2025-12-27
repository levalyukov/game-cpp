# Предметы

Вся информация о предметах храниться в классе `Items`.

Есть два контейнера `items` и `recipes`:

### Контейнер `items`

Хранит все игровые предметы.

```cpp
struct Item {
  unsigned int id;
  std::string icon;
  unsigned int price;
};
```

- `id` - 
- `icon` - 
- `price` - 


### Контейнер `recipes`

Хранит все рецепты приготовления блюд, рецепт не является игровым предметом.

```cpp
struct CookRecipe {
  unsigned int id;
  std::string title;
  std::string description;
  std::string icon;
  unsigned int output;
  float cook_time = 0.f;
  float customer_wait = 0.f;
};
```

- `id` - идентификатор рецепта
- `title` - название 
- `description` - короткое описание 
- `icon` - путь до иконки
- `output` - получаемый предмет после готовке
- `cook_time` - время приготовления
- `customer_wait` - время ожидания клиента


## Методы

### Проверка существования рецепта
```cpp
bool hasRecipe(const uint8_t id);
```

### Получить структуру `Item`
Если структуры по указанному `id` нет — nullptr.
```cpp
Item* getItemInfo(const uint8_t id);
```

### Получить структуру `CookRecipe`
Если структуры по указанному `id` нет — nullptr.
```cpp
CookRecipe* getRecipeInfo(const uint8_t id);
```

### Размер контейнера `items`
```cpp
size_t getAllItems() const;
```

### Размер контейнера `recipes`
```cpp
size_t getAllRecipes() const;
```