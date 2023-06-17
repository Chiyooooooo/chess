#include "move.hh"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

void Move::generateMoves(const Chessboard& board, int square, std::vector<int>& moves)
{
    Piece piece = board.getPiece(square);
    Color color = board.getColor(square);

    switch (piece)
    {
        case PAWN:
            generatePawnMoves(board, square, color, moves);
            break;
        case ROOK:
            generateRookMoves(board, square, moves);
            break;
        case KNIGHT:
            generateKnightMoves(board, square, moves);
            break;
        case BISHOP:
            generateBishopMoves(board, square, moves);
            break;
        case QUEEN:
            generateQueenMoves(board, square, moves);
            break;
        case KING:
            generateKingMoves(board, square, moves);
            break;
        default:
            break;
    }
}

void Move::generatePawnMoves(const Chessboard& board, int square, Color color, std::vector<int>& moves)
{
    int rank = board.getRank(square);
    int file = board.getFile(square);

    int forwardDir = (color == WHITE) ? 1 : -1;
    int forwardSquare = board.getSquare(file, rank + forwardDir);

    if (board.isValidSquare(forwardSquare) && board.getPiece(forwardSquare) == EMPTY)
    {
        moves.push_back(forwardSquare);

        // Check if it's the pawn's first move and it can move two squares forward
        if ((rank == 1 && color == WHITE) || (rank == 6 && color == BLACK))
        {
            int doubleForwardSquare = board.getSquare(file, rank + 2 * forwardDir);
            if (board.isValidSquare(doubleForwardSquare) && board.getPiece(doubleForwardSquare) == EMPTY)
            {
                moves.push_back(doubleForwardSquare);
            }
        }
    }

    // Generate diagonal captures
    int leftCaptureSquare = board.getSquare(file - 1, rank + forwardDir);
    int rightCaptureSquare = board.getSquare(file + 1, rank + forwardDir);

    if (board.isValidSquare(leftCaptureSquare) && board.getPiece(leftCaptureSquare) != EMPTY &&
        board.getColor(leftCaptureSquare) != color)
    {
        moves.push_back(leftCaptureSquare);
    }

    if (board.isValidSquare(rightCaptureSquare) && board.getPiece(rightCaptureSquare) != EMPTY &&
        board.getColor(rightCaptureSquare) != color)
    {
        moves.push_back(rightCaptureSquare);
    }
}

void Move::generateRookMoves(const Chessboard& board, int square, std::vector<int>& moves)
{
    int rank = board.getRank(square);
    int file = board.getFile(square);

    // Generate moves along the rank
    for (int f = 0; f < Chessboard::Size; ++f)
    {
        if (f != file)
        {
            int targetSquare = board.getSquare(f, rank);
            if (isMoveLegal(board, square, targetSquare))
            {
                moves.push_back(targetSquare);
            }
        }
    }

    // Generate moves along the file
    for (int r = 0; r < Chessboard::Size; ++r)
    {
        if (r != rank)
        {
            int targetSquare = board.getSquare(file, r);
            if (isMoveLegal(board, square, targetSquare))
            {
                moves.push_back(targetSquare);
            }
        }
    }
}

