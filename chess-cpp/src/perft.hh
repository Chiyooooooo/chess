#ifndef PERFT_HH
#define PERFT_HH

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "board.hh"
#include "move.hh"

int perft(Chessboard &board, int depth, Color currentColor);

#endif // PERFT_HH
