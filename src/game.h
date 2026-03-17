/**
 * GAME
 * A.D.S. Games
 * 05/05/2017
 **/
#pragma once

#include <asw/asw.h>
#include <memory>
#include <vector>

#include "state.h"

#include "cart.h"
#include "direction.h"
#include "tile_type.h"
#include "enemy.h"
#include "guest.h"
#include "particle.h"
#include "tile.h"
#include "ui/ui_handler.h"

enum class EditorTool {
  PlacePathEast  = 0,
  PlacePathSouth = 1,
  PlacePathWest  = 2,
  PlacePathNorth = 3,
  Grabber        = 4,
  PlaceCoaster   = 5,
};

namespace GameBalance {
constexpr int kPathCost     = 100;
constexpr int kCoasterCost  = 500;
constexpr int kUmbrellaGain = 10;
}  // namespace GameBalance

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
  void load_level(const std::string& filename);

  // Entities
  std::vector<Tile> gameTiles;
  std::vector<Guest> gameGuests;
  std::vector<Enemy> gameEnemies;
  std::vector<Particle> gameParticles;

  // UI
  UIHandler gameUI;

  // Guest selected by grabber
  std::unique_ptr<Guest> selectedGuest;

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
  asw::Texture tweezer;

  asw::Font font;
  asw::Font font_small;

  int frame;
  int guest_spawn;
  bool started;
  bool finished;
  int spawn_rate;
  float speed_g;
  EditorTool editor_tool;

  bool canPlaceTile(const asw::Vec2<float>& pos);
};
