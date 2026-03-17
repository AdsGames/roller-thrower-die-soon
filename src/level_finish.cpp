#include "level_finish.h"

#include <format>

void LevelFinish::init() {
  font = asw::assets::load_font("assets/font/font.ttf", 18);
  font_big = asw::assets::load_font("assets/font/font.ttf", 56);
  font_extra_thicc = asw::assets::load_font("assets/font/font.ttf", 100);

  LevelFinishUI = UIHandler();
  auto& btn_continue = LevelFinishUI.createElement<Button>("continue");
  btn_continue.setPosition({200.0F, 800.0F});
  btn_continue.setFont(font);
  btn_continue.setText("Continue");
}

void LevelFinish::update(float dt) {
  LevelFinishUI.update();

  if (LevelFinishUI.getElementById("continue")->clicked()) {
    game::level = 4;
    manager.set_next_scene(ProgramStates::Options);
  }
}

void LevelFinish::draw() {
  asw::draw::clear_color(asw::Color(50, 50, 50));

  LevelFinishUI.draw();

  asw::draw::text(font_extra_thicc, "Carnage Report", asw::Vec2<float>(700, 20),
                  asw::Color(200, 0, 0), asw::TextJustify::Left);

  int total_guests = 123;

  if (game::level == 1) {
    total_guests = 10;
  }

  if (game::level == 2) {
    total_guests = 15;
  }

  if (game::level == 3) {
    total_guests = 70;
  }

  if (game::level == 4) {
    total_guests = 150;
  }

  if (game::level == 5 || game::level == 6) {
    total_guests = 200;
  }

  asw::draw::text(font_big, std::format("Total guests:{}", total_guests),
                  asw::Vec2<float>(200, 200), asw::Color(150, 150, 150),
                  asw::TextJustify::Left);
  asw::draw::text(font_big,
                  std::format("Total drowned:{}", game::guests_died_falling),
                  asw::Vec2<float>(200, 260), asw::Color(150, 0, 0),
                  asw::TextJustify::Left);
  asw::draw::text(
      font_big,
      std::format("Total killed by octopi:{}", game::guests_died_enemies),
      asw::Vec2<float>(200, 320), asw::Color(150, 0, 0),
      asw::TextJustify::Left);
  asw::draw::text(font_big,
                  std::format("Total rescued:{}", game::guests_rescued),
                  asw::Vec2<float>(200, 380), asw::Color(0, 150, 0),
                  asw::TextJustify::Left);
  asw::draw::text(font_big, std::format("Final cash:{}", game::money),
                  asw::Vec2<float>(200, 440), asw::Color(0, 150, 0),
                  asw::TextJustify::Left);

  float total_lived = game::guests_rescued;
  float percent = (total_lived / total_guests) * 100;

  asw::draw::text(font_extra_thicc, std::format("{:.1f}%", percent),
                  asw::Vec2<float>(1200, 300), asw::Color(200, 50, 50),
                  asw::TextJustify::Left);
  asw::draw::text(font, "of guests survived.", asw::Vec2<float>(1250, 420),
                  asw::Color(200, 50, 50), asw::TextJustify::Left);
}
