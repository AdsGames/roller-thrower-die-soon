#pragma once

#include <string>
#include <vector>

#include "tools.h"

class Message {
 public:
  Message() = default;

  static void update();
  static void draw();
  static void load();
  static int message_count;
  static void sendMessage(std::string newMessage);
  static asw::Font font;
  static int time;
  static std::vector<std::string> messageList;
  static void clear();
};
