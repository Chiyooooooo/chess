#include "move.hh"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

////petit roque, pas oublier de faire le grand roque
bool Move::lilCastlingMove(const Chessboard &board, int caseDebut, int caseFin)
{
    int rangDebut = board.getRank(caseDebut);
    int colonneDebut = board.getFile(caseDebut);
    int rangFin = board.getRank(caseFin);
    int colonneFin = board.getFile(caseFin);

    if (board.getPiece(caseDebut) != KING || board.getPiece(caseFin) != ROOK)
    {
        return false;
    }

    if (board.getColor(caseDebut) != board.getColor(caseFin))
    {
        return false;
    }

    if (rangDebut != rangFin)
    {
        return false;
    }

    if (std::abs(colonneDebut - colonneFin) != 3)
    {
        return false;
    }

    if (!board.isPathClear(caseDebut, caseFin))
    {
        return false;
    }
    return true;
}

bool Move::bigCastlingMove(const Chessboard &board, int caseDebut, int caseFin)
{
    int rangDebut = board.getRank(caseDebut);
    int colonneDebut = board.getFile(caseDebut);
    int rangFin = board.getRank(caseFin);
    int colonneFin = board.getFile(caseFin);

    if (board.getPiece(caseDebut) != KING || board.getPiece(caseFin) != ROOK)
    {
        return false;
    }
    if (board.getColor(caseDebut) != board.getColor(caseFin))
    {
        return false;
    }
    if (rangDebut != rangFin)
    {
        return false;
    }
    if (std::abs(colonneDebut - colonneFin) != 4)
    {
        return false;
    }

    if (!board.isPathClear(caseDebut, caseFin))
    {
        return false;
    }
    return true;
}

bool Move::isCastlingLegal(const Chessboard &board, int caseDebut, int caseFin)
{

    if (board.isKingInCheck(board.getColor(caseDebut)))
    {
        return false;
    }

    if (!board.isPathClear(caseDebut, caseFin))
    {
        return false;
    }
    return true;
}

bool Move::isEnPassantMove(const Chessboard& board, int caseDebut, int caseFin)
{
    int rangDebut = board.getRank(caseDebut);
    int colonneDebut = board.getFile(caseDebut);
    int rangFin = board.getRank(caseFin);
    int colonneFin = board.getFile(caseFin);

    if (board.getPiece(caseDebut) != PAWN || board.getPiece(caseFin) != EMPTY)
    {
        return false;
    }
    if (board.getColor(caseDebut) == board.getColor(caseFin))
    {
        return false;
    }
    if (rangDebut != rangFin){
        return false;}
    if (std::abs(colonneDebut - colonneFin) != 1)
    {
        return false;
    }
    if (board.getColor(caseDebut) == WHITE && rangFin != 5)
    {
        return false;
    }
    if (board.getColor(caseDebut) == BLACK && rangFin != 2)
    {
        return false;
    }
    int enPassantSquare = board.getSquare(colonneFin, rangDebut);
    if (board.getPiece(enPassantSquare) != PAWN || board.getColor(enPassantSquare) == board.getColor(caseDebut))
    {
        return false;
    }
    if (board.isKingInCheck(board.getColor(caseDebut)))
    {
        return false;
    }
    //std::cout<<"ENPA "<<Chessboard::enPA<<std::endl;
    return true;
}

int findPosition(int k, int n)
{
    // Iterate through all fibonacci numbers
    unsigned long long int f1 = 0, f2 = 1, f3;
    for (int i = 2; i <= 55; i++) {
        f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
 
        // Found first multiple of k at position i
        if (f2 % k == 0)
 
            // n'th multiple would be at position n*i
            // using Periodic property of Fibonacci
            // numbers under modulo.
            return n * i;
    }
    return 9;
}

