#include "game.h"

#include <algorithm>
#include <format>
#include <string>

#include "../message.h"

int Game::level = 1;
int Game::guests_died_enemies = 0;
int Game::guests_died_falling = 0;
int Game::guests_rescued = 0;
int Game::money = 0;

void Game::init() {
  Guest::speed = 0.5;
  guests_died_enemies = 0;
  guests_died_falling = 0;
  guests_rescued = 0;
  money = 0;

  _spawn_timer = 0.0F;
  _spawn_rate = 2.0F;
  _started = false;
  _finished = false;
  _speed_g = 0.5F;
  _fast_forward = false;
  _selected_guest = nullptr;
  _level_editor.set_tool(EditorTool::Grabber);

  Message::load();
  Message::clear();

  _tile_map.clear();
  _entities.clear();

  const auto configs = LevelConfigLoader::load_all("assets/levels/levels.json");
  const auto cfg_opt = LevelConfigLoader::for_level(configs, level);
  if (!cfg_opt) {
    asw::log::warn("Game::init: no config found for level " +
                   std::to_string(level));
    return;
  }
  _current_level_config = *cfg_opt;

  auto result = _tile_map.load_from_file(_current_level_config.tile_map_file);
  for (auto& [x, y] : result.enemy_spawn_positions) {
    _entities.spawn_enemy(x, y);
  }
  _guest_spawn = _current_level_config.total_guests;

  // Load path images
  _path[0] = asw::assets::load_texture("assets/images/tiles/Path_0.png");
  _path[1] = asw::assets::load_texture("assets/images/tiles/Path_1.png");
  _path[2] = asw::assets::load_texture("assets/images/tiles/Path_2.png");
  _path[3] = asw::assets::load_texture("assets/images/tiles/Path_3.png");
  _coaster = asw::assets::load_texture("assets/images/tiles/coaster.png");
  _coaster_small =
      asw::assets::load_texture("assets/images/tiles/coaster_small.png");

  _level_1_help = asw::assets::load_texture("assets/images/level_1_help.png");
  _level_2_help = asw::assets::load_texture("assets/images/level_2_help.png");
  _level_3_help = asw::assets::load_texture("assets/images/level_3_help.png");
  _level_4_help = asw::assets::load_texture("assets/images/level_4_help.png");

  _tweezer = asw::assets::load_texture("assets/images/tweezersButton.png");

  _entrance_back =
      asw::assets::load_texture("assets/images/tiles/EntranceBack.png");
  _entrance_front =
      asw::assets::load_texture("assets/images/tiles/EntranceFront.png");
  _entrance_front_transparent =
      asw::assets::load_texture("assets/images/tiles/EntranceFrontTrans.png");

  _path_hover = asw::assets::load_texture("assets/images/tiles/Path_Hover.png");

  _cursor_open = asw::assets::load_texture("assets/images/tweezersOpen.png");
  _cursor_closed =
      asw::assets::load_texture("assets/images/tweezersClosed.png");

  asw::Font _font = asw::assets::load_font("assets/font/font.ttf", 48);
  asw::Font _font_small = asw::assets::load_font("assets/font/font.ttf", 24);

  // Build UI
  const auto& hidden = _current_level_config.hidden_buttons;
  const auto is_hidden = [&](const std::string& id) {
    return std::find(hidden.begin(), hidden.end(), id) != hidden.end();
  };

  _show_path_costs = !is_hidden("cost_100");
  _show_coaster_cost = !is_hidden("cost_500");

  _ui = asw::ui::Root();
  _ui.root.transform.size = asw::Vec2f(0, 0);
  _ui.ctx.theme.btn_bg = asw::Color(100, 100, 100);
  _ui.ctx.theme.btn_hover = asw::Color(150, 150, 150);

  auto& btn_path_0 = _ui.root.add_child<asw::ui::Button>();
  btn_path_0.transform.position = asw::Vec2f(25.0F, 25.0F);
  btn_path_0.padding = 10;
  btn_path_0.set_texture(_path[0], true);
  btn_path_0.visible = !is_hidden("path_0");
  btn_path_0.on_click = [this] {
    _level_editor.set_tool(EditorTool::PlacePathEast);
  };
  _btn_path_0 = &btn_path_0;

  auto& btn_path_1 = _ui.root.add_child<asw::ui::Button>();
  btn_path_1.transform.position = asw::Vec2f(25.0F + 128.0F, 25.0F);
  btn_path_1.padding = 10;
  btn_path_1.set_texture(_path[1], true);
  btn_path_1.visible = !is_hidden("path_1");
  btn_path_1.on_click = [this] {
    _level_editor.set_tool(EditorTool::PlacePathSouth);
  };
  _btn_path_1 = &btn_path_1;

  auto& btn_path_2 = _ui.root.add_child<asw::ui::Button>();
  btn_path_2.transform.position = asw::Vec2f(25.0F + 128.0F * 2, 25.0F);
  btn_path_2.padding = 10;
  btn_path_2.set_texture(_path[2], true);
  btn_path_2.visible = !is_hidden("path_2");
  btn_path_2.on_click = [this] {
    _level_editor.set_tool(EditorTool::PlacePathWest);
  };
  _btn_path_2 = &btn_path_2;

  auto& btn_path_3 = _ui.root.add_child<asw::ui::Button>();
  btn_path_3.transform.position = asw::Vec2f(25.0F + 128.0F * 3, 25.0F);
  btn_path_3.padding = 10;
  btn_path_3.set_texture(_path[3], true);
  btn_path_3.visible = !is_hidden("path_3");
  btn_path_3.on_click = [this] {
    _level_editor.set_tool(EditorTool::PlacePathNorth);
  };
  _btn_path_3 = &btn_path_3;

  auto& btn_tweezer = _ui.root.add_child<asw::ui::Button>();
  btn_tweezer.transform.position = asw::Vec2f(25.0F, 25.0F + 64.0F + 4.0F);
  btn_tweezer.padding = 10;
  btn_tweezer.set_texture(_tweezer, true);
  btn_tweezer.visible = !is_hidden("tweezer");
  btn_tweezer.on_click = [this] {
    _level_editor.set_tool(EditorTool::Grabber);
  };

  auto& btn_coaster = _ui.root.add_child<asw::ui::Button>();
  btn_coaster.transform.position =
      asw::Vec2f(25.0F + 128.0F * 3, 25.0F + 64.0F + 4.0F);
  btn_coaster.padding = 10;
  btn_coaster.set_texture(_coaster_small, true);
  btn_coaster.visible = !is_hidden("coaster");
  btn_coaster.on_click = [this] {
    _level_editor.set_tool(EditorTool::PlaceCoaster);
  };
  _btn_coaster = &btn_coaster;

  auto& btn_start_game = _ui.root.add_child<asw::ui::Button>();
  btn_start_game.transform.position = asw::Vec2f(200.0F, 500.0F);
  btn_start_game.padding = 10;
  btn_start_game.font = _font;
  btn_start_game.set_text("Start Game", true);
  _btn_start_game = &btn_start_game;
  _btn_start_game->on_click = [this] {
    _started = true;
    _btn_start_game->visible = false;
  };

  auto& btn_finish = _ui.root.add_child<asw::ui::Button>();
  btn_finish.transform.position = asw::Vec2f(200.0F, 500.0F);
  btn_finish.padding = 10;
  btn_finish.font = _font;
  btn_finish.set_text("Finish", true);
  btn_finish.visible = false;
  btn_finish.on_click = [this] {
    manager.set_next_scene(ProgramStates::LevelFinish);
  };
  _btn_finish = &btn_finish;

  auto& btn_fast_forward = _ui.root.add_child<asw::ui::Button>();
  btn_fast_forward.transform.position = asw::Vec2f(1800.0F, 5.0F);
  btn_fast_forward.padding = 10;
  btn_fast_forward.font = _font;
  btn_fast_forward.set_text(">>", true);
  btn_fast_forward.visible = !is_hidden("fast_forward");
  btn_fast_forward.on_click = [this, &btn_fast_forward] {
    _fast_forward = !_fast_forward;
    btn_fast_forward.text = _fast_forward ? ">" : ">>";
  };

  auto& lbl_money = _ui.root.add_child<asw::ui::Label>();
  lbl_money.transform.position = asw::Vec2f(30.0F, 200.0F);
  lbl_money.font = _font;
  lbl_money.color = asw::Color(100, 0, 0);
  lbl_money.justify = asw::TextJustify::Left;
  _lbl_money = &lbl_money;

  auto& lbl_remaining_guests = _ui.root.add_child<asw::ui::Label>();
  lbl_remaining_guests.transform.position = asw::Vec2f(30.0F, 260.0F);
  lbl_remaining_guests.font = _font_small;
  lbl_remaining_guests.color = asw::Color(0, 0, 0);
  lbl_remaining_guests.justify = asw::TextJustify::Left;
  _lbl_remaining_guests = &lbl_remaining_guests;

  auto& lbl_path_cost = _ui.root.add_child<asw::ui::Label>();
  lbl_path_cost.transform.position =
      asw::Vec2f(25.0F + 4.0F + 128.0F * 4, 29.0F);
  lbl_path_cost.font = _font_small;
  lbl_path_cost.text = "Cost:$100";
  lbl_path_cost.color = asw::Color(0, 0, 0);
  lbl_path_cost.justify = asw::TextJustify::Left;
  lbl_path_cost.visible = _show_path_costs;

  auto& lbl_coaster_cost = _ui.root.add_child<asw::ui::Label>();
  lbl_coaster_cost.transform.position =
      asw::Vec2f(25.0F + 4.0F + 128.0F * 4, 29.0F + 64.0F);
  lbl_coaster_cost.font = _font_small;
  lbl_coaster_cost.text = "Cost:$500";
  lbl_coaster_cost.color = asw::Color(0, 0, 0);
  lbl_coaster_cost.justify = asw::TextJustify::Left;
  lbl_coaster_cost.visible = _show_coaster_cost;
}

