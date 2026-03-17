#pragma once

#include "UIElement.h"

class CheckBox : public UIElement {
 public:
  CheckBox();
  CheckBox(int, int, std::string, asw::Font);
  virtual ~CheckBox() = default;

  void update() override;
  void draw() override;
  bool getChecked() override { return checked; }

 private:
  int checkbox_width = 20;
  bool checked;
};
