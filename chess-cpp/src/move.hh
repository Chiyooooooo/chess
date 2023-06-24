#ifndef MOVE_HH
#define MOVE_HH

#include "board.hh"

class Move
{
public:
    static bool lilCastlingMove(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool bigCastlingMove(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isCastlingLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isEnPassantMove(const Chessboard &board, int sourceSquare, int targetSquare);

    static bool isPromotionLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isPawnMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare, Color color);
    static bool isRookMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isKnightMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isBishopMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isQueenMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isKingMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);

    static std::vector<int> generateAllLegalMoves(const Chessboard &board, Color currentColor);

    static int getSquareFromName(const std::string &name);
};

#endif // MOVE_HH
