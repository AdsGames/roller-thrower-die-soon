#include "entity_manager.h"

#include <algorithm>

void EntityManager::clear() {
  _guests.clear();
  _enemies.clear();
  _particles.clear();
}

void EntityManager::spawn_guest(const asw::Vec2f& pos) {
  _guests.emplace_back(pos);
}

void EntityManager::spawn_cart(const asw::Vec2f& pos) {
  _carts.emplace_back(pos);
}

void EntityManager::add_guest(Guest guest) {
  _guests.push_back(std::move(guest));
}

void EntityManager::spawn_enemy(int x, int y) {
  _enemies.emplace_back(x, y);
}

void EntityManager::spawn_particle(const asw::Vec2f& pos, ParticleType type) {
  _particles.emplace_back(pos, type);
}

void EntityManager::update_guests(float dt) {
  for (auto& guest : _guests) {
    guest.update(dt);
  }

  std::erase_if(_guests, [](const Guest& g) { return g.get_is_dead(); });
}

void EntityManager::update_carts(float dt) {
  for (auto& cart : _carts) {
    cart.update(dt);
  }

  std::erase_if(_carts, [](const Cart& c) { return c.get_is_dead(); });
}

void EntityManager::update_enemies() {
  for (auto& enemy : _enemies) {
    enemy.update();

    if (enemy.get_health() == 0) {
      spawn_particle(enemy.get_position(), ParticleType::EnemyDeath);
    }
  }

  std::erase_if(_enemies, [](const Enemy& e) { return e.get_health() == 0; });
}

void EntityManager::update_particles(float dt) {
  for (auto& particle : _particles) {
    particle.update(dt);
  }

  std::erase_if(_particles, [](const Particle& p) { return p.is_dead(); });
}

void EntityManager::draw_guests() const {
  for (const auto& guest : _guests) {
    guest.draw();
  }
}

void EntityManager::draw_carts() const {
  for (const auto& cart : _carts) {
    cart.draw();
  }
}

void EntityManager::draw_enemies() const {
  for (const auto& enemy : _enemies) {
    enemy.draw();
  }
}

void EntityManager::draw_particles() const {
  for (const auto& particle : _particles) {
    particle.draw();
  }
}
