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
  // Init vars
  old_mouse_x = 0;
  old_mouse_y = 0;

  Message::load();
  Message::clear();

  x_velocity = 0;
  y_velocity = 0;

  selectedGuest = nullptr;

  srand(time(nullptr));

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

  // Load font
  font = asw::assets::load_font("assets/font/font.ttf", 48);
  font_small = asw::assets::load_font("assets/font/font.ttf", 24);

  // Create buttons
  gameUI.addElement(new Button(25, 25, "path_0", path[0]));
  gameUI.getElementById("path_0")->setBackgroundColour(
      asw::Color(100, 100, 100));

  gameUI.addElement(new Button(25 + 128, 25, "path_1", path[1]));
  gameUI.getElementById("path_1")->setBackgroundColour(
      asw::Color(100, 100, 100));

  gameUI.addElement(new Button(25 + 128 * 2, 25, "path_2", path[2]));
  gameUI.getElementById("path_2")->setBackgroundColour(
      asw::Color(100, 100, 100));

  gameUI.addElement(new Button(25 + 128 * 3, 25, "path_3", path[3]));
  gameUI.getElementById("path_3")->setBackgroundColour(
      asw::Color(100, 100, 100));

  gameUI.addElement(
      new UIElement(25 + 4 + 128 * 4, 25, "Cost:$100", font_small));
  gameUI.getElementByText("Cost:$100")->setDisableHoverEffect(true);

  gameUI.addElement(new Button(
      25, 25 + 64 + 4, "tweezer",
      asw::assets::load_texture("assets/images/tweezersButton.png")));

  gameUI.addElement(
      new Button(25 + 128 * 3, 25 + 64 + 4, "coaster", coaster_small));

  gameUI.addElement(
      new UIElement(25 + 4 + 128 * 4, 29 + 64, "Cost:$500", font_small));
  gameUI.getElementByText("Cost:$500")->setDisableHoverEffect(true);

  gameUI.addElement(new Button(200, 500, "Start Game", font));
  gameUI.addElement(new Button(200, 500, "Finish", font));

  gameUI.addElement(new Button(1800, 5, ">>", font));

  gameUI.getElementByText("Finish")->toggleStatus();

  if (level == 1 || level == 2) {
    gameUI.getElementById("path_0")->toggleStatus();
    gameUI.getElementById("path_1")->toggleStatus();

    gameUI.getElementById("path_2")->toggleStatus();

    gameUI.getElementById("path_3")->toggleStatus();
    gameUI.getElementById("tweezer")->toggleStatus();
    gameUI.getElementByText("Cost:$100")->toggleStatus();
  }

  if (level == 1) {
    gameUI.getElementByText(">>")->toggleStatus();
  }

  if (level == 1 || level == 2 || level == 3) {
    gameUI.getElementById("coaster")->toggleStatus();
    gameUI.getElementByText("Cost:$500")->toggleStatus();
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
void game::load_level(std::string filename) {
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
          gameTiles.emplace_back(i, j - joffset, 0);
        } else {
          gameTiles.emplace_back(i, j - joffset, tools::convertStringToInt(s));
        }

        j++;
      }

      i++;
    }

    myfile.close();
  }
}

