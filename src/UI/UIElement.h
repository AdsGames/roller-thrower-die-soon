#pragma once

#include <asw/asw.h>
#include <string>

// #include "Button.h"
#include "../tools.h"

class UIElement {
 public:
  // Constructor
  UIElement();
  UIElement(int, int, std::string, asw::Font);
  UIElement(int, int, std::string, std::string, asw::Font);

  virtual ~UIElement() = default;

  // Getters
  int getX() { return x; }
  int getY() { return y; }

  std::string getText() { return text; }
  std::string getId() { return id; }

  void setDefaults();
  void setVisibility(bool newVisible) { visible = newVisible; }
  void toggleVisibility();
  void toggleStatus();
  void setTransparency(float newAlpha) { alpha = newAlpha; }
  void setBitmapRotationAngle(float newRotation) {
    bitmap_rotation_angle = newRotation;
  }
  void setX(int newX) { x = newX; }
  void setTextColour(asw::Color newColour) { text_colour = newColour; }
  void setBackgroundColour(asw::Color newColour) {
    background_colour = newColour;
  }
  void setCellFillTransparent(bool n) { transparent_cell_fill = n; }
  void setStatus(bool newStatus) {
    visible = newStatus;
    active = newStatus;
  }
  void setJustification(int newJustification) {
    justification = newJustification;
  }
  void setActive(bool n) { active = n; }

  int getWidth() { return width + padding_x * 2; }
  int getHeight() { return height + padding_y * 2; }
  int getPaddingX() { return padding_x; }
  int getPaddingY() { return padding_y; }
  int getRightX() { return x + getWidth(); }
  void setPadding(int padding_x, int padding_y) {
    this->padding_x = padding_x;
    this->padding_y = padding_y;
  }
  // Setters
  void setPosition(int x, int y) {
    this->x = x;
    this->y = y;
  }
  void setSize(int width, int height) {
    this->width = width;
    this->height = height;
  }
  void setText(std::string text) { this->text = text; }
  void setId(std::string id) { this->id = id; }
  void setImage(asw::Texture image);
  void setFont(asw::Font font);
  void setVisibleBackground(bool b) { visible_background = b; }
  void setWidth(int newWidth) { width = newWidth; }
  void setHeight(int newHeight) { height = newHeight; }
  void setOutlineThickness(int newThickness) {
    outline_thickness = newThickness;
  }
  void setDisableHoverEffect(bool b) { disabled_hover_effect = b; }

  bool mouseReleased();
  bool hover();
  bool clicked();
  bool held();

  virtual bool getChecked() { return false; }

  virtual void update();

  virtual void draw();

 protected:
  // Variables
  int x;
  int y;
  int width;
  int height;

  int padding_x;
  int padding_y;

  float bitmap_rotation_angle;

  bool hovering;
  bool old_mouse_down;
  bool mouse_released;
  bool visible_background;

  int outline_thickness;

  float alpha;

  int justification;

  // Frick you
  asw::Color text_colour;
  asw::Color background_colour;

  // Inactive cannot be clicked/hovered
  // Invisible cannot be seen
  // Disabled is both
  bool visible;
  bool active;

  bool transparent_cell_fill;
  bool disabled_hover_effect;

  asw::Texture image;

  // Font
  asw::Font UIElement_font;

  std::string text;
  std::string id;

 private:
};
