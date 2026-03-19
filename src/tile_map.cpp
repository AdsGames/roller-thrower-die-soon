#include "tile_map.h"

#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

LevelLoadResult TileMap::load_from_file(const std::string& path) {
  LevelLoadResult result;
  std::string line;
  std::ifstream file(path.c_str());

  int i = 0;

  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::istringstream buf(line);
      const std::istream_iterator<std::string> beg(buf);
      const std::istream_iterator<std::string> end;
      const std::vector<std::string> tokens(beg, end);

      const int joffset = 12;
      int j = 0;

      for (const auto& s : tokens) {
        if (s == "100") {
          result.enemy_spawn_positions.emplace_back(i, j - joffset);
          _tiles.emplace_back(asw::Vec2f(i, j - joffset), TileType::Grass);
        } else {
          _tiles.emplace_back(asw::Vec2f(i, j - joffset),
                              static_cast<TileType>(std::stoi(s)));
        }
        j++;
      }
      i++;
    }
    file.close();
  }

  return result;
}

void TileMap::clear() {
  _tiles.clear();
}

bool TileMap::can_place_tile(const asw::Vec2f& pos) const {
  for (const auto& tile : _tiles) {
    const auto& tile_pos = tile.get_position();
    if (pos.x == tile_pos.x && pos.y == tile_pos.y) {
      if (tile.get_type() == TileType::Water ||
          tile.get_type() == TileType::Entrance ||
          tile.get_type() == TileType::Umbrella ||
          tile.get_type() == TileType::Win) {
        return false;
      }
    }
  }
  return true;
}

void TileMap::update(float dt) {
  for (auto& tile : _tiles) {
    tile.update(dt);
  }
}

void TileMap::draw() const {
  for (const auto& tile : _tiles) {
    if (tile.get_type() != TileType::Coaster) {
      tile.draw();
    }
  }
}

void TileMap::draw_coasters() const {
  for (const auto& tile : _tiles) {
    if (tile.get_type() == TileType::Coaster) {
      tile.draw();
    }
  }
}

std::optional<asw::Vec2f> TileMap::find_entrance_iso_pos() const {
  for (const auto& tile : _tiles) {
    if (tile.get_type() == TileType::Entrance) {
      return tile.get_iso_position();
    }
  }
  return std::nullopt;
}

std::vector<asw::Vec2f> TileMap::find_coaster_iso_positions() const {
  std::vector<asw::Vec2f> positions;
  for (const auto& tile : _tiles) {
    if (tile.get_type() == TileType::Coaster) {
      positions.push_back(tile.get_iso_position());
    }
  }
  return positions;
}
