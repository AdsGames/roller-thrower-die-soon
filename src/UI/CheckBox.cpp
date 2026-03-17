#include "CheckBox.h"

CheckBox::CheckBox() {
  // ctor
}
CheckBox::CheckBox(int newX, int newY, std::string newText, asw::Font newFont) {
  this->alpha = 255;

  this->checkbox_width = 20;

  this->image = nullptr;
  this->UIElement_font = newFont;

  this->x = newX;
  this->y = newY;

  this->text = newText;

  this->UIElement_font = UIElement_font;

  this->visible = true;
  this->active = true;

  this->mouse_released = false;
  this->old_mouse_down = false;
  this->hovering = false;

  this->checked = false;

  if (UIElement_font != nullptr) {
    const auto text_size = asw::util::get_text_size(UIElement_font, text);
    this->width = text_size.x + checkbox_width + padding_x;
    this->height = text_size.y;
  } else {
    this->width = 10;
    this->height = 10;
  }
}

void CheckBox::update() {
  mouse_released = false;

  if (active) {
    if (hovering && old_mouse_down &&
        !get_mouse_button(asw::input::MouseButton::Left)) {
      mouse_released = true;
      checked = !checked;
    }

    old_mouse_down =
        hovering && get_mouse_button(asw::input::MouseButton::Left);
    hovering = asw::input::mouse.position.x > x &&
               asw::input::mouse.position.x < x + getWidth() &&
               asw::input::mouse.position.y > y &&
               asw::input::mouse.position.y < y + getHeight();
  } else {
    hovering = false;
  }
}

void CheckBox::draw() {
  if (visible) {
    // Backdrop
    asw::draw::rect_fill(
        asw::Quad<float>(x, y, width + padding_x * 2, height + padding_y * 2),
        asw::Color(200 + 20 * hovering, 200 + 20 * hovering,
                   200 + 20 * hovering, alpha));

    asw::draw::rect(
        asw::Quad<float>(x, y, width + padding_x * 2, height + padding_y * 2),
        asw::Color(0, 0, 0, alpha));

    // Checkbox
    asw::draw::rect_fill(
        asw::Quad<float>(x + padding_x, y + padding_y, checkbox_width,
                         checkbox_width),
        asw::Color(200 + 20 * hovering, 200 + 20 * hovering,
                   200 + 20 * hovering, alpha));
    asw::draw::rect(
        asw::Quad<float>(x + padding_x, y + padding_y, checkbox_width,
                         checkbox_width),
        asw::Color(0, 0, 0, alpha));

    if (checked) {
      asw::draw::rect_fill(
          asw::Quad<float>(x + padding_x + 2, y + padding_y + 2,
                           checkbox_width - 4, checkbox_width - 4),
          asw::Color(0, 0, 0, alpha));
    }

    // Text
    if (UIElement_font != nullptr) {
      asw::draw::text(
          UIElement_font, text,
          asw::Vec2<float>(x + padding_x + checkbox_width + padding_x,
                           y + padding_y),
          asw::Color(0, 0, 0, alpha), asw::TextJustify::Left);
    }
  }
}
