#include "move.hh"
#include "perft.hh"


int main()
{
    Chessboard board;

    //board.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"); // 20
    // board.loadFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R");//44
    // board.loadFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8");//14
    board.loadFEN("8/8/b7/8/8/8/8/8");//14
    board.prettyPrint();

    //int sol = 0;
/*
    for (int square = 0; square < Chessboard::Size * Chessboard::Size; ++square)
    {
        std::vector<int> moves;
        Move::generateMoves(board, square, moves);
        std::cout << "Moves for square " << square << ": ";
        for (std::vector<int>::iterator it = moves.begin(); it != moves.end(); ++it)
        {
            int move = *it;
            std::cout << move << " ";
            sol++;
        }
        std::cout << std::endl;
    }*/

    //board.setPiece(17, PAWN, BLACK);
    std::cout << Move::isPawnMoveLegal(board, 8, 17, WHITE) << std::endl;
    
    //board.setPiece(24, BISHOP, WHITE);
    //board.setPiece(8, BISHOP, WHITE);
    //board.prettyPrint();


    int square  = 40;
    std::vector<int> legalMoves = Move::getLegalMoves(board, square);
    std::cout << legalMoves.size() << std::endl;

    //std::vector<int> alllegalMoves = Move::getAllLegalMoves(board);
    //std::cout << alllegalMoves.size() << std::endl;
    //for (unsigned long i = 0; i < alllegalMoves.size(); ++i) {
    //    std::cout << Move::getSquareName(alllegalMoves[i]) << " ";
    //}

    int result = perft(board, 1);
    std::cout << result << std::endl;

    return 0;
}


/*
int main() {

    Chessboard board;
    board.loadFEN("8/8/8/8/8/8/8/8");
    //board.prettyPrint();
    
    board.setPiece(35, QUEEN, WHITE);
    board.setPiece(8, PAWN, WHITE);
    board.setPiece(17, PAWN, BLACK);

    board.setPiece(44, BISHOP, WHITE);
    board.setPiece(53, BISHOP, WHITE);
    board.setPiece(62, BISHOP, WHITE);
    board.setPiece(28, BISHOP, WHITE);
    board.setPiece(21, BISHOP, WHITE);
    board.setPiece(14, BISHOP, WHITE);
    board.setPiece(7, BISHOP, WHITE);
    board.setPiece(26, BISHOP, WHITE);
    board.setPiece(17, BISHOP, WHITE);
    board.setPiece(42, BISHOP, WHITE);
    board.setPiece(49, BISHOP, WHITE);
    board.setPiece(56, BISHOP, WHITE);

    Piece p= board.getPiece(42);
    board.setPiece(10,  PAWN, WHITE);
    Piece a = board.getPiece(10);
    board.prettyPrint();

    board.setPiece(0,p,BLACK);
    board.movePiece(42, 18);
    board.prettyPrint();
    board.undoMove(42, 18, EMPTY, EMPTY_COLOR);

    board.prettyPrint();

    int square = 35;
    std::vector<int> legalMoves = Move::getLegalMoves(board, square);
    std::cout << "Legal moves for square " << Move::getSquareName(square) << ":" << std::endl;
    std::cout << legalMoves.size();
    std::cout << std::endl;
    for (unsigned long i = 0; i < legalMoves.size(); ++i) {
        std::cout << Move::getSquareName(legalMoves[i]) << " ";
    }

    std::cout << std::endl;
    return 0;
}
*/


/*
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

int main()
{
    std::cout<<"Hello World";
    return 0;
}
*/
