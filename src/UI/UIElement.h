#pragma once

#include <asw/asw.h>
#include <string>

class UIElement {
 public:
  // Constructor
  UIElement() = default;
  UIElement(const std::string& id);

  virtual ~UIElement() = default;

  std::string getText() const { return text; }
  std::string getId() const { return id; }

  void toggleStatus();

  void setBackgroundColour(asw::Color newColour) {
    background_colour = newColour;
  }
  void setActive(bool n) { active = n; }
  void setPosition(const asw::Vec2<float>& pos) { _transform.position = pos; }
  void setFont(const asw::Font& font) { UIElement_font = font; }
  void setText(const std::string& newText) {
    text = newText;
    if (UIElement_font != nullptr) {
      const auto text_size = asw::util::get_text_size(UIElement_font, text);
      this->_transform.size =
          asw::Vec2<float>(text_size.x, text_size.y) + _padding * 2;
    }
  }
  void setTexture(const asw::Texture& texture) {
    image = texture;
    if (image != nullptr) {
      this->_transform.size =
          asw::Vec2<float>(image->w, image->h) + _padding * 2;
    }
  }

  void setDisableHoverEffect(bool b) { disabled_hover_effect = b; }

  bool hover() const;
  bool clicked() const;
  bool held() const;

  virtual void update();

  virtual void draw() const;

 protected:
  // Variables
  asw::Quad<float> _transform{0, 0, 0, 0};
  asw::Vec2<float> _padding{10, 10};

  float bitmap_rotation_angle{0.0F};

  bool hovering{false};

  // Frick you
  asw::Color background_colour{200, 200, 200, 255};

  // Inactive cannot be clicked/hovered
  // Invisible cannot be seen
  // Disabled is both
  bool visible{true};
  bool active{true};
  bool disabled_hover_effect{false};

  asw::Texture image{nullptr};

  // Font
  asw::Font UIElement_font{nullptr};

  std::string text;
  std::string id;
};
