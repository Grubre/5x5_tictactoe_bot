#include "board.hpp"
#include "cmdline_args.hpp"
#include "connection.hpp"
#include "heuristic.hpp"
#include "minimax.hpp"
#include "game.hpp"
#include <iostream>
#include <future>
#include <utility>

auto main(int argc, char *argv[]) -> int
{
    auto ret = play_online(argc, argv);
    return ret;
}
