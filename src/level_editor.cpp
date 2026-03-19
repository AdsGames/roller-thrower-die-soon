#include "level_editor.h"

#include <asw/asw.h>

#include "game_balance.h"
#include "tile.h"

void LevelEditor::handle_input(TileMap& tile_map, int& money) {
  if (!asw::input::get_mouse_button(asw::input::MouseButton::Left)) {
    return;
  }

  for (auto& tile : tile_map.tiles()) {
    if (!tile_map.can_place_tile(tile.get_position())) {
      continue;
    }

    if (!tile.colliding(asw::input::mouse.position)) {
      continue;
    }

    switch (_current_tool) {
      case EditorTool::PlacePathEast:
        tile = Tile(tile.get_position(), TileType::DirectionalEast);
        money -= GameBalance::PATH_COST;
        _current_tool = EditorTool::Grabber;
        return;

      case EditorTool::PlacePathSouth:
        tile = Tile(tile.get_position(), TileType::DirectionalSouth);
        money -= GameBalance::PATH_COST;
        _current_tool = EditorTool::Grabber;
        return;

      case EditorTool::PlacePathWest:
        tile = Tile(tile.get_position(), TileType::DirectionalWest);
        money -= GameBalance::PATH_COST;
        _current_tool = EditorTool::Grabber;
        return;

      case EditorTool::PlacePathNorth:
        tile = Tile(tile.get_position(), TileType::DirectionalNorth);
        money -= GameBalance::PATH_COST;
        _current_tool = EditorTool::Grabber;
        return;

      case EditorTool::PlaceCoaster:
        tile = Tile(tile.get_position(), TileType::Coaster);
        money -= GameBalance::COASTER_COST;
        _current_tool = EditorTool::Grabber;
        return;

      default:
        break;
    }
  }
}
