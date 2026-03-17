#include "Options.h"

void Options::init() {
  font = asw::assets::load_font("assets/font/font.ttf", 18);
  font_big = asw::assets::load_font("assets/font/font.ttf", 36);

  cursor = asw::assets::load_texture("assets/images/tweezersOpen.png");
  background = asw::assets::load_texture("assets/images/levelSelecT.png");
  load = asw::assets::load_texture("assets/images/loading.png");

  OptionsUI.addElement(new Button(400, 550, "Level 1", font_big));
  OptionsUI.addElement(new Button(600, 550, "Level 2", font_big));
  OptionsUI.addElement(new Button(800, 550, "Level 3", font_big));
  OptionsUI.addElement(new Button(1000, 550, "Level 4", font_big));
  OptionsUI.addElement(new Button(1200, 550, "Level 5", font_big));
  OptionsUI.addElement(new Button(1400, 550, "Level 6", font_big));
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

  if (OptionsUI.getElementByText("Level 1")->clicked()) {
    game::level = 1;
    manager.set_next_scene(ProgramStates::Game);
  }

  if (OptionsUI.getElementByText("Level 2")->clicked()) {
    game::level = 2;
    manager.set_next_scene(ProgramStates::Game);
  }

  if (OptionsUI.getElementByText("Level 3")->clicked()) {
    game::level = 3;
    manager.set_next_scene(ProgramStates::Game);
  }

  if (OptionsUI.getElementByText("Level 4")->clicked()) {
    game::level = 4;
    manager.set_next_scene(ProgramStates::Game);
  }

  if (OptionsUI.getElementByText("Level 5")->clicked()) {
    game::level = 5;
    manager.set_next_scene(ProgramStates::Game);
  }

  if (OptionsUI.getElementByText("Level 6")->clicked()) {
    game::level = 6;
    manager.set_next_scene(ProgramStates::Game);
  }

  OptionsUI.update();
}
