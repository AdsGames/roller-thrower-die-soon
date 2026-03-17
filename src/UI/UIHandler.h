#pragma once

#include <string>
#include <vector>

#include "../globals.h"
#include "UIElement.h"

// class UIElement;

class UIHandler {
 public:
  UIHandler() {};
  virtual ~UIHandler() {};
  void addElement(UIElement* newUIElement);
  void draw();
  void update();
  bool isHovering();
  UIElement* getElementByText(std::string);
  UIElement* getElementById(std::string);

  std::vector<UIElement*> getUIElements() { return ui_elements; }

  void createButton(int x, int y, std::string newText, asw::Font newFont);
  void createAnchoredButton(std::string, asw::Font, std::string, bool);
  void createAnchoredButton(std::string,
                            asw::Font,
                            std::string,
                            std::string,
                            bool);

 private:
  std::vector<UIElement*> ui_elements;
};