void Game::update(float dt) {
  if (asw::input::get_key_down(asw::input::Key::Escape)) {
    manager.set_next_scene(ProgramStates::Options);
  }

  Guest::speed = GameBalance::GUEST_BASE_SPEED;
  _spawn_rate = GameBalance::SPAWN_RATE;

  if (_fast_forward || asw::input::get_key(asw::input::Key::F)) {
    Guest::speed = GameBalance::GUEST_BASE_SPEED * 2.0F;
    _spawn_rate = GameBalance::SPAWN_RATE / 2.0F;
  }

  // Update path button affordance based on money
  const bool can_afford_path = money >= GameBalance::PATH_COST;
  _btn_path_0->enabled = can_afford_path;
  _btn_path_1->enabled = can_afford_path;
  _btn_path_2->enabled = can_afford_path;
  _btn_path_3->enabled = can_afford_path;

  const bool can_afford_coaster = money >= GameBalance::COASTER_COST;
  _btn_coaster->enabled = can_afford_coaster;

  // Update stat labels
  const int remaining_guests =
      _current_level_config.total_guests -
      (guests_rescued + guests_died_enemies + guests_died_falling);
  _lbl_money->text = std::format("Money:{}", money);
  _lbl_remaining_guests->text =
      std::format("Remaining Guests:{}", remaining_guests);

  // Level completion check
  const int total_processed =
      guests_rescued + guests_died_enemies + guests_died_falling;
  if (!_finished && total_processed == _current_level_config.total_guests) {
    _finished = true;
    _btn_finish->visible = true;
  }

  // Update subsystems
  _entities.update_particles(dt);
  _tile_map.update(dt);
  Message::update(dt);
  _ui.update();

  // Tile placement via editor tool
  _level_editor.handle_input(_tile_map, money);

  // Release grabbed guest
  if (_selected_guest != nullptr) {
    _selected_guest->set_position(asw::input::mouse.position);
    _selected_guest->update(dt);

    if (asw::input::get_mouse_button_up(asw::input::MouseButton::Left)) {
      _selected_guest->set_captured(false);
      _selected_guest->set_velocity(asw::input::mouse.change / 4.0F);
      _selected_guest->set_direction(Direction::East);
      _entities.add_guest(*_selected_guest);
      _selected_guest = nullptr;
    }
  }

  // Enemy lifecycle
  _entities.update_enemies(dt);

  // Guest processing
  for (auto& guest : _entities.guests()) {
    // Pick up with grabber
    const asw::Quadf guest_quad = asw::Quadf(
        guest.get_position() - asw::Vec2f(25, 30), asw::Vec2f(50, 75));
    if (_selected_guest == nullptr &&
        _level_editor.current_tool() == EditorTool::Grabber &&
        asw::input::get_mouse_button(asw::input::MouseButton::Left) &&
        guest_quad.contains(asw::input::mouse.position)) {
      _selected_guest = std::make_unique<Guest>(guest);
      _selected_guest->set_captured(true);
      guest.set_is_dead(true);
    }

    CollisionSystem::resolve_vs_tiles(guest, _tile_map.tiles(),
                                      _entities.particles(), money,
                                      guests_rescued, guests_died_falling);

    CollisionSystem::resolve_off_map(guest, _entities.particles(),
                                     guests_died_falling);

    CollisionSystem::resolve_vs_enemies(
        guest, _entities.enemies(), _entities.particles(), guests_died_enemies);
  }

  // Cart processing
  for (auto& cart : _entities.carts()) {
    CollisionSystem::resolve_off_map(cart);
    CollisionSystem::resolve_vs_enemies(cart, _entities.enemies(),
                                        _entities.particles());
  }

  // Spawn guests from entrance
  _spawn_timer += dt;
  if (_spawn_timer >= _spawn_rate) {
    _spawn_timer -= _spawn_rate;

    auto entrance_pos = _tile_map.find_entrance_iso_pos();
    if (entrance_pos) {
      if (_guest_spawn > 0 && _started) {
        _entities.spawn_guest(*entrance_pos + asw::Vec2f(56.0F, 12.0F));
        _guest_spawn--;
      }
    }
  }

  // Update guests
  _entities.update_guests(dt);

  // Update carts
  _entities.update_carts(dt);

  // Spawn guests from coaster tiles
  for (const auto& pos : _tile_map.find_coaster_iso_positions()) {
    if (asw::random::between(1, 20) == 1) {
      _entities.spawn_cart(pos + asw::Vec2f(32, -64));
    }
  }

  // Add money debug
  if (asw::input::get_key_down(asw::input::Key::M)) {
    money += 100;
  }
}

