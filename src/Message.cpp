#include "Message.h"

int Message::message_count = 0;
int Message::time = 100;
asw::Font Message::font;
std::vector<std::string> Message::messageList;

void Message::sendMessage(std::string newMessage) {
  messageList.insert(messageList.begin(), newMessage);
  time = 60;
}

void Message::load() {
  font = asw::assets::load_font("assets/font/font.ttf", 18);
}

void Message::update() {
  time--;

  if (time <= 0) {
    time = 60;

    if (messageList.size() > 0)
      messageList.erase(messageList.begin());
  }
}
void Message::clear() {
  messageList.clear();
}

void Message::draw() {
  if (messageList.size() > 0)
    for (unsigned int i = 0; i < messageList.size(); i++)
      asw::draw::text(font, messageList.at(i),
                      asw::Vec2<float>(1500, 1040 - (i * 20)),
                      asw::Color(255, 255, 255), asw::TextJustify::Left);
}
