#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../src/board.hpp"

TEST_CASE("check_wins") {
    Board board;
    board.set_cell(0, 0, Marker::X);
    board.set_cell(1, 0, Marker::X);
    board.set_cell(2, 0, Marker::X);
    board.print_board();
    CHECK(board.check_winner() == Marker::O);
}
