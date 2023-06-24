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

void Chessboard::FEN(const std::string &fen)
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
{/*
    int rankDiff = std::abs(getRank(toSquare) - getRank(fromSquare)); // bon rang
    if (rankDiff != 1)
        return false;

    int fileDiff = std::abs(getFile(toSquare) - getFile(fromSquare)); // bonne column
    if (fileDiff > 1 )
        return false;
*/
    //std::cout << "fromsquare" << fromSquare << std::endl;
    //std::cout << "tosquare" << (toSquare)<< std::endl;

    int forwardDir = (color == WHITE) ? 1 : -1; // bonne direction
   
    //if (std::abs(getFile(toSquare)-getFile(fromSquare))==1)

    return (getRank(toSquare) - getRank(fromSquare) == forwardDir)&&(std::abs(getFile(toSquare)-getFile(fromSquare))==1);
   // if ((getRank(toSquare) - getRank(fromSquare) != forwardDir))//&& getPiece(toSquare)!=EMPTY)
     //   return false;

   // if ((std::abs(getFile(toSquare)-getFile(fromSquare)==1)) )//&& getPiece(toSquare)==EMPTY)
   //     return true;

    return false;
}

bool Chessboard::isValidRookMove(int fromSquare, int toSquare) const
{
    //std::cout<<"isvaliderook\n";
    if (getRank(fromSquare) != getRank(toSquare) && getFile(fromSquare) != getFile(toSquare))
        return false;
    
    //std::cout<<"isvalid22222\n";

    if (!isPathClear(fromSquare, toSquare))
        return false;
 //   std::cout<<"isvtrue\n";

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
        // std::cout<<getFile(currentSquare) + fileDir<<"   "<< getRank(currentSquare) + rankDir<< "\n";
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

    if (color == WHITE && getRank(piece) == 0 && getFile(piece) == 0)
    {
        castlingWQ = false;
    }
    if (color == WHITE && getRank(piece) == 0 && getFile(piece) == 7)
    {
        castlingWK = false;
    }
    if (color == BLACK && getRank(piece) == 7 && getFile(piece) == 0)
    {
        castlingBQ = false;
    }
    if (color == BLACK && getRank(piece) == 7 && getFile(piece) == 7)
    {
        castlingBK = false;
    }
    /////cas du en passant 
    int caseFin = toSquare;
    int caseDebut = fromSquare;
    int rankDiff = getRank(caseFin) - getRank(caseDebut);

    if (getPiece(caseFin) == EMPTY)
        {
            int startRank = (color == WHITE) ? 1 : 6;
            if (getRank(caseDebut) == startRank && std::abs(rankDiff) == 2)
            {
                int intermediateRank = startRank + (rankDiff / 2);
                int intermediateSquare = getSquare(getFile(caseDebut), intermediateRank);
                if (getPiece(intermediateSquare) == EMPTY)
                {
                    int leftNeighborSquare = caseFin - 1;
                    int rightNeighborSquare = caseFin + 1;

                    if (/*Chessboard::enPA =="-" &&*/ color == WHITE && ((getPiece(leftNeighborSquare) == PAWN && getColor(leftNeighborSquare) == BLACK) ||
                                           (getPiece(rightNeighborSquare) == PAWN && getColor(rightNeighborSquare) == BLACK)))
                    {
                        Chessboard::enPA = getSquareName(caseFin - 8);
                      //  std::cout << Chessboard::enPA << "nouveau enpa calcule BLANC\n";
                    }
                    else if (/*Chessboard::enPA =="-" &&*/ color == BLACK && ((getPiece(leftNeighborSquare) == PAWN && getColor(leftNeighborSquare) == WHITE) ||
                                                (getPiece(rightNeighborSquare) == PAWN && getColor(rightNeighborSquare) == WHITE)))
                    {
                        Chessboard::enPA = getSquareName(caseFin + 8);
                      //  std::cout << Chessboard::enPA << "nouveau enpa calcule  NOIR\n";
                    }
                }
            }
        }

    setPiece(toSquare, piece, color);
    setPiece(fromSquare, EMPTY, EMPTY_COLOR);
}

void Chessboard::undoMove(int fromSquare, int toSquare, Piece capturedPiece, Color capturedPieceColor)
{
    movePiece(toSquare, fromSquare);
    setPiece(toSquare, capturedPiece, capturedPieceColor);
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
bool Chessboard::isRookInCheck(int rookSquare, Color kingColor) const
{
if (getPiece(rookSquare) == ROOK && getColor(rookSquare) == kingColor){
    
    for (int square = 0; square < Size * Size; ++square)
    {
        Piece piece = getPiece(square);
        Color color = getColor(square);

        if (piece == EMPTY || color == kingColor)
            continue;
        if (isValidMove(square, rookSquare))
        {
            return true;
        }
    }}
    return false;
}

std::string Chessboard::getSquareName(int square)
{
    int rank = square / Chessboard::Size;
    int file = square % Chessboard::Size;

    std::string name;
    name += ('a' + file);
    name += ('1' + rank);
    return name;
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

    std::istringepth);
    //std::cout << result << std::endl;

    return 0;
}


*/
