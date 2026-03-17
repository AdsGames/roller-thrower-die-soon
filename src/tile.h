#pragma once

#include <asw/asw.h>
#include <array>

#include "tile_type.h"

class Tile {
 public:
  Tile(const asw::Vec2<float>& position, TileType type);

  void update(float dt) { frame_counter += dt; }
  void draw() const;

  const asw::Vec2<float>& getPosition() const { return position; }

  const asw::Vec2<float>& getIsoPosition() const { return iso_position; }

  TileType getType() const { return type; }

  // Check if x and y are in tile
  bool colliding(const asw::Vec2<float>& pos) const;

 private:
  constexpr static float FRAMES_PER_SECOND = 3.0F;

  asw::Texture sprite;
  asw::Texture grid;
  std::array<asw::Texture, 4> spritesheet_water;

  asw::Vec2<float> position;
  asw::Vec2<float> iso_position;
  TileType type;
  float frame_counter{0};
};
