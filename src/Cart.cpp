#include "Cart.h"

Cart::Cart(int x, int y) {
  this->x = x;
  this->y = y;
  cart = asw::assets::load_texture("assets/images/tiles/car.png");
  accel = 0.0f;
  spin = 0.0f;
  x_velocity = -0;
  y_velocity = -0;
  is_cart = true;
}

void Cart::update() {
  accel += 0.02f;

  if (accel > 0.4f) {
    spin += 0.1f + (accel * 0.1f);
  }

  x_velocity += accel * -4;
  y_velocity += accel * -4;
  x += x_velocity;
  y += y_velocity;
}

void Cart::draw() const {
  asw::draw::rotate_sprite(cart, asw::Vec2<float>(x, y), spin);
}