bool Move::isPromotionLegal(const Chessboard &board, int caseDebut, int caseFin)
{
    //std::cout << "caseDebut" << caseDebut << std::endl;
    //std::cout << "caseFin" << caseFin << std::endl;
    //std::cout << "board.getPiece(caseDebut)" << board.getPiece(caseDebut) << std::endl;
    if (board.getPiece(caseDebut) != PAWN)
        return false;

    Color color = board.getColor(caseDebut);
    int rangFin =board.getRank(caseFin);
    //std::cout << "rangFin" << rangFin << std::endl;
    if (color == WHITE && rangFin == 7)
    {
        //std::cout << "PROMOTION" << std::endl;
        return true;
    }
    else if (color == BLACK && rangFin == 0)
        return true;

    return false;
}

bool Move::isMoveLegal(const Chessboard &board, int caseDebut, int caseFin)
{
    Color color = board.getColor(caseDebut);
    Piece piece = board.getPiece(caseDebut);
    
    if (((color == WHITE) && ::Chessboard::castlingWQ == true) || ((color == BLACK) && ::Chessboard::castlingBQ == true))
    {
        if (bigCastlingMove(board, caseDebut, caseFin))
        {
            return isCastlingLegal(board, caseDebut, caseFin);
        }
    }
    if (((color == WHITE) && ::Chessboard::castlingWK == true) || ((color == BLACK) && ::Chessboard::castlingBK == true))
    {
        if (lilCastlingMove(board, caseDebut, caseFin))
        {
            return isCastlingLegal(board, caseDebut, caseFin);
        }
    }
    
    if (Chessboard::enPA != "-" && Chessboard::prof=="1") ////dmd utilite de ce truc
    {
            Color safecolor = board.getColor(caseDebut);
            int rangDebut = board.getRank(caseDebut);
            int rangFin = board.getRank(caseFin);

            if (safecolor == WHITE && rangDebut == 4 && rangFin == 5)
            {
                //std::cout<<"HARDCODE ENPA    "<<std::endl;
                if (board.getPiece(caseDebut)==PAWN && board.getPiece(caseFin)==EMPTY && board.getPiece(board.getSquare(board.getFile(caseFin), board.getRank(caseDebut)))==PAWN && board.getColor(board.getSquare(board.getFile(caseFin), board.getRank(caseDebut)))==BLACK)
                {
                    return true;
                }

            else if (safecolor == BLACK && rangDebut == 3 && rangFin == 2)
                if (board.getPiece(caseDebut)==PAWN && board.getPiece(caseFin)==EMPTY && board.getPiece(board.getSquare(board.getFile(caseFin), board.getRank(caseDebut)))==PAWN && board.getColor(board.getSquare(board.getFile(caseFin), board.getRank(caseDebut)))==WHITE)
                {
                    return true;
                }
            }
        }
/*
    if (safecolor == WHITE && rangDebut == 1 && rangFin == 3)
    {
        int leftNeighborSquare = caseFin - 1;
        int rightNeighborSquare = caseFin + 1;
        if ((board.getPiece(leftNeighborSquare) == PAWN && board.getColor(leftNeighborSquare) == BLACK) ||
               (board.getPiece(rightNeighborSquare) == PAWN && board.getColor(rightNeighborSquare) == BLACK)) {
                Chessboard::enPA = "y";
                return true;
                }        
    }
    else if (safecolor == BLACK && rangDebut == 6 && rangFin == 4)
    {
        int leftNeighborSquare = caseFin - 1;
        int rightNeighborSquare = caseFin + 1;
        if ((board.getPiece(leftNeighborSquare) == PAWN && board.getColor(leftNeighborSquare) == WHITE) ||
               (board.getPiece(rightNeighborSquare) == PAWN && board.getColor(rightNeighborSquare) == WHITE)) {
                Chessboard::enPA = "y";
                return true;
                }
    }
        return isEnPassantMove(board, caseDebut, caseFin);
    }*/
    
    if (board.getPiece(caseFin) != EMPTY && board.getColor(caseFin) == color)
    {
        return false;
    }

    switch (piece)
    {
    case 1:
        // std::cout << "pawn";
        return isPawnMoveLegal(board, caseDebut, caseFin, color);
    case 2:
        // std::cout << "rook";
        return isRookMoveLegal(board, caseDebut, caseFin);
    case 3:
        // std::cout << "knight";
        return isKnightMoveLegal(board, caseDebut, caseFin);
    case 4:
        // std::cout << "bishop";
        return isBishopMoveLegal(board, caseDebut, caseFin);
    case 5:
        // std::cout << "queen";
        return isQueenMoveLegal(board, caseDebut, caseFin);
    case 6:
        // std::cout << "king";
        return isKingMoveLegal(board, caseDebut, caseFin);

    default:
        // std::cout << "RIEN";
        return false;
    }
}

