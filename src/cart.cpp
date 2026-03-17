#include "cart.h"

Cart::Cart(const asw::Vec2<float>& position) {
  this->position = position;
  cart = asw::assets::load_texture("assets/images/tiles/car.png", "cart");
  is_cart = true;
}

void Cart::update(float dt) {
  accel += 0.02F;

  if (accel > MAX_ACCEL) {
    spin += 0.1F + (accel * 0.1F);
  }

  velocity += asw::Vec2<float>(accel, accel) * -4.0F;
  position += velocity;
}

void Cart::draw() const {
  asw::draw::rotate_sprite(cart, position, spin);
}
