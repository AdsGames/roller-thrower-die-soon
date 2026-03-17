#pragma once

#include <asw/asw.h>

#include "Message.h"
#include "tools.h"

class Guest {
 public:
  Guest() = default;
  Guest(int x, int y);
  virtual ~Guest() = default;

  virtual void draw() const;
  virtual void update();

  int getX() const { return x; }
  int getY() const { return y; }
  void setX(int d) {
    x = d;  // XD loL
  }
  void setY(int d) { y = d; }
  void setDirection(int d) { direction = d; }
  void setVelocityX(float bx) { x_velocity = bx; }
  void setVelocityY(float by) { y_velocity = by; }
  int getVelocityX() const { return x_velocity; }
  int getVelocityY() const { return y_velocity; }
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
  asw::Texture spritesheet[43];
  asw::Texture spritesheet_panic[25];

  float x = 0;
  float y = 0;
  float x_velocity = 0;
  float y_velocity = 0;

  int frame = 0;
  int frame_panic = 0;
  int direction = 0;
  bool captured = false;
  bool has_umbrella = false;
  bool is_cart = false;

 private:
  std::string name;
  std::string inital;
};
