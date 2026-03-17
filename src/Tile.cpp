#include "Tile.h"

Tile::Tile(int x, int y, int type) {
  // Nullify bitmaps
  sprite = nullptr;
  grid = nullptr;

  // Set type
  this->type = type;

  // Set sprites
  switch (type) {
    case 0:
      sprite = asw::assets::load_texture("assets/images/tiles/Grass.png");
      break;

    case 1:
      sprite = asw::assets::load_texture("assets/images/tiles/Path.png");
      break;

    case 2:
      sprite = asw::assets::load_texture("assets/images/tiles/Path_0.png");
      break;

    case 3:
      sprite = asw::assets::load_texture("assets/images/tiles/Win.png");
      break;

    case 4:
      sprite = asw::assets::load_texture("assets/images/tiles/Path_3.png");
      break;

    case 5:
      sprite = asw::assets::load_texture("assets/images/tiles/Path_0.png");
      break;

    case 6:
      sprite = asw::assets::load_texture("assets/images/tiles/Path_1.png");
      break;

    case 7:
      sprite = asw::assets::load_texture("assets/images/tiles/Path_2.png");
      break;

    case 8:
      sprite = asw::assets::load_texture("assets/images/tiles/Water.png");

      for (int i = 0; i < 4; i++) {
        spritesheet_Water[i] = asw::assets::create_texture(128, 64);
        asw::draw::stretch_sprite_blit(sprite,
                                       asw::Quad<float>(i * 128, 0, 128, 64),
                                       asw::Quad<float>(0, 0, 128, 64));
      }
      break;

    case 9:
      sprite =
          asw::assets::load_texture("assets/images/tiles/umbrellaStand2.png");
      break;

    case 10:
      sprite = asw::assets::load_texture("assets/images/tiles/coaster.png");
      break;

    default:
      break;
  }

  // Load grid
  grid = asw::assets::load_texture("assets/images/tiles/EmptyGrid.png");

  // Set position
  this->x = x;
  this->y = y;

  // Calculate isometric position
  const int bigx = x * 64;
  const int bigy = y * 64;
  iso_x = (bigx - bigy);
  iso_y = (bigx + bigy) / 2;
}

// Check if x and y are in tile
bool Tile::colliding(int x, int y, int width, int height) const {
  return tools::collision(x, x + width, iso_x + 32, iso_x + 96, y, y + height,
                          iso_y + 0, iso_y + 64);
}

bool Tile::colliding_water(int x, int y, int width, int height) const {
  return tools::collision(x, x + width, iso_x + 32, iso_x + 96, y, y + height,
                          iso_y + 16, iso_y + 48);
}

bool Tile::colliding_loose(int x, int y, int width, int height) const {
  return tools::collision(x, x + width, iso_x + 32 - 64, iso_x + 96 + 64, y,
                          y + height, iso_y + 0 - 32, iso_y + 64 + 32);
}

// Check if x and y are in tile (tight)
bool Tile::colliding_tight(int x, int y, int width, int height) const {
  return tools::collision(x, x + width, iso_x + 48, iso_x + 80, y, y + height,
                          iso_y + 16, iso_y + 48);
}

void Tile::draw() {
  if (sprite != nullptr) {
    if (type == 9) {
      asw::draw::sprite(sprite, asw::Vec2<float>(iso_x, iso_y - 57));
    } else if (type == 10) {
      asw::draw::sprite(sprite, asw::Vec2<float>(iso_x - 238, iso_y - 319));
    } else if (type == 8) {
      frame++;
      asw::draw::sprite(spritesheet_Water[frame / 10],
                        asw::Vec2<float>(iso_x, iso_y));

      if (frame >= 39) {
        frame = 0;
      }
    } else {
      asw::draw::sprite(sprite, asw::Vec2<float>(iso_x, iso_y));
    }
  }

  if (type != 9) {
    if (grid != nullptr) {
      asw::draw::sprite(grid, asw::Vec2<float>(iso_x, iso_y));
    }
  }
}
