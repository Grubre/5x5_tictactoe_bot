#include "heuristic.hpp"
#include "board.hpp"
#include <algorithm>
#include <array>
#include <optional>

/*
 Heurystyka szuka roznych wzorow na planszy i zwraca je z odpowiadajacymi wagami
 przykladowe wzorce
 *X*
 O-*
 *X*
 *X*
 XX_X
 X_XX
*/

struct Pattern
{
    std::vector<std::vector<Marker>> pattern;
    Marker winner;
    int value;
};

static const std::vector<Pattern> patterns_4x3 = {
    { { { Marker::ANY, Marker::X, Marker::ANY },
        { Marker::O, Marker::NONE, Marker::O },
        { Marker::ANY, Marker::X, Marker::ANY },
        { Marker::ANY, Marker::X, Marker::ANY } },
      Marker::X,
      10000 },

    { { { Marker::O, Marker::X, Marker::ANY },
        { Marker::ANY, Marker::NONE, Marker::ANY },
        { Marker::ANY, Marker::X, Marker::O },
        { Marker::ANY, Marker::X, Marker::ANY } },
      Marker::X,
      10000 },

    { { { Marker::ANY, Marker::X, Marker::O },
        { Marker::ANY, Marker::NONE, Marker::ANY },
        { Marker::O, Marker::X, Marker::ANY },
        { Marker::ANY, Marker::X, Marker::ANY } },
      Marker::X,
      10000 },

    { { { Marker::ANY, Marker::O, Marker::ANY },
        { Marker::X, Marker::NONE, Marker::X },
        { Marker::ANY, Marker::O, Marker::ANY },
        { Marker::ANY, Marker::O, Marker::ANY } },
      Marker::O,
      10000 },

    { { { Marker::X, Marker::O, Marker::ANY },
        { Marker::ANY, Marker::NONE, Marker::ANY },
        { Marker::ANY, Marker::O, Marker::X },
        { Marker::ANY, Marker::O, Marker::ANY } },
      Marker::O,
      10000 },

    { { { Marker::ANY, Marker::O, Marker::X },
        { Marker::ANY, Marker::NONE, Marker::ANY },
        { Marker::X, Marker::O, Marker::ANY },
        { Marker::ANY, Marker::O, Marker::ANY } },
      Marker::O,
      10000 },
};

static const std::vector<Pattern> patterns_3x4 = {

    { { { Marker::ANY, Marker::ANY, Marker::O, Marker::ANY },
        { Marker::X, Marker::X, Marker::NONE, Marker::X },
        { Marker::ANY, Marker::ANY, Marker::O, Marker::ANY } },
      Marker::X,
      10000 },
    { { { Marker::ANY, Marker::O, Marker::ANY, Marker::ANY },
        { Marker::X, Marker::X, Marker::NONE, Marker::X },
        { Marker::ANY, Marker::ANY, Marker::ANY, Marker::O } },
      Marker::X,
      10000 },
    { { { Marker::ANY, Marker::ANY, Marker::ANY, Marker::O },
        { Marker::X, Marker::X, Marker::NONE, Marker::X },
        { Marker::ANY, Marker::O, Marker::ANY, Marker::ANY } },
      Marker::X,
      10000 },


    { { { Marker::ANY, Marker::O, Marker::ANY, Marker::ANY },
        { Marker::X, Marker::ANY, Marker::X, Marker::X },
        { Marker::ANY, Marker::O, Marker::ANY, Marker::ANY } },
      Marker::X,
      10000 },
    { { { Marker::ANY, Marker::ANY, Marker::O, Marker::ANY },
        { Marker::X, Marker::ANY, Marker::X, Marker::X },
        { Marker::O, Marker::ANY, Marker::ANY, Marker::ANY } },
      Marker::X,
      10000 },
    { { { Marker::O, Marker::ANY, Marker::ANY, Marker::ANY },
        { Marker::X, Marker::ANY, Marker::X, Marker::X },
        { Marker::ANY, Marker::ANY, Marker::O, Marker::ANY } },
      Marker::X,
      10000 },


    { { { Marker::ANY, Marker::ANY, Marker::X, Marker::ANY },
        { Marker::O, Marker::O, Marker::NONE, Marker::O },
        { Marker::ANY, Marker::ANY, Marker::X, Marker::ANY } },
      Marker::O,
      10000 },
    { { { Marker::ANY, Marker::X, Marker::ANY, Marker::ANY },
        { Marker::O, Marker::O, Marker::NONE, Marker::O },
        { Marker::ANY, Marker::ANY, Marker::ANY, Marker::X } },
      Marker::O,
      10000 },
    { { { Marker::ANY, Marker::ANY, Marker::ANY, Marker::X },
        { Marker::O, Marker::O, Marker::NONE, Marker::O },
        { Marker::ANY, Marker::X, Marker::ANY, Marker::ANY } },
      Marker::O,
      10000 },


    { { { Marker::ANY, Marker::X, Marker::ANY, Marker::ANY },
        { Marker::O, Marker::ANY, Marker::O, Marker::O },
        { Marker::ANY, Marker::X, Marker::ANY, Marker::ANY } },
      Marker::O,
      10000 },
    { { { Marker::ANY, Marker::ANY, Marker::X, Marker::ANY },
        { Marker::O, Marker::ANY, Marker::O, Marker::O },
        { Marker::X, Marker::ANY, Marker::ANY, Marker::ANY } },
      Marker::O,
      10000 },
    { { { Marker::X, Marker::ANY, Marker::ANY, Marker::ANY },
        { Marker::O, Marker::ANY, Marker::O, Marker::O },
        { Marker::ANY, Marker::ANY, Marker::X, Marker::ANY } },
      Marker::O,
      10000 },


};

