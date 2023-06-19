#include "move.hh"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>


void Move::generateMoves(const Chessboard &board, int square, std::vector<int> &moves)
{
    Piece piece = board.getPiece(square);
    Color color = board.getColor(square);

    switch (piece)
    {
    case 1:
        generatePawnMoves(board, square, color, moves);
        break;
    case 2:
        generateRookMoves(board, square, moves);
        break;
    case 3:
        generateKnightMoves(board, square, moves);
        break;
    case 4:
        generateBishopMoves(board, square, moves);
        break;
    case 5:
        generateQueenMoves(board, square, moves);
        break;
    case 6:
        generateKingMoves(board, square, moves);
        break;
    default:
        break;
    }
}

void Move::generatePawnMoves(const Chessboard &board, int square, Color color, std::vector<int> &moves)
{
    int rank = board.getRank(square);
    int file = board.getFile(square);

    int forwardDir = (color == WHITE) ? 1 : -1;
    int forwardSquare = board.getSquare(file, rank + forwardDir);

    if (board.isValidSquare(forwardSquare) && board.getPiece(forwardSquare) == EMPTY)
    {
        moves.push_back(forwardSquare);

        // Cpremier coup ? alors go avancer de deux
        if ((rank == 1 && color == WHITE) || (rank == 6 && color == BLACK))
        {
            int doubleForwardSquare = board.getSquare(file, rank + 2 * forwardDir);
            if (board.isValidSquare(doubleForwardSquare) && board.getPiece(doubleForwardSquare) == EMPTY)
            {
                moves.push_back(doubleForwardSquare);
            }
        }
    }
    //capture autre piece ennemi
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

void Move::generateRookMoves(const Chessboard &board, int square, std::vector<int> &moves)
{
    int rank = board.getRank(square);
    int file = board.getFile(square);

    for (int f = 0; f < Chessboard::Size; ++f)
    {
        if (f != file) //collumn
        {
            int targetSquare = board.getSquare(f, rank);
            if (isMoveLegal(board, square, targetSquare))
            {
                moves.push_back(targetSquare);
            }
        }
    }

    for (int r = 0; r < Chessboard::Size; ++r)
    {
        if (r != rank) //rang
        {
            int targetSquare = board.getSquare(file, r);
            if (isMoveLegal(board, square, targetSquare))
            {
                moves.push_back(targetSquare);
            }
        }
    }
}

void Move::generateKnightMoves(const Chessboard &board, int square, std::vector<int> &moves)
{
    int rank = board.getRank(square);
    int file = board.getFile(square);

    int rankOffsets[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int fileOffsets[] = {1, -1, 1, -1, 2, -2, 2, -2};

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

void Move::generateBishopMoves(const Chessboard &board, int square, std::vector<int> &moves)
{
    int rank = board.getRank(square);
    int file = board.getFile(square);
        
    for (int offset = 1; offset < Chessboard::Size; ++offset)
    {
        int targetRank = rank + offset;
        int targetFile = file + offset;
        int targetSquare = board.getSquare( targetFile, targetRank);

        if (board.isValidSquare(targetSquare) && board.isValidBishopMove( square, targetSquare))
        {
            moves.push_back(targetSquare);
        }
                else
        {
            break; 
        }
    }

    for (int offset = 1; offset < Chessboard::Size; ++offset)
    {
        int targetRank = rank - offset;
        int targetFile = file + offset;
        int targetSquare = board.getSquare( targetFile, targetRank);

        if (board.isValidSquare(targetSquare) && board.isValidBishopMove( square, targetSquare))
        {
            moves.push_back(targetSquare);
        }
        else
        {
            break;
        }
    }

    for (int offset = 1; offset < Chessboard::Size; ++offset)
    {
        int targetRank = rank - offset;
        int targetFile = file - offset;
        int targetSquare = board.getSquare( targetFile, targetRank);
 
        if (board.isValidSquare(targetSquare) && board.isValidBishopMove( square, targetSquare))
        {
            moves.push_back(targetSquare);
        }
        else
        {
            break; 
        }
    }

    for (int offset = 1; offset < Chessboard::Size; ++offset)
    {
        int targetRank = rank + offset;
        int targetFile = file - offset;
        int targetSquare = board.getSquare( targetFile, targetRank);

        if (board.isValidSquare(targetSquare) && board.isValidBishopMove( square, targetSquare))
        {
            moves.push_back(targetSquare);
        }
        else
        {
            break; 
        }
    }
}

void Move::generateQueenMoves(const Chessboard &board, int square, std::vector<int> &moves)
{
    generateRookMoves(board, square, moves);
    generateBishopMoves(board, square, moves);
}

void Move::generateKingMoves(const Chessboard &board, int square, std::vector<int> &moves)
{
    int rank = board.getRank(square);
    int file = board.getFile(square);

    int rankOffsets[] = {1, 1, 1, 0, 0, -1, -1, -1};
    int fileOffsets[] = {1, 0, -1, 1, -1, 1, 0, -1};

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
////petit roque, pas oublier de faire le grand roque
bool Move::lilCastlingMove(const Chessboard& board, int sourceSquare, int targetSquare)
{
    //std::cout<<"ROQUE"<<std::endl;
    int sourceRank = board.getRank(sourceSquare);
    int sourceFile = board.getFile(sourceSquare);
    int targetRank = board.getRank(targetSquare);
    int targetFile = board.getFile(targetSquare);

    if (board.getPiece(sourceSquare) != KING || board.getPiece(targetSquare) != ROOK)
    {
        return false;
    }

    if (board.getColor(sourceSquare) != board.getColor(targetSquare))
    {
        return false;
    }

    if (sourceRank != targetRank)
    {
        return false;
    }

    if (std::abs(sourceFile - targetFile) != 3)
    {    
        return false;
    }/*
    std::cout<<"COLUMN"<<std::endl;
    std::cout<<"rank fin : "<<targetRank<<std::endl;
    std::cout<<"col fin  : "<<targetFile<<std::endl;
    std::cout<<"rank debut : "<<sourceRank<<std::endl;
    std::cout<<"col  debut : "<<sourceFile<<std::endl;
    std::cout<<"VALID"<<std::endl;*/
    return true;
}

bool Move::bigCastlingMove(const Chessboard& board, int sourceSquare, int targetSquare)
{
    int sourceRank = board.getRank(sourceSquare);
    int sourceFile = board.getFile(sourceSquare);
    int targetRank = board.getRank(targetSquare);
    int targetFile = board.getFile(targetSquare);
    if (board.getPiece(sourceSquare) != KING || board.getPiece(targetSquare) != ROOK)
    {
        return false;
    }
    if (board.getColor(sourceSquare) != board.getColor(targetSquare))
    {
        return false;
    }
    if (sourceRank != targetRank)
    {
        return false;
    }
    if (std::abs(sourceFile - targetFile) != 4)
    {    
        return false;
    }
    return true;
}

bool Move::isCastlingLegal(const Chessboard& board, int sourceSquare, int targetSquare)
{
    if (board.isKingInCheck(board.getColor(sourceSquare)))
    {
        return false;
    }

    if (!board.isPathClear(sourceSquare, targetSquare))
    {
        return false;
    }
    return true;
}

bool Move::isMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare)
{
    Color color = board.getColor(sourceSquare);
    Piece piece = board.getPiece(sourceSquare);


    if (lilCastlingMove(board, sourceSquare, targetSquare) || bigCastlingMove(board, sourceSquare, targetSquare))
    {
        return isCastlingLegal(board, sourceSquare, targetSquare);
    }


    if (board.getPiece(targetSquare) != EMPTY && board.getColor(targetSquare) == color)
    {
        return false;
    }

    switch (piece)
    {
    case 1:
        return isPawnMoveLegal(board, sourceSquare, targetSquare, color);
    case 2:
        //std::cout << "rook";
        return isRookMoveLegal(board, sourceSquare, targetSquare);
    case 3:
        //std::cout << "knight";
        return isKnightMoveLegal(board, sourceSquare, targetSquare);
    case 4:
        //std::cout << "bishop";
        return isBishopMoveLegal(board, sourceSquare, targetSquare);
    case 5:
        //std::cout << "queen";
        return isQueenMoveLegal(board, sourceSquare, targetSquare);
    case 6:
        //std::cout << "king";
        return isKingMoveLegal(board, sourceSquare, targetSquare);
    default:
        //std::cout << "RIEN";
        return false;
    }
}

bool Move::isPawnMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare, Color color)
{
    int rankDiff = board.getRank(targetSquare) - board.getRank(sourceSquare);
    int fileDiff = std::abs(board.getFile(targetSquare) - board.getFile(sourceSquare));

    if ((color == WHITE && rankDiff <= 0) || (color == BLACK && rankDiff >= 0))
    {
        return false;
    }

    if (std::abs(rankDiff) > 2)
    {
        return false;
    }

    if (fileDiff == 0)
    {
        if (board.getPiece(targetSquare) == EMPTY)
        {
            if (std::abs(rankDiff) == 1)
            {
                return true;
            }

            int startRank = (color == WHITE) ? 1 : 6;
            if (board.getRank(sourceSquare) == startRank && std::abs(rankDiff) == 2)
            {
                int intermediateRank = startRank + (rankDiff / 2);
                int intermediateSquare = board.getSquare(board.getFile(sourceSquare), intermediateRank);
                if (board.getPiece(intermediateSquare) == EMPTY)
                {
                    return true;
                }
            }
        }
    }
    else if (fileDiff == 1 && std::abs(rankDiff) == 1)//capture un ennemi
    {
        if (board.getPiece(targetSquare) != EMPTY && board.getColor(targetSquare) != color)
        {
            return true;
        }
    }
    return false;
}

bool Move::isRookMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare)
{
    int sourceRank = board.getRank(sourceSquare);
    int sourceFile = board.getFile(sourceSquare);
    int targetRank = board.getRank(targetSquare);
    int targetFile = board.getFile(targetSquare);

    if (sourceRank == targetRank || sourceFile == targetFile)
    {
        if (!board.isPathClear(sourceSquare,targetSquare))
        {
            return false;
        }
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

bool Move::isKnightMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare)
{
    int rankDiff = std::abs(board.getRank(targetSquare) - board.getRank(sourceSquare));
    int fileDiff = std::abs(board.getFile(targetSquare) - board.getFile(sourceSquare));
    // Check if the move is in an L-shape (2 squares in one direction and 1 square in the other)
    return (rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2);
}

bool Move::isBishopMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare)
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

bool Move::isQueenMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare)
{
    return isRookMoveLegal(board, sourceSquare, targetSquare) || isBishopMoveLegal(board, sourceSquare, targetSquare);
}

