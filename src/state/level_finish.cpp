#include "level_finish.h"

#include <format>

#include "../level_config_loader.h"

void LevelFinish::init() {
  _font = asw::assets::load_font("assets/font/font.ttf", 18);
  _font_big = asw::assets::load_font("assets/font/font.ttf", 56);
  _font_extra_thicc = asw::assets::load_font("assets/font/font.ttf", 100);

  const auto configs = LevelConfigLoader::load_all("assets/levels/levels.json");
  const auto cfg_opt = LevelConfigLoader::for_level(configs, Game::level);
  if (cfg_opt) {
    _config = *cfg_opt;
  }

  _ui = asw::ui::Root();
  _ui.root.bg = asw::Color(50, 50, 50);
  _ui.root.transform.size = asw::Vec2f(1920, 1080);

  auto& btn_continue = _ui.root.add_child<asw::ui::Button>();
  btn_continue.transform.position = asw::Vec2f(200.0F, 800.0F);
  btn_continue.transform.size = asw::Vec2f(200.0F, 80.0F);
  btn_continue.font = _font;
  btn_continue.text = "Continue";
  btn_continue.on_click = [this]() {
    Game::level++;
    manager.set_next_scene(ProgramStates::Game);
  };
}

void LevelFinish::update(float dt) {
  _ui.update();
}

void LevelFinish::draw() {
  _ui.draw();

  asw::draw::text(_font_extra_thicc, "Carnage Report", {700, 20},
                  asw::Color(200, 0, 0));

  asw::draw::text(_font_big,
                  std::format("Total guests:{}", _config.total_guests),
                  {200, 200}, asw::Color(150, 150, 150));
  asw::draw::text(_font_big,
                  std::format("Total drowned:{}", Game::guests_died_falling),
                  {200, 260}, asw::Color(150, 0, 0));

  asw::draw::text(
      _font_big,
      std::format("Total killed by octopi:{}", Game::guests_died_enemies),
      {200, 320}, asw::Color(150, 0, 0));

  asw::draw::text(_font_big,
                  std::format("Total rescued:{}", Game::guests_rescued),
                  {200, 380}, asw::Color(0, 150, 0));

  asw::draw::text(_font_big, std::format("Final cash:{}", Game::money),
                  {200, 440}, asw::Color(0, 150, 0));

  const float percent = _config.total_guests > 0
                            ? (static_cast<float>(Game::guests_rescued) /
                               static_cast<float>(_config.total_guests)) *
                                  100.0F
                            : 0.0F;

  const auto percent_color =
      asw::Color(static_cast<uint8_t>(200 * (1.0F - percent / 100.0F)),
                 static_cast<uint8_t>(200 * (percent / 100.0F)), 50);

  asw::draw::text(_font_extra_thicc, std::format("{:.1f}%", percent),
                  {1200, 300}, percent_color);

  asw::draw::text(_font, "of guests survived.", {1250, 420}, percent_color);
}
