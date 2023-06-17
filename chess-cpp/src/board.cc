#include "board.hh"

    Chessboard::Chessboard()
    {
        reset();
    }

    void Chessboard::reset()
    {
        for (int square = 0; square < Size * Size; ++square)
        {
            board_[square] = EMPTY;
            color_[square] = EMPTY_COLOR;
        }
    }

    void Chessboard::setPiece(int square, Piece piece, Color color)
    {
        if (isValidSquare(square))
        {
            board_[square] = piece;
            color_[square] = color;
        }
    }

    Piece Chessboard::getPiece(int square) const
    {
        if (isValidSquare(square))
        {
            return static_cast<Piece>(board_[square]);
        }
        return EMPTY;
    }

    Color Chessboard::getColor(int square) const
    {
        if (isValidSquare(square))
        {
            return static_cast<Color>(color_[square]);
        }
        return EMPTY_COLOR;
    }

    bool Chessboard::isValidSquare(int square) const
    {
        return (square >= 0 && square < Size * Size);
    }

    void Chessboard::loadFEN(const std::string &fen)
    {
        reset();
        int rank = Size - 1;
        int file = 0;
        for (size_t i = 0; i < fen.size(); ++i)
        {
            char c = fen[i];
            if (c == '/')
            {
                rank--;
                file = 0;
            }
            else if (isdigit(c))
            {
                file += (c - '0');
            }
            else if (isalpha(c))
            {
                Piece piece = getPieceFromChar(c);
                Color color = islower(c) ? BLACK : WHITE;
                int square = rank * Size + file;
                setPiece(square, piece, color);
                file++;
            }
        }
    }
    /*
    #######################################################################################################################################################
                                                                MOVE GENERATION
    #######################################################################################################################################################
    */

    bool Chessboard::isValidMove(int fromSquare, int toSquare) const
    {
        // Check if the squares are valid
        if (!isValidSquare(fromSquare) || !isValidSquare(toSquare))
            return false;

        // Check if the piece at 'fromSquare' can move to 'toSquare' according to the chess rules
        Piece piece = getPiece(fromSquare);
        Color color = getColor(fromSquare);

        // Check if the move is valid for the given piece and color
        switch (piece)
        {
        case PAWN:
            return isValidPawnMove(fromSquare, toSquare, color);
        case ROOK:
            return isValidRookMove(fromSquare, toSquare);
        case KNIGHT:
            return isValidKnightMove(fromSquare, toSquare);
        case BISHOP:
            return isValidBishopMove(fromSquare, toSquare);
        case QUEEN:
            return isValidQueenMove(fromSquare, toSquare);
        case KING:
            return isValidKingMove(fromSquare, toSquare);
        default:
            return false; // Invalid piece
        }
    }

    bool Chessboard::isValidPawnMove(int fromSquare, int toSquare, Color color) const
    {
        // Check if the move is within one rank
        int rankDiff = std::abs(getRank(toSquare) - getRank(fromSquare));
        if (rankDiff != 1)
            return false;

        // Check if the move is within one file
        int fileDiff = std::abs(getFile(toSquare) - getFile(fromSquare));
        if (fileDiff > 1)
            return false;

        // Check if the pawn is moving forward
        int forwardDir = (color == WHITE) ? 1 : -1;
        if (getRank(toSquare) - getRank(fromSquare) != forwardDir)
            return false;

        // TODO: Implement additional pawn move logic, such as capturing, en passant, promotion, etc.

        return true;
    }

    bool Chessboard::isValidRookMove(int fromSquare, int toSquare) const
    {
        // Check if the move is horizontal or vertical
        if (getRank(fromSquare) != getRank(toSquare) && getFile(fromSquare) != getFile(toSquare))
            return false;

        // Check if there are any obstructions along the path
        if (!isPathClear(fromSquare, toSquare))
            return false;

        return true;
    }

    bool Chessboard::isValidKnightMove(int fromSquare, int toSquare) const
    {
        // Check if the move is in an L-shape (2 squares in one direction, 1 square in the other)
        int rankDiff = std::abs(getRank(toSquare) - getRank(fromSquare));
        int fileDiff = std::abs(getFile(toSquare) - getFile(fromSquare));
        if ((rankDiff != 2 || fileDiff != 1) && (rankDiff != 1 || fileDiff != 2))
            return false;

        return true;
    }

    bool Chessboard::isValidBishopMove(int fromSquare, int toSquare) const
    {
        // Check if the move is diagonal
        if (std::abs(getRank(toSquare) - getRank(fromSquare)) != std::abs(getFile(toSquare) - getFile(fromSquare)))
            return false;

        // Check if there are any obstructions along the path
        if (!isPathClear(fromSquare, toSquare))
            return false;

        return true;
    }

    bool Chessboard::isValidQueenMove(int fromSquare, int toSquare) const
    {
        // Check if the move is horizontal, vertical, or diagonal
        if (getRank(fromSquare) != getRank(toSquare) && getFile(fromSquare) != getFile(toSquare) &&
            std::abs(getRank(toSquare) - getRank(fromSquare)) != std::abs(getFile(toSquare) - getFile(fromSquare)))
            return false;

        // Check if there are any obstructions along the path
        if (!isPathClear(fromSquare, toSquare))
            return false;

        return true;
    }

    bool Chessboard::isValidKingMove(int fromSquare, int toSquare) const
    {
        // Check if the move is within one square in any direction
        int rankDiff = std::abs(getRank(toSquare) - getRank(fromSquare));
        int fileDiff = std::abs(getFile(toSquare) - getFile(fromSquare));
        if (rankDiff > 1 || fileDiff > 1)
            return false;

        return true;
    }

    bool Chessboard::isPathClear(int fromSquare, int toSquare) const
    {
        int rankDiff = getRank(toSquare) - getRank(fromSquare);
        int fileDiff = getFile(toSquare) - getFile(fromSquare);
        int rankDir = (rankDiff > 0) ? 1 : (rankDiff < 0) ? -1
                                                          : 0;
        int fileDir = (fileDiff > 0) ? 1 : (fileDiff < 0) ? -1
                                                          : 0;
        int currentSquare = fromSquare;

        while (currentSquare != toSquare)
        {
            currentSquare = getSquare(getFile(currentSquare) + fileDir, getRank(currentSquare) + rankDir);
            if (currentSquare != toSquare && getPiece(currentSquare) != EMPTY)
                return false;
        }

        return true;
    }

    int Chessboard::getRank(int square) const
    {
        return square / Chessboard::Size;
    }

    int Chessboard::getFile(int square) const
    {
        return square % Chessboard::Size;
    }

    int Chessboard::getSquare(int file, int rank) const
    {
        return rank * Chessboard::Size + file;
    }

    void Chessboard::movePiece(int fromSquare, int toSquare)
    {
        // Check if the squares are valid
        if (!isValidSquare(fromSquare) || !isValidSquare(toSquare))
            return;

        // Check if there is a piece at 'fromSquare'
        if (getPiece(fromSquare) == EMPTY)
            return;

        // Move the piece from 'fromSquare' to 'toSquare'
        Piece piece = getPiece(fromSquare);
        Color color = getColor(fromSquare);

        setPiece(toSquare, piece, color);
        setPiece(fromSquare, EMPTY, EMPTY_COLOR);
    }

    void Chessboard::undoMove( int fromSquare, int toSquare, Piece capturedPiece, Color capturedPieceColor)
{
    movePiece(toSquare, fromSquare); // Move the piece back to its original position
    setPiece(toSquare, capturedPiece, capturedPieceColor); // Restore the captured piece
}


    bool Chessboard::isKingInCheck(Color kingColor) const
    {
        // Find the king's square
        int kingSquare = -1;
        for (int square = 0; square < Size * Size; ++square)
        {
            if (getPiece(square) == KING && getColor(square) == kingColor)
            {
                kingSquare = square;
                break;
            }
        }

        // Check if the king's square is under attack
        for (int square = 0; square < Size * Size; ++square)
        {
            Piece piece = getPiece(square);
            Color color = getColor(square);

            // Skip empty squares or pieces of the same color as the king
            if (piece == EMPTY || color == kingColor)
                continue;

            // Check if the piece can attack the king's square
            if (isValidMove(square, kingSquare))
            {
                // The king's square is under attack
                return true;
            }
        }

        // The king's square is not under attack
        return false;
    }

    void Chessboard::prettyPrint() const
    {
        char piece[Size * Size];
        int color[Size * Size];

        for (int square = 0; square < Size * Size; ++square)
        {
            Piece p = getPiece(square);
            switch (p)
            {
            case ROOK:
                piece[square] = 'r';
                break;
            case KNIGHT:
                piece[square] = 'n';
                break;
            case BISHOP:
                piece[square] = 'b';
                break;
            case QUEEN:
                piece[square] = 'q';
                break;
            case KING:
                piece[square] = 'k';
                break;
            case PAWN:
                piece[square] = 'p';
                break;
            default:
                piece[square] = ' ';
            }
            color[square] = getColor(square);
        }

        std::cout << "int piece[64] = {" << std::endl;
        for (int rank = Size - 1; rank >= 0; --rank)
        {
            for (int file = 0; file < Size; ++file)
            {
                int square = rank * Size + file;
                std::cout << "    '" << piece[square] << "',";
            }
            std::cout << std::endl;
        }
        std::cout << "};" << std::endl;

        std::cout << std::endl;

        std::cout << "int color[64] = {" << std::endl;
        for (int rank = Size - 1; rank >= 0; --rank)
        {
            for (int file = 0; file < Size; ++file)
            {
                int square = rank * Size + file;
                std::cout << "    " << color[square] << ",";
            }
            std::cout << std::endl;
        }
        std::cout << "};" << std::endl;
    }

