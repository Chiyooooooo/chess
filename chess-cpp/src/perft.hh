#ifndef PERFT_HH
#define PERFT_HH

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "board.hh"
#include "move.hh"

unsigned long long perft(Chessboard &board, int depth);

#endif  // PERFT_HH