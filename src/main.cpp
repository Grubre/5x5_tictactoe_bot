#include "board.hpp"
#include "cmdline_args.hpp"
#include "connection.hpp"
#include "game.hpp"
#include "heuristic.hpp"
#include "minimax.hpp"
#include <fstream>
#include <future>
#include <iostream>
#include <utility>

struct Counters
{
    long long won = 0;
    long long lost = 0;
};

auto winrate(const Counters& counters) -> double {
    return (double)counters.won / (double)(counters.lost + counters.won);
}

std::unordered_map<Board, int> best_move{};
std::unordered_map<Board, double> valuation{};

constexpr int max_depth = 14;
constexpr int save_depth = 10;

auto minimax_bin(Board &board,
  int depth,
  Marker current_player,
  Marker maximizing_player,
  int alpha,
  int beta,
  Counters &counters) -> int
{
    if(!best_move.contains(board)) {
        if(current_player == Marker::X)
            valuation[board] = std::numeric_limits<double>::min();
        else
            valuation[board] = std::numeric_limits<double>::max();
    }
    auto winner = board.check_winner();

    if (winner == maximizing_player) {
        counters.won++;
        return std::numeric_limits<int>::max();
    } else if (winner == get_opponent(maximizing_player)) {
        counters.lost++;
        return std::numeric_limits<int>::min();
    } else if (depth == 0) {
        return 0;
    }

    bool is_maximizing_player = (current_player == maximizing_player);
    auto best_value = is_maximizing_player ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    auto next_player = get_opponent(current_player);

    bool pruning_occurred = false;

    Board board_copy = board;

    for (auto row = 0; row < 5 && !pruning_occurred; ++row) {
        for (auto col = 0; col < 5; ++col) {
            if (board.get_cell(row, col) == Marker::NONE) {
                if(depth == max_depth) {
                    std::cout << row << ", " << col << std::endl;
                }
                board.set_cell(row, col, current_player);

                Counters counters_child;
                auto value = minimax_bin(board, depth - 1, next_player, maximizing_player, alpha, beta, counters_child);
                auto winratio = winrate(counters_child);
                if(current_player == Marker::X) {
                    if(depth >= max_depth - save_depth && winratio >= valuation[board_copy]) {
                        valuation[board_copy] = winratio;
                        best_move[board_copy] = row * 10 + col + 11;
                    }
                }
                else {
                    if(depth >= max_depth - save_depth && winratio <= valuation[board_copy]) {
                        valuation[board_copy] = winratio;
                        best_move[board_copy] = row * 10 + col + 11;
                    }
                }
                counters.won += counters_child.won;
                counters.lost += counters_child.lost;

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

auto main(int argc, char *argv[]) -> int
{
    Board board{};
    auto alpha = std::numeric_limits<int>::min();
    auto beta = std::numeric_limits<int>::max();
    Counters counters{};

    auto x = minimax_bin(board, max_depth, Marker::X, Marker::X, alpha, beta, counters);

    std::ofstream output("output.txt");
    for(auto& [key,value] : best_move) {
        int markers_cnt = 0;
        for(auto& row: key) {
            for(auto marker: row){
                markers_cnt += (marker != Marker::NONE);
            }
        }
        output << key.to_str() << " " << value << (markers_cnt % 2 == 0 ? " X's turn" : " O's turn") << " winrate: " << valuation[key] << std::endl;
    }

    return 0;
}