bool Move::isPawnMoveLegal(const Chessboard &board, int caseDebut, int caseFin, Color color)
{
// rajouter ici le check si j'ai bien un en passant, puis je set le bail du en passant a un autre chose que -
// et apres je rajoute le move dans le vector de move, puis je remet le bail a - apres avoir fait le perft associe;
// tester avec le test que j'ai et apres tester avec un pion et deux autres qqui poeuvent fair een passant .
// et apres je fais le perft et je vois si ca marche bien

  /*  Color safecolor = board.getColor(caseDebut);
    int rangDebut = board.getRank(caseDebut);
    int rangFin = board.getRank(caseFin);

    if (safecolor == WHITE && rangDebut == 1 && rangFin == 3)
    {
        int leftNeighborSquare = caseFin - 1;
        int rightNeighborSquare = caseFin + 1;
        if ((board.getPiece(leftNeighborSquare) == PAWN && board.getColor(leftNeighborSquare) == BLACK) ||
               (board.getPiece(rightNeighborSquare) == PAWN && board.getColor(rightNeighborSquare) == BLACK)) {
                Chessboard::enPA = "y";
                return true;
                }        
    }
    else if (safecolor == BLACK && rangDebut == 6 && rangFin == 4)
    {
        int leftNeighborSquare = caseFin - 1;
        int rightNeighborSquare = caseFin + 1;
        if ((board.getPiece(leftNeighborSquare) == PAWN && board.getColor(leftNeighborSquare) == WHITE) ||
               (board.getPiece(rightNeighborSquare) == PAWN && board.getColor(rightNeighborSquare) == WHITE)) {
                Chessboard::enPA = "y";
                return true;
                }
    }

    if (safecolor == WHITE && rangDebut == 4 && rangFin == 5)
    {
        if (board.getPiece(caseDebut)==PAWN && board.getPiece(caseFin)==EMPTY && board.getPiece(board.getSquare(board.getFile(caseDebut), board.getRank(caseFin)))==PAWN && board.getColor(board.getSquare(board.getFile(caseFin), rangFin-1))==BLACK)
        {
            return true;
        }
        int leftNeighborSquare = caseFin - 1;
        int rightNeighborSquare = caseFin + 1;
        if ((board.getPiece(leftNeighborSquare) == PAWN && board.getColor(leftNeighborSquare) == BLACK) ||
               (board.getPiece(rightNeighborSquare) == PAWN && board.getColor(rightNeighborSquare) == BLACK)) {
                Chessboard::enPA = "y";
                return true;
                }       
    }
    else if (safecolor == BLACK && rangDebut == 3 && rangFin == 2)
    {
        int leftNeighborSquare = caseFin - 1;
        int rightNeighborSquare = caseFin + 1;
        if ((board.getPiece(leftNeighborSquare) == PAWN && board.getColor(leftNeighborSquare) == WHITE) ||
               (board.getPiece(rightNeighborSquare) == PAWN && board.getColor(rightNeighborSquare) == WHITE)) {
                Chessboard::enPA = "y";
                return true;
                }
    }*/

    int rankDiff = board.getRank(caseFin) - board.getRank(caseDebut);
    int fileDiff = std::abs(board.getFile(caseFin) - board.getFile(caseDebut));

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
        if (board.getPiece(caseFin) == EMPTY)
        {
            if (std::abs(rankDiff) == 1)
            {
                return true;
            }

            int startRank = (color == WHITE) ? 1 : 6;
            if (board.getRank(caseDebut) == startRank && std::abs(rankDiff) == 2)
            {
                int intermediateRank = startRank + (rankDiff / 2);
                int intermediateSquare = board.getSquare(board.getFile(caseDebut), intermediateRank);
                if (board.getPiece(intermediateSquare) == EMPTY)
                {
                    return true;
                }
            }
        }
    }
    else if (fileDiff == 1 && std::abs(rankDiff) == 1) // capture un ennemi
    {
        if (board.getPiece(caseFin) != EMPTY && board.getColor(caseFin) != color)
        {
            return true;
        }
    }
    return false;
}

