
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
    
   // if (depth==1) {
       // board.prettyPrint();
     //   for (unsigned long i = 0; i < sol.size(); i+=2) {
       //     std::cout << "coup  : " << board.getSquareName(sol[i]) << board.getSquareName(sol[i+1])
         //   << " de " << sol[i] << " a " << sol[i+1] << std::endl;}
           // std::cout << std::endl;}
        
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
        int caseEnPaW = board.getSquare(board.getFile(Move::getSquareFromName(Chessboard::enPADONEW)), board.getRank(Move::getSquareFromName(Chessboard::enPADONEW)));   
        int caseEnPaB = board.getSquare(board.getFile(Move::getSquareFromName(Chessboard::enPADONEB)), board.getRank(Move::getSquareFromName(Chessboard::enPADONEB)));   

         //std::cout << Move::getSquareName(fromSquare) << "" << Move::getSquareName(toSquare)<<std::endl;
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
                //std::cout<< "fromsq : "<< fromSquare << " , tosqr : " << toSquare<< "\n";
                if ((fromSquare == 4 && toSquare == 0))
                {
                    if (Move::isCastlingLegal(board, fromSquare, toSquare))
                    {
                        
                     //   std::cout << board.getSquareName(fromSquare) << "" << board.getSquareName(toSquare) << std::endl;
                        board.movePiece(fromSquare, 2);
                        board.movePiece(0, 3);
                        if (!board.isKingInCheck(col))
                        {
                            if (!board.isRookInCheck(3,col))
                    {
                        //board.prettyPrint();
                        Chessboard::castlingWQ = false; 
                     //   std::cout<<"ROQUE big : ";
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                        Chessboard::castlingWQ = true; 
                    }}
                        //solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                        board.undoMove(fromSquare, 2, EMPTY, EMPTY_COLOR);
                        board.undoMove(0, 3, EMPTY, EMPTY_COLOR);
                        
                    }
                }
                if ((fromSquare == 60 && toSquare == 56))
                {
                    if (Move::isCastlingLegal(board, fromSquare, toSquare))
                    {
                      //  std::cout<<"ROQUE big : ";
                  //      std::cout << board.getSquareName(fromSquare) << "" << board.getSquareName(toSquare) << std::endl;
                        board.movePiece(fromSquare, 58);
                        board.movePiece(56, 59);
                        if (!board.isKingInCheck(col))
                        {
                            if (!board.isRookInCheck(59,col))
                    {
                        Chessboard::castlingBK=false ;
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                        Chessboard::castlingBK=true ;
                    }}
                        //solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                        board.undoMove(fromSquare, 58, EMPTY, EMPTY_COLOR);
                        board.undoMove(56, 59, EMPTY, EMPTY_COLOR);
                    }
                }
                if ((fromSquare == 4 && toSquare == 7))
                {
                    if (Move::isCastlingLegal(board, fromSquare, toSquare))
                    {   
                     //   std::cout << board.getSquareName(fromSquare) << "" << board.getSquareName(toSquare) << std::endl;
                        board.movePiece(fromSquare, 6);
                        board.movePiece(7, 5);
                     //   std::cout << "kingcheck" << (!board.isKingInCheck(col)) ;
                      //  std::cout << "kingcheck" << (!board.isRookInCheck(7,col));
                      //  board.prettyPrint();
                    if ((!board.isKingInCheck(col)))
                    {   if (!board.isRookInCheck(5,col))
                    {
                        Chessboard::castlingWK=false ;
                      //  std::cout<<"ROQUE lil  : ";
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                        Chessboard::castlingWK=true ;
                    }}

                       // solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                        board.undoMove(fromSquare, 6, EMPTY, EMPTY_COLOR); // a voir mais normalement ok
                        board.undoMove(7, 5, EMPTY, EMPTY_COLOR);
                        
                    }
                }
                if ((fromSquare == 60 && toSquare == 63))
                {
                    if (Move::isCastlingLegal(board, fromSquare, toSquare))
                    {//   std::cout<<"ROQUE lil  : ";
              //          std::cout << board.getSquareName(fromSquare) << "" << board.getSquareName(toSquare) << std::endl;
                        board.movePiece(fromSquare, 62);
                        board.movePiece(63, 61);
                        
                    if (!board.isKingInCheck(col)){
                        if  (!board.isRookInCheck(61,col))
                    {
                        Chessboard::castlingBK=false ;
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                        Chessboard::castlingBK=true ;
                    }}
                        //solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                        board.undoMove(fromSquare, 62, EMPTY, EMPTY_COLOR); // a voir mais normalement ok
                        board.undoMove(63, 61, EMPTY, EMPTY_COLOR);
                    }
                }
            }

            ///////laisser le castling juste avant l'autre bail
            else if (Chessboard::enPADONEW != "-" && board.getPiece(fromSquare) == PAWN  && caseEnPaW ==toSquare && board.getPiece(toSquare) == EMPTY)
            {   //std::cout << "ENPA W PERFT";

                if (Move::isEnPassantMove(board, fromSquare, caseEnPaW))
                {
                  //  board.prettyPrint();
                    board.movePiece(fromSquare, caseEnPaW);
                 //   std::cout << " from sq " << fromSquare << "\n";
                 //   std::cout << " to sq " << caseEnPaW << "\n";
                    board.setPiece(caseEnPaW - 8, EMPTY, EMPTY_COLOR);
                 //   board.prettyPrint();
                    if (!board.isKingInCheck(col))
                    {
                       // std::cout << "ENPA W PERFT";
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                    }
                    board.undoMove(fromSquare, caseEnPaW, capturedPiece, capturedPieceColor);
                    board.setPiece(caseEnPaW - 8, PAWN, BLACK);
                 //   board.prettyPrint();
                    Chessboard::enPADONEW = "-";
                    Chessboard::enPA = "-";
                }
                // utilite et savoir si c'est bien place
            }

            else if (Chessboard::enPADONEB != "-" && board.getPiece(fromSquare) == PAWN && caseEnPaB==toSquare && board.getPiece(toSquare)==EMPTY)
            {
                //std::cout << "ENPA B PERFT";
                //std::cout << " from sq " << fromSquare << "\n";
                //std::cout << " to sq " << caseEnPaB << "\n";
                if (Move::isEnPassantMove(board, fromSquare, caseEnPaB) && toSquare==caseEnPaB)
                {
                    //int caseEnPa = board.getSquare(board.getFile(Move::getSquareFromName(Chessboard::enPADONEB)), board.getRank(Move::getSquareFromName(Chessboard::enPADONEB)));   
                 //   int enPaDiff = board.getFile(fromSquare)-board.getFile(caseEnPaB);
                //    board.prettyPrint();
                    board.movePiece(fromSquare, caseEnPaB );
                  //  std::cout << " from sq " << fromSquare << "\n";
                   // std::cout << " to sq " << caseEnPaB << "\n";
                   // std::cout << "case en pa" << enPaDiff << "\n";

                    board.setPiece(caseEnPaB +8 , EMPTY, EMPTY_COLOR);
                  //  board.prettyPrint();
                    if (!board.isKingInCheck(col))
                    {
                     //   std::cout << "ENPA B PERFT";
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                    }
                    board.undoMove(fromSquare, caseEnPaB, capturedPiece, capturedPieceColor);
                    board.setPiece(caseEnPaB + 8 , PAWN, WHITE);
                 //   board.prettyPrint();
                    Chessboard::enPADONEB = "-";
                    Chessboard::enPA = "-";
                }
                    // utilite et savoir si c'est bien place
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
                /*
                if (fromSquare == 4 && toSquare == 5)
                {
                    // std::cout << Move::getSquareName(fromSquare) << "" << Move::getSquareName(toSquare)<<std::endl;
                      board.movePiece(fromSquare, toSquare);
                    std::cout << "validite du coup  " << toSquare << ": " << board.isKingInCheck(col) << std::endl;
                    std::cout << "check avec validmove  " << toSquare << ": " << board.isValidMove(fromSquare, toSquare) << std::endl;
                  
                    if (!board.isKingInCheck(col))
                    {
                        std::cout << board.getSquareName(fromSquare) << "" << board.getSquareName(toSquare) << std::endl;
                        solution += perft(board, depth - 1, (currentColor == WHITE) ? BLACK : WHITE);
                    }
                    ///// pas obublier de changer le boolean pr le roque
                    board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);
                }*/

                board.movePiece(fromSquare, toSquare);
                if (!board.isKingInCheck(col))
                {
                   // std::cout << board.getSquareName(fromSquare) << "" << board.getSquareName(toSquare) << std::endl;
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
