#pragma once

#include <asw/asw.h>
#include "tools.h"

class Tile {
 public:
  Tile(int x, int y, int type);

  void draw();
  int getX() const { return x; }
  int getY() const { return y; }
  int getIsoX() const { return iso_x; }
  int getIsoY() const { return iso_y; }
  void setType(int type) { this->type = type; }
  int getType() const { return type; }

  // Check if x and y are in tile
  bool colliding(int x, int y, int width = 0, int height = 0) const;
  bool colliding_tight(int x, int y, int width = 0, int height = 0) const;
  bool colliding_loose(int x, int y, int width = 0, int height = 0) const;
  bool colliding_water(int x, int y, int width = 0, int height = 0) const;

 private:
  asw::Texture sprite;
  asw::Texture grid;
  asw::Texture spritesheet_Water[4];

  int frame = 0;
  int x;
  int y;
  int type;
  int iso_x;
  int iso_y;
};
