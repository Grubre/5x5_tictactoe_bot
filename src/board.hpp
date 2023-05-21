#pragma once
#include <array>
#include <cstdint>
#include <iostream>
#include <functional>
#include <fstream>
#include <unordered_map>


enum class Marker { NONE, X, O, ANY };
std::ostream& operator<<(std::ostream& os, const Marker& marker);

class Board
{
public:
    Board();
    Board(const std::string& a);
    Board(uint64_t value);
    void set_cell(int row, int col, Marker player);
    [[nodiscard]] auto get_cell(int row, int col) const -> Marker;
    [[nodiscard]] auto check_winner() const -> Marker;
    void const print_board() const;

    auto to_str() const -> std::string;
    auto to_ll() const -> uint64_t;

    auto marker_cnt() const -> int;

private:
    std::array<std::array<Marker, 5>, 5> board{};

public:
    auto begin() -> decltype(board.begin());
    auto end() -> decltype(board.end());
    [[nodiscard]] auto begin() const -> decltype(board.begin());
    [[nodiscard]] auto end() const -> decltype(board.end());

    friend auto operator==(const Board& a, const Board& b) -> bool {
        return a.board == b.board;
    }

    friend auto operator!=(const Board& a, const Board& b) -> bool {
        return !(a == b);
    }

    auto operator[](std::size_t index) -> std::array<Marker, 5>& {
        if (index >= 5) {
            throw std::out_of_range("Index out of range");
        }
        return board[index];
    }

    auto operator[](std::size_t index) const -> const std::array<Marker, 5>& {
        if (index >= 5) {
            throw std::out_of_range("Index out of range");
        }
        return board[index];
    }
};

inline auto get_opponent(Marker mark) -> Marker { return Marker{ 3 - (int)mark }; }

constexpr int win[28][4][2] = { { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
    { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 } },
    { { 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 } },
    { { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } },
    { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 } },
    { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 } },
    { { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 } },
    { { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 } },
    { { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 } },
    { { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 } },
    { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } },
    { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } },
    { { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 } },
    { { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 } },
    { { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 } },
    { { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 } },
    { { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 } },
    { { 1, 2 }, { 2, 2 }, { 3, 2 }, { 4, 2 } },
    { { 1, 3 }, { 2, 3 }, { 3, 3 }, { 4, 3 } },
    { { 1, 4 }, { 2, 4 }, { 3, 4 }, { 4, 4 } },
    { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } },
    { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 } },
    { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 } },
    { { 1, 0 }, { 2, 1 }, { 3, 2 }, { 4, 3 } },
    { { 0, 3 }, { 1, 2 }, { 2, 1 }, { 3, 0 } },
    { { 0, 4 }, { 1, 3 }, { 2, 2 }, { 3, 1 } },
    { { 1, 3 }, { 2, 2 }, { 3, 1 }, { 4, 0 } },
    { { 1, 4 }, { 2, 3 }, { 3, 2 }, { 4, 1 } } };

constexpr int lose[48][3][2] = { { { 0, 0 }, { 0, 1 }, { 0, 2 } },
    { { 0, 1 }, { 0, 2 }, { 0, 3 } },
    { { 0, 2 }, { 0, 3 }, { 0, 4 } },
    { { 1, 0 }, { 1, 1 }, { 1, 2 } },
    { { 1, 1 }, { 1, 2 }, { 1, 3 } },
    { { 1, 2 }, { 1, 3 }, { 1, 4 } },
    { { 2, 0 }, { 2, 1 }, { 2, 2 } },
    { { 2, 1 }, { 2, 2 }, { 2, 3 } },
    { { 2, 2 }, { 2, 3 }, { 2, 4 } },
    { { 3, 0 }, { 3, 1 }, { 3, 2 } },
    { { 3, 1 }, { 3, 2 }, { 3, 3 } },
    { { 3, 2 }, { 3, 3 }, { 3, 4 } },
    { { 4, 0 }, { 4, 1 }, { 4, 2 } },
    { { 4, 1 }, { 4, 2 }, { 4, 3 } },
    { { 4, 2 }, { 4, 3 }, { 4, 4 } },
    { { 0, 0 }, { 1, 0 }, { 2, 0 } },
    { { 1, 0 }, { 2, 0 }, { 3, 0 } },
    { { 2, 0 }, { 3, 0 }, { 4, 0 } },
    { { 0, 1 }, { 1, 1 }, { 2, 1 } },
    { { 1, 1 }, { 2, 1 }, { 3, 1 } },
    { { 2, 1 }, { 3, 1 }, { 4, 1 } },
    { { 0, 2 }, { 1, 2 }, { 2, 2 } },
    { { 1, 2 }, { 2, 2 }, { 3, 2 } },
    { { 2, 2 }, { 3, 2 }, { 4, 2 } },
    { { 0, 3 }, { 1, 3 }, { 2, 3 } },
    { { 1, 3 }, { 2, 3 }, { 3, 3 } },
    { { 2, 3 }, { 3, 3 }, { 4, 3 } },
    { { 0, 4 }, { 1, 4 }, { 2, 4 } },
    { { 1, 4 }, { 2, 4 }, { 3, 4 } },
    { { 2, 4 }, { 3, 4 }, { 4, 4 } },
    { { 0, 2 }, { 1, 3 }, { 2, 4 } },
    { { 0, 1 }, { 1, 2 }, { 2, 3 } },
    { { 1, 2 }, { 2, 3 }, { 3, 4 } },
    { { 0, 0 }, { 1, 1 }, { 2, 2 } },
    { { 1, 1 }, { 2, 2 }, { 3, 3 } },
    { { 2, 2 }, { 3, 3 }, { 4, 4 } },
    { { 1, 0 }, { 2, 1 }, { 3, 2 } },
    { { 2, 1 }, { 3, 2 }, { 4, 3 } },
    { { 2, 0 }, { 3, 1 }, { 4, 2 } },
    { { 0, 2 }, { 1, 1 }, { 2, 0 } },
    { { 0, 3 }, { 1, 2 }, { 2, 1 } },
    { { 1, 2 }, { 2, 1 }, { 3, 0 } },
    { { 0, 4 }, { 1, 3 }, { 2, 2 } },
    { { 1, 3 }, { 2, 2 }, { 3, 1 } },
    { { 2, 2 }, { 3, 1 }, { 4, 0 } },
    { { 1, 4 }, { 2, 3 }, { 3, 2 } },
    { { 2, 3 }, { 3, 2 }, { 4, 1 } },
    { { 2, 4 }, { 3, 3 }, { 4, 2 } } };

namespace std {
    template<>
    struct hash<Marker> {
        auto operator()(const Marker &marker) const -> size_t {
            return hash<int>()(static_cast<int>(marker));
        }
    };
    template<>
    struct hash<Board> {
        auto operator()(const Board &board) const -> size_t {
            std::hash<Marker> marker_hasher;
            size_t hash = 0;

            for (const auto &row : board) {
                for (const auto &marker : row) {
                    hash ^= marker_hasher(marker) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
                }
            }

            return hash;
        }
    };
}
