#include "cart.h"

Cart::Cart(const asw::Vec2f& position) {
  _position = position;
  _cart = asw::assets::load_texture("assets/images/tiles/car.png", "cart");
  _is_cart = true;
}

void Cart::update(float dt) {
  _accel += 0.02F;

  if (_accel > MAX_ACCEL) {
    _spin += 0.1F + (_accel * 0.1F);
  }

  _velocity += asw::Vec2f(_accel, _accel) * -4.0F;
  _position += _velocity;
}

void Cart::draw() const {
  asw::draw::rotate_sprite(_cart, _position, _spin);
}
