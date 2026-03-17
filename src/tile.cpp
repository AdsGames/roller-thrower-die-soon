#include "tile.h"

#include <cmath>

Tile::Tile(const asw::Vec2<float>& position, TileType type)
    : position(position), type(type) {
  // Set sprites
  switch (type) {
    case TileType::Grass:
      sprite =
          asw::assets::load_texture("assets/images/tiles/Grass.png", "grass");
      break;

    case TileType::Path:
      sprite =
          asw::assets::load_texture("assets/images/tiles/Path.png", "path");
      break;

    case TileType::Entrance:
      sprite =
          asw::assets::load_texture("assets/images/tiles/Path_0.png", "path_0");
      break;

    case TileType::Win:
      sprite = asw::assets::load_texture("assets/images/tiles/Win.png", "win");
      break;

    case TileType::DirectionalNorth:
      sprite =
          asw::assets::load_texture("assets/images/tiles/Path_3.png", "path_3");
      break;

    case TileType::DirectionalEast:
      sprite = asw::assets::load_texture("assets/images/tiles/Path_0.png",
                                         "path_0_2");
      break;

    case TileType::DirectionalSouth:
      sprite =
          asw::assets::load_texture("assets/images/tiles/Path_1.png", "path_1");
      break;

    case TileType::DirectionalWest:
      sprite =
          asw::assets::load_texture("assets/images/tiles/Path_2.png", "path_2");
      break;

    case TileType::Water:
      sprite =
          asw::assets::load_texture("assets/images/tiles/Water.png", "water");

      for (int i = 0; i < 4; i++) {
        spritesheet_water[i] = asw::assets::create_texture(128, 64);
        asw::display::set_render_target(spritesheet_water[i]);
        asw::draw::stretch_sprite_blit(sprite,
                                       asw::Quad<float>(i * 128, 0, 128, 64),
                                       asw::Quad<float>(0, 0, 128, 64));
        asw::display::reset_render_target();
      }
      break;

    case TileType::Umbrella:
      sprite = asw::assets::load_texture(
          "assets/images/tiles/umbrellaStand2.png", "umbrella_stand");
      break;

    case TileType::Coaster:
      sprite = asw::assets::load_texture("assets/images/tiles/coaster.png",
                                         "coaster");
      break;

    default:
      break;
  }

  // Load grid
  grid = asw::assets::load_texture("assets/images/tiles/EmptyGrid.png",
                                   "empty_grid");

  // Calculate isometric position
  const auto big_pos = position * 64.0F;
  iso_position.x = (big_pos.x - big_pos.y);
  iso_position.y = (big_pos.x + big_pos.y) / 2;
}

// Check if x and y are in tile (diamond check)
bool Tile::colliding(const asw::Vec2<float>& pos) const {
  const float dx = std::abs(pos.x - (iso_position.x + 64.0F)) / 64.0F;
  const float dy = std::abs(pos.y - (iso_position.y + 32.0F)) / 32.0F;
  return (dx + dy) <= 1.0F;
}

void Tile::draw() const {
  if (sprite != nullptr) {
    if (type == TileType::Umbrella) {
      asw::draw::sprite(sprite,
                        asw::Vec2<float>(iso_position.x, iso_position.y - 57));
    } else if (type == TileType::Coaster) {
      asw::draw::sprite(
          sprite, asw::Vec2<float>(iso_position.x - 238, iso_position.y - 319));
    } else if (type == TileType::Water) {
      const auto frame = static_cast<int>(frame_counter * FRAMES_PER_SECOND) %
                         spritesheet_water.size();

      asw::draw::sprite(spritesheet_water[frame],
                        asw::Vec2<float>(iso_position.x, iso_position.y));
    } else {
      asw::draw::sprite(sprite,
                        asw::Vec2<float>(iso_position.x, iso_position.y));
    }
  }

  if (type != TileType::Umbrella) {
    asw::draw::sprite(grid, iso_position);
  }
}
