#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../src/board.hpp"
#include "../src/heuristic.hpp"

TEST_CASE("check_wins_horizontal") {
    Board board;
    board.set_cell(0, 0, Marker::X);
    board.set_cell(0, 1, Marker::X);
    board.set_cell(0, 2, Marker::X);
    CHECK(board.check_winner() == Marker::O);
}

TEST_CASE("check_wins_vertical") {
    Board board;
    board.set_cell(0, 0, Marker::X);
    board.set_cell(1, 0, Marker::X);
    board.set_cell(2, 0, Marker::X);
    CHECK(board.check_winner() == Marker::O);
}

TEST_CASE("check_wins_diagonal") {
    Board board;
    board.set_cell(0, 0, Marker::X);
    board.set_cell(1, 1, Marker::X);
    board.set_cell(2, 2, Marker::X);
    CHECK(board.check_winner() == Marker::O);
}

TEST_CASE("check_wins_antidiagonal") {
    Board board;
    board.set_cell(4, 1, Marker::X);
    board.set_cell(3, 2, Marker::X);
    board.set_cell(2, 3, Marker::X);
    CHECK(board.check_winner() == Marker::O);
}

TEST_CASE("check_func") {
    Board board;

    board.set_cell(0, 0, Marker::O);
    board.set_cell(0, 1, Marker::O);

    board.set_cell(2, 0, Marker::X);
    board.set_cell(2, 2, Marker::X);
    board.set_cell(2, 3, Marker::X);
    
    board.print_board();

    std::cout << "Evaluation = " << evaluate_board(board, Marker::X) << std::endl;;
    CHECK(false);
}
