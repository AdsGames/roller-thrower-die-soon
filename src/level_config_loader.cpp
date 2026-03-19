#include "level_config_loader.h"

#include <fstream>

#include <asw/asw.h>
#include <nlohmann/json.hpp>

std::vector<LevelConfig> LevelConfigLoader::load_all(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    asw::log::warn("LevelConfigLoader: could not open " + path);
    return {};
  }

  const auto json = nlohmann::json::parse(file);
  std::vector<LevelConfig> configs;

  for (const auto& entry : json["levels"]) {
    LevelConfig cfg;
    cfg.level_number   = entry["level_number"];
    cfg.total_guests   = entry["total_guests"];
    cfg.money_target   = entry["money_target"];
    cfg.tile_map_file  = entry["tile_map_file"];
    cfg.hidden_buttons = entry["hidden_buttons"].get<std::vector<std::string>>();
    configs.push_back(std::move(cfg));
  }

  return configs;
}

std::optional<LevelConfig> LevelConfigLoader::for_level(
    const std::vector<LevelConfig>& configs,
    int level) {
  for (const auto& cfg : configs) {
    if (cfg.level_number == level) {
      return cfg;
    }
  }
  return std::nullopt;
}
