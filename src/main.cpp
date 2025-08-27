#include "Game.hpp"
#include "engine/ecs/ComponentManager.hpp"
#include <array>
#include <print>

int main(int argc, char *argv[]) {

  engine::ecs::ComponentArray<std::string> test;
  test.initialize();
  test.print();
  std::println("Removing entityId 1");
  test.remove(1);
  std::println("Adding entityId 4 and data 'e' ");
  test.add(4, "e");
  std::println("Removing entityId 0");
  test.remove(0);
  std::println("Adding entityId 5 and data 'f' ");
  test.add(5, "f");

  // Game game;
  // game.run();
  std::println("Success");
  return 0;
}
