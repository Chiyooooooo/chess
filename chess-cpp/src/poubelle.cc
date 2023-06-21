/*
bool Move::isCastlingLegal(const Chessboard& board, int sourceSquare, int targetSquare)
{
   
    int file = ( board.getFile(sourceSquare) + board.getFile(targetSquare)) / 2; 
    std::cout<< "la nouveau rang"<<file <<std::endl;


     int sourceRank = board.getRank(sourceSquare);
    int sourceFile = board.getFile(sourceSquare);
    //int targetRank = board.getRank(targetSquare);
    int targetFile = board.getFile(targetSquare);

    int rank = sourceRank;

    //int rookSquare = board.getSquare(file, rank);
    int rookSquare = targetSquare;
    if (board.getPiece(targetSquare) != ROOK)
    {
        return false;
    }
    if (board.getColor(rookSquare) != board.getColor(sourceSquare))
    {
        return false;
    }
    if (board.getPiece(sourceSquare) != KING || board.getPiece(rookSquare) != ROOK)
    {
        return false;
    }

    if (board.getColor(sourceSquare) != board.getColor(rookSquare))
    {
        return false;
    }
    
    if (board.isKingInCheck(board.getColor(sourceSquare)))
    {
        return false;
    }

    if (!board.isPathClear(sourceSquare, targetSquare))
    {
        return false;
    }
    std::cout<<"FELICITATION "<<std::endl;
    return true;
}





std::vector<int> Move::generateAllLegalMoves(const Chessboard &board)
{
    std::vector<int> allLegalMoves;

    for (int sourceSquare = 0; sourceSquare < 64; sourceSquare++) {
        if (board.getPiece(sourceSquare) != EMPTY && board.getColor(sourceSquare) != BLACK              && board.getColor(sourceSquare) == board.sideToMove()) {
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










int main()
{
    Chessboard board;

    board.loadFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R");//48 
    board.prettyPrint();

    std::vector<int> all = Move::generateAllLegalMoves(board);
    std::cout << all.size() << std::endl;
    for (unsigned long i = 0; i < all.size(); ++i) {
        std::cout << Move::getSquareName(all[i]) << " ";
    }

    int result = perft(board, 1);
    std::cout << result << std::endl;

    return 0;
}









/////////////////////
bool Move::isEnPassantMove(const Chessboard &board, int sourceSquare, int targetSquare)
{
    // Check if the source piece is a pawn
    if (board.getPiece(sourceSquare) != PAWN)
        return false;

    Color color = board.getColor(sourceSquare);
    int targetRank = getRank(targetSquare);

    // Check if the target square is a valid en passant capture square
    if (color == WHITE && targetRank == Rank_6)
    {
        int enPassantSquare = targetSquare - Chessboard::Size;
        return (board.getPiece(enPassantSquare) == PAWN && board.getColor(enPassantSquare) == BLACK);
    }
    else if (color == BLACK && targetRank == Rank_3)
    {
        int enPassantSquare = targetSquare + Chessboard::Size;
        return (board.getPiece(enPassantSquare) == PAWN && board.getColor(enPassantSquare) == WHITE);
    }

    return false;
}

bool Move::isPromotionLegal(const Chessboard &board, int sourceSquare, int targetSquare)
{
    // Check if the source piece is a pawn
    if (board.getPiece(sourceSquare) != PAWN)
        return false;

    Color color = board.getColor(sourceSquare);
    int targetRank = getRank(targetSquare);

    // Check if the target square is a valid promotion square
    if (color == WHITE && targetRank == Rank_8)
        return true;
    else if (color == BLACK && targetRank == Rank_1)
        return true;

    return false;
}

*/



