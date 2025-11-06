#include "GameConfig.hpp"
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("GameConfig constants are valid", "[config]") {
  REQUIRE(GameConfig::cLogicalWidth > 0);
  REQUIRE(GameConfig::cLogicalHeight > 0);
  REQUIRE(GameConfig::cPlayerSpeed > 0.0f);
  REQUIRE(GameConfig::cExpectedFrameRate > 0);
}
