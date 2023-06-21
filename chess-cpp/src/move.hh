#ifndef MOVE_HH
#define MOVE_HH

#include "board.hh"

class Move
{
public:

    static void generateMoves(const Chessboard &board, int square, std::vector<int> &moves);
    static void generatePawnMoves(const Chessboard &board, int square, Color color, std::vector<int> &moves);
    static void generateRookMoves(const Chessboard &board, int square, std::vector<int> &moves);
    static void generateKnightMoves(const Chessboard &board, int square, std::vector<int> &moves);
    static void generateBishopMoves(const Chessboard &board, int square, std::vector<int> &moves);
    static void generateQueenMoves(const Chessboard &board, int square, std::vector<int> &moves);
    static void generateKingMoves(const Chessboard &board, int square, std::vector<int> &moves);

    static bool lilCastlingMove(const Chessboard& board, int sourceSquare, int targetSquare);
    static bool bigCastlingMove(const Chessboard& board, int sourceSquare, int targetSquare);
    static bool isCastlingLegal(const Chessboard& board, int sourceSquare, int targetSquare);
    static bool isEnPassantMove(const Chessboard& board, int sourceSquare, int targetSquare);

    static bool isPromotionLegal(const Chessboard& board, int sourceSquare, int targetSquare);
    static bool isMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isPawnMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare, Color color);
    static bool isRookMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isKnightMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isBishopMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isQueenMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);
    static bool isKingMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare);



    static std::vector<int> getLegalMoves(const Chessboard &board, int square);
    static std::vector<int> getAllLegalMoves(const Chessboard &board);
    
    static std::vector<int> generateAllLegalMoves(const Chessboard &board, Color currentColor);

    static std::string getSquareName(int square);
};

#endif // MOVE_HH
