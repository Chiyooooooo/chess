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

bool Move::isEnPassantMove(const Chessboard &board, int caseDebut, int caseFin)
{
    //Color safecolor = board.getColor(caseDebut);

    int rangDebut = board.getRank(caseDebut);
    int colonneDebut = board.getFile(caseDebut);
    int rangFin = board.getRank(caseFin);
    int colonneFin = board.getFile(caseFin);
    if (board.getPiece(caseDebut) != PAWN || board.getPiece(caseFin) != EMPTY)
    {std::cout<<"OKpp1 \n";
        return false;
    }
    if (board.getColor(caseDebut) == board.getColor(caseFin))
    {std::cout<<"OKpp2 \n";
        return false;
    }
        std::cout<<std::abs(rangFin)<< " RANGG FIN  "<< std::endl;

    std::cout<<std::abs(rangDebut)<< " RANGG DEBUT  "<< std::endl;

    if (std::abs(rangDebut - rangFin) != 1)
    {std::cout<<"OKpp3 \n";

        return false;
    }
    std::cout<<colonneDebut<< " COPLONNNNNE  "<<colonneFin << std::endl;

    if (std::abs(colonneDebut - colonneFin) != 1)
    {std::cout<<"OooK \n";

        return false;
    }
    if ((board.getColor(caseDebut) == WHITE && rangFin != 5)||(board.getColor(caseDebut) == BLACK && rangFin != 2))
    {std::cout<<"OK \n";

        return false;
    }
    int enPassantSquare = board.getSquare(colonneFin, rangDebut);
    if (board.getPiece(enPassantSquare) != PAWN || board.getColor(enPassantSquare) == board.getColor(caseDebut))
    {std::cout<<"OK \n";
        return false;
    }
    if (board.isKingInCheck(board.getColor(caseDebut)))
    {std::cout<<"OK \n";
        return false;
    }
    return true;
}

int findPosition(int k, int n)
{
    unsigned long long int f1 = 0, f2 = 1, f3;
    for (int i = 2; i <= 55; i++)
    {
        f3 = f1 + f2;
        f1 = f2;
        f2 = f3;

        if (f2 % k == 0)

            return n * i;
    }
    return 9;
}

