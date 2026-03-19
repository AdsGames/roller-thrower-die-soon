#pragma once

#include <string>
#include <vector>

struct LevelConfig {
  int level_number{1};
  int total_guests{10};
  int money_target{0};
  std::string tile_map_file;
  // Button IDs that should be hidden (toggleStatus) for this level
  std::vector<std::string> hidden_buttons;
};
