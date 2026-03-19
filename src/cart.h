#pragma once

#include <asw/asw.h>

#include "guest.h"

class Cart : public Guest {
 public:
  Cart(const asw::Vec2f& position);

  void update(float dt) override;
  void draw() const override;

 private:
  constexpr static float MAX_ACCEL = 0.4F;

  float _accel{0.0F};
  float _spin{0.0F};
  asw::Texture _cart;
};
