#pragma once
#include <optional>
#include <string>
#include <vector>
#include "board.hpp"

struct cmdline_args
{
    std::string ip;
    int port;
    Marker marker;
    int depth;
};

auto validate_arguments(const std::vector<std::string> &args) -> std::optional<cmdline_args>;
