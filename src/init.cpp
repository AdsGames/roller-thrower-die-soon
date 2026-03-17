#include "init.h"

namespace {
asw::Music game_music;
}

void Init::update(float dt) {
  game_music = asw::assets::load_music("assets/music/RollerCoasterTydoom.ogg");
  asw::sound::play_music(game_music);

  manager.set_next_scene(ProgramStates::Menu);
}
