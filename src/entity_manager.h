#pragma once

#include <vector>

#include "cart.h"
#include "enemy.h"
#include "guest.h"
#include "particle.h"

class EntityManager {
 public:
  void clear();

  void spawn_guest(const asw::Vec2f& pos);
  void spawn_cart(const asw::Vec2f& pos);
  void add_guest(Guest guest);
  void spawn_enemy(int x, int y);
  void spawn_particle(const asw::Vec2f& pos, ParticleType type);

  void update_guests(float dt);
  void update_carts(float dt);
  void update_enemies(float dt);
  void update_particles(float dt);

  void draw_guests() const;
  void draw_carts() const;
  void draw_enemies() const;
  void draw_particles() const;

  std::vector<Guest>& guests() { return _guests; }
  std::vector<Cart>& carts() { return _carts; }
  std::vector<Enemy>& enemies() { return _enemies; }
  std::vector<Particle>& particles() { return _particles; }

 private:
  std::vector<Guest> _guests;
  std::vector<Cart> _carts;
  std::vector<Enemy> _enemies;
  std::vector<Particle> _particles;
};
