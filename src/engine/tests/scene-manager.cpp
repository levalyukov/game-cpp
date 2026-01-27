#include <memory>
#include <catch2/catch_all.hpp>
#include <scenes/scene-manager.hpp>
#include <scenes/scene.hpp>

/*<! ----- !>*/
class Spawn : public Scene {
  public:
    inline void update(sf::RenderWindow& window, sf::Event& event) override {};
};
/*<! ----- !>*/

TEST_CASE("Add level", "[SceneManager]") {
  SceneManager sm;
  CHECK(sm.addScene("foo", std::make_unique<Spawn>()));
};

TEST_CASE("Add an level with the same ID", "[SceneManager]") {
  SceneManager sm;
  REQUIRE(sm.addScene("foo", std::make_unique<Spawn>()));
  CHECK(!sm.addScene("foo", std::make_unique<Spawn>()));
};

TEST_CASE("Remove element", "[SceneManager]") {
  SceneManager sm;
  REQUIRE(sm.addScene("zoo", std::make_unique<Spawn>()));
  CHECK(sm.removeScene("zoo"));
};

TEST_CASE("Remove null element", "[SceneManager]") {
  SceneManager sm;
  CHECK(!sm.removeScene("boo"));
};

TEST_CASE("Change poiner to level", "[SceneManager]") {
  SceneManager sm;
  REQUIRE(sm.addScene("goo", std::make_unique<Spawn>()));
  CHECK(sm.setScene("goo"));
};

TEST_CASE("Change pointer to null level", "[SceneManager]") {
  SceneManager sm;
  CHECK(!sm.setScene("loo"));
};

TEST_CASE("Change poiner to level and remove", "[SceneManager]") {
  SceneManager sm;
  REQUIRE(sm.addScene("joo", std::make_unique<Spawn>()));
  REQUIRE(sm.setScene("joo"));
  REQUIRE(sm.getPointer() == sm.getScene("joo"));
  REQUIRE(sm.removeScene("joo"));
  CHECK(!sm.getPointer());
};