void Move::generateKnightMoves(const Chessboard& board, int square, std::vector<int>& moves)
{
    int rank = board.getRank(square);
    int file = board.getFile(square);

    // Generate all possible knight moves
    int rankOffsets[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
    int fileOffsets[] = { 1, -1, 1, -1, 2, -2, 2, -2 };

    for (int i = 0; i < 8; ++i)
    {
        int targetRank = rank + rankOffsets[i];
        int targetFile = file + fileOffsets[i];
        int targetSquare = board.getSquare(targetFile, targetRank);

        if (board.isValidSquare(targetSquare) && isMoveLegal(board, square, targetSquare))
        {
            moves.push_back(targetSquare);
        }
    }
}

void Move::generateBishopMoves(const Chessboard& board, int square, std::vector<int>& moves)
{
    int rank = board.getRank(square);
    int file = board.getFile(square);

    // Generate moves along the diagonals
    for (int offset = 1; offset < Chessboard::Size; ++offset)
    {
        // Generate moves along the positive diagonal
        int targetRank = rank + offset;
        int targetFile = file + offset;
        int targetSquare = board.getSquare(targetFile, targetRank);

        if (board.isValidSquare(targetSquare) && isMoveLegal(board, square, targetSquare))
        {
            moves.push_back(targetSquare);
        }

        // Generate moves along the negative diagonal
        targetRank = rank - offset;
        targetFile = file - offset;
        targetSquare = board.getSquare(targetFile, targetRank);

        if (board.isValidSquare(targetSquare) && isMoveLegal(board, square, targetSquare))
        {
            moves.push_back(targetSquare);
        }
    }
}

void Move::generateQueenMoves(const Chessboard& board, int square, std::vector<int>& moves)
{
    // Generate moves as a combination of rook and bishop moves
    generateRookMoves(board, square, moves);
    generateBishopMoves(board, square, moves);
}

void Move::generateKingMoves(const Chessboard& board, int square, std::vector<int>& moves)
{
    int rank = board.getRank(square);
    int file = board.getFile(square);

    // Generate all possible king moves
    int rankOffsets[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
    int fileOffsets[] = { 1, 0, -1, 1, -1, 1, 0, -1 };

    for (int i = 0; i < 8; ++i)
    {
        int targetRank = rank + rankOffsets[i];
        int targetFile = file + fileOffsets[i];
        int targetSquare = board.getSquare(targetFile, targetRank);

        if (board.isValidSquare(targetSquare) && isMoveLegal(board, square, targetSquare))
        {
            moves.push_back(targetSquare);
        }
    }
}

bool Move::isMoveLegal(const Chessboard& board, int sourceSquare, int targetSquare)
{
    Color color = board.getColor(sourceSquare);
    Piece piece = board.getPiece(sourceSquare);

    // Check if the target square is occupied by a piece of the same color
    if (board.getPiece(targetSquare) != EMPTY && board.getColor(targetSquare) == color)
    {
        return false;
    }
    // Check if the move is valid for the specific piece
    switch (piece)
    {
        case PAWN:
            return isPawnMoveLegal(board, sourceSquare, targetSquare, color);
        case ROOK:
            return isRookMoveLegal(board, sourceSquare, targetSquare);
        case KNIGHT:
            return isKnightMoveLegal(board, sourceSquare, targetSquare);
        case BISHOP:
            return isBishopMoveLegal(board, sourceSquare, targetSquare);
        case QUEEN:
            return isQueenMoveLegal(board, sourceSquare, targetSquare);
        case KING:
            return isKingMoveLegal(board, sourceSquare, targetSquare);
        default:
            return false;
    }
}

bool Move::isPawnMoveLegal(const Chessboard& board, int sourceSquare, int targetSquare, Color color)
{
    int rankDiff = board.getRank(targetSquare) - board.getRank(sourceSquare);
    int fileDiff = std::abs(board.getFile(targetSquare) - board.getFile(sourceSquare));

    // Check if the pawn is moving forward
    if ((color == WHITE && rankDiff <= 0) || (color == BLACK && rankDiff >= 0))
    {
        return false;
    }

    // Check if the pawn is moving too far
    if (std::abs(rankDiff) > 2)
    {
        return false;
    }

    // Check if the pawn is moving forward along the file
    if (fileDiff == 0)
    {
        // Check if the target square is unoccupied
        if (board.getPiece(targetSquare) == EMPTY)
        {
            // Check if it's a single square move
            if (std::abs(rankDiff) == 1)
            {
                return true;
            }

            // Check if it's a double square move from the starting position
            int startRank = (color == WHITE) ? 1 : 6;
            if (board.getRank(sourceSquare) == startRank && std::abs(rankDiff) == 2)
            {
                // Check if the intermediate square is unoccupied
                int intermediateRank = startRank + (rankDiff / 2);
                int intermediateSquare = board.getSquare(board.getFile(sourceSquare), intermediateRank);
                if (board.getPiece(intermediateSquare) == EMPTY)
                {
                    return true;
                }
            }
        }
    }
    // Check if the pawn is capturing diagonally
    else if (fileDiff == 1 && std::abs(rankDiff) == 1)
    {
        // Check if the target square is occupied by an opponent's piece
        if (board.getPiece(targetSquare) != EMPTY && board.getColor(targetSquare) != color)
        {
            return true;
        }
    }

    return false;
}

bool Move::isRookMoveLegal(const Chessboard& board, int sourceSquare, int targetSquare)
{
    int sourceRank = board.getRank(sourceSquare);
    int sourceFile = board.getFile(sourceSquare);
    int targetRank = board.getRank(targetSquare);
    int targetFile = board.getFile(targetSquare);

    // Check if the move is along the same rank or file
    if (sourceRank == targetRank || sourceFile == targetFile)
    {
        // Check if there are any pieces obstructing the path
        int rankDiff = targetRank - sourceRank;
        int fileDiff = targetFile - sourceFile;

        int rankStep = (rankDiff > 0) ? 1 : ((rankDiff < 0) ? -1 : 0);
        int fileStep = (fileDiff > 0) ? 1 : ((fileDiff < 0) ? -1 : 0);

        int currentRank = sourceRank + rankStep;
        int currentFile = sourceFile + fileStep;

        while (currentRank != targetRank || currentFile != targetFile)
        {
            int currentSquare = board.getSquare(currentFile, currentRank);
            if (board.getPiece(currentSquare) != EMPTY)
            {
                return false;
            }

            currentRank += rankStep;
            currentFile += fileStep;
        }

        return true;
    }

    return false;
}

bool Move::isKnightMoveLegal(const Chessboard& board, int sourceSquare, int targetSquare)
{
    int rankDiff = std::abs(board.getRank(targetSquare) - board.getRank(sourceSquare));
    int fileDiff = std::abs(board.getFile(targetSquare) - board.getFile(sourceSquare));

    // Check if the move is in an L-shape (2 squares in one direction and 1 square in the other)
    return (rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2);
}

bool Move::isBishopMoveLegal(const Chessboard& board, int sourceSquare, int targetSquare)
{
    int sourceRank = board.getRank(sourceSquare);
    int sourceFile = board.getFile(sourceSquare);
    int targetRank = board.getRank(targetSquare);
    int targetFile = board.getFile(targetSquare);

    // Check if the move is along a diagonal
    if (std::abs(targetRank - sourceRank) == std::abs(targetFile - sourceFile))
    {
        // Check if there are any pieces obstructing the path
        int rankDiff = targetRank - sourceRank;
        int fileDiff = targetFile - sourceFile;

        int rankStep = (rankDiff > 0) ? 1 : -1;
        int fileStep = (fileDiff > 0) ? 1 : -1;

        int currentRank = sourceRank + rankStep;
        int currentFile = sourceFile + fileStep;

        while (currentRank != targetRank || currentFile != targetFile)
        {
            int currentSquare = board.getSquare(currentFile, currentRank);
            if (board.getPiece(currentSquare) != EMPTY)
            {
                return false;
            }

            currentRank += rankStep;
            currentFile += fileStep;
        }

        return true;
    }

    return false;
}

bool Move::isQueenMoveLegal(const Chessboard& board, int sourceSquare, int targetSquare)
{
    // A queen can move like a rook or a bishop
    return isRookMoveLegal(board, sourceSquare, targetSquare) || isBishopMoveLegal(board, sourceSquare, targetSquare);
}

bool Move::isKingMoveLegal(const Chessboard& board, int sourceSquare, int targetSquare)
{
    int rankDiff = std::abs(board.getRank(targetSquare) - board.getRank(sourceSquare));
    int fileDiff = std::abs(board.getFile(targetSquare) - board.getFile(sourceSquare));

    // Check if the move is valid (1 square in any direction)
    return rankDiff <= 1 && fileDiff <= 1;
}

std::vector<int> Move::getLegalMoves(const Chessboard& board, int square)
{
    std::vector<int> legalMoves;
    generateMoves(board, square, legalMoves);
    return legalMoves;
}

std::string Move::getSquareName(int square)
{
    int rank = square / Chessboard::Size;
    int file = square % Chessboard::Size;

    std::string name;
    name += ('a' + file);
    name += ('1' + rank);
    return name;
}

/*
int main() {
    // Create a chessboard
    Chessboard board;
    board.loadFEN("8/8/8/8/8/8/8/8");
    //board.prettyPrint();
    // Set up a test position

    board.setPiece(42, ROOK, WHITE);
    board.setPiece(14, PAWN,  WHITE);
    board.setPiece(10,  PAWN, WHITE);
    board.prettyPrint();

    board.movePiece(42, 18);
    board.prettyPrint();

    board.undoMove(42, 18, EMPTY, EMPTY_COLOR);
    board.prettyPrint();


    // Generate and display legal moves for a square
    int square = 42;
    std::vector<int> legalMoves = Move::getLegalMoves(board, square);
    std::cout << "Legal moves for square " << Move::getSquareName(square) << ":" << std::endl;
    std::cout << legalMoves.size();
    
    int squar = 10;
    std::vector<int> legalMove = Move::getLegalMoves(board, squar);
    std::cout << "Legal moves for square " << Move::getSquareName(squar) << ":" << std::endl;
  //  /*for (int i = 0; i < legalMoves.size(); i++) {
    //    int move = legalMoves[i];   
      //  std::cout << Move::getSquareName(move) << std::endl;
    //}
    
    std::cout << legalMove.size();

    return 0;
}

*/
