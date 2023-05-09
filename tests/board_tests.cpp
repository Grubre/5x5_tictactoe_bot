#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../src/board.hpp"
#include "../src/heuristic.hpp"

TEST_CASE("Board Initialization")
{
    Board b;
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) { CHECK(b.get_cell(row, col) == Marker::NONE); }
    }
}

TEST_CASE("Board::set_cell and Board::get_cell")
{
    Board b;

    SUBCASE("Valid position")
    {
        b.set_cell(0, 0, Marker::X);
        CHECK(b.get_cell(0, 0) == Marker::X);

        b.set_cell(4, 4, Marker::O);
        CHECK(b.get_cell(4, 4) == Marker::O);
    }

    SUBCASE("Invalid position")
    {
        b.set_cell(-1, 0, Marker::X);
        CHECK(b.get_cell(-1, 0) == Marker::NONE);

        b.set_cell(0, -1, Marker::X);
        CHECK(b.get_cell(0, -1) == Marker::NONE);

        b.set_cell(5, 0, Marker::X);
        CHECK(b.get_cell(5, 0) == Marker::NONE);

        b.set_cell(0, 5, Marker::X);
        CHECK(b.get_cell(0, 5) == Marker::NONE);
    }
}

TEST_CASE("Board::check_winner_hand_picked")
{
    // Test horizontal win
    SUBCASE("horizontal win")
    {
        Board board;
        board.set_cell(0, 0, Marker::X);
        board.set_cell(0, 1, Marker::X);
        board.set_cell(0, 2, Marker::X);
        board.set_cell(0, 3, Marker::X);
        CHECK(board.check_winner() == Marker::X);
    }

    // Test vertical win
    SUBCASE("vertical win")
    {
        Board board;
        board.set_cell(0, 0, Marker::X);
        board.set_cell(0, 0, Marker::X);
        board.set_cell(1, 0, Marker::X);
        board.set_cell(2, 0, Marker::X);
        board.set_cell(3, 0, Marker::X);
        CHECK(board.check_winner() == Marker::X);
    }

    // Test diagonal win (bottom-left to top-right)
    SUBCASE("diagonal win (bottom-left to top-right)")
    {
        Board board;
        board.set_cell(0, 0, Marker::X);
        board.set_cell(1, 0, Marker::X);
        board.set_cell(2, 1, Marker::X);
        board.set_cell(3, 2, Marker::X);
        board.set_cell(4, 3, Marker::X);
        CHECK(board.check_winner() == Marker::X);
    }

    // Test diagonal win (top-left to bottom-right)
    SUBCASE("diagonal win (top-left to bottom-right)")
    {
        Board board;
        board.set_cell(0, 0, Marker::X);
        board.set_cell(0, 0, Marker::X);
        board.set_cell(1, 1, Marker::X);
        board.set_cell(2, 2, Marker::X);
        board.set_cell(3, 3, Marker::X);
        CHECK(board.check_winner() == Marker::X);
    }

    // Test win when there are both four and three in a row
    SUBCASE("win when three in a row")
    {
        Board board;
        board.set_cell(0, 1, Marker::X);
        board.set_cell(1, 1, Marker::X);
        board.set_cell(2, 1, Marker::X);
        board.set_cell(3, 1, Marker::X);

        board.set_cell(2, 0, Marker::X);
        board.set_cell(2, 2, Marker::X);

        board.print_board();
        CHECK(board.check_winner() == Marker::X);
    }

    // Test losing scenarios
    SUBCASE("horizontal lose")
    {
        Board board;
        board.set_cell(0, 0, Marker::X);
        board.set_cell(0, 0, Marker::X);
        board.set_cell(0, 1, Marker::X);
        board.set_cell(0, 2, Marker::X);
        CHECK(board.check_winner() == Marker::O);
    }

    SUBCASE("vertical lose")
    {
        Board board;
        board.set_cell(0, 0, Marker::X);
        board.set_cell(0, 0, Marker::X);
        board.set_cell(1, 0, Marker::X);
        board.set_cell(2, 0, Marker::X);
        CHECK(board.check_winner() == Marker::O);
    }

    SUBCASE("diagonal lose (bottom-left to top-right)")
    {
        Board board;
        board.set_cell(0, 0, Marker::X);
        board.set_cell(1, 0, Marker::X);
        board.set_cell(2, 1, Marker::X);
        board.set_cell(3, 2, Marker::X);
        CHECK(board.check_winner() == Marker::O);
    }

    SUBCASE("diagonal lose (top-left to bottom-right)")
    {
        Board board;
        board.set_cell(0, 0, Marker::X);
        board.set_cell(0, 0, Marker::X);
        board.set_cell(1, 1, Marker::X);
        board.set_cell(2, 2, Marker::X);
        CHECK(board.check_winner() == Marker::O);
    }
}

TEST_CASE("Board::check_winner_arrays")
{
    for (const auto &winLine : win) {
        Board board;
        board.set_cell(winLine[0][0], winLine[0][1], Marker::X);
        board.set_cell(winLine[1][0], winLine[1][1], Marker::X);
        board.set_cell(winLine[2][0], winLine[2][1], Marker::X);
        board.set_cell(winLine[3][0], winLine[3][1], Marker::X);

        CHECK(board.check_winner() == Marker::X);
    }

    for (const auto &loseLine : lose) {
        Board board;
        board.set_cell(loseLine[0][0], loseLine[0][1], Marker::X);
        board.set_cell(loseLine[1][0], loseLine[1][1], Marker::X);
        board.set_cell(loseLine[2][0], loseLine[2][1], Marker::X);

        CHECK(board.check_winner() == Marker::O);
    }
}
