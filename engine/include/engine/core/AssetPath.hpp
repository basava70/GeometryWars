#pragma once
#include <cstdlib>
#include <filesystem>
#include <format>
#include <iostream>
#include <optional>
#include <string_view>

namespace engine::core {

/// \brief Resolve an asset path regardless of working directory.
/// \details Checks current dir, parent dir, and $ASSET_PATH environment
/// variable.
inline std::optional<std::filesystem::path>
resolve_asset_path(std::string_view relative_file) {
  namespace fs = std::filesystem;
  auto cwd = fs::current_path();

  if (fs::exists(cwd / "assets")) {
    return cwd / "assets" / relative_file;
  }
  if (fs::exists(cwd.parent_path() / "assets")) {
    return cwd.parent_path() / "assets" / relative_file;
  }
  if (const char *env = std::getenv("ASSET_PATH")) {
    fs::path env_path{env};
    if (fs::exists(env_path)) {
      return env_path / relative_file;
    }
  }

  std::cerr << std::format(
      "[Asset] Could not find '{}'. Tried:\n  - {}\n  - {}\n  - $ASSET_PATH\n",
      relative_file, (cwd / "assets").string(),
      (cwd.parent_path() / "assets").string());

  return std::nullopt;
}

} // namespace engine::core
