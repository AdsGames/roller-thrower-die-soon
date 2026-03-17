#include "UIElement.h"

// Defaults
UIElement::UIElement() {
  setDefaults();
}
void UIElement::setDefaults() {
  this->alpha = 255;
  this->background_colour = asw::Color(200, 200, 200, alpha);
  this->text_colour = asw::Color(0, 0, 0, alpha);
  this->x = 0;
  this->y = 0;
  this->width = 0;
  this->height = 0;
  this->text = "";
  this->UIElement_font = nullptr;
  this->hovering = false;
  this->old_mouse_down = false;
  this->mouse_released = false;
  this->visible = true;
  this->active = true;
  this->image = nullptr;
  this->padding_x = 10;
  this->padding_y = 10;
  this->id = "";
  this->visible_background = true;
  this->justification = 0;
  this->outline_thickness = 2;
  this->transparent_cell_fill = false;
  this->disabled_hover_effect = false;
}

UIElement::UIElement(int x, int y, std::string text, asw::Font UIElement_font) {
  setDefaults();
  // Literally this
  this->x = x;
  this->y = y;
  this->text = text;
  this->UIElement_font = UIElement_font;

  if (UIElement_font != nullptr) {
    const auto text_size = asw::util::get_text_size(UIElement_font, text);
    this->width = text_size.x;
    this->height = text_size.y;
  } else {
    this->width = 10;
    this->height = 10;
  }
}

UIElement::UIElement(int x,
                     int y,
                     std::string text,
                     std::string id,
                     asw::Font UIElement_font) {
  setDefaults();
  // Literally this
  this->x = x;
  this->y = y;
  this->text = text;
  this->id = id;
  this->UIElement_font = UIElement_font;

  if (UIElement_font != nullptr) {
    const auto text_size = asw::util::get_text_size(UIElement_font, text);
    this->width = text_size.x;
    this->height = text_size.y;
  } else {
    this->width = 10;
    this->height = 10;
  }
}

// Sets an image
void UIElement::setImage(asw::Texture image) {
  this->image = image;
  this->width = this->image->w;
  this->height = this->image->h;
}

// Set new font
void UIElement::setFont(asw::Font font) {
  this->UIElement_font = font;

  if (UIElement_font != nullptr) {
    const auto text_size = asw::util::get_text_size(UIElement_font, text);
    this->width = text_size.x;
    this->height = text_size.y;
  }
}
void UIElement::toggleVisibility() {
  visible = !visible;
}

void UIElement::toggleStatus() {
  visible = !visible;
  active = !active;
}

// Update
void UIElement::update() {
  mouse_released = false;

  if (active) {
    if (hovering && old_mouse_down &&
        !asw::input::get_mouse_button(asw::input::MouseButton::Left)) {
      mouse_released = true;
    }

    old_mouse_down =
        hovering && asw::input::get_mouse_button(asw::input::MouseButton::Left);
    hovering = asw::input::mouse.position.x > x &&
               asw::input::mouse.position.x < x + getWidth() &&
               asw::input::mouse.position.y > y &&
               asw::input::mouse.position.y < y + getHeight();
  } else {
    hovering = false;
  }
}

// True if hovering
bool UIElement::hover() {
  return hovering;
}

// True if clicked
bool UIElement::clicked() {
  return hovering &&
         asw::input::get_mouse_button_down(asw::input::MouseButton::Left);
}

bool UIElement::held() {
  return hovering &&
         asw::input::get_mouse_button(asw::input::MouseButton::Left);
}

void UIElement::draw() {
  if (visible) {
    // std::cout<<"How do I actually oop?\n";
    // Backdrop
    if (visible_background) {
      asw::draw::rect_fill(
          asw::Quad<float>(x, y, width + padding_x * 2, height + padding_y * 2),
          asw::Color(200 + 20 * hovering, 200 + 20 * hovering,
                     200 + 20 * hovering, alpha));
      asw::draw::rect(
          asw::Quad<float>(x, y, width + padding_x * 2, height + padding_y * 2),
          asw::Color(0, 0, 0, alpha));
    }

    // Text
    if (UIElement_font != nullptr) {
      if (justification == 0) {
        asw::draw::text(UIElement_font, text,
                        asw::Vec2<float>(x + padding_x, y + padding_y),
                        text_colour, asw::TextJustify::Left);
      }

      if (justification == 1) {
        int text_x;
        int text_y;

        text_x = x + padding_x + width / 2;
        text_y = y + padding_y -
                 (tools::get_text_height(UIElement_font, text) - height) / 2;

        asw::draw::text(
            UIElement_font, text,
            asw::Vec2<float>(text_x, text_y - tools::get_text_offset_y(
                                                  UIElement_font, text)),
            text_colour, asw::TextJustify::Center);
      }
    }

    // Image if avail
    if (image != nullptr) {
      asw::draw::sprite(image, asw::Vec2<float>(x + padding_x, y + padding_y));
    }
  }
}
