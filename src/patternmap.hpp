#pragma once
#include "board.hpp"
#include <unordered_set>
#include <optional>

class pattern_map {
public:
    pattern_map();
    auto contains(const Board& board) const -> bool;
    void insert_state(const Board& board);
    void insert_state(uint64_t board);

public:
    std::unordered_set<uint64_t> states;
};
