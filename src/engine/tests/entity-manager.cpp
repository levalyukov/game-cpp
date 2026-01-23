#include <memory>
#include <catch2/catch_all.hpp>
#include <entity/entity-manager.hpp>
#include <entity/entity.hpp>

/*<!-- Imitation of the entity class -->*/
class Ritchie : public Entity {
	public:
    inline void update(sf::RenderWindow& window, sf::Event& event) override {};
    inline sf::Sprite& getSprite(void) const override {
      sf::Sprite sprite;
      return sprite;
    };
};
/*<!-- ----------------------------- -->*/

TEST_CASE("Add entity", "[EntityManager]") {
  EntityManager em;
  REQUIRE(em.addEntity("boo", std::make_unique<Ritchie>()));
  CHECK(em.getEntity("boo"));
};

TEST_CASE("Add an entity with the same ID", "[EntityManager]") {
  EntityManager em;
  REQUIRE(em.addEntity("roo", std::make_unique<Ritchie>()));
  CHECK(!em.addEntity("roo", std::make_unique<Ritchie>()));
};

TEST_CASE("Remove entity", "[EntityManager]") {
  EntityManager em;
  REQUIRE(em.addEntity("roo", std::make_unique<Ritchie>()));
  REQUIRE(em.getEntity("roo"));
  REQUIRE(em.removeEntity("roo"));
  CHECK(!em.getEntity("roo"));
};

TEST_CASE("Delete a non-existing entity", "[EntityManager]") {
  EntityManager em;
  CHECK(!em.removeEntity("loo"));
};

TEST_CASE("Get null entity", "[EntityManager]") {
	EntityManager em;
	CHECK(!em.getEntity("foo"));
};