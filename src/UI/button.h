#pragma once

#include "UIElement.h"

class Button : public UIElement {
 public:
  Button(int x, int y, std::string text, asw::Font button_font);
  Button(int x, int y, std::string text, std::string id, asw::Font button_font);
  Button(int x, int y, std::string text, asw::Font button_font, int w, int h);
  Button(int x,
         int y,
         std::string text,
         asw::Texture newImage,
         float newRotation);
  Button(int x, int y, std::string id, asw::Texture newImage);

  Button() = default;
  virtual ~Button() = default;

  void setWidth(int newWidth) { width = newWidth; }
  void setHeight(int newHeight) { height = newHeight; }

  void draw() override;
};
