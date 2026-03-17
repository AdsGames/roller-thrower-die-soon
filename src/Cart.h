#pragma once

#include <asw/asw.h>

#include "Guest.h"

class Cart : public Guest {
 public:
  Cart(const asw::Vec2<float>& position);

  void update(float dt) override;
  void draw() const override;

 private:
  constexpr static float MAX_ACCEL = 0.4F;

  float accel{0.0F};
  float spin{0.0F};
  asw::Texture cart;
};
