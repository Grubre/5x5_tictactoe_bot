#pragma once
#include "board.hpp"
#include <functional>
#include <limits>
#include <utility>

using heuristic_func = const std::function<int(const Board &, Marker)> &;

auto minimax(Board &board,
  heuristic_func evaluate_board,
  int depth,
  Marker current_player,
  Marker maximizing_player,
  int alpha,
  int beta) -> int;

auto find_best_move(Board &board, heuristic_func evaluate_board, Marker current_player, int depth) -> int;
