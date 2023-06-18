
#include "perft.hh"
#include "move.hh"

int perft(Chessboard &board, int depth)
{
    if (depth == 0){return 1;}

    int solution = 0;

    for (int fromSquare = 0; fromSquare < Chessboard::Size * Chessboard::Size; ++fromSquare)
    {
        //Piece piece = board.getPiece(fromSquare);
        for (int toSquare = 0; toSquare < Chessboard::Size * Chessboard::Size; ++toSquare)
        {
            if (board.isValidSquare(toSquare) && board.isValidMove(fromSquare, toSquare))
            {
                Piece capturedPiece = board.getPiece(toSquare);
                Color capturedPieceColor = board.getColor(toSquare);
                

                board.movePiece(fromSquare, toSquare);
                // std::cout<< Move::isMoveLegal(board, fromSquare, toSquare);
                // std::cout<<fromSquare<<std::endl;
                // std::cout<<toSquare<<std::endl;
                if (!board.isKingInCheck(WHITE) && Move::isMoveLegal(board, fromSquare, toSquare))
                {
                    std::cout << "dedans";
                    solution += perft(board, depth - 1);
                }
                board.undoMove(fromSquare, toSquare, capturedPiece, capturedPieceColor);
            }
        }
    }
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
