#pragma once

namespace engine::core {

/// \brief Ensure the current working directory points to the project root.
/// \details Searches upwards until an `assets/` directory is found and sets CWD
/// there. Returns true if successful.
bool ensure_project_root();

} // namespace engine::core
