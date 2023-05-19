#include "board.hpp"
#include "cmdline_args.hpp"
#include "connection.hpp"
#include "game.hpp"
#include "heuristic.hpp"
#include "minimax.hpp"
#include <fstream>
#include <future>
#include <iostream>
#include <utility>
#include "openings.hpp"

auto main(int argc, char *argv[]) -> int {
    auto ret = play_online(argc, argv);
    return 0;
}
