# Класс `UIManager`

Позволяет отрисовывать UI-элементы, наследующие класс `UIElement`, для создания целостного игрового UI.

Тест: [tests/ui-manager.cpp](../../src/engine/tests/ui-manager.cpp)

## Методы

### UI-Элементы

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
virtual void setDepth(const int16_t depth) = 0;
```

Возвращает 16-и битное Z-координату UI-элемента.
```cpp
virtual int16_t getDepth(void) const = 0;
```

### Шрифты

Создает и добавляет шрифт в хранилище шрифтов.

Возвращает `true` при успешном добавлении.
```cpp
bool addFont(const std::string& name, const std::string& path_to_font);
```

Возвращает сырой указатель на шрифт, если существует.

Вернет `nullptr` если шрифта нет.

```cpp
sf::Font* getFont(const std::string& name) const
```

Удаляет существующий шрифт. 

При успешном удалении вернет `true`.

```cpp
bool removeFont(const std::string& name)
```

### Текстуры

Добавляет текстуру в хранилище текстур.

При успешном добавлении `true` текстуры.

```cpp
bool addTexture(const std::string& name, const std::string& path_to_texture);
```

Возвращает сырой указатель на текстуру, если существует.
```cpp
sf::Texture* getTexture(const std::string& name) const;
```

Удаляет существующую текстуру. 

При успешном удалении вернет `true`.
```cpp
bool removeTexture(const std::string& name);
```


### Пример кода

Ниже приведен пример создания главного меню.

menu.hpp
```cpp
class MainMenu : public Scene {
  public:
    MainMenu(
      sf::RenderWindow& game_window,
      sf::Event& game_event,
      SceneManager* scene_manager
    ) : event(game_event),
        window(game_window),
        scenes(*scene_manager) { init(); };

    inline void update(sf::RenderWindow& window, sf::Event& event) override {
      window.clear(sf::Color(255, 222, 180));
      if (ui) ui->update(window, event);
      window.display();
    };

  private:
    sf::Event& event;
    SceneManager& scenes;
    sf::RenderWindow& window;
    std::unique_ptr<UIManager> ui = std::make_unique<UIManager>();

    void init(void);
    void initResources(void);
    void initButtons(void);
    void initPosition(void);
    void initLambda(void);
    void initButtonsLabel(void);
};
```

menu.cpp
```cpp
#include "menu.hpp"

#include <ui/elements/label.hpp>
#include <ui/elements/button.hpp>

void MainMenu::init(void) {
  if (!ui) return;

  initResources();
  initButtons();
  initPosition();
  initLambda();
  initButtonsLabel();
};

void MainMenu::initResources(void) {
  ui->addTexture("button", "../../../assets/textures/ui/buttons.png");
  ui->addFont("nunito", "../../../assets/fonts/nunito.ttf");
};

void MainMenu::initButtons(void) {
  if (ui->getTexture("button")) {
    ui->addElement("play-button", std::make_unique<Button>(
      ui->getTexture("button"),
      sf::Vector2i{ 48,16 },
      sf::Vector2i{ 0,0 }
    ));

    ui->addElement("settings-button", std::make_unique<Button>(
      ui->getTexture("button"),
      sf::Vector2i{ 48,16 },
      sf::Vector2i{ 64,128 + 16 }
    ));

    ui->addElement("exit-button", std::make_unique<Button>(
      ui->getTexture("button"),
      sf::Vector2i{ 48,16 },
      sf::Vector2i{ 64,192 + 32 }
    ));
  };
};

void MainMenu::initPosition(void) {
  auto play = ui->getElement("play-button");
  if (play)
    ui->setElementPosition(window,
      static_cast<Button*>(play)->getButton(),
      UIManager::UIPosition::TopCenter,
      { 0,128 }
    );

  auto settings = ui->getElement("settings-button");
  if (settings)
    ui->setElementPosition(window,
      static_cast<Button*>(settings)->getButton(),
      UIManager::UIPosition::MiddleCenter,
      { 0,0 }
    );

  auto exit = ui->getElement("exit-button");
  if (exit)
    ui->setElementPosition(window,
      static_cast<Button*>(exit)->getButton(),
      UIManager::UIPosition::BottomCenter,
      { 0,128 }
    );
};

void MainMenu::initLambda(void) {
  auto play = static_cast<Button*>(ui->getElement("play-button"));
  auto settings = static_cast<Button*>(ui->getElement("settings-button"));
  auto exit = static_cast<Button*>(ui->getElement("exit-button"));

  if (play) play->setFunction([this]() {scenes.setPointer("level1"); });
  if (settings) settings->setFunction([]() {printf("<!-- Config Menu -->\n"); });
  if (exit) exit->setFunction([this]() {window.close(); });
};

void MainMenu::initButtonsLabel(void) {
  auto play = static_cast<Button*>(ui->getElement("play-button"));
  auto settings = static_cast<Button*>(ui->getElement("settings-button"));
  auto exit = static_cast<Button*>(ui->getElement("exit-button"));

  if (play) {
    play->setButtonText(ui->getFont("nunito"), L"Продолжить");
    ui->setLabelPosition(
      play->getButton(),
      play->getButtonText(),
      UIManager::MiddleCenter
    );
  };

  if (settings) {
    settings->setButtonText(ui->getFont("nunito"), L"Настройки");
    ui->setLabelPosition(
      settings->getButton(),
      settings->getButtonText(),
      UIManager::MiddleCenter
    );
  };

  if (exit) {
    exit->setButtonText(ui->getFont("nunito"), L"Выйти из игры");
    ui->setLabelPosition(
      exit->getButton(),
      exit->getButtonText(),
      UIManager::MiddleCenter
    );
  };
};
```