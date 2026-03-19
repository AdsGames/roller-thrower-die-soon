#pragma once

#include <asw/asw.h>
#include <array>

enum class TileType {
  Grass = 0,
  Path = 1,
  Entrance = 2,
  Win = 3,
  // Directional path tiles - set guest direction when walked on
  DirectionalNorth = 4,
  DirectionalEast = 5,
  DirectionalSouth = 6,
  DirectionalWest = 7,
  Water = 8,
  Umbrella = 9,
  Coaster = 10,
};

class Tile {
 public:
  Tile(const asw::Vec2f& position, TileType type);

  void update(float dt) { frame_counter += dt; }
  void draw() const;

  const asw::Vec2f& get_position() const { return position; }
  const asw::Vec2f& get_iso_position() const { return iso_position; }

  TileType get_type() const { return type; }

  // Check if x and y are in tile
  bool colliding(const asw::Vec2f& pos) const;

 private:
  constexpr static float FRAMES_PER_SECOND = 3.0F;

  asw::Texture sprite;
  asw::Texture grid;
  std::array<asw::Texture, 4> spritesheet_water;

  asw::Vec2f position;
  asw::Vec2f iso_position;
  TileType type;
  float frame_counter{0};
};
