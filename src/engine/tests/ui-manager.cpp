#include <memory>
#include <stdint.h>
#include <catch2/catch_all.hpp>
#include <ui/ui-manager.hpp>
#include <ui/elements/element.hpp>

/*<! ----------------- !>*/
class Claus : public UIElement {
  public:
    inline void update(sf::RenderWindow& window, sf::Event& event) override {};
    inline void setDepth(int16_t depth) override {};
    inline int16_t getDepth(void) const override { return 0; };
    inline bool getVisible(void) const override { return true; };
    inline void setVisible(const bool& new_state) override {};
};
/*<! ----------------- !>*/

TEST_CASE("Add ui element", "[UIManager]") {
  UIManager ui;
  REQUIRE(ui.addElement("foo", std::make_unique<Claus>()));
  CHECK(ui.getElement("foo"));
};

TEST_CASE("Add an element with the same ID ", "[UIManager]") {
  UIManager ui;
  REQUIRE(ui.addElement("roo", std::make_unique<Claus>()));
  CHECK(!ui.addElement("roo", std::make_unique<Claus>()));
};

TEST_CASE("Remove element", "[UIManager]") {
  UIManager ui;
  REQUIRE(ui.addElement("roo", std::make_unique<Claus>()));
  REQUIRE(ui.getElement("roo"));
  REQUIRE(ui.removeElement("roo"));
  CHECK(!ui.getElement("roo"));
};

TEST_CASE("Delete a non-existing element", "[UIManager]") {
  UIManager ui;
  CHECK(!ui.removeElement("loo"));
};

TEST_CASE("Get null element", "[UIManager]") {
  UIManager ui;
  CHECK(!ui.getElement("foo"));
};