bool game::canPlaceTile(int x, int y) {
  for (const auto& tile : gameTiles) {
    if (x == tile.getX() && y == tile.getY()) {
      if (tile.getType() == 8 || tile.getType() == 2 || tile.getType() == 9 ||
          tile.getType() == 3) {
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

  if (gameUI.getElementByText(">>")->held() ||
      asw::input::get_key(asw::input::Key::F)) {
    Guest::speed = 2;
    spawn_rate = 4;
  }

  if (asw::input::get_key_down(asw::input::Key::Num1)) {
    speed_g = 0.1f;
    Message::sendMessage("Difficulty set to 1");
  }

  if (asw::input::get_key_down(asw::input::Key::Num2)) {
    speed_g = 0.2f;
    Message::sendMessage("Difficulty set to 2");
  }

  if (asw::input::get_key_down(asw::input::Key::Num3)) {
    speed_g = 0.3f;
    Message::sendMessage("Difficulty set to 3");
  }

  if (asw::input::get_key_down(asw::input::Key::Num4)) {
    speed_g = 0.4f;
    Message::sendMessage("Difficulty set to 4");
  }

  if (asw::input::get_key_down(asw::input::Key::Num5)) {
    speed_g = 0.5f;
    Message::sendMessage("Difficulty set to 5");
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

  if (money >= 100 && level > 2) {
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
  if (money >= 500 && !(level < 3)) {
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
    gameUI.getElementByText("Finish")->toggleStatus();
  }

  if (level == 2 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 15 &&
      !finished) {
    finished = true;
    gameUI.getElementByText("Finish")->toggleStatus();
  }

  if (level == 3 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 70 &&
      !finished) {
    finished = true;
    gameUI.getElementByText("Finish")->toggleStatus();
  }

  if (level == 4 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 150 &&
      !finished) {
    finished = true;
    gameUI.getElementByText("Finish")->toggleStatus();
  }

  if (level == 5 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 200 &&
      !finished) {
    finished = true;
    gameUI.getElementByText("Finish")->toggleStatus();
  }

  if (level == 6 &&
      guests_rescued + guests_died_enemies + guests_died_falling == 200 &&
      !finished) {
    finished = true;
    gameUI.getElementByText("Finish")->toggleStatus();
  }

  for (auto& particle : gameParticles) {
    particle.update();
  }

  std::erase_if(gameParticles,
                [](const Particle& particle) { return particle.is_dead(); });

  Message::update();
  gameUI.update();

  if (gameUI.getElementById("path_0")->clicked()) {
    editor_tool = 0;
  }
  if (gameUI.getElementById("path_1")->clicked()) {
    editor_tool = 1;
  }
  if (gameUI.getElementById("path_2")->clicked()) {
    editor_tool = 2;
  }
  if (gameUI.getElementById("path_3")->clicked()) {
    editor_tool = 3;
  }
  if (gameUI.getElementById("tweezer")->clicked()) {
    editor_tool = 4;
  }
  if (gameUI.getElementById("coaster")->clicked()) {
    editor_tool = 5;
  }

  if (gameUI.getElementByText("Start Game")->clicked()) {
    started = true;
    gameUI.getElementByText("Start Game")->toggleStatus();
  }

  if (gameUI.getElementByText("Finish")->clicked()) {
    manager.set_next_scene(ProgramStates::LevelFinish);
  }

  // Velocity of mouse
  x_velocity = -1 * (old_mouse_x - asw::input::mouse.position.x);
  y_velocity = -1 * (old_mouse_y - asw::input::mouse.position.y);

  old_mouse_x = asw::input::mouse.position.x;
  old_mouse_y = asw::input::mouse.position.y;

  for (auto& tile : gameTiles) {
    const int mxo = asw::input::mouse.position.x - 64;
    const int myo = asw::input::mouse.position.y - 32;

    if ((asw::input::get_mouse_button(asw::input::MouseButton::Left) &&
         !gameUI.isHovering()) &&
        canPlaceTile(tile.getX(), tile.getY()) && mxo > tile.getIsoX() - 32 &&
        mxo < tile.getIsoX() + 32 && myo < tile.getIsoY() + 32 &&
        myo > tile.getIsoY() - 32) {
      switch (editor_tool) {
        case 0:
          tile = Tile(tile.getX(), tile.getY(), 5);
          money -= 100;
          editor_tool = 4;
          break;

        case 1:
          tile = Tile(tile.getX(), tile.getY(), 6);
          money -= 100;
          editor_tool = 4;
          break;

        case 2:
          tile = Tile(tile.getX(), tile.getY(), 7);
          money -= 100;
          editor_tool = 4;
          break;

        case 3:
          tile = Tile(tile.getX(), tile.getY(), 4);
          money -= 100;
          editor_tool = 4;
          break;

        case 5:
          tile = Tile(tile.getX(), tile.getY(), 10);
          money -= 500;
          editor_tool = 4;
          break;

        default:
          break;
      }
    }
  }

  // Release guest
  if (selectedGuest != nullptr) {
    selectedGuest->setX(asw::input::mouse.position.x);
    selectedGuest->setY(asw::input::mouse.position.y);

    if (asw::input::get_mouse_button_up(asw::input::MouseButton::Left)) {
      selectedGuest->setCaptured(false);
      selectedGuest->setVelocityX(x_velocity);
      selectedGuest->setVelocityY(y_velocity);
      selectedGuest->setDirection(0);

      gameGuests.push_back(*selectedGuest);
      selectedGuest = nullptr;
    }
  }

  // Enemy logic
  for (auto& enemy : gameEnemies) {
    enemy.update();

    if (enemy.getHealth() == 0) {
      gameParticles.emplace_back(enemy.getX(), enemy.getY(), 4);
    }
  }

  std::erase_if(gameEnemies,
                [](const Enemy& enemy) { return enemy.getHealth() == 0; });

  // Run guest logic
  // In grabber
  if (selectedGuest != nullptr) {
    selectedGuest->update();
  }

  // Rest of guests
  for (int i = 0; i < static_cast<int>(gameGuests.size()); i++) {
    auto& guest = gameGuests.at(i);
    bool off_map = true;
    bool guest_alive = true;

    const bool is_cart = guest.getIsCart();
    const int guest_x = guest.getX() + 8;
    const int guest_y = guest.getY() + 32;

    guest.update();

    // Pick up guest
    if (selectedGuest == nullptr && editor_tool == 4 &&
        tools::clicked(guest.getX() - 25, guest.getX() + 25, guest.getY() - 30,
                       guest.getY() + 45)) {
      selectedGuest = &guest;
      selectedGuest->setCaptured(true);
      gameGuests.erase(gameGuests.begin() + i);
      i--;
      continue;
    }

    // Collision with tiles
    for (const auto& tile : gameTiles) {
      const int guest_x = guest.getX() + 8;
      const int guest_y = guest.getY() + 32;

      if (tile.colliding_loose(guest_x, guest_y) && guest_x < 1920 &&
          guest_x > 0 && guest_y < 1080 && guest_y > 0) {
        off_map = false;
      }

      if (guest_alive) {
        // Shorthand
        const int current = tile.getType();

        if (tile.colliding_water(guest_x, guest_y) && !is_cart) {
          if (current == 8 && !is_cart) {
            if (!is_cart) {
              const auto stringyboi =
                  guest.getName() + " has died from drowining.";
              Message::sendMessage(stringyboi);
              gameParticles.emplace_back(guest_x, guest_y, 1);
              guests_died_falling++;
            }

            gameGuests.erase(gameGuests.begin() + i);
            i--;
            guest_alive = false;

            break;
          }
        }

        // Collision with map tile
        if (tile.colliding(guest_x, guest_y) && !is_cart) {
          if (current == 3 && !is_cart) {
            gameParticles.emplace_back(guest_x, guest_y, 2);

            gameGuests.erase(gameGuests.begin() + i);
            i--;
            guest_alive = false;
            guests_rescued++;

            break;
          }
        }

        if (guest_alive) {
          if (tile.colliding_loose(guest_x, guest_y) && !is_cart) {
            if (current == 9) {
              if (guest.giveUmbrella()) {
                money += 10;
                gameParticles.emplace_back(guest_x, guest_y, 0);
              }
            }
          }
        }

        if (guest_alive) {
          // Touching special tile
          if (tile.colliding_tight(guest_x, guest_y)) {
            // Directional tilesoff_map
            if (current == 4) {
              guest.setDirection(3);
            }

            if (current == 5) {
              guest.setDirection(0);
            }

            if (current == 6) {
              guest.setDirection(1);
            }

            if (current == 7) {
              guest.setDirection(2);
            }

            // End point
          }

          // Water tile
        }
      }
    }

    // Off the edge
    if (off_map && guest_alive) {
      if (!is_cart) {
        const auto stringyboi = guest.getName() + " has died from drowining.";
        Message::sendMessage(stringyboi);
        gameParticles.emplace_back(guest_x, guest_y, 1);
        guests_died_falling++;
      }

      gameGuests.erase(gameGuests.begin() + i);
      i--;
      continue;
    }

    // Guest with enemy collision
    if (guest_alive) {
      for (auto& enemy : gameEnemies) {
        if (tools::collision(guest.getX(), guest.getX() + 16,
                             enemy.getX() + 100, enemy.getX() + 400,
                             guest.getY(), guest.getY() + 54,
                             enemy.getY() + 100, enemy.getY() + 200)) {
          if (!is_cart) {
            std::string stringyboi =
                guest.getName() + " has died from an angry octopus.";
            Message::sendMessage(stringyboi);
            gameParticles.emplace_back(guest_x, guest_y, 1);
            guests_died_enemies++;

            if (guest.getVelocityX() != 0 && guest.getVelocityY() != 0) {
              guest.setVelocityX(10);
              guest.setVelocityY(0);
              gameParticles.emplace_back(guest_x + 32, guest_y + 32, 3);
            }

          } else {
            gameParticles.emplace_back(guest_x, guest_y, 3);
          }

          enemy.applyDamage(abs(guest.getVelocityX()) +
                            abs(guest.getVelocityY()));

          gameGuests.erase(gameGuests.begin() + i);
          i--;

          break;
        }
      }
    }
  }

  frame++;

  // Spawn guests
  for (const auto& tile : gameTiles) {
    if (tile.getType() == 2) {
      if (frame >= spawn_rate) {
        if (guest_spawn > 0 && started) {
          gameGuests.emplace_back(tile.getIsoX() + 64 - 8,
                                  tile.getIsoY() + 32 - 20);
          guest_spawn--;
        }

        frame = 0;
      }
    }
  }

  for (const auto& tile : gameTiles) {
    if (tile.getType() == 10) {
      if (asw::random::between(1, 20) == 1) {
        gameGuests.emplace_back(tile.getIsoX() + 32, tile.getIsoY() - 64);
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

  if (asw::input::get_key(asw::input::Key::G)) {
    for (auto& tile : gameTiles) {
      asw::draw::rect(
          asw::Quad<float>(tile.getIsoX() + 32, tile.getIsoY(), 64, 64),
          asw::Color(99, 33, 0));
    }
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
    if (canPlaceTile(tile.getX(), tile.getY())) {
      if (editor_tool >= 0 && editor_tool <= 3 &&
          tile.colliding(asw::input::mouse.position.x,
                         asw::input::mouse.position.y)) {
        asw::draw::sprite(path_hover,
                          asw::Vec2<float>(tile.getIsoX(), tile.getIsoY()));
      }

      if (editor_tool == 5 && tile.colliding(asw::input::mouse.position.x,
                                             asw::input::mouse.position.y))
        asw::draw::sprite(coaster, asw::Vec2<float>(tile.getIsoX() - 200,
                                                    tile.getIsoY() - 300));
    }
  }

  // Picked up guest
  if (selectedGuest != nullptr) {
    selectedGuest->draw();
    asw::draw::sprite(cursor_closed,
                      asw::Vec2<float>(asw::input::mouse.position.x - 8,
                                       asw::input::mouse.position.y - 56));
  }

  else if (editor_tool == 4) {
    asw::draw::sprite(cursor_open,
                      asw::Vec2<float>(asw::input::mouse.position.x - 8,
                                       asw::input::mouse.position.y - 56));
  }

  switch (editor_tool) {
    case 0:
      asw::draw::sprite(path[0],
                        asw::Vec2<float>(asw::input::mouse.position.x - 64,
                                         asw::input::mouse.position.y - 32));
      break;

    case 1:
      asw::draw::sprite(path[1],
                        asw::Vec2<float>(asw::input::mouse.position.x - 64,
                                         asw::input::mouse.position.y - 32));
      break;

    case 2:
      asw::draw::sprite(path[2],
                        asw::Vec2<float>(asw::input::mouse.position.x - 64,
                                         asw::input::mouse.position.y - 32));
      break;

    case 3:
      asw::draw::sprite(path[3],
                        asw::Vec2<float>(asw::input::mouse.position.x - 64,
                                         asw::input::mouse.position.y - 32));
      break;

    case 5:
      asw::draw::sprite(coaster,
                        asw::Vec2<float>(asw::input::mouse.position.x - 238,
                                         asw::input::mouse.position.y - 319));
      break;

    default:
      break;
  }

  for (auto& tile : gameTiles) {
    if (tile.getType() == 10) {
      tile.draw();
    }
  }

  for (auto& guest : gameGuests) {
    if (guest.getIsCart()) {
      guest.draw();
    }
  }

  for (auto& particle : gameParticles) {
    particle.draw();
  }

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
