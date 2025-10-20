#include "engine/core/Environment.hpp"
#include <filesystem>
#include <iostream>

namespace engine::core {

bool ensure_project_root() {
  namespace fs = std::filesystem;
  fs::path cwd = fs::current_path();

  std::cerr << "[Engine] Initial CWD: " << cwd << "\n";

  for (int i = 0; i < 10; ++i) { // try going up to 10 parent dirs
    if (fs::exists(cwd / "assets")) {
      std::cerr << "[Engine] Found assets in: " << cwd << "\n";
      fs::current_path(cwd);
      return true;
    }
    if (cwd.has_parent_path()) {
      cwd = cwd.parent_path();
    } else {
      break;
    }
  }

  std::cerr << "[Engine] Could not find 'assets/' in any parent directory.\n";
  return false;
}

} // namespace engine::core
