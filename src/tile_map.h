#pragma once

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <asw/asw.h>

#include "tile.h"

struct LevelLoadResult {
  std::vector<std::pair<int, int>> enemy_spawn_positions;
};

class TileMap {
 public:
  LevelLoadResult load_from_file(const std::string& path);
  void clear();

  bool can_place_tile(const asw::Vec2f& pos) const;

  void update(float dt);
  void draw() const;
  void draw_coasters() const;

  const std::vector<Tile>& tiles() const { return _tiles; }
  std::vector<Tile>& tiles() { return _tiles; }

  std::optional<asw::Vec2f> find_entrance_iso_pos() const;
  std::vector<asw::Vec2f> find_coaster_iso_positions() const;

 private:
  std::vector<Tile> _tiles;
};
