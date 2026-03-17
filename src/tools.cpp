#include "tools.h"

// Convert string to int
int tools::convertStringToInt(std::string newString) {
  int result;
  std::stringstream(newString) >> result;
  return result;
}

bool tools::clicked(int x_1, int x_2, int y_1, int y_2) {
  return (asw::input::get_mouse_button(asw::input::MouseButton::Left) &&
          x_1 < asw::input::mouse.position.x &&
          x_2 > asw::input::mouse.position.x &&
          y_1 < asw::input::mouse.position.y &&
          y_2 > asw::input::mouse.position.y);
}

// A function to streamline error reporting in file loading
void tools::abort_on_error(std::string message, std::string title) {
  asw::util::abort_on_error(message);
}

int tools::get_text_offset_x(asw::Font newFont, std::string newText) {
  // int text_width = 0;
  // int text_height = 0;
  // int text_offset_x;
  // int text_offset_y;

  // al_get_text_dimensions(newFont, newText.c_str(), &text_offset_x,
  //                        &text_offset_y, &text_width, &text_height);

  return 0;
}

int tools::get_text_offset_y(asw::Font newFont, std::string newText) {
  // int text_width = 0;
  // int text_height = 0;
  // int text_offset_x;
  // int text_offset_y;

  // al_get_text_dimensions(newFont, newText.c_str(), &text_offset_x,
  //                        &text_offset_y, &text_width, &text_height);

  return 0;
}

int tools::get_text_width(asw::Font newFont, std::string newText) {
  return asw::util::get_text_size(newFont, newText).x;
}

int tools::get_text_height(asw::Font newFont, std::string newText) {
  return asw::util::get_text_size(newFont, newText).y;
}

// Convert char to float
float tools::string_to_float(std::string newChar) {
  float number = 0.0f;
  int sign = 1;

  // Parse string
  // Negative
  if (newChar[0] == '-') {
    sign = -1;
    newChar = newChar.substr(1, newChar.length());
  }

  // Location of decimal
  int decimal_loc = newChar.length();

  for (unsigned int i = 0; i < newChar.length(); i++) {
    if (newChar[i] == '.') {
      decimal_loc = i;
      newChar =
          newChar.substr(0, i) + newChar.substr(i + 1, newChar.length() - i);
    }
  }

  // Numbers
  for (unsigned int i = 0; i < newChar.length(); i++) {
    int tempNumber = int(newChar[i]) - 48;
    number += tempNumber * pow(10, (newChar.length()) - (i + 1));
  }

  return (number / float(pow(10, newChar.length() - decimal_loc))) * sign;
}
