#include "game.h"

#include <algorithm>
#include <format>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "UI/button.h"

int game::level = 1;
int game::guests_died_enemies = 0;
int game::guests_died_falling = 0;
int game::guests_rescued = 0;
int game::money = 0;

// Constructor
void game::init() {
  Guest::speed = 0.5;
  game::guests_died_enemies = 0;
  game::guests_died_falling = 0;
  game::guests_rescued = 0;
  game::money = 0;

  frame = 0;
  started = false;
  finished = false;
  spawn_rate = 16;
  speed_g = 0.5F;
  editor_tool = EditorTool::Grabber;

  selectedGuest = nullptr;

  // Init vars
  Message::load();
  Message::clear();

  gameTiles.clear();
  gameGuests.clear();
  gameEnemies.clear();
  gameParticles.clear();

  if (level == 1) {
    load_level("assets/maps/level1.txt");
    guest_spawn = 10;
  }

  if (level == 2) {
    load_level("assets/maps/level2.txt");
    guest_spawn = 15;
  }

  if (level == 3) {
    load_level("assets/maps/level3.txt");
    guest_spawn = 70;
  }

  if (level == 4) {
    load_level("assets/maps/level4.txt");
    guest_spawn = 150;
  }

  if (level == 5) {
    load_level("assets/maps/level5.txt");
    guest_spawn = 200;
  }

  if (level == 6) {
    load_level("assets/maps/level6.txt");
    guest_spawn = 200;
  }

  // Load path images
  path[0] = asw::assets::load_texture("assets/images/tiles/Path_0.png");
  path[1] = asw::assets::load_texture("assets/images/tiles/Path_1.png");
  path[2] = asw::assets::load_texture("assets/images/tiles/Path_2.png");
  path[3] = asw::assets::load_texture("assets/images/tiles/Path_3.png");
  coaster = asw::assets::load_texture("assets/images/tiles/coaster.png");
  coaster_small =
      asw::assets::load_texture("assets/images/tiles/coaster_small.png");

  level_1_help = asw::assets::load_texture("assets/images/level_1_help.png");
  level_2_help = asw::assets::load_texture("assets/images/level_2_help.png");
  level_3_help = asw::assets::load_texture("assets/images/level_3_help.png");
  level_4_help = asw::assets::load_texture("assets/images/level_4_help.png");

  tweezer = asw::assets::load_texture("assets/images/tweezersButton.png");

  // Load font
  font = asw::assets::load_font("assets/font/font.ttf", 48);
  font_small = asw::assets::load_font("assets/font/font.ttf", 24);

  // Create buttons
  gameUI = UIHandler();
  auto& btn_path_0 = gameUI.createElement<Button>("path_0");
  btn_path_0.setPosition({25.0F, 25.0F});
  btn_path_0.setTexture(path[0]);
  btn_path_0.setBackgroundColour(asw::Color(100, 100, 100));

  auto& btn_path_1 = gameUI.createElement<Button>("path_1");
  btn_path_1.setPosition({25.0F + 128.0F, 25.0F});
  btn_path_1.setTexture(path[1]);
  btn_path_1.setBackgroundColour(asw::Color(100, 100, 100));

  auto& btn_path_2 = gameUI.createElement<Button>("path_2");
  btn_path_2.setPosition({25.0F + 128.0F * 2, 25.0F});
  btn_path_2.setTexture(path[2]);
  btn_path_2.setBackgroundColour(asw::Color(100, 100, 100));

  auto& btn_path_3 = gameUI.createElement<Button>("path_3");
  btn_path_3.setPosition({25.0F + 128.0F * 3, 25.0F});
  btn_path_3.setTexture(path[3]);
  btn_path_3.setBackgroundColour(asw::Color(100, 100, 100));

  auto& lbl_cost_100 = gameUI.createElement<UIElement>("cost_100");
  lbl_cost_100.setPosition({25.0F + 4.0F + 128.0F * 4, 29.0F});
  lbl_cost_100.setFont(font_small);
  lbl_cost_100.setText("Cost:$100");
  lbl_cost_100.setDisableHoverEffect(true);

  auto& btn_tweezer = gameUI.createElement<Button>("tweezer");
  btn_tweezer.setPosition({25.0F, 25.0F + 64.0F + 4.0F});
  btn_tweezer.setTexture(tweezer);

  auto& btn_coaster = gameUI.createElement<Button>("coaster");
  btn_coaster.setPosition({25.0F + 128.0F * 3, 25.0F + 64.0F + 4.0F});
  btn_coaster.setTexture(coaster_small);

  auto& lbl_cost_500 = gameUI.createElement<UIElement>("cost_500");
  lbl_cost_500.setPosition({25.0F + 4.0F + 128.0F * 4, 29.0F + 64.0F});
  lbl_cost_500.setFont(font_small);
  lbl_cost_500.setText("Cost:$500");
  lbl_cost_500.setDisableHoverEffect(true);

  auto& btn_start_game = gameUI.createElement<Button>("start_game");
  btn_start_game.setPosition({200.0F, 500.0F});
  btn_start_game.setFont(font);
  btn_start_game.setText("Start Game");

  auto& btn_finish = gameUI.createElement<Button>("finish");
  btn_finish.setPosition({200.0F, 500.0F});
  btn_finish.setFont(font);
  btn_finish.setText("Finish");

  auto& btn_fast_forward = gameUI.createElement<Button>("fast_forward");
  btn_fast_forward.setPosition({1800.0F, 5.0F});
  btn_fast_forward.setFont(font);
  btn_fast_forward.setText(">>");

  btn_finish.toggleStatus();

  if (level == 1 || level == 2) {
    btn_path_0.toggleStatus();
    btn_path_1.toggleStatus();
    btn_path_2.toggleStatus();
    btn_path_3.toggleStatus();
    btn_tweezer.toggleStatus();
    lbl_cost_100.toggleStatus();
  }

  if (level == 1) {
    btn_fast_forward.toggleStatus();
  }

  if (level == 1 || level == 2 || level == 3) {
    btn_coaster.toggleStatus();
    lbl_cost_500.toggleStatus();
  }

  // Load images for entrance
  entrance_back =
      asw::assets::load_texture("assets/images/tiles/EntranceBack.png");
  entrance_front =
      asw::assets::load_texture("assets/images/tiles/EntranceFront.png");
  entrance_front_transparent =
      asw::assets::load_texture("assets/images/tiles/EntranceFrontTrans.png");

  path_hover = asw::assets::load_texture("assets/images/tiles/Path_Hover.png");

  // Load grabber images
  cursor_open = asw::assets::load_texture("assets/images/tweezersOpen.png");
  cursor_closed = asw::assets::load_texture("assets/images/tweezersClosed.png");

  // Load level
}

