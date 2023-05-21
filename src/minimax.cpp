#include "minimax.hpp"
#include "board.hpp"
#include <algorithm>
#include <array>
#include <future>
#include <utility>
#include <vector>
#include <random>
#include "patternmap.hpp"

static const pattern_map openings{};

auto minimax(Board &board,
  heuristic_func evaluate_board,
  int depth,
  Marker current_player,
  Marker maximizing_player,
  int alpha,
  int beta) -> int
{
    if(openings.contains(board)) {
        return (depth + 1) * 1000;
    }
    auto winner = board.check_winner();

    if (winner == maximizing_player) {
        return std::numeric_limits<int>::max();
    } else if (winner == get_opponent(maximizing_player)) {
        return std::numeric_limits<int>::min();
    } else if (depth == 0) {
        return evaluate_board(board, maximizing_player, depth); 
    }

    bool is_maximizing_player = (current_player == maximizing_player);
    auto best_value = is_maximizing_player ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    auto next_player = get_opponent(current_player);

    bool pruning_occurred = false;

    for (auto row = 0; row < 5 && !pruning_occurred; ++row) {
        for (auto col = 0; col < 5; ++col) {
            if (board.get_cell(row, col) == Marker::NONE) {
                board.set_cell(row, col, current_player);
                auto value = minimax(board, evaluate_board, depth - 1, next_player, maximizing_player, alpha, beta);
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

auto find_best_move(Board &board, heuristic_func evaluate_board, Marker current_player, int depth) -> int
{
    auto best_value = std::numeric_limits<int>::min();
    auto best_move = -1;
    auto alpha = std::numeric_limits<int>::min();
    auto beta = std::numeric_limits<int>::max();
    auto futures = std::vector<std::future<std::pair<int, int>>>{};

    for (auto row = 0; row < 5; ++row) {
        for (auto col = 0; col < 5; ++col) {
            if (board.get_cell(row, col) == Marker::NONE) {
                futures.push_back(std::async(
                  std::launch::async, [board, evaluate_board, row, col, current_player, depth, alpha, beta]() {
                      Board board_copy = board;
                      board_copy.set_cell(row, col, current_player);
                      auto move_value = minimax(
                        board_copy, evaluate_board, depth - 1, get_opponent(current_player), current_player, alpha, beta);
                      board_copy.set_cell(row, col, Marker::NONE);
                      return std::make_pair(move_value, row * 10 + col + 11);
                  }));
            }
        }
    }

    std::vector<std::pair<int,int>> moves{};
    for (auto &future : futures) {
        auto result = future.get();
        std::cout << "move: " << result.second << ", value: " << result.first << std::endl;
        moves.push_back(result);
    }
    std::sort(moves.begin(), moves.end(), [](const std::pair<int,int>& a, const std::pair<int,int>& b) {
        return a.first > b.first;
    });
    auto best_eval = moves.front().first;
    auto draw_idx = 0;
    while(draw_idx < 25 && moves[draw_idx].first == best_eval) {
        draw_idx++;
    }
    if(draw_idx > 1) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> dist(0, draw_idx - 1);

        best_move = moves[dist(mt)].second;
    } else {
        best_move = moves.front().second;
    }

    return best_move;
}
