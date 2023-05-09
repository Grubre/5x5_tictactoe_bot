#include "board.hpp"
#include "cmdline_args.hpp"
#include "connection.hpp"
#include "heuristic.hpp"
#include "minimax.hpp"
#include "game.hpp"
#include <iostream>

auto main(int argc, char *argv[]) -> int
{
    int a = 5;
    return play_online(argc, argv);
}
