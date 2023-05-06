#include "minimax.hpp"

#include <utility>

auto evaluate_board(const Board &board) -> int{
    return 0;
}

auto minimax(Board& board, int depth, Marker current_player, int alpha, int beta) -> int {
    auto winner = board.check_winner();

    if (winner != Marker::NONE) {
        return evaluate_board(board); // You need to define this function.
    }

    if (depth == 0) {
        return evaluate_board(board); // You need to define this function.
    }

    auto is_maximizing_player = (current_player == Marker::X);
    auto best_value = is_maximizing_player ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    auto next_player = is_maximizing_player ? Marker::O : Marker::X;

    for (auto row = 0; row < 5; ++row) {
        for (auto col = 0; col < 5; ++col) {
            if (board.get_cell(row, col) == Marker::NONE) {
                board.set_cell(row, col, current_player);
                auto value = minimax(board, depth - 1, next_player, alpha, beta);
                board.set_cell(row, col, Marker::NONE);

                if (is_maximizing_player) {
                    best_value = std::max(best_value, value);
                    alpha = std::max(alpha, best_value);
                } else {
                    best_value = std::min(best_value, value);
                    beta = std::min(beta, best_value);
                }

                if (beta <= alpha) {
                    break;
                }
            }
        }
    }

    return best_value;
}

auto find_best_move(Board& board, Marker current_player, int depth) -> int {
    auto best_value = std::numeric_limits<int>::min();
    auto best_move = -1;
    auto alpha = std::numeric_limits<int>::min();
    auto beta = std::numeric_limits<int>::max();

    for (auto row = 0; row < 5; ++row) {
        for (auto col = 0; col < 5; ++col) {
            if (board.get_cell(row, col) == Marker::NONE) {
                board.set_cell(row, col, current_player);
                auto move_value = minimax(board, depth - 1, current_player == Marker::X ? Marker::O : Marker::X, alpha, beta);
                board.set_cell(row, col, Marker::NONE);

                if (move_value > best_value) {
                    best_value = move_value;
                    best_move = row * 10 + col + 11;
                }
            }
        }
    }

    return best_move;
}

