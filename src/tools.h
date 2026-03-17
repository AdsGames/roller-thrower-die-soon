/**
 * TOOLS
 * Allan Legemaate
 * 05/05/2017
 **/
#pragma once

#include <asw/asw.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class tools {
 public:
  // Convert char to float
  static float string_to_float(std::string newChar);
  static void abort_on_error(std::string message, std::string title);
  static int convertStringToInt(std::string);

  static int get_text_offset_x(asw::Font newFont, std::string newText);
  static int get_text_offset_y(asw::Font newFont, std::string newText);
  static int get_text_width(asw::Font newFont, std::string newText);
  static int get_text_height(asw::Font newFont, std::string newText);
  static bool clicked(int, int, int, int);

  // Clamp values
  template <class T>
  static T clamp(T min_val, T max_val, T value) {
    if (value < min_val) {
      return min_val;
    }

    if (value > max_val) {
      return max_val;
    }

    return value;
  }

  // Clamp values
  template <class T>
  static T negative_clamp_thing(T min_val, T max_val, T value) {
    if (value < min_val) {
      return min_val + -1 * value;
    }

    if (value > max_val) {
      return max_val - value;
    }

    return value;
  }

  // Function to check for collision
  template <class T>
  static bool collision(T xMin1,
                        T xMax1,
                        T xMin2,
                        T xMax2,
                        T yMin1,
                        T yMax1,
                        T yMin2,
                        T yMax2) {
    return static_cast<bool>(xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 &&
                             yMin2 < yMax1);
  }
};
