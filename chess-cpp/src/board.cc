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
    if (!isValidSquare(fromSquare) || !isValidSquare(toSquare))
        return false;

    Piece piece = getPiece(fromSquare);
    Color color = getColor(fromSquare);

    switch (piece)
    {
    case 1:
        return isValidPawnMove(fromSquare, toSquare, color);
    case 2:
        return isValidRookMove(fromSquare, toSquare);
    case 3:
        return isValidKnightMove(fromSquare, toSquare);
    case 4:
        return isValidBishopMove(fromSquare, toSquare);
    case 5:
        return isValidQueenMove(fromSquare, toSquare);
    case 6:
        return isValidKingMove(fromSquare, toSquare);
    default:
        return false; 
    }
}

bool Chessboard::isValidPawnMove(int fromSquare, int toSquare, Color color) const
{
    int rankDiff = std::abs(getRank(toSquare) - getRank(fromSquare));//bon rang
    if (rankDiff != 1)
        return false;

    int fileDiff = std::abs(getFile(toSquare) - getFile(fromSquare));//bonne column
    if (fileDiff > 1)
        return false;

    int forwardDir = (color == WHITE) ? 1 : -1; //bonne direction
    if (getRank(toSquare) - getRank(fromSquare) != forwardDir)
        return false;

    // en passant, promotion, etc.

    return true;
}

bool Chessboard::isValidRookMove(int fromSquare, int toSquare) const
{
    if (getRank(fromSquare) != getRank(toSquare) && getFile(fromSquare) != getFile(toSquare))
        return false;

    if (!isPathClear(fromSquare, toSquare))
        return false;

    return true;
}

bool Chessboard::isValidKnightMove(int fromSquare, int toSquare) const
{
    int rankDiff = std::abs(getRank(toSquare) - getRank(fromSquare));
    int fileDiff = std::abs(getFile(toSquare) - getFile(fromSquare));
    if ((rankDiff != 2 || fileDiff != 1) && (rankDiff != 1 || fileDiff != 2))
        return false;

    return true;
}

bool Chessboard::isValidBishopMove(int fromSquare, int toSquare) const
{
    if (std::abs(getRank(toSquare) - getRank(fromSquare)) != std::abs(getFile(toSquare) - getFile(fromSquare)))
        return false;

    if (!isPathClear(fromSquare, toSquare))
        return false;

    return true;
}

bool Chessboard::isValidQueenMove(int fromSquare, int toSquare) const
{
    if (getRank(fromSquare) != getRank(toSquare) && getFile(fromSquare) != getFile(toSquare) &&
        std::abs(getRank(toSquare) - getRank(fromSquare)) != std::abs(getFile(toSquare) - getFile(fromSquare)))
        return false;

    if (!isPathClear(fromSquare, toSquare))
        return false;

    return true;
}

bool Chessboard::isValidKingMove(int fromSquare, int toSquare) const
{
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
    if (!isValidSquare(fromSquare) || !isValidSquare(toSquare))
        return;

    if (getPiece(fromSquare) == EMPTY)
        return;

    Piece piece = getPiece(fromSquare);
    Color color = getColor(fromSquare);

    setPiece(toSquare, piece, color);
    setPiece(fromSquare, EMPTY, EMPTY_COLOR);
}

void Chessboard::undoMove(int fromSquare, int toSquare, Piece capturedPiece, Color capturedPieceColor)
{
    movePiece(toSquare, fromSquare);                       // Move the piece back to its original position
    setPiece(toSquare, capturedPiece, capturedPieceColor); // Restore the captured piece
}

bool Chessboard::isKingInCheck(Color kingColor) const
{
    int kingSquare = -1;
    for (int square = 0; square < Size * Size; ++square)
    {
        if (getPiece(square) == KING && getColor(square) == kingColor)
        {
            kingSquare = square;
            break;
        }
    }

    for (int square = 0; square < Size * Size; ++square)
    {
        Piece piece = getPiece(square);
        Color color = getColor(square);

        if (piece == EMPTY || color == kingColor)
            continue;

        if (isValidMove(square, kingSquare))
        {
            return true;
        }
    }
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

/*
#######################################################################################################################################################
                                                            PERFT
#######################################################################################################################################################
*/
/*

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
