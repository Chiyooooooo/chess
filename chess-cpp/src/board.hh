#ifndef BOARD_HH
#define BOARD_HH

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

enum Piece
{
    EMPTY = -1,
    PAWN = 1,
    ROOK = 2,
    KNIGHT = 3,
    BISHOP = 4,
    QUEEN = 5,
    KING = 6
};

enum Color
{
    EMPTY_COLOR = -1,
    BLACK = 0,
    WHITE = 1
};

class Chessboard
{
public:
    static const int Size = 8;

    inline static bool castlingWK = true;
    inline static bool castlingWQ = true;
    inline static bool castlingBK = true;
    inline static bool castlingBQ = true;
    inline static std::string enPA = "-";
    inline static std::string enPADONEW = "-";
    inline static std::string enPADONEB = "-";
    inline static int enPaDiff = 0;


    inline static Color PlayerToMove;
    inline static std::string prof = "0";

    Chessboard();

    void reset();
    void setPiece(int square, Piece piece, Color color);
    Piece getPiece(int square) const;
    Color getColor(int square) const;
    bool isValidSquare(int square) const; // case bien dans l'echiquier
    void FEN(const std::string &fen);
    bool isValidMove(int fromSquare, int toSquare) const;
    bool isValidPawnMove(int fromSquare, int toSquare, Color color) const;
    bool isValidRookMove(int fromSquare, int toSquare) const;
    bool isValidKnightMove(int fromSquare, int toSquare) const;
    bool isValidBishopMove(int fromSquare, int toSquare) const;
    bool isValidQueenMove(int fromSquare, int toSquare) const;
    bool isValidKingMove(int fromSquare, int toSquare) const;
    bool isPathClear(int fromSquare, int toSquare) const;
    int getRank(int square) const;
    int getFile(int square) const;
    int getSquare(int file, int rank) const;
    static std::string getSquareName(int square);

    void movePiece(int fromSquare, int toSquare);
    void undoMove(int fromSquare, int toSquare, Piece capturedPiece, Color capturedPieceColor);
    bool isKingInCheck(Color kingColor) const;
    bool isRookInCheck(int rookSquare, Color kingColor) const;

    void prettyPrint() const;

private:
    int board_[Size * Size];
    int color_[Size * Size];

    Piece getPieceFromChar(char c) const;
};

int perft(Chessboard &board, int depth);

#endif // BOARD_HH
