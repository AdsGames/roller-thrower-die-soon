#pragma once

#include "UIElement.h"

class Button : public UIElement {
 public:
  Button() = default;
  Button(const std::string& id);
};
