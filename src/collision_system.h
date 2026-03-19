#pragma once

#include <vector>

#include "cart.h"
#include "enemy.h"
#include "guest.h"
#include "particle.h"
#include "tile.h"

namespace CollisionSystem {

// Handles water/win/directional/umbrella tile interactions.
// Returns true if the guest was removed (water or win tile).
bool resolve_vs_tiles(Guest& guest,
                      const std::vector<Tile>& tiles,
                      std::vector<Particle>& particles,
                      int& money,
                      int& guests_rescued,
                      int& guests_died_falling);

// Returns true if the guest is off the map and should be removed.
void resolve_off_map(Guest& guest,
                     std::vector<Particle>& particles,
                     int& guests_died_falling);

// Returns true if the cart is off the map and should be removed.
void resolve_off_map(Cart& cart);

// Returns true if the guest collided with an enemy and should be removed.
bool resolve_vs_enemies(Guest& guest,
                        std::vector<Enemy>& enemies,
                        std::vector<Particle>& particles,
                        int& guests_died_enemies);

// Returns true if the cart collided with an enemy and should be removed.
bool resolve_vs_enemies(Cart& cart,
                        std::vector<Enemy>& enemies,
                        std::vector<Particle>& particles);

}  // namespace CollisionSystem
