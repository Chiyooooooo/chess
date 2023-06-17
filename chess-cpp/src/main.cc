#include "move.hh"
#include "perft.hh"


int main()
{
    Chessboard board;

    board.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");//20
    //board.loadFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R");//44
    //board.loadFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8");//14


    // Generate and print the moves for each square on the board
    for (int square = 0; square < Chessboard::Size * Chessboard::Size; ++square)
    {
        std::vector<int> moves;
        Move::generateMoves(board, square, moves);

        std::cout << "Moves for square " << square << ": ";
        for (std::vector<int>::iterator it = moves.begin(); it != moves.end(); ++it)
        {
            int move = *it;
            std::cout << move << " ";
        }
        std::cout << std::endl;
    }
    unsigned long long result = perft(board, 1);
    std::cout << result << std::endl;

    return 0;
}

/*
int main()
{
    std::cout<<"Hello World";
    return 0;
}
*/
