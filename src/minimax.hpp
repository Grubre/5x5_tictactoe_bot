#pragma once
#include "board.hpp"
#include <limits>
#include <utility>

auto minimax(Board &board, int depth, bool is_maximizing_player, int alpha, int beta) -> int;
auto find_best_move(Board &board, Marker current_player, int depth) -> int;
