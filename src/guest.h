#pragma once

#include <asw/asw.h>
#include <array>

#include "direction.h"
#include "message.h"

class Guest {
 public:
  Guest() = default;
  explicit Guest(const asw::Vec2f& position);

  Guest(const Guest& other) = default;
  virtual ~Guest() = default;

  virtual void draw() const;
  virtual void update(float dt);

  // Position offset to feet
  asw::Vec2f get_position() const;
  void set_position(const asw::Vec2f& pos);

  void set_velocity(const asw::Vec2f& v);
  const asw::Vec2f& get_velocity() const;

  bool get_is_cart() const;
  void set_direction(Direction d);
  void set_captured(bool b);

  void set_is_dead(bool b);
  bool get_is_dead() const;

  bool give_umbrella();

  std::string get_name() const;

  static float speed;

 protected:
  asw::Texture _umbrella;

  asw::Vec2f _position;
  asw::Vec2f _velocity;

  float _frame_counter{0.0F};
  Direction _direction{Direction::East};
  bool _captured{false};
  bool _has_umbrella{false};
  bool _is_cart{false};
  bool _is_dead{false};

 private:
  constexpr static float MIN_VELOCITY = 0.5F;
  constexpr static float DECELERATION_FACTOR = 0.02F;
  constexpr static float FRAMES_PER_S = 50.0F;

  std::string _name;
  std::string _inital;
};
