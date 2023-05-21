#pragma once
#include "board.hpp"
#include <array>

auto evaluate_board(const Board &board, Marker current_player, int depth) -> int;