bool Move::isPromotionLegal(const Chessboard &board, int caseDebut, int caseFin)
{
    // std::cout << "caseDebut" << caseDebut << std::endl;
    // std::cout << "caseFin" << caseFin << std::endl;
    // std::cout << "board.getPiece(caseDebut)" << board.getPiece(caseDebut) << std::endl;
    if (board.getPiece(caseDebut) != PAWN)
        return false;

    Color color = board.getColor(caseDebut);
    int rangFin = board.getRank(caseFin);
    // std::cout << "rangFin" << rangFin << std::endl;
    if (color == WHITE && rangFin == 7)
    {
        // std::cout << "PROMOTION" << std::endl;
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
    //std::cout << Chessboard::enPA << "ENPAAAA la ";
    /*if ((piece ==KING) && board.isKingInCheck(color)==true)
    {
        int rankDiff = std::abs(board.getRank(caseFin) - board.getRank(caseDebut));
        int fileDiff = std::abs(board.getFile(caseFin) - board.getFile(caseDebut));
        return rankDiff <= 1 && fileDiff <= 1;
    }*/

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

    if (Chessboard::enPA != "-") //&& Chessboard::prof == "1") ///a verufier si fctionne
    {
        //std::cout << "EN PASSANT" << std::endl;

        int caseEnPa = board.getSquare(board.getFile(getSquareFromName(Chessboard::enPA)), board.getRank(getSquareFromName(Chessboard::enPA)));
        Color safecolor = board.getColor(caseDebut);
        int rangDebut = board.getRank(caseDebut);
        int rangFin = board.getRank(caseFin);
        int colonneDebut = board.getFile(caseDebut);
        int colonneFin = board.getFile(caseFin);

        if (safecolor == WHITE && rangDebut == 4 && rangFin == 5)
        {   
            if (std::abs(colonneDebut - colonneFin)==1){
            if (board.getPiece(caseDebut) == PAWN && board.getPiece(caseFin) == EMPTY &&
             board.getPiece(board.getSquare(board.getFile(caseFin), board.getRank(caseDebut))) == PAWN && 
             board.getColor(board.getSquare(board.getFile(caseFin), board.getRank(caseDebut))) == BLACK)
            {
                std::cout << "casefin : " << caseFin << " caseENPa :" << caseEnPa << std::endl;
                if (caseFin == caseEnPa)
                {
                    std::cout << "EN PASSANT" << std::endl;
                    Chessboard::enPADONEW = Chessboard::enPA;
                    Chessboard::enPA = "-";
                    std::cout << "EN PASSANTW "<< rangDebut<< " enpaW : "<< Chessboard::enPADONEW<< std::endl;
                    return true;
                }
            }}
        }
        else if (safecolor == BLACK && rangDebut == 3 && rangFin == 2){
            if (std::abs(colonneDebut - colonneFin)==1){
            if (board.getPiece(caseDebut) == PAWN && board.getPiece(caseFin) == EMPTY && 
            board.getPiece(board.getSquare(board.getFile(caseFin), board.getRank(caseDebut))) == PAWN && 
            board.getColor(board.getSquare(board.getFile(caseFin), board.getRank(caseDebut))) == WHITE)
            {
                // std::cout << "EN PASSANTB" << std::endl;
                if (caseFin == caseEnPa)
                {
                    Chessboard::enPADONEB = Chessboard::enPA;
                    std::cout << Chessboard::enPA;
                    Chessboard::enPA = "-";
                    std::cout << "EN PASSANTB" << std::endl;
                    std::cout << " CASE DEBUT " << caseDebut << "\n";
                    std::cout << " CASE FIN " << caseFin << "\n";
                    return true;
                }
            }}
        }
    }

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
                    int leftNeighborSquare = caseFin - 1;
                    int rightNeighborSquare = caseFin + 1;

                    if (/*Chessboard::enPA =="-" &&*/ color == WHITE && ((board.getPiece(leftNeighborSquare) == PAWN && board.getColor(leftNeighborSquare) == BLACK) ||
                                           (board.getPiece(rightNeighborSquare) == PAWN && board.getColor(rightNeighborSquare) == BLACK)))
                    {
                        //Chessboard::enPA = board.getSquareName(caseFin - 8);
                        std::cout << Chessboard::enPA << "nouveau enpa calcule BLANC\n";
                        return true;
                    }
                    else if (/*Chessboard::enPA =="-" &&*/ color == BLACK && ((board.getPiece(leftNeighborSquare) == PAWN && board.getColor(leftNeighborSquare) == WHITE) ||
                                                (board.getPiece(rightNeighborSquare) == PAWN && board.getColor(rightNeighborSquare) == WHITE)))
                    {
                        //Chessboard::enPA = board.getSquareName(caseFin + 8);
                        std::cout << Chessboard::enPA << "nouveau enpa calcule  NOIR\n";

                        return true;
                    }
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
    if (rankDiff <= 1 && fileDiff <= 1)
    {
       // std::cout << "caseDebut" << caseDebut << std::endl;
        //std::cout << "caseFin" << caseFin << std::endl;
        return true;
    }
    return false;
}

std::vector<int> Move::generateAllLegalMoves(const Chessboard &board, Color currentColor)
{
    std::vector<int> allLegalMoves;
    // std::cout << "playertomove :" << board.PlayerToMove << std::endl;
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



int Move::getSquareFromName(const std::string &name)
{
    if (name.length() != 2)
        return -1; // Invalid square name

    int file = name[0] - 'a';
    int rank = name[1] - '1';

    if (file < 0 || file >= Chessboard::Size || rank < 0 || rank >= Chessboard::Size)
        return -1; // Invalid square name

    return rank * Chessboard::Size + file;
}
