#pragma once

#include <asw/asw.h>

#include "tile_map.h"

enum class EditorTool {
  PlacePathEast = 0,
  PlacePathSouth = 1,
  PlacePathWest = 2,
  PlacePathNorth = 3,
  Grabber = 4,
  PlaceCoaster = 5,
};

class LevelEditor {
 public:
  LevelEditor() = default;

  // Handles tile placement clicks — modifies tiles in tile_map and deducts
  // money.
  void handle_input(TileMap& tile_map, int& money);

  EditorTool current_tool() const { return _current_tool; }
  void set_tool(EditorTool tool) { _current_tool = tool; }

 private:
  EditorTool _current_tool{EditorTool::Grabber};
};