auto check_pattern(const Board &board, const Pattern &pattern, int r, int c) -> std::optional<Marker>
{
    for (int i = 0; i < pattern.pattern.size(); ++i) {
        for (int j = 0; j < pattern.pattern[0].size(); ++j) {
            if (pattern.pattern[i][j] != Marker::ANY && board[r + i][c + j] != pattern.pattern[i][j]) {
                return std::nullopt;
            }
        }
    }
    return pattern.winner;
}

auto check_for_patterns(const Board &board, const std::vector<Pattern> &patterns) -> std::optional<Pattern>
{
    for (const auto &pattern : patterns) {
        for (int r = 0; r <= 5 - pattern.pattern.size(); ++r) {
            for (int c = 0; c <= 5 - pattern.pattern[0].size(); ++c) {
                auto winner = check_pattern(board, pattern, r, c);
                if (winner) { return pattern; }
            }
        }
    }
    return std::nullopt;
}


auto cnt_almost_fours(const Board &board) -> std::pair<int, int>
{
    std::pair<int, int> count{ 0, 0 };

    for (const auto &pattern : win) {
        std::array<Marker, 4> markers{};
        for (int i = 0; i < 4; ++i) { markers[i] = board.get_cell(pattern[i][0], pattern[i][1]); }

        // Check for X_XX, XX_X
        if ((markers[0] == Marker::X && markers[1] == Marker::NONE && markers[2] == Marker::X
              && markers[3] == Marker::X)
            || (markers[0] == Marker::X && markers[1] == Marker::X && markers[2] == Marker::NONE
                && markers[3] == Marker::X)) {
            ++count.first;
        }

        // Check for O_OO, OO_O
        if ((markers[0] == Marker::O && markers[1] == Marker::NONE && markers[2] == Marker::O
              && markers[3] == Marker::O)
            || (markers[0] == Marker::O && markers[1] == Marker::O && markers[2] == Marker::NONE
                && markers[3] == Marker::O)) {
            ++count.second;
        }
    }

    return count;
}


auto cnt_potential_twos(const Board &board) -> std::pair<int, int>
{
    std::pair<int, int> count{ 0, 0 };

    for (const auto &pattern : win) {
        std::array<Marker, 4> markers{};
        for (int i = 0; i < 4; ++i) { markers[i] = board.get_cell(pattern[i][0], pattern[i][1]); }

        if(markers[0] == Marker::X && markers[1] == Marker::X && markers[2] == Marker::NONE && markers[3] == Marker::NONE) {
            ++count.first;
        }

        if(markers[0] == Marker::O && markers[1] == Marker::O && markers[2] == Marker::NONE && markers[3] == Marker::NONE) {
            ++count.second;
        }
    }

    return count;
}



auto evaluate_board(const Board &board, Marker current_player, int turn) -> int
{
    auto [x_almost_fours, o_almost_fours] = cnt_almost_fours(board);
    auto [x_potential_twos, o_potential_twos] = cnt_potential_twos(board);
    int enemy_almost_fours = 0;
    int my_almost_fours = 0;
    int enemy_potential_twos = 0;
    int my_potential_twos = 0;

    auto eval = 0;

    if (current_player == Marker::X) {
        enemy_almost_fours += o_almost_fours;
        my_almost_fours += x_almost_fours;
        enemy_potential_twos += o_potential_twos;
        my_potential_twos += x_potential_twos;
    } else {
        enemy_almost_fours += x_almost_fours;
        my_almost_fours += o_almost_fours;
        enemy_potential_twos += x_potential_twos;
        my_potential_twos += o_potential_twos;
    }

    if (my_almost_fours == 0 && enemy_almost_fours > 0) { eval -= 100; }
    if (my_almost_fours > 0 && enemy_almost_fours == 0) { eval += 100; }

    auto pattern_3x4 = check_for_patterns(board, patterns_3x4);

    if (pattern_3x4) {
        auto p = pattern_3x4.value();
        if (p.winner == current_player) {
            eval += p.value;
        } else {
            eval -= p.value;
        }
    }

    auto pattern_4x3 = check_for_patterns(board, patterns_3x4);

    if (pattern_4x3) {
        auto p = pattern_4x3.value();
        if (p.winner == current_player) {
            eval += p.value;
        } else {
            eval -= p.value;
        }
    }


    return eval + my_almost_fours * 40 - enemy_almost_fours * 30 + my_potential_twos * 15 - enemy_potential_twos * 12;
}
