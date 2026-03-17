#include "message.h"

#include <asw/asw.h>
#include <algorithm>

namespace {
asw::Font font;

struct MessageEntry {
  std::string message;
  float time_remaining_s;
};

std::vector<MessageEntry> messages;

}  // namespace

void Message::send_message(const std::string& message) {
  messages.insert(messages.begin(), {message, 5.0f});
}

void Message::load() {
  font = asw::assets::load_font("assets/font/font.ttf", 18);
}

void Message::update(float dt) {
  for (auto& message : messages) {
    message.time_remaining_s -= dt;
  }

  std::erase_if(messages, [](const MessageEntry& message) {
    return message.time_remaining_s <= 0.0f;
  });
}

void Message::clear() {
  messages.clear();
}

void Message::draw() {
  for (size_t i = 0; i < messages.size(); i++) {
    const float y = 1040.0F - (i * 20.0F);
    const auto position = asw::Vec2<float>(1500.0F, y);
    asw::draw::text(font, messages.at(i).message, position, asw::color::white);
  }
}
