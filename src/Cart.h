#pragma once

#include <asw/asw.h>

#include "Guest.h"

class Cart : public Guest {
 public:
  Cart(int x, int y);

  void update() override;
  void draw() const override;

 private:
  float accel;
  float spin;
  asw::Texture cart;
};
