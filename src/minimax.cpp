#include "minimax.hpp"
#include "heuristic.hpp"

#include <algorithm>
#include <future>
#include <utility>
#include <vector>

auto minimax(Board &board, int depth, Marker current_player, Marker maximizing_player, int alpha, int beta) -> int
{
    auto winner = board.check_winner();

    if (winner != Marker::NONE) { return evaluate_board(board, maximizing_player); }

    if (depth == 0) { return evaluate_board(board, maximizing_player); }

    auto is_maximizing_player = (current_player == maximizing_player);
    auto best_value = is_maximizing_player ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    auto next_player =
      is_maximizing_player ? (maximizing_player == Marker::X ? Marker::O : Marker::X) : maximizing_player;

    bool pruning_occurred = false;

    for (auto row = 0; row < 5 && !pruning_occurred; ++row) {
        for (auto col = 0; col < 5; ++col) {
            if (board.get_cell(row, col) == Marker::NONE) {
                board.set_cell(row, col, current_player);
                auto value = minimax(board, depth - 1, next_player, maximizing_player, alpha, beta);
                board.set_cell(row, col, Marker::NONE);

                if (is_maximizing_player) {
                    best_value = std::max(best_value, value);
                    alpha = std::max(alpha, best_value);
                } else {
                    best_value = std::min(best_value, value);
                    beta = std::min(beta, best_value);
                }

                if (beta <= alpha) {
                    pruning_occurred = true;
                    break;
                }
            }
        }
    }

    return best_value;
}

auto find_best_move(Board &board, Marker current_player, int depth) -> int
{
    auto best_value = std::numeric_limits<int>::min();
    auto best_move = -1;
    auto alpha = std::numeric_limits<int>::min();
    auto beta = std::numeric_limits<int>::max();
    std::vector<std::future<std::pair<int, int>>> futures;

    for (auto row = 0; row < 5; ++row) {
        for (auto col = 0; col < 5; ++col) {
            if (board.get_cell(row, col) == Marker::NONE) {
                Board board_copy = board;
                futures.push_back(
                  std::async(std::launch::async, [board_copy, row, col, current_player, depth, alpha, beta]() mutable {
                      board_copy.set_cell(row, col, current_player);
                      auto move_value = minimax(board_copy,
                        depth - 1,
                        current_player == Marker::X ? Marker::O : Marker::X,
                        current_player,
                        alpha,
                        beta);
                      board_copy.set_cell(row, col, Marker::NONE);
                      return std::make_pair(move_value, row * 10 + col + 11);
                  }));
            }
        }
    }

    for (auto &future : futures) {
        auto result = future.get();
        std::cout << "move: " << result.second << ", value: " << result.first << std::endl;

        if (result.first > best_value) {
            best_value = result.first;
            best_move = result.second;
        }
    }

    return best_move;
}
