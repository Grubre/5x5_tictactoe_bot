#pragma once
#include <optional>
#include <string>
#include <vector>

struct cmdline_args
{
    std::string ip;
    int port;
    std::string marker;
    int depth;
};

auto validate_arguments(const std::vector<std::string> &args) -> std::optional<cmdline_args>;