// Load map from text
void game::load_level(const std::string& filename) {
  std::string line;
  std::ifstream myfile(filename.c_str());

  int i = 0;

  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      std::istringstream buf(line);
      const std::istream_iterator<std::string> beg(buf);
      const std::istream_iterator<std::string> end;
      const std::vector<std::string> tokens(beg, end);

      // your moms a joffset
      const int joffset = 12;

      int j = 0;

      for (const auto& s : tokens) {
        if (s == "100") {
          gameEnemies.emplace_back(i, j - joffset);
          gameTiles.emplace_back(asw::Vec2<float>(i, j - joffset),
                                 TileType::Grass);
        } else {
          gameTiles.emplace_back(asw::Vec2<float>(i, j - joffset),
                                 static_cast<TileType>(std::stoi(s)));
        }

        j++;
      }

      i++;
    }

    myfile.close();
  }
}

bool game::canPlaceTile(const asw::Vec2<float>& pos) {
  for (const auto& tile : gameTiles) {
    const auto& tile_pos = tile.getPosition();
    if (pos.x == tile_pos.x && pos.y == tile_pos.y) {
      if (tile.getType() == TileType::Water ||
          tile.getType() == TileType::Entrance ||
          tile.getType() == TileType::Umbrella ||
          tile.getType() == TileType::Win) {
        return false;
      }
    }
  }

  return true;
}

