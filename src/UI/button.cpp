#include "button.h"

Button::Button(int x,
               int y,
               std::string text,
               asw::Texture image,
               float newRotation) {
  setDefaults();

  // Naming schemes are frickin' hard
  this->image = image;
  this->bitmap_rotation_angle = newRotation;

  // Literally this
  this->x = x;
  this->y = y;
  this->text = text;
  this->UIElement_font = UIElement_font;

  if (image != nullptr) {
    this->width = image->w;
    this->height = image->h;
  } else {
    std::cout << "WARNING: Button " << text
              << " has been given a nullptr image!\n";
  }

  this->padding_x = 0;
  this->padding_y = 0;
}

Button::Button(int x, int y, std::string id, asw::Texture image) {
  setDefaults();

  // Naming schemes are frickin' hard
  this->image = image;
  this->bitmap_rotation_angle = 0.0f;

  // Literally this
  this->x = x;
  this->y = y;
  this->id = id;

  if (image != nullptr) {
    this->width = image->w;
    this->height = image->h;
  } else {
    std::cout << "WARNING: Button " << text
              << " has been given a nullptr image!\n";
  }

  this->padding_x = 2;
  this->padding_y = 2;
}

Button::Button(int x, int y, std::string text, asw::Font UIElement_font) {
  setDefaults();

  this->bitmap_rotation_angle = 0;
  // Literally this
  this->x = x;
  this->y = y;
  this->text = text;
  this->image = nullptr;
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
Button::Button(int x,
               int y,
               std::string text,
               std::string id,
               asw::Font UIElement_font) {
  setDefaults();

  this->bitmap_rotation_angle = 0;
  // Literally this
  this->id = id;
  this->x = x;
  this->y = y;
  this->text = text;
  this->image = nullptr;
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

Button::Button(int x,
               int y,
               std::string text,
               asw::Font UIElement_font,
               int newWidth,
               int newHeight) {
  this->bitmap_rotation_angle = 0;
  this->alpha = 255;

  setDefaults();

  // Literally this
  this->x = x;
  this->y = y;
  this->text = text;
  this->image = nullptr;
  this->UIElement_font = UIElement_font;

  this->width = newWidth;
  this->height = newHeight;
}

void Button::draw() {
  if (visible) {
    // Backdrop

    // This hover colour has more lines than the whole game loop
    const int new_r = tools::negative_clamp_thing(
        0, 255, (int)((background_colour.r * 255) + (40 * hovering)));
    const int new_g = tools::negative_clamp_thing(
        0, 255, (int)((background_colour.g * 255) + (40 * hovering)));
    const int new_b = tools::negative_clamp_thing(
        0, 255, (int)((background_colour.b * 255) + (40 * hovering)));

    auto hover_colour = asw::Color(new_r, new_g, new_b, alpha);

    if (disabled_hover_effect) {
      hover_colour = background_colour;
    }

    if (visible_background) {
      if (!transparent_cell_fill) {
        asw::draw::rect_fill(asw::Quad<float>(x, y, width + padding_x * 2,
                                              height + padding_y * 2),
                             hover_colour);
      }

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
      if (bitmap_rotation_angle == 0) {
        asw::draw::sprite(image,
                          asw::Vec2<float>(x + padding_x, y + padding_y));
      } else {
        asw::draw::rotate_sprite(image,
                                 asw::Vec2<float>(x + padding_x + (width / 2),
                                                  y + padding_y + (height / 2)),
                                 bitmap_rotation_angle);
      }
    }
  }
}