//private:
    int board_[Chessboard::Size * Chessboard::Size];
    int color_[Chessboard::Size * Chessboard::Size];

    Piece Chessboard::getPieceFromChar(char c) const
    {
        switch (tolower(c))
        {
        case 'r':
            return ROOK;
        case 'n':
            return KNIGHT;
        case 'b':
            return BISHOP;
        case 'q':
            return QUEEN;
        case 'k':
            return KING;
        case 'p':
            return PAWN;
        default:
            return EMPTY;
        }
    }
//};

/*
#######################################################################################################################################################
                                                            PERFT
#######################################################################################################################################################
*/
/*

unsigned long long perft(Chessboard &board, int depth)
{
    if (depth == 0)
    {
        return 1;
    }

    unsigned long long leafNodes = 0;

    for (int fromSquare = 0; fromSquare < Chessboard::Size * Chessboard::Size; ++fromSquare)
    {
        Piece piece = board.getPiece(fromSquare);

        if (board.getColor(fromSquare) != WHITE || piece == EMPTY)
        {
            continue;
        }

        for (int toSquare = 0; toSquare < Chessboard::Size * Chessboard::Size; ++toSquare)
        {
            if (board.isValidSquare(toSquare) && board.isValidMove(fromSquare, toSquare) && move.isMoveLegal(board,fromSquare, toSquare))
            {
                Piece capturedPiece = board.getPiece(toSquare);
                Color capturedPieceColor = board.getColor(toSquare);

                board.movePiece(fromSquare, toSquare);

                if (!board.isKingInCheck(WHITE))
                {
                    leafNodes += perft(board, depth - 1);
                }
                board.setPiece(fromSquare, piece, WHITE);
                board.setPiece(toSquare, capturedPiece, capturedPieceColor);
            }
        }
    }

    return leafNodes;
}




int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <perft_string>" << std::endl;
        return 1;
    }

    std::istringstream perftStringStream(argv[1]);

    std::string fen;
    int depth;

    perftStringStream >> fen >> depth;

    Chessboard board;
    board.loadFEN(fen);

    //unsigned long long result = perft(board, depth);
    //std::cout << result << std::endl;

    return 0;
}




class MoveGenerator
{
public:
    static void generateMoves(const Chessboard &board, int square, std::vector<int> &moves)
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

private:
    static void generatePawnMoves(const Chessboard &board, int square, Color color, std::vector<int> &moves)
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
    }

    static void generateRookMoves(const Chessboard &board, int square, std::vector<int> &moves)
    {
        int rank = board.getRank(square);
        int file = board.getFile(square);

        // Generate moves along the rank
        for (int f = 0; f < Chessboard::Size; ++f)
        {
            if (f != file)
            {
                moves.push_back(board.getSquare(f, rank));
            }
        }

        // Generate moves along the file
        for (int r = 0; r < Chessboard::Size; ++r)
        {
            if (r != rank)
            {
                moves.push_back(board.getSquare(file, r));
            }
        }
    }

    static void generateKnightMoves(const Chessboard &board, int square, std::vector<int> &moves)
    {
        int rank = board.getRank(square);
        int file = board.getFile(square);

        // Generate all possible knight moves
        int rankOffsets[] = {2, 2, -2, -2, 1, 1, -1, -1};
        int fileOffsets[] = {1, -1, 1, -1, 2, -2, 2, -2};

        for (int i = 0; i < 8; ++i)
        {
            int targetRank = rank + rankOffsets[i];
            int targetFile = file + fileOffsets[i];
            int targetSquare = board.getSquare(targetFile, targetRank);

                       if (board.isValidSquare(targetSquare))
            {
                moves.push_back(targetSquare);
            }
        }
    }

    static void generateBishopMoves(const Chessboard &board, int square, std::vector<int> &moves)
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

            if (board.isValidSquare(targetSquare))
            {
                moves.push_back(targetSquare);
            }

            // Generate moves along the negative diagonal
            targetRank = rank - offset;
            targetFile = file - offset;
            targetSquare = board.getSquare(targetFile, targetRank);

            if (board.isValidSquare(targetSquare))
            {
                moves.push_back(targetSquare);
            }
        }
    }

    static void generateQueenMoves(const Chessboard &board, int square, std::vector<int> &moves)
    {
        // Generate moves as a combination of rook and bishop moves
        generateRookMoves(board, square, moves);
        generateBishopMoves(board, square, moves);
    }

    static void generateKingMoves(const Chessboard &board, int square, std::vector<int> &moves)
    {
        int rank = board.getRank(square);
        int file = board.getFile(square);

        // Generate all possible king moves
        int rankOffsets[] = {1, 1, 1, 0, 0, -1, -1, -1};
        int fileOffsets[] = {1, 0, -1, 1, -1, 1, 0, -1};

        for (int i = 0; i < 8; ++i)
        {
            int targetRank = rank + rankOffsets[i];
            int targetFile = file + fileOffsets[i];
            int targetSquare = board.getSquare(targetFile, targetRank);

            if (board.isValidSquare(targetSquare))
            {
                moves.push_back(targetSquare);
            }
        }
    }
};



int main()
{
    Chessboard board;
    // Load the initial position or any other position using the FEN notation
    board.loadFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R");

    // Generate and print the moves for each square on the board
    for (int square = 0; square < Chessboard::Size * Chessboard::Size; ++square)
    {
        std::vector<int> moves;
        Move::generateMoves(board, square, moves);

        std::cout << "Moves for square " << square << ": ";
        for (std::vector<int>::iterator it = moves.begin(); it != moves.end(); ++it)
        {
            int move = *it;
            std::cout << move << " ";
        }
        std::cout << std::endl;
    }

    unsigned long long result = perft(board, 1);

    std::cout << result << std::endl;

    return 0;
}

*/