bool Move::isKingMoveLegal(const Chessboard &board, int sourceSquare, int targetSquare)
{
    int rankDiff = std::abs(board.getRank(targetSquare) - board.getRank(sourceSquare));
    int fileDiff = std::abs(board.getFile(targetSquare) - board.getFile(sourceSquare));

    // Check if the move is valid (1 square in any direction)
    return rankDiff <= 1 && fileDiff <= 1;
}

std::vector<int> Move::getLegalMoves(const Chessboard &board, int square)
{
    std::vector<int> legalMoves;
    generateMoves(board, square, legalMoves);
    return legalMoves;
}

std::vector<int> Move::getAllLegalMoves(const Chessboard &board) ///marche vrmnt pas bien
{
   std::vector<int> allLegalMoves;

    for (int square = 0; square < 64; square++) {
        if (board.getPiece(square) == EMPTY || board.getColor(square) != WHITE)//board.sideToMove())
            continue;

        generateMoves(board, square, allLegalMoves);
        //std::vector<int> legalMoves = Move::getLegalMoves(board, square);
        //allLegalMoves.insert(allLegalMoves.end(), legalMoves.begin(), legalMoves.end());
    }

    return allLegalMoves;
}


std::vector<int> Move::generateAllLegalMoves(const Chessboard &board)
{
    std::vector<int> allLegalMoves;

    for (int sourceSquare = 0; sourceSquare < 64; sourceSquare++) {
        if (board.getPiece(sourceSquare) != EMPTY && board.getColor(sourceSquare) != BLACK/*&& board.getColor(sourceSquare) == board.sideToMove()*/) {
            for (int targetSquare = 0; targetSquare < 64; targetSquare++) {
                if (targetSquare == sourceSquare) {
                    continue;
                }
                else{
                    if (isMoveLegal(board, sourceSquare, targetSquare)) {
                        //allLegalMoves.push_back(sourceSquare);
                        allLegalMoves.push_back(targetSquare);
                    }
                }
            }
        }
    }

    return allLegalMoves;
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
bool Move::isCheckmate(const Chessboard &board, Color sideToMove)
{
    int opponentKingSquare = board.findKing(sideToMove);
    if (!isSquareUnderAttack(board, opponentKingSquare, sideToMove))
    {
        return false; 
    }

    std::vector<int> legalMoves = getLegalMoves(board, opponentKingSquare);

    for (int targetSquare : legalMoves)
    {
        if (!isSquareUnderAttack(board, targetSquare, sideToMove))
        {
            return false; // King can escape check, not checkmate
        }
    }
    return true;
}
*/