// Update
void game::update(float dt) {
  if (asw::input::get_key_down(asw::input::Key::Escape)) {
    manager.set_next_scene(ProgramStates::Options);
  }

  Guest::speed = speed_g;

  spawn_rate = 16;

  if (gameUI.getElementById("fast_forward")->held() ||
      asw::input::get_key(asw::input::Key::F)) {
    Guest::speed = 2;
    spawn_rate = 4;
  }

  if (asw::input::get_key_down(asw::input::Key::Num1)) {
    speed_g = 0.1f;
    Message::send_message("Difficulty set to 1");
  }

  if (asw::input::get_key_down(asw::input::Key::Num2)) {
    speed_g = 0.2f;
    Message::send_message("Difficulty set to 2");
  }

  if (asw::input::get_key_down(asw::input::Key::Num3)) {
    speed_g = 0.3f;
    Message::send_message("Difficulty set to 3");
  }

  if (asw::input::get_key_down(asw::input::Key::Num4)) {
    speed_g = 0.4f;
    Message::send_message("Difficulty set to 4");
  }

  if (asw::input::get_key_down(asw::input::Key::Num5)) {
    speed_g = 0.5f;
    Message::send_message("Difficulty set to 5");
  }

  gameUI.getElementById("path_0")->setBackgroundColour(
      asw::Color(100, 100, 100));
  gameUI.getElementById("path_0")->setDisableHoverEffect(true);
  gameUI.getElementById("path_0")->setActive(false);

  gameUI.getElementById("path_1")->setBackgroundColour(
      asw::Color(100, 100, 100));
  gameUI.getElementById("path_1")->setDisableHoverEffect(true);
  gameUI.getElementById("path_1")->setActive(false);

  gameUI.getElementById("path_2")->setBackgroundColour(
      asw::Color(100, 100, 100));
  gameUI.getElementById("path_2")->setDisableHoverEffect(true);
  gameUI.getElementById("path_2")->setActive(false);

  gameUI.getElementById("path_3")->setBackgroundColour(
      asw::Color(100, 100, 100));
  gameUI.getElementById("path_3")->setDisableHoverEffect(true);
  gameUI.getElementById("path_3")->setActive(false);

  if (money >= GameBalance::kPathCost && level > 2) {
    gameUI.getElementById("path_0")->setBackgroundColour(asw::Color(0, 220, 0));
    gameUI.getElementById("path_0")->setDisableHoverEffect(false);
    gameUI.getElementById("path_0")->setActive(true);

    gameUI.getElementById("path_1")->setBackgroundColour(asw::Color(0, 220, 0));
    gameUI.getElementById("path_1")->setDisableHoverEffect(false);
    gameUI.getElementById("path_1")->setActive(true);

    gameUI.getElementById("path_2")->setBackgroundColour(asw::Color(0, 220, 0));
    gameUI.getElementById("path_2")->setDisableHoverEffect(false);
    gameUI.getElementById("path_2")->setActive(true);

    gameUI.getElementById("path_3")->setBackgroundColour(asw::Color(0, 220, 0));
    gameUI.getElementById("path_3")->setDisableHoverEffect(false);
    gameUI.getElementById("path_3")->setActive(true);
  }

  //                 sully made me do it
  if (money >= GameBalance::kCoasterCost && !(level < 3)) {
    gameUI.getElementById("coaster")->setBackgroundColour(
        asw::Color(0, 220, 0));
    gameUI.getElementById("coaster")->setDisableHoverEffect(false);
    gameUI.getElementById("coaster")->setActive(true);
  } else {
    gameUI.getElementById("coaster")->setBackgroundColour(
        asw::Color(100, 100, 100));
    gameUI.getElementById("coaster")->setDisableHoverEffect(true);
    gameUI.getElementById("coaster")->setActive(false);
  }

  if (level == 1 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 10 &&
      !finished) {
    finished = true;
    gameUI.getElementById("finish")->toggleStatus();
  }

  if (level == 2 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 15 &&
      !finished) {
    finished = true;
    gameUI.getElementById("finish")->toggleStatus();
  }

  if (level == 3 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 70 &&
      !finished) {
    finished = true;
    gameUI.getElementById("finish")->toggleStatus();
  }

  if (level == 4 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 150 &&
      !finished) {
    finished = true;
    gameUI.getElementById("finish")->toggleStatus();
  }

  if (level == 5 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 200 &&
      !finished) {
    finished = true;
    gameUI.getElementById("finish")->toggleStatus();
  }

  if (level == 6 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 200 &&
      !finished) {
    finished = true;
    gameUI.getElementById("finish")->toggleStatus();
  }

  for (auto& particle : gameParticles) {
    particle.update(dt);
  }

  std::erase_if(gameParticles,
                [](const Particle& particle) { return particle.is_dead(); });

  Message::update(dt);
  gameUI.update();

  if (gameUI.getElementById("path_0")->clicked()) {
    editor_tool = EditorTool::PlacePathEast;
  }
  if (gameUI.getElementById("path_1")->clicked()) {
    editor_tool = EditorTool::PlacePathSouth;
  }
  if (gameUI.getElementById("path_2")->clicked()) {
    editor_tool = EditorTool::PlacePathWest;
  }
  if (gameUI.getElementById("path_3")->clicked()) {
    editor_tool = EditorTool::PlacePathNorth;
  }
  if (gameUI.getElementById("tweezer")->clicked()) {
    editor_tool = EditorTool::Grabber;
  }
  if (gameUI.getElementById("coaster")->clicked()) {
    editor_tool = EditorTool::PlaceCoaster;
  }

  if (gameUI.getElementById("start_game")->clicked()) {
    started = true;
    gameUI.getElementById("start_game")->toggleStatus();
  }

  if (gameUI.getElementById("finish")->clicked()) {
    manager.set_next_scene(ProgramStates::LevelFinish);
  }

  for (auto& tile : gameTiles) {
    tile.update(dt);

    const asw::Quad<float> tile_quad =
        asw::Quad<float>(tile.getIsoPosition() - asw::Vec2<float>(32, 32),
                         asw::Vec2<float>(32, 32));

    if (asw::input::get_mouse_button(asw::input::MouseButton::Left) &&
        !gameUI.isHovering() && canPlaceTile(tile.getPosition()) &&
        tile_quad.contains(asw::input::mouse.position)) {
      switch (editor_tool) {
        case EditorTool::PlacePathEast:
          tile = Tile(tile.getPosition(), TileType::DirectionalEast);
          money -= GameBalance::kPathCost;
          editor_tool = EditorTool::Grabber;
          break;

        case EditorTool::PlacePathSouth:
          tile = Tile(tile.getPosition(), TileType::DirectionalSouth);
          money -= GameBalance::kPathCost;
          editor_tool = EditorTool::Grabber;
          break;

        case EditorTool::PlacePathWest:
          tile = Tile(tile.getPosition(), TileType::DirectionalWest);
          money -= GameBalance::kPathCost;
          editor_tool = EditorTool::Grabber;
          break;

        case EditorTool::PlacePathNorth:
          tile = Tile(tile.getPosition(), TileType::DirectionalNorth);
          money -= GameBalance::kPathCost;
          editor_tool = EditorTool::Grabber;
          break;

        case EditorTool::PlaceCoaster:
          tile = Tile(tile.getPosition(), TileType::Coaster);
          money -= GameBalance::kCoasterCost;
          editor_tool = EditorTool::Grabber;
          break;

        default:
          break;
      }
    }
  }

  // Release guest
  if (selectedGuest != nullptr) {
    selectedGuest->setPosition(asw::input::mouse.position);
    selectedGuest->update(dt);

    if (asw::input::get_mouse_button_up(asw::input::MouseButton::Left)) {
      selectedGuest->setCaptured(false);
      selectedGuest->setVelocity(asw::input::mouse.change / 4.0F);
      selectedGuest->setDirection(Direction::East);

      gameGuests.emplace_back(*selectedGuest);
      selectedGuest = nullptr;
    }
  }

  // Enemy logic
  for (auto& enemy : gameEnemies) {
    enemy.update();

    if (enemy.getHealth() == 0) {
      gameParticles.emplace_back(enemy.getPosition(), ParticleType::EnemyDeath);
    }
  }

  std::erase_if(gameEnemies,
                [](const Enemy& enemy) { return enemy.getHealth() == 0; });

  // Rest of guests
  for (unsigned int i = 0; i < gameGuests.size(); i++) {
    auto& guest = gameGuests.at(i);
    bool off_map = true;
    bool removed = false;

    const auto is_cart = guest.getIsCart();
    const auto guest_x = guest.getPosition().x;
    const auto guest_y = guest.getPosition().y;

    guest.update(dt);

    // Pick up guest
    const auto guest_quad =
        asw::Quad<float>(guest.getPosition() - asw::Vec2<float>(25, 30),
                         asw::Vec2<float>(50, 75));
    if (selectedGuest == nullptr && editor_tool == EditorTool::Grabber &&
        asw::input::get_mouse_button(asw::input::MouseButton::Left) &&
        guest_quad.contains(asw::input::mouse.position)) {
      selectedGuest = std::make_unique<Guest>(guest);
      selectedGuest->setCaptured(true);
      gameGuests.erase(gameGuests.begin() + i);
      i--;
      continue;
    }

    // Collision with tiles
    for (const auto& tile : gameTiles) {
      if (off_map && tile.colliding(guest.getPosition()) && guest_x < 1920 &&
          guest_x > 0 && guest_y < 1080 && guest_y > 0) {
        off_map = false;
      }

      // Shorthand
      if (tile.colliding(guest.getPosition()) && !is_cart) {
        // Water
        if (tile.getType() == TileType::Water) {
          if (!is_cart) {
            const auto stringyboi =
                guest.getName() + " has died from drowining.";
            Message::send_message(stringyboi);
            gameParticles.emplace_back(guest.getPosition(),
                                       ParticleType::Death);
            guests_died_falling++;
          }

          gameGuests.erase(gameGuests.begin() + i);
          i--;
          removed = true;
          break;
        }

        // Win
        if (tile.getType() == TileType::Win) {
          gameParticles.emplace_back(guest.getPosition(), ParticleType::Rescue);
          gameGuests.erase(gameGuests.begin() + i);
          i--;
          guests_rescued++;
          removed = true;
          break;
        }

        // Directional tiles
        if (tile.getType() == TileType::DirectionalNorth) {
          guest.setDirection(Direction::North);
        }

        if (tile.getType() == TileType::DirectionalEast) {
          guest.setDirection(Direction::East);
        }

        if (tile.getType() == TileType::DirectionalSouth) {
          guest.setDirection(Direction::South);
        }

        if (tile.getType() == TileType::DirectionalWest) {
          guest.setDirection(Direction::West);
        }

        // Umbrella
        if (tile.getType() == TileType::Umbrella) {
          if (guest.giveUmbrella()) {
            money += GameBalance::kUmbrellaGain;
            gameParticles.emplace_back(guest.getPosition(), ParticleType::Coin);
          }
        }
      }
    }

    if (removed) {
      continue;
    }

    // Off the edge
    if (off_map) {
      if (!is_cart) {
        const auto stringyboi = guest.getName() + " has died from drowining.";
        Message::send_message(stringyboi);
        gameParticles.emplace_back(guest.getPosition(), ParticleType::Death);
        guests_died_falling++;
      }

      gameGuests.erase(gameGuests.begin() + i);
      i--;
      continue;
    }

    // Guest with enemy collision
    for (auto& enemy : gameEnemies) {
      const asw::Quad<float> enemy_quad =
          asw::Quad<float>(enemy.getPosition(), asw::Vec2<float>(100, 100));
      const asw::Quad<float> guest_quad =
          asw::Quad<float>(guest.getPosition() - asw::Vec2<float>(8, 12),
                           asw::Vec2<float>(16, 24));
      if (guest_quad.collides(enemy_quad)) {
        if (!is_cart) {
          const auto stringyboi =
              guest.getName() + " has died from an angry octopus.";
          Message::send_message(stringyboi);
          gameParticles.emplace_back(guest.getPosition(), ParticleType::Death);
          guests_died_enemies++;

          if (guest.getVelocity() != asw::Vec2<float>(0, 0)) {
            guest.setVelocity(asw::Vec2<float>(10, 0));
            gameParticles.emplace_back(
                guest.getPosition() + asw::Vec2<float>(32, 32),
                ParticleType::Hit);
          }

        } else {
          gameParticles.emplace_back(guest.getPosition(), ParticleType::Hit);
        }

        enemy.applyDamage(guest.getVelocity().magnitude());

        gameGuests.erase(gameGuests.begin() + i);
        i--;
        break;
      }
    }
  }

  frame++;

  // Spawn guests
  for (const auto& tile : gameTiles) {
    // Entrance
    if (tile.getType() == TileType::Entrance) {
      if (frame >= spawn_rate) {
        if (guest_spawn > 0 && started) {
          gameGuests.emplace_back(tile.getIsoPosition() +
                                  asw::Vec2<float>(64 - 8, 32 - 20));
          guest_spawn--;
        }

        frame = 0;
      }
    }

    // Roller coaster
    if (tile.getType() == TileType::Coaster) {
      if (asw::random::between(1, 20) == 1) {
        gameGuests.emplace_back(tile.getIsoPosition() +
                                asw::Vec2<float>(32, -64));
      }
    }
  }
}