void Game::draw() {
  asw::draw::clear_color(asw::Color(40, 40, 60));

  _tile_map.draw();

  asw::draw::sprite(_entrance_back, asw::Vec2f(129, 640));
  asw::draw::sprite(_entrance_front, asw::Vec2f(255, 767));

  _entities.draw_guests();

  asw::draw::sprite(_entrance_front_transparent, asw::Vec2f(255, 767));

  _entities.draw_enemies();

  // Path/coaster hover preview
  const bool is_placing_path =
      _level_editor.current_tool() == EditorTool::PlacePathEast ||
      _level_editor.current_tool() == EditorTool::PlacePathSouth ||
      _level_editor.current_tool() == EditorTool::PlacePathWest ||
      _level_editor.current_tool() == EditorTool::PlacePathNorth;

  for (const auto& tile : _tile_map.tiles()) {
    if (!_tile_map.can_place_tile(tile.get_position())) {
      continue;
    }
    if (is_placing_path && tile.colliding(asw::input::mouse.position)) {
      asw::draw::sprite(_path_hover, tile.get_iso_position());
    }
    if (_level_editor.current_tool() == EditorTool::PlaceCoaster &&
        tile.colliding(asw::input::mouse.position)) {
      asw::draw::sprite(_coaster,
                        tile.get_iso_position() - asw::Vec2f(200, 300));
    }
  }

  // Grabber cursor
  if (_selected_guest != nullptr) {
    asw::draw::sprite(_cursor_closed,
                      asw::Vec2f(asw::input::mouse.position.x - 8,
                                 asw::input::mouse.position.y - 56));
    _selected_guest->draw();
  } else if (_level_editor.current_tool() == EditorTool::Grabber) {
    asw::draw::sprite(_cursor_open,
                      asw::input::mouse.position - asw::Vec2f(8, 56));
  }

  // Tool cursor sprite at mouse
  switch (_level_editor.current_tool()) {
    case EditorTool::PlacePathEast:
      asw::draw::sprite(_path[0],
                        asw::input::mouse.position - asw::Vec2f(64, 32));
      break;
    case EditorTool::PlacePathSouth:
      asw::draw::sprite(_path[1],
                        asw::input::mouse.position - asw::Vec2f(64, 32));
      break;
    case EditorTool::PlacePathWest:
      asw::draw::sprite(_path[2],
                        asw::input::mouse.position - asw::Vec2f(64, 32));
      break;
    case EditorTool::PlacePathNorth:
      asw::draw::sprite(_path[3],
                        asw::input::mouse.position - asw::Vec2f(64, 32));
      break;
    case EditorTool::PlaceCoaster:
      asw::draw::sprite(_coaster,
                        asw::input::mouse.position - asw::Vec2f(238, 319));
      break;
    default:
      break;
  }

  // Coasters drawn after guests for z-ordering
  _tile_map.draw_coasters();
  _entities.draw_carts();
  _entities.draw_particles();

  // Help screens
  if (level == 1 && !_started) {
    asw::draw::sprite(_level_1_help, asw::Vec2f(0, 0));
  }
  if (level == 2 && !_started) {
    asw::draw::sprite(_level_2_help, asw::Vec2f(0, 0));
  }
  if (level == 3 && !_started) {
    asw::draw::sprite(_level_3_help, asw::Vec2f(0, 0));
  }
  if (level == 4 && !_started) {
    asw::draw::sprite(_level_4_help, asw::Vec2f(0, 0));
  }

  _ui.draw();

  Message::draw();
}
