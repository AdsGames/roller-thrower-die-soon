#include "collision_system.h"

#include "direction.h"
#include "game_balance.h"
#include "message.h"
#include "tile.h"

namespace CollisionSystem {

bool resolve_vs_tiles(Guest& guest,
                      const std::vector<Tile>& tiles,
                      std::vector<Particle>& particles,
                      int& money,
                      int& guests_rescued,
                      int& guests_died_falling) {
  for (const auto& tile : tiles) {
    if (!tile.colliding(guest.get_position())) {
      continue;
    }

    if (tile.get_type() == TileType::Water) {
      Message::send_message(guest.get_name() + " has died from drowning.");
      particles.emplace_back(guest.get_position(), ParticleType::Death);
      guests_died_falling++;
      guest.set_is_dead(true);
      return true;
    }

    if (tile.get_type() == TileType::Win) {
      particles.emplace_back(guest.get_position(), ParticleType::Rescue);
      guests_rescued++;
      guest.set_is_dead(true);
      return true;
    }

    if (tile.get_type() == TileType::DirectionalNorth) {
      guest.set_direction(Direction::North);
    }
    if (tile.get_type() == TileType::DirectionalEast) {
      guest.set_direction(Direction::East);
    }
    if (tile.get_type() == TileType::DirectionalSouth) {
      guest.set_direction(Direction::South);
    }
    if (tile.get_type() == TileType::DirectionalWest) {
      guest.set_direction(Direction::West);
    }

    if (tile.get_type() == TileType::Umbrella) {
      if (guest.give_umbrella()) {
        money += GameBalance::UMBRELLA_GAIN;
        particles.emplace_back(guest.get_position(), ParticleType::Coin);
      }
    }
  }

  return false;
}

void resolve_off_map(Guest& guest,
                     std::vector<Particle>& particles,
                     int& guests_died_falling) {
  const auto pos = guest.get_position();
  const bool in_screen = pos.x > 0 && pos.x < 1920 && pos.y > 0 && pos.y < 1080;

  if (in_screen) {
    return;
  }

  guest.set_is_dead(true);
  Message::send_message(guest.get_name() + " has died from drowning.");
  particles.emplace_back(pos, ParticleType::Death);
  guests_died_falling++;
}

void resolve_off_map(Cart& cart) {
  const auto pos = cart.get_position();
  const bool in_screen = pos.x > 0 && pos.x < 1920 && pos.y > 0 && pos.y < 1080;

  if (in_screen) {
    return;
  }

  cart.set_is_dead(true);
}

bool resolve_vs_enemies(Guest& guest,
                        std::vector<Enemy>& enemies,
                        std::vector<Particle>& particles,
                        int& guests_died_enemies) {
  const asw::Quadf guest_quad =
      asw::Quadf(guest.get_position() - asw::Vec2f(8, 12), asw::Vec2f(16, 24));

  for (auto& enemy : enemies) {
    const asw::Quadf enemy_quad =
        asw::Quadf(enemy.get_position(), asw::Vec2f(100, 100));

    if (!guest_quad.collides(enemy_quad)) {
      continue;
    }

    Message::send_message(guest.get_name() +
                          " has died from an angry octopus.");
    particles.emplace_back(guest.get_position(), ParticleType::Death);
    guests_died_enemies++;

    if (guest.get_velocity() != asw::Vec2f(0, 0)) {
      particles.emplace_back(guest.get_position() + asw::Vec2f(32, 32),
                             ParticleType::Hit);
    }

    enemy.apply_damage(guest.get_velocity().magnitude());
    guest.set_is_dead(true);
    return true;
  }

  return false;
}

bool resolve_vs_enemies(Cart& cart,
                        std::vector<Enemy>& enemies,
                        std::vector<Particle>& particles) {
  const asw::Quadf cart_quad =
      asw::Quadf(cart.get_position() - asw::Vec2f(8, 12), asw::Vec2f(16, 24));

  for (auto& enemy : enemies) {
    const asw::Quadf enemy_quad =
        asw::Quadf(enemy.get_position(), asw::Vec2f(498, 297));

    if (!cart_quad.collides(enemy_quad)) {
      continue;
    }

    particles.emplace_back(cart.get_position(), ParticleType::Hit);

    enemy.apply_damage(cart.get_velocity().magnitude());
    cart.set_is_dead(true);
    return true;
  }

  return false;
}

}  // namespace CollisionSystem
