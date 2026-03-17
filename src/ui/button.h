#pragma once

#include "ui_element.h"

class Button : public UIElement {
 public:
  Button() = default;
  Button(const std::string& id);
};
