#pragma once
#include "board.hpp"
#include <array>
#include <optional>
#include <string>
#include <vector>

struct cmdline_args
{
    std::string ip;
    int port;
    Marker marker;
    int depth;
    std::array<int, 4> params;
};

auto validate_arguments(const std::vector<std::string> &args) -> std::optional<cmdline_args>;
auto validate_arguments_params(const std::vector<std::string> &args) -> std::optional<cmdline_args>;
