
#include "perft.hh"
#include "move.hh"

int perft(Chessboard &board, int depth, Color currentColor)
{
    // std::cout << "\n";

    if (depth == 0)
    {
        return 1;
    }

    int solution = 0;
    std::vector<int> sol = Move::generateAllLegalMoves(board, currentColor);
    /*
    for (unsigned long i = 0; i < sol.size(); ++i) {
        std::cout << sol[i] << " ";
    }
    std::cout << std::endl;*/

    // std::cout << "depth " << depth << " : " << sol.size() / 2 << " moves" << std::endl;
    /*if (depth == 1){
       return ((Move::generateAllLegalMoves(board)).size()/2);
    }*/
    int len = (int)sol.size();
    int i;
    for (i = 0; i < len; i += 2)
    {
        int fromSquare = sol[i];
        int toSquare = sol[i + 1];

        // std::cout << Move::getSquareName(fromSquare) << "" << Move::getSquareName(toSquare);
        //  if (board.isValidSquare(toSquare) && Move::isMoveLegal(board, fromSquare, toSquare))
        {
            Piece capturedPiece = board.getPiece(toSquare);
            Color capturedPieceColor = board.getColor(toSquare);
            Color col = board.getColor(fromSquare);

            if (Move::isPromotionLegal(board, fromSquare, toSquare))
            {
                // PROMOTION
                // std::cout << "PROMOTION";
                board.movePiece(fromSquare, toSquare);
                board.setPiece(toSquare, ROOK, col);
                if (!board.isKingInCheck(col))
                {
                    solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                }
                board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);

                board.movePiece(fromSquare, toSquare);
                board.setPiece(toSquare, KNIGHT, col);
                if (!board.isKingInCheck(col))
                {
                    solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                }
                board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);

                board.movePiece(fromSquare, toSquare);
                board.setPiece(toSquare, BISHOP, col);
                if (!board.isKingInCheck(col))
                {
                    solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                }
                board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);

                board.movePiece(fromSquare, toSquare);
                board.setPiece(toSquare, QUEEN, col);
                if (!board.isKingInCheck(col))
                {
                    solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                }
                board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);
                board.setPiece(fromSquare, PAWN, col);
                // board.prettyPrint();
            }

            else if (Move::bigCastlingMove(board, fromSquare, toSquare) || Move::lilCastlingMove(board, fromSquare, toSquare))
            {
                if (fromSquare == 4 && toSquare == 0)
                {
                    if (Move::isCastlingLegal(board, fromSquare, toSquare))
                    {
                        board.movePiece(fromSquare, 2);
                        board.movePiece(0, 3);
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                        board.undoMove(fromSquare, 2, EMPTY, EMPTY_COLOR);
                        board.undoMove(0, 3, EMPTY, EMPTY_COLOR);
                    }
                }
                if (fromSquare == 4 && toSquare == 7)
                {
                    if (fromSquare == 4 && toSquare == 7)
                    {
                        if (Move::isCastlingLegal(board, fromSquare, toSquare))
                        {
                            board.movePiece(fromSquare, 6);
                            board.movePiece(7, 5);
                            solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                            board.undoMove(fromSquare, 6, EMPTY, EMPTY_COLOR); // a voir mais normalement ok
                            board.undoMove(7, 5, EMPTY, EMPTY_COLOR);
                        }
                    }
                }
            }

            ///////laisser le castling juste avant l'autre bail

            else if (Chessboard::enPADONEW != "-")
            {
                //   if (Move::isEnPassantMove(board, fromSquare, toSquare))
                {
                    board.movePiece(fromSquare, toSquare);
                    board.setPiece(toSquare - 8, EMPTY, EMPTY_COLOR);
                    if (!board.isKingInCheck(col))
                    {
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                    }
                    board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);
                    board.setPiece(toSquare - 8, PAWN, BLACK);
                }
                Chessboard::enPADONEW = "-";
                Chessboard::enPA = "-"; // utilite et savoir si c'est bien place
            }
            else if (Chessboard::enPADONEB != "-")
            {
                // if (Move::isEnPassantMove(board, fromSquare, toSquare))
                {
                    board.movePiece(fromSquare, toSquare);
                    board.setPiece(toSquare + 8, EMPTY, EMPTY_COLOR);
                    if (!board.isKingInCheck(col))
                    {
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                    }
                    board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);
                    board.setPiece(toSquare + 8, PAWN, WHITE);
                }
                Chessboard::enPADONEB = "-";
                Chessboard::enPA = "-"; // utilite et savoir si c'est bien place
            }
            /*{
                if (Move::isEnPassantMove(board, fromSquare, toSquare))
                {
                    std::cout << "EN PASSANT";
                    board.movePiece(fromSquare, toSquare);
                    board.setPiece(toSquare - 8, EMPTY, EMPTY_COLOR);
                    if (!board.isKingInCheck(col))
                    {
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                    }
                    board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);
                    board.setPiece(toSquare - 8, PAWN, (currentColor == WHITE) ? BLACK : WHITE);}
                //Chessboard::enPA = "-";
            }*/
            else
            {
                if (fromSquare == 31 && toSquare == 22)
                {
                    // std::cout << Move::getSquareName(fromSquare) << "" << Move::getSquareName(toSquare)<<std::endl;
                    std::cout << "validite du coup  " << toSquare << ": " << board.isKingInCheck(col) << std::endl;
                    std::cout << "check avec validmove  " << toSquare << ": " << board.isValidMove(fromSquare, toSquare) << std::endl;
                    board.movePiece(fromSquare, toSquare);

                    if (!board.isKingInCheck(col))
                    {
                        std::cout << Move::getSquareName(fromSquare) << "" << Move::getSquareName(toSquare) << std::endl;
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                    }
                    ///// pas obublier de changer le boolean pr le roque
                    board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);
                }

                board.movePiece(fromSquare, toSquare);
                if (!board.isKingInCheck(col))
                {
                    std::cout << Move::getSquareName(fromSquare) << "" << Move::getSquareName(toSquare) << std::endl;

                    solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                }
                ///// pas obublier de changer le boolean pr le roque
                board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);
            }
        }
    }
    /*
        for (int fromSquare = 0; fromSquare < Chessboard::Size * Chessboard::Size; ++fromSquare)
        {
            //Piece piece = board.getPiece(fromSquare);
            for (int toSquare = 0; toSquare < Chessboard::Size * Chessboard::Size; ++toSquare)
            {
                if (board.isValidSquare(toSquare) && board.isValidMove(fromSquare, toSquare) && Move::isMoveLegal(board, fromSquare, toSquare))
                {
                    Piece capturedPiece = board.getPiece(toSquare);
                    Color capturedPieceColor = board.getColor(toSquare);
                    Color col = board.getColor(fromSquare);

                    board.movePiece(fromSquare, toSquare);
                    if (!board.isKingInCheck(col))
                    {
                        solution += perft(board, depth - 1);
                    }
                    ///// pas obublier de changer le boolean pr le roque
                    board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);
                }
            }
        }
    */
    return solution;
}
