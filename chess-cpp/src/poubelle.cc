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
*/