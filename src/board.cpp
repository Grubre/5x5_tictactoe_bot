#include "board.hpp"

Board::Board() { board.fill({ { Marker::NONE, Marker::NONE, Marker::NONE, Marker::NONE, Marker::NONE } }); }
Board::Board(const std::string& a) {
    for(int i = 0; i < 25; i++) {
        int row = i / 5;
        int col = i % 5;
        Marker m;
        if(a[i] == 'X') m = Marker::X;
        else if(a[i] == 'O') m = Marker::O;
        else m = Marker::NONE;
        board[row][col] = m;
    }
}

Board::Board(uint64_t value) {
    for(auto& i : board) {
        for(auto& j : i) {
            j = (Marker)(value % 3);
            value /= 3;
        }
    }
}

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


auto Board::marker_cnt() const -> int {
    auto cnt = 0;
    for(auto& row : board) {
        for(auto marker : row) {
            cnt += (marker != Marker::NONE);
        }
    }
    return cnt;
}

void const Board::print_board() const
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

auto Board::begin() -> decltype(board.begin()) {
    return board.begin();
}

auto Board::end() -> decltype(board.end()) {
    return board.end();
}

auto Board::begin() const -> decltype(board.begin()) {
    return board.begin();
}

auto Board::end() const -> decltype(board.end()) {
    return board.end();
}

auto Board::to_str() const -> std::string {
    std::string a;
    for(int i = 0; i < 25; i++) {
        int row = i / 5;
        int col = i % 5;
        if(board[row][col] == Marker::X) a += 'X';
        else if(board[row][col] == Marker::O) a += 'O';
        else a += '-';
    }

    return a;
}

auto Board::to_ll() const -> uint64_t {
    uint64_t factor = 1;
    uint64_t value = 0;
    for(auto& row : board) {
        for(auto val : row) {
            value += (int)val * factor;
            factor *= 3;
        }
    }
    
    return value;
}

std::ostream& operator<<(std::ostream& os, const Marker& marker) {
    switch (marker) {
        case Marker::NONE:
            os << "NONE";
            break;
        case Marker::X:
            os << "X";
            break;
        case Marker::O:
            os << "O";
            break;
        case Marker::ANY:
            os << "ANY";
            break;
    }
    return os;
}


