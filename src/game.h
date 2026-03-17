/**
 * GAME
 * A.D.S. Games
 * 05/05/2017
 **/
#pragma once

#include <vector>

#include <asw/asw.h>

#include "state.h"

#include "Cart.h"
#include "Enemy.h"
#include "Guest.h"
#include "Particle.h"
#include "Tile.h"
#include "UI/UIHandler.h"
#include "tools.h"

class game : public asw::scene::Scene<ProgramStates> {
 public:
  using asw::scene::Scene<ProgramStates>::Scene;

  // Override parent
  void init() override;
  void update(float dt) override;
  void draw() override;

  static int level;
  static int guests_rescued;
  static int guests_died_enemies;
  static int guests_died_falling;
  static int money;

 private:
  // Load map from text
  void load_level(std::string filename);

  // Entities
  std::vector<Tile> gameTiles;
  std::vector<Guest> gameGuests;
  std::vector<Enemy> gameEnemies;
  std::vector<Particle> gameParticles;

  // UI
  UIHandler gameUI;

  // Guest selected by grabber
  Guest* selectedGuest = nullptr;

  // Images
  asw::Texture tile;
  asw::Texture coaster;
  asw::Texture coaster_small;

  asw::Texture path[4];
  asw::Texture entrance_back;
  asw::Texture entrance_front;
  asw::Texture entrance_front_transparent;

  asw::Texture cursor_open;
  asw::Texture cursor_closed;
  asw::Texture path_hover;

  asw::Texture level_1_help;
  asw::Texture level_2_help;
  asw::Texture level_3_help;
  asw::Texture level_4_help;

  asw::Font font;
  asw::Font font_small;

  int frame = 0;
  int guest_spawn = 50;
  bool started = 0;
  bool finished = false;
  int spawn_rate = 16;
  float speed_g = 0.5f;
  bool canPlaceTile(int sullys, int nose);

  // Grabber info
  int old_mouse_x;
  int old_mouse_y;

  int editor_tool = 4;

  float x_velocity;
  float y_velocity;
};
