#pragma once

#include <optional>
#include <string>
#include <vector>

#include "level_config.h"

class LevelConfigLoader {
 public:
  static std::vector<LevelConfig> load_all(const std::string& path);
  static std::optional<LevelConfig> for_level(
      const std::vector<LevelConfig>& configs,
      int level);
};
