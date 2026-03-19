#pragma once

#include <asw/asw.h>
#include <string>
#include <vector>

class Message {
 public:
  static void update(float dt);
  static void draw();
  static void load();
  static void send_message(const std::string& message);
  static void clear();

 private:
  static asw::Font font;
};
