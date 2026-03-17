#include "Options.h"

void Options::init() {
  font = asw::assets::load_font("assets/font/font.ttf", 18);
  font_big = asw::assets::load_font("assets/font/font.ttf", 36);

  cursor = asw::assets::load_texture("assets/images/tweezersOpen.png");
  background = asw::assets::load_texture("assets/images/levelSelecT.png");
  load = asw::assets::load_texture("assets/images/loading.png");

  auto& btn_level_1 = OptionsUI.createElement<Button>("level_1");
  btn_level_1.setPosition({400.0F, 550.0F});
  btn_level_1.setFont(font_big);
  btn_level_1.setText("Level 1");

  auto& btn_level_2 = OptionsUI.createElement<Button>("level_2");
  btn_level_2.setPosition({600.0F, 550.0F});
  btn_level_2.setFont(font_big);
  btn_level_2.setText("Level 2");

  auto& btn_level_3 = OptionsUI.createElement<Button>("level_3");
  btn_level_3.setPosition({800.0F, 550.0F});
  btn_level_3.setFont(font_big);
  btn_level_3.setText("Level 3");

  auto& btn_level_4 = OptionsUI.createElement<Button>("level_4");
  btn_level_4.setPosition({1000.0F, 550.0F});
  btn_level_4.setFont(font_big);
  btn_level_4.setText("Level 4");

  auto& btn_level_5 = OptionsUI.createElement<Button>("level_5");
  btn_level_5.setPosition({1200.0F, 550.0F});
  btn_level_5.setFont(font_big);
  btn_level_5.setText("Level 5");

  auto& btn_level_6 = OptionsUI.createElement<Button>("level_6");
  btn_level_6.setPosition({1400.0F, 550.0F});
  btn_level_6.setFont(font_big);
  btn_level_6.setText("Level 6");
}

void Options::draw() {
  asw::draw::clear_color(asw::Color(50, 50, 50));

  asw::draw::sprite(background, asw::Vec2<float>(0, 0));

  OptionsUI.draw();

  asw::draw::sprite(cursor,
                    asw::Vec2<float>(asw::input::mouse.position.x - 8,
                                     asw::input::mouse.position.y - 56));
}

void Options::update(float dt) {
  if (asw::input::get_key_down(asw::input::Key::Escape)) {
    manager.set_next_scene(ProgramStates::Menu);
  }

  if (OptionsUI.getElementById("level_1")->clicked()) {
    game::level = 1;
    manager.set_next_scene(ProgramStates::Game);
  }

  if (OptionsUI.getElementById("level_2")->clicked()) {
    game::level = 2;
    manager.set_next_scene(ProgramStates::Game);
  }

  if (OptionsUI.getElementById("level_3")->clicked()) {
    game::level = 3;
    manager.set_next_scene(ProgramStates::Game);
  }

  if (OptionsUI.getElementById("level_4")->clicked()) {
    game::level = 4;
    manager.set_next_scene(ProgramStates::Game);
  }

  if (OptionsUI.getElementById("level_5")->clicked()) {
    game::level = 5;
    manager.set_next_scene(ProgramStates::Game);
  }

  if (OptionsUI.getElementById("level_6")->clicked()) {
    game::level = 6;
    manager.set_next_scene(ProgramStates::Game);
  }

  OptionsUI.update();
}
