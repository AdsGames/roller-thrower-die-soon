#include "init.h"

void Init::update(float dt) {
  _game_music = asw::assets::load_music("assets/music/RollerCoasterTydoom.ogg");
  asw::sound::play_music(_game_music);
  manager.set_next_scene(ProgramStates::Menu);
}
