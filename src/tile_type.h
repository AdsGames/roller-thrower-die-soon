#pragma once

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