bool Move::isRookMoveLegal(const Chessboard &board, int caseDebut, int caseFin)
{
    int rangDebut = board.getRank(caseDebut);
    int colonneDebut = board.getFile(caseDebut);
    int rangFin = board.getRank(caseFin);
    int colonneFin = board.getFile(caseFin);

    if (rangDebut == rangFin || colonneDebut == colonneFin)
    {
        if (!board.isPathClear(caseDebut, caseFin))
        {
            return false;
        }
        int rankDiff = rangFin - rangDebut;
        int fileDiff = colonneFin - colonneDebut;

        int rankStep = (rankDiff > 0) ? 1 : ((rankDiff < 0) ? -1 : 0);
        int fileStep = (fileDiff > 0) ? 1 : ((fileDiff < 0) ? -1 : 0);

        int currentRank = rangDebut + rankStep;
        int currentFile = colonneDebut + fileStep;

        while (currentRank != rangFin || currentFile != colonneFin)
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

bool Move::isKnightMoveLegal(const Chessboard &board, int caseDebut, int caseFin)
{
    int rankDiff = std::abs(board.getRank(caseFin) - board.getRank(caseDebut));
    int fileDiff = std::abs(board.getFile(caseFin) - board.getFile(caseDebut));
    // Check if the move is in an L-shape (2 squares in one direction and 1 square in the other)
    return (rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2);
}

bool Move::isBishopMoveLegal(const Chessboard &board, int caseDebut, int caseFin)
{
    int rangDebut = board.getRank(caseDebut);
    int colonneDebut = board.getFile(caseDebut);
    int rangFin = board.getRank(caseFin);
    int colonneFin = board.getFile(caseFin);

    if (std::abs(rangFin - rangDebut) == std::abs(colonneFin - colonneDebut))
    {
        int rankDiff = rangFin - rangDebut;
        int fileDiff = colonneFin - colonneDebut;

        int rankStep = (rankDiff > 0) ? 1 : -1;
        int fileStep = (fileDiff > 0) ? 1 : -1;

        int currentRank = rangDebut + rankStep;
        int currentFile = colonneDebut + fileStep;

        while (currentRank != rangFin || currentFile != colonneFin)
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

bool Move::isQueenMoveLegal(const Chessboard &board, int caseDebut, int caseFin)
{
    return isRookMoveLegal(board, caseDebut, caseFin) || isBishopMoveLegal(board, caseDebut, caseFin);
}

bool Move::isKingMoveLegal(const Chessboard &board, int caseDebut, int caseFin)
{
    int rankDiff = std::abs(board.getRank(caseFin) - board.getRank(caseDebut));
    int fileDiff = std::abs(board.getFile(caseFin) - board.getFile(caseDebut));

    return rankDiff <= 1 && fileDiff <= 1;
}

std::vector<int> Move::generateAllLegalMoves(const Chessboard &board, Color currentColor)
{
    std::vector<int> allLegalMoves;
    //std::cout << "playertomove :" << board.PlayerToMove << std::endl;
    for (int caseDebut = 0; caseDebut < 64; caseDebut++)
    {
        if (board.getPiece(caseDebut) != EMPTY && board.getColor(caseDebut) == currentColor)
        {
            for (int caseFin = 0; caseFin < 64; caseFin++)
            {
                if (caseFin == caseDebut)
                {
                    continue;
                }
                else
                {
                    if (isMoveLegal(board, caseDebut, caseFin))
                    {
                        allLegalMoves.push_back(caseDebut);
                        allLegalMoves.push_back(caseFin);
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
