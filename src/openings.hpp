#pragma once
#include <unordered_map>
#include "board.hpp"
#include <optional>

struct Openings {
public:
    Openings();
    auto get_opening(const Board& board) const -> std::optional<int>;
    std::unordered_map<Board, int> openings_map;
};
