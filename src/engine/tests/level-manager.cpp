#include <memory>
#include <catch2/catch_all.hpp>
#include <levels/level-manager.hpp>
#include <levels/level.hpp>

/*<! ----- !>*/
class Spawn : public Level {
  public:
    inline void update(sf::RenderWindow& window, sf::Event& event) override {};
};
/*<! ----- !>*/

TEST_CASE("Add level", "[LevelManager]") {
  LevelManager lm;
  CHECK(lm.addLevel("foo", std::make_unique<Spawn>()));
};

TEST_CASE("Add an level with the same ID", "[LevelManager]") {
  LevelManager lm;
  REQUIRE(lm.addLevel("foo", std::make_unique<Spawn>()));
  CHECK(!lm.addLevel("foo", std::make_unique<Spawn>()));
};

TEST_CASE("Remove element", "[LevelManager]") {
  LevelManager lm;
  REQUIRE(lm.addLevel("zoo", std::make_unique<Spawn>()));
  CHECK(lm.removeLevel("zoo"));
};

TEST_CASE("Remove null element", "[LevelManager]") {
  LevelManager lm;
  CHECK(!lm.removeLevel("boo"));
};

TEST_CASE("Change poiner to level", "[LevelManager]") {
  LevelManager lm;
  REQUIRE(lm.addLevel("goo", std::make_unique<Spawn>()));
  CHECK(lm.setLevel("goo"));
};

TEST_CASE("Change pointer to null level", "[LevelManager]") {
  LevelManager lm;
  CHECK(!lm.setLevel("loo"));
};

TEST_CASE("Change poiner to level and remove", "[LevelManager]") {
  LevelManager lm;
  REQUIRE(lm.addLevel("joo", std::make_unique<Spawn>()));
  REQUIRE(lm.setLevel("joo"));
  REQUIRE(lm.getPointer() == lm.getLevel("joo"));
  REQUIRE(lm.removeLevel("joo"));
  CHECK(!lm.getPointer());
};