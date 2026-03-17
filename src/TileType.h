#pragma once

#include <asw/asw.h>

class TileType {
 public:
  TileType(int id, asw::Texture image);

  asw::Texture image;
  int id;
};
