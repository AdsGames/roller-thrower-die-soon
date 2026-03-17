#include "UIHandler.h"

#include <algorithm>

#include "button.h"

bool UIHandler::isHovering() const {
  return std::ranges::any_of(
      ui_elements,
      [](const std::shared_ptr<UIElement>& elem) { return elem->hover(); });
}

//
// if buttons.press(){
//
//    use Allan.radiostation();
//
//    if(bug){
//        bug.stop();
//    }
//    if(goingto.crash()){
//        dont();
//    }
//
//
//}

std::shared_ptr<UIElement> UIHandler::getElementById(const std::string& id) {
  for (auto& elem : ui_elements) {
    if (elem->getId() == id) {
      return elem;
    }
  }

  asw::log::warn("UIHandler: no element with id '{}'", id);
  return nullptr;
}

void UIHandler::draw() const {
  for (const auto& elem : ui_elements) {
    elem->draw();
  }
}

void UIHandler::update() {
  for (auto& elem : ui_elements) {
    elem->update();
  }
}
