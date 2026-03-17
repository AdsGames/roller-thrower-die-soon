#include "UIElement.h"

UIElement::UIElement(const std::string& id) : id(id) {}

void UIElement::toggleStatus() {
  visible = !visible;
  active = !active;
}

// Update
void UIElement::update() {
  hovering = active && _transform.contains(asw::input::mouse.position);
}

// True if hovering
bool UIElement::hover() const {
  return hovering;
}

// True if clicked
bool UIElement::clicked() const {
  return hovering &&
         asw::input::get_mouse_button_down(asw::input::MouseButton::Left);
}

bool UIElement::held() const {
  return hovering &&
         asw::input::get_mouse_button(asw::input::MouseButton::Left);
}

void UIElement::draw() const {
  if (!visible) {
    return;
  }

  // std::cout<<"How do I actually oop?\n";
  // Backdrop
  auto background = background_colour;

  if (hovering && !disabled_hover_effect) {
    background = background.lighten(0.2F);
  }

  asw::draw::rect_fill(_transform, background);
  asw::draw::rect(_transform, asw::color::black);

  // Text
  const auto padded_position = _transform.position + _padding;
  if (UIElement_font != nullptr && !text.empty()) {
    asw::draw::text(UIElement_font, text, padded_position, asw::color::black,
                    asw::TextJustify::Left);
  }

  // Image if avail
  if (image != nullptr) {
    asw::draw::sprite(image, padded_position);
  }
}
