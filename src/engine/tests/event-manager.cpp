#include <memory>
#include <iostream>
#include <stdio.h>
#include <catch2/catch_all.hpp>
#include <events/event-manager.hpp>

TEST_CASE("Add event", "[EventManager]") {
  EventManager em;
  CHECK(em.addEvent("foo", std::make_unique<Event_t>(
    []() {std::cout << "Hello, World!\n"; }, 1, false)));
};

TEST_CASE("Add an event with the same ID", "[EventManager]") {
  EventManager em;
  REQUIRE(em.addEvent("boo", std::make_unique<Event_t>(
    []() {std::cout << "Hello, World!\n"; }, 1, false)));
  CHECK(!em.addEvent("boo", std::make_unique<Event_t>(
    []() {std::cout << "Hello, World!\n"; }, 1, false)));
};

TEST_CASE("Remove event", "[EventManager]") {
  EventManager em;
  REQUIRE(em.addEvent("zoo", std::make_unique<Event_t>(
    []() {std::cout << "Hello, World!\n"; }, 1, false)));
  CHECK(em.removeEvent("zoo"));
};

TEST_CASE("Remove a null event", "[EventManager]") {
  EventManager em;
  CHECK(!em.removeEvent("goo"));
};

TEST_CASE("Get pointer to event", "[EventManager]") {
  EventManager em;
  REQUIRE(em.addEvent("loo", std::make_unique<Event_t>(
    []() {std::cout << "Hello, World!\n"; }, 1, false)));
  CHECK(em.getEvent("loo"));
};

TEST_CASE("Get pointer to null event", "[EventManager]") {
  EventManager em;
  CHECK(!em.getEvent("xoo"));
};      