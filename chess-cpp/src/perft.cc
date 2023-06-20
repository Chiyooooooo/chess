
#include "perft.hh"
#include "move.hh"

int perft(Chessboard &board, int depth)
{
    if (depth == 0){return 1;}
    
    int solution = 0;
    std::vector<int> sol = Move::generateAllLegalMoves(board);
    /*if (depth == 1){
       return ((Move::generateAllLegalMoves(board)).size()/2);
    }*/

    int len = (int)sol.size();
    int i;
    //int j;
    for ( i=0 ; i < len; i+=2)
    {
        int fromSquare = sol[i];
        std::cout<<fromSquare<<"\n";
        //for( j=1 ; j < len; j+=2)
        
            int toSquare = sol[i+1];
             //if (board.isValidSquare(toSquare))// && board.isValidMove(fromSquare, toSquare) && Move::isMoveLegal(board, fromSquare, toSquare))
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

/*
int perft(Chessboard &board, int depth)
{
    if (depth == 0) return 1;
    int nodes = 0;

    std::vector<int> moves = Move::getLegalMoves(board, square);
    for (const Move move: moves) {
        board.makeMove(move);
        if (!inCheck(board, Pieces::invertColor(board.sideToMove))) {
            int childNodes = perft(depth - 1, board);
            nodes += childNodes;
        }
        board.unMakeMove();
    }
    return nodes;
}
*/

/*
public long perft(int depth){

        List<Move> moves = board.getAllMoves(board.state.currentPlayer);
        int n_moves = moves.size();
        long totalNodes = 0L;

        if (depth == 1)                 
            return n_moves;     

        for (Move mv : moves){                  
            BoardState undo = board.makeMove(mv);               
            totalNodes += perft(depth - 1);         
            board.undoMove(mv, undo);
        }
        return totalNodes;
}
*/

/*
unsigned long long perft(Chessboard &board, int depth)
{
    if (depth == 0)
    {
        return 1;
    }

    unsigned long long solution = 0;

    for (int fromSquare = 0; fromSquare < Chessboard::Size * Chessboard::Size; ++fromSquare)
    {
        Piece piece = board.getPiece(fromSquare);

        if (board.getColor(fromSquare) != WHITE || piece == EMPTY)
        {
            continue;
        }

        for (int toSquare = 0; toSquare < Chessboard::Size * Chessboard::Size; ++toSquare)
        {
            if (board.isValidSquare(toSquare) && board.isValidMove(fromSquare, toSquare) && isMoveLegal(board,fromSquare, toSquare))
            {
                Piece capturedPiece = board.getPiece(toSquare);
                Color capturedPieceColor = board.getColor(toSquare);

                board.movePiece(fromSquare, toSquare);

                if (!board.isKingInCheck(WHITE))
                {
                    solution += perft(board, depth - 1);
                }
                board.setPiece(fromSquare, piece, WHITE);
                board.setPiece(toSquare, capturedPiece, capturedPieceColor);
            }
        }
    }

    return solution;
}
*/
