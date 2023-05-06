#pragma once
#include <iostream>
#include <array>
#include <concepts>

enum class Marker { NONE, X, O };

class Board {
public:

    Board();
    void set_cell(int row, int col, Marker player);
    [[nodiscard]] auto get_cell(int row, int col) const -> Marker;
    [[nodiscard]] auto check_winner() const -> Marker;
    void print_board();
private:
    std::array<std::array<Marker, 5>, 5> board{};
};

inline auto get_opponent(Marker mark) -> Marker {
    return Marker{3 - (int)mark};
}
