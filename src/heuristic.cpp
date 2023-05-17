#include "heuristic.hpp"
#include "board.hpp"

auto evaluate_board(const std::array<int, 4> &params,
  const Board &board,
  Marker current_player,
  int turn,
  Marker winner) -> int
{
    int my_4s = 0;
    int enemy_4s = 0;
    int my_3s = 0;
    int enemy_3s = 0;
    int my_2s = 0;
    int enemy_2s = 0;

        // return 30 * my_4s - 20 * enemy_4s - 10 * my_3s + 10 * enemy_3s + my_2s - enemy_2s;
    return params[0] * my_2s + params[1] * enemy_2s + 0 + 0;
}


// TODO:
// Sprawdzac czworki i trojki razem i zliczac trojki tylko jesli nie sa
// czescia jakiejs czworki
// zepsuty kod ktory mial to robic:
/*
 *
    auto check_sequence = [&](int count_X, int count_O) {
        if (count_X == 4) {
            (current_player == Marker::X) ? my_4s++ : enemy_4s++;
        } else if (count_O == 4) {
            (current_player == Marker::X) ? enemy_4s++ : my_4s++;
        } else if (count_X == 3 && count_O == 0) {
            (current_player == Marker::X) ? my_3s++ : enemy_3s++;
        } else if (count_O == 3 && count_X == 0) {
            (current_player == Marker::X) ? enemy_3s++ : my_3s++;
        } else if (count_X == 2 && count_O == 0) {
            (current_player == Marker::X) ? my_2s++ : enemy_2s++;
        } else if (count_O == 2 && count_X == 0) {
            (current_player == Marker::X) ? enemy_2s++ : my_2s++;
        }
    };

    // Check for horizontal groups
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 2; ++col) {
            int consecutive_X = 0;
            int consecutive_O = 0;
            for (int k = 0; k < 4; ++k) {
                if (board.get_cell(row, col + k) == Marker::X) {
                    consecutive_X++;
                } else if (board.get_cell(row, col + k) == Marker::O) {
                    consecutive_O++;
                }
            }
            check_sequence(consecutive_X, consecutive_O);
        }
    }

    // Check for vertical groups
    for (int col = 0; col < 5; ++col) {
        for (int row = 0; row < 2; ++row) {
            int consecutive_X = 0;
            int consecutive_O = 0;
            for (int k = 0; k < 4; ++k) {
                if (board.get_cell(row + k, col) == Marker::X) {
                    consecutive_X++;
                } else if (board.get_cell(row + k, col) == Marker::O) {
                    consecutive_O++;
                }
            }
            check_sequence(consecutive_X, consecutive_O);
        }
    }

    // Check for main diagonals
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            int consecutive_X = 0;
            int consecutive_O = 0;
            for (int k = 0; k < 4; ++k) {
                if (board.get_cell(i + k, j + k) == Marker::X) {
                    consecutive_X++;
                } else if (board.get_cell(i + k, j + k) == Marker::O) {
                    consecutive_O++;
                }
            }
            check_sequence(consecutive_X, consecutive_O);
        }
    }

    // Check for anti-diagonals
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {// change this line
            int consecutive_X = 0;
            int consecutive_O = 0;
            for (int k = 0; k < 4; ++k) {
                if (board.get_cell(i + k, j + 3 - k) == Marker::X) {// change this line
                    consecutive_X++;
                } else if (board.get_cell(i + k, j + 3 - k) == Marker::O) {// change this line
                    consecutive_O++;
                }
            }
            check_sequence(consecutive_X, consecutive_O);
        }
    }
 */
