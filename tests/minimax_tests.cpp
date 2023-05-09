#include "../external/doctest.h"
#include "../src/board.hpp"
#include "../src/minimax.hpp"

TEST_CASE("Minimax winning scenario")
{
    Board board;
    // Create a board state where the current player (Marker::X) can win in the next move.
    board.set_cell(0, 0, Marker::X);
    board.set_cell(0, 1, Marker::X);
    board.set_cell(0, 2, Marker::NONE);
    board.set_cell(0, 3, Marker::X);

    std::function<int(const Board &, Marker)> evaluator = [](const Board &board, Marker maximizing_player) {
        auto winner = board.check_winner();
        if (winner == maximizing_player) { return 1; }
        if (winner == get_opponent(maximizing_player)) { return -1; }
        return 0;
    };

    int depth = 1;
    Marker current_player = Marker::X;
    Marker maximizing_player = Marker::X;
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();

    int result = minimax(board, evaluator, depth, current_player, maximizing_player, alpha, beta);
    CHECK(result == 1);
}