#include "board.hpp"

Board::Board() { board.fill({ { Marker::NONE, Marker::NONE, Marker::NONE, Marker::NONE, Marker::NONE } }); }

void Board::set_cell(int row, int col, Marker player)
{
    if (row >= 0 && row < 5 && col >= 0 && col < 5) { board[row][col] = player; }
}

[[nodiscard]] auto Board::get_cell(int row, int col) const -> Marker
{
    if (row >= 0 && row < 5 && col >= 0 && col < 5) { return board[row][col]; }
    return Marker::NONE;
}

[[nodiscard]] auto Board::check_winner() const -> Marker
{
    for (const auto &winLine : win) {
        auto a = board[winLine[0][0]][winLine[0][1]];
        auto b = board[winLine[1][0]][winLine[1][1]];
        auto c = board[winLine[2][0]][winLine[2][1]];
        auto d = board[winLine[3][0]][winLine[3][1]];

        if (a == b && b == c && c == d && a != Marker::NONE) { return a; }
    }

    for (const auto &loseLine : lose) {
        auto a = board[loseLine[0][0]][loseLine[0][1]];
        auto b = board[loseLine[1][0]][loseLine[1][1]];
        auto c = board[loseLine[2][0]][loseLine[2][1]];

        if (a == b && b == c && a != Marker::NONE) { return get_opponent(a); }
    }

    return Marker::NONE;
}

void Board::print_board()
{
    std::cout << "  1 2 3 4 5\n";
    for (int i = 0; i < 5; i++) {
        std::cout << i + 1;
        for (const auto &cell : board[i]) {
            switch (cell) {
            case Marker::NONE:
                std::cout << " -";
                break;
            case Marker::X:
                std::cout << " X";
                break;
            case Marker::O:
                std::cout << " O";
                break;
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