// Draw to screen
void game::draw() {
  // Background
  asw::draw::clear_color(asw::Color(40, 40, 60));

  // Draw tiles
  for (auto& tile : gameTiles) {
    tile.draw();
  }

  asw::draw::sprite(entrance_back, asw::Vec2<float>(129, 640));
  asw::draw::sprite(entrance_front, asw::Vec2<float>(255, 767));

  // Draw guests
  for (const auto& guest : gameGuests) {
    guest.draw();
  }

  asw::draw::sprite(entrance_front_transparent, asw::Vec2<float>(255, 767));

  // Draw enemies
  for (const auto& enemy : gameEnemies) {
    enemy.draw();
  }

  gameUI.draw();

  // Modified x and y for isometric conversions
  for (const auto& tile : gameTiles) {
    if (canPlaceTile(tile.getPosition())) {
      const bool is_placing_path = editor_tool == EditorTool::PlacePathEast ||
                                   editor_tool == EditorTool::PlacePathSouth ||
                                   editor_tool == EditorTool::PlacePathWest ||
                                   editor_tool == EditorTool::PlacePathNorth;
      if (is_placing_path && tile.colliding(asw::input::mouse.position)) {
        asw::draw::sprite(path_hover, tile.getIsoPosition());
      }

      if (editor_tool == EditorTool::PlaceCoaster &&
          tile.colliding(asw::input::mouse.position)) {
        asw::draw::sprite(coaster,
                          tile.getIsoPosition() - asw::Vec2<float>(200, 300));
      }
    }
  }

  // Picked up guest
  if (selectedGuest != nullptr) {
    asw::draw::sprite(cursor_closed,
                      asw::Vec2<float>(asw::input::mouse.position.x - 8,
                                       asw::input::mouse.position.y - 56));

    selectedGuest->draw();
  }

  else if (editor_tool == EditorTool::Grabber) {
    asw::draw::sprite(cursor_open,
                      asw::input::mouse.position - asw::Vec2<float>(8, 56));
  }

  switch (editor_tool) {
    case EditorTool::PlacePathEast:
      asw::draw::sprite(path[0],
                        asw::input::mouse.position - asw::Vec2<float>(64, 32));
      break;

    case EditorTool::PlacePathSouth:
      asw::draw::sprite(path[1],
                        asw::input::mouse.position - asw::Vec2<float>(64, 32));
      break;

    case EditorTool::PlacePathWest:
      asw::draw::sprite(path[2],
                        asw::input::mouse.position - asw::Vec2<float>(64, 32));
      break;

    case EditorTool::PlacePathNorth:
      asw::draw::sprite(path[3],
                        asw::input::mouse.position - asw::Vec2<float>(64, 32));
      break;

    case EditorTool::PlaceCoaster:
      asw::draw::sprite(
          coaster, asw::input::mouse.position - asw::Vec2<float>(238, 319));
      break;

    default:
      break;
  }

  // Draw coaster layer later, since they are not perfect tiles
  for (const auto& tile : gameTiles) {
    if (tile.getType() == TileType::Coaster) {
      tile.draw();
    }
  }

  // Draw guests
  for (const auto& guest : gameGuests) {
    if (guest.getIsCart()) {
      guest.draw();
    }
  }

  // Draw particles
  for (const auto& particle : gameParticles) {
    particle.draw();
  }

  // Help Screens
  if (level == 1 && !started) {
    asw::draw::sprite(level_1_help, asw::Vec2<float>(0, 0));
  }

  if (level == 2 && !started) {
    asw::draw::sprite(level_2_help, asw::Vec2<float>(0, 0));
  }

  if (level == 3 && !started) {
    asw::draw::sprite(level_3_help, asw::Vec2<float>(0, 0));
  }

  if (level == 4 && !started) {
    asw::draw::sprite(level_4_help, asw::Vec2<float>(0, 0));
  }

  // whitespace is heavenly
  // angels glow white because they're made of pure whitespace

  /// send help

  // its 2 am and this is the funniest thing ive ever seen

  asw::draw::text(font, std::format("Money:{}", money),
                  asw::Vec2<float>(30, 200), asw::Color(100, 0, 0),
                  asw::TextJustify::Left);

  int total_guests = 0;
  if (level == 1) {
    total_guests = 10;
  }
  if (level == 2) {
    total_guests = 15;
  }
  if (level == 3) {
    total_guests = 70;
  }
  if (level == 4) {
    total_guests = 150;
  }
  if (level == 5) {
    total_guests = 200;
  }
  if (level == 6) {
    total_guests = 200;
  }

  asw::draw::text(
      font_small,
      std::format("Remaining Guests:{}",
                  total_guests - (guests_rescued + guests_died_enemies +
                                  guests_died_falling)),
      asw::Vec2<float>(30, 260), asw::Color(0, 0, 0), asw::TextJustify::Left);

  Message::draw();
}
