#pragma once

#include <asw/asw.h>
#include <array>

#include "Direction.h"
#include "Message.h"

class Guest {
 public:
  Guest() = default;
  explicit Guest(const asw::Vec2<float>& position);

  Guest(const Guest& other) = default;
  virtual ~Guest() = default;

  virtual void draw() const;
  virtual void update(float dt);

  // Position offset to feet
  asw::Vec2<float> getPosition() const {
    return asw::Vec2<float>(position.x, position.y + 12);
  }

  void setPosition(const asw::Vec2<float>& pos) { position = pos; }

  void setVelocity(const asw::Vec2<float>& v) { velocity = v; }
  const asw::Vec2<float>& getVelocity() const { return velocity; }

  void setDirection(Direction d) { direction = d; }
  bool getIsCart() const { return is_cart; }
  void setCaptured(bool b) { captured = b; }

  bool giveUmbrella() {
    if (!has_umbrella) {
      has_umbrella = true;
      return true;
    }

    return false;
  }

  std::string getName() const;

  static float speed;

 protected:
  asw::Texture sprite;
  asw::Texture umbrella;
  std::array<asw::Texture, 43> spritesheet;
  std::array<asw::Texture, 25> spritesheet_panic;

  asw::Vec2<float> position;
  asw::Vec2<float> velocity;

  float frame_counter{0.0F};
  Direction direction{Direction::East};
  bool captured{false};
  bool has_umbrella{false};
  bool is_cart{false};

 private:
  constexpr static float MIN_VELOCITY = 0.5F;
  constexpr static float DECELERATION_FACTOR = 0.02F;
  constexpr static float FRAMES_PER_S = 50.0F;
  constexpr static float PIXELS_PER_S = 30.0F;

  std::string name;
  std::string inital;
};
