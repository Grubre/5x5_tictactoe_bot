#pragma once
#include "board.hpp"
#include <array>

auto evaluate_board(const std::array<int, 4> &params,
  const Board &board,
  Marker current_player,
  int depth,
  Marker winner) -> int;
