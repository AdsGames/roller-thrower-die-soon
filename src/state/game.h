/**
 * GAME
 * A.D.S. Games
 * 05/05/2017
 **/
#pragma once

#include <asw/asw.h>
#include <memory>

#include "state.h"

#include "../collision_system.h"
#include "../entity_manager.h"
#include "../game_balance.h"
#include "../guest.h"
#include "../level_config.h"
#include "../level_config_loader.h"
#include "../level_editor.h"
#include "../tile_map.h"

class Game : public asw::scene::Scene<ProgramStates> {
 public:
  using asw::scene::Scene<ProgramStates>::Scene;

  void init() override;
  void update(float dt) override;
  void draw() override;

  static int level;
  static int guests_rescued;
  static int guests_died_enemies;
  static int guests_died_falling;
  static int money;

 private:
  // Subsystems
  TileMap _tile_map;
  EntityManager _entities;
  LevelEditor _level_editor;
  asw::ui::Root _ui;

  // UI button references for dynamic updates
  asw::ui::Button* _btn_path_0{nullptr};
  asw::ui::Button* _btn_path_1{nullptr};
  asw::ui::Button* _btn_path_2{nullptr};
  asw::ui::Button* _btn_path_3{nullptr};
  asw::ui::Button* _btn_coaster{nullptr};
  asw::ui::Button* _btn_finish{nullptr};
  asw::ui::Button* _btn_start_game{nullptr};
  asw::ui::Label* _lbl_money{nullptr};
  asw::ui::Label* _lbl_remaining_guests{nullptr};

  bool _fast_forward{false};
  bool _show_path_costs{true};
  bool _show_coaster_cost{true};

  // Guest held by grabber tool
  std::unique_ptr<Guest> _selected_guest;

  // Images
  asw::Texture _coaster;
  asw::Texture _coaster_small;
  asw::Texture _path[4];
  asw::Texture _entrance_back;
  asw::Texture _entrance_front;
  asw::Texture _entrance_front_transparent;
  asw::Texture _cursor_open;
  asw::Texture _cursor_closed;
  asw::Texture _path_hover;
  asw::Texture _level_1_help;
  asw::Texture _level_2_help;
  asw::Texture _level_3_help;
  asw::Texture _level_4_help;
  asw::Texture _tweezer;

  LevelConfig _current_level_config;

  float _spawn_timer;
  float _spawn_rate;
  int _guest_spawn;
  bool _started;
  bool _finished;
  float _speed_g;
};
