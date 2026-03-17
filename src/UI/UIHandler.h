#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "../globals.h"
#include "UIElement.h"

class UIHandler {
 public:
  UIHandler() = default;

  template <typename T, typename... Args>
    requires std::derived_from<T, UIElement>
  T& createElement(Args&&... args) {
    auto elem = std::make_shared<T>(std::forward<Args>(args)...);
    T& ref = *elem;
    ui_elements.push_back(std::move(elem));
    return ref;
  }

  bool isHovering() const;
  void draw() const;
  void update();

  std::shared_ptr<UIElement> getElementById(const std::string& id);

 private:
  std::vector<std::shared_ptr<UIElement>> ui_elements;
};
