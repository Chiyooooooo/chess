#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class Piece {
    None,
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

enum class Color {
    None,
    White,
    Black
};

struct Square {
    Piece piece;
    Color color;
};

class Chessboard {
public:
    static const int Size = 8;

    Chessboard() {
        reset(); 
    }

    void reset() {
        std::string startingPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
        setBoardFromFEN(startingPosition);
    }

    void setBoardFromFEN(const std::string& fen) {
        clearBoard();

        std::stringstream ss(fen);
        std::string token;

        std::getline(ss, token, ' ');

        int rank = Size - 1;
        int file = 0;

        for (char c : token) {
            if (c == '/') {
                rank--;
                file = 0;
            } else if (isdigit(c)) {
                int emptySquares = c - '0';
                for (int i = 0; i < emptySquares; ++i) {
                    board_[rank][file++] = { Piece::None, Color::None };
                }
            } else {
                Piece piece = symbolToPiece(c);
                Color color = (isupper(c)) ? Color::White : Color::Black;
                board_[rank][file++] = { piece, color };
            }
        }

        // Parse the remaining parts of the FEN (active color, castling rights, en passant target, halfmove clock, fullmove number)
        std::getline(ss, token, ' '); // Read the active color field
        activeColor_ = (token == "w") ? Color::White : Color::Black;

        std::getline(ss, token, ' '); // Read the castling rights field
        parseCastlingRights(token);

        std::getline(ss, token, ' '); // Read the en passant target field
        parseEnPassantTarget(token);

        std::getline(ss, token, ' '); // Read the halfmove clock field
        halfmoveClock_ = std::stoi(token);

        std::getline(ss, token, ' '); // Read the fullmove number field
        fullmoveNumber_ = std::stoi(token);
    }

    std::string getFEN() const {
        std::stringstream fen;

        // Generate the piece placement part of the FEN
        for (int rank = Size - 1; rank >= 0; --rank) {
            int emptySquares = 0;

            for (int file = 0; file < Size; ++file) {
                const Square& square = board_[rank][file];

                if (square.piece == Piece::None) {
                    emptySquares++;
                } else {
                    if (emptySquares > 0) {
                        fen << emptySquares;
                        emptySquares = 0;
                    }

                    char symbol = pieceToSymbol(square.piece);
                    symbol = (square.color == Color::White) ? toupper(symbol) : tolower(symbol);
                    fen << symbol;
                }
            }

            if (emptySquares > 0) {
                fen << emptySquares;
            }

            if (rank > 0) {
                fen << '/';
            }
        }

        // Append the remaining parts of the FEN (active color, castling rights, en passant target, halfmove clock, fullmove number)
        fen << ' ' << ((activeColor_ == Color::White) ? 'w' : 'b') << ' ';
        fen << getCastlingRightsString() << ' ';
        fen << getEnPassantTargetString() << ' ';
        fen << halfmoveClock_ << ' ';
        fen << fullmoveNumber_;

        return fen.str();
    }

    void print() const {
        for (int rank = Size - 1; rank >= 0; --rank) {
            for (int file = 0; file < Size; ++file) {
                const Square& square = board_[rank][file];
                char symbol = pieceToSymbol(square.piece);
                symbol = (square.color == Color::White) ? toupper(symbol) : tolower(symbol);
                std::cout << symbol << ' ';
            }
            std::cout << std::endl;
        }
    }

private:
    std::array<std::array<Square, Size>, Size> board_;
    Color activeColor_;
    std::vector<bool> castlingRights_;
    int enPassantTarget_;
    int halfmoveClock_;
    int fullmoveNumber_;

    void clearBoard() {
        for (auto& rank : board_) {
            for (auto& square : rank) {
                square.piece = Piece::None;
                square.color = Color::None;
            }
        }
    }

    Piece symbolToPiece(char symbol) const {
        switch (toupper(symbol)) {
            case 'P':
                return Piece::Pawn;
            case 'R':
                return Piece::Rook;
            case 'N':
                return Piece::Knight;
            case 'B':
                return Piece::Bishop;
            case 'Q':
                return Piece::Queen;
            case 'K':
                return Piece::King;
            default:
                return Piece::None;
        }
    }

    char pieceToSymbol(Piece piece) const {
        switch (piece) {
            case Piece::Pawn:
                return 'p';
            case Piece::Rook:
                return 'r';
            case Piece::Knight:
                return 'n';
            case Piece::Bishop:
                return 'b';
            case Piece::Queen:
                return 'q';
            case Piece::King:
                return 'k';
            default:
                return '.';
        }
    }

    void parseCastlingRights(const std::string& rights) {
        castlingRights_ = std::vector<bool>(4, false); // Initialize all castling rights to false

        if (rights.find('K') != std::string::npos)
            castlingRights_[0] = true;

        if (rights.find('Q') != std::string::npos)
            castlingRights_[1] = true;

        if (rights.find('k') != std::string::npos)
            castlingRights_[2] = true;

        if (rights.find('q') != std::string::npos)
            castlingRights_[3] = true;
    }

    std::string getCastlingRightsString() const {
        std::string rights;

        if (castlingRights_[0])
            rights += 'K';

        if (castlingRights_[1])
            rights += 'Q';

        if (castlingRights_[2])
            rights += 'k';

        if (castlingRights_[3])
            rights += 'q';

        return (rights.empty()) ? "-" : rights;
    }

    void parseEnPassantTarget(const std::string& target) {
        if (target == "-") {
            enPassantTarget_ = -1; // No en passant target square
        } else {
            // Convert the en passant target square from algebraic notation to the corresponding index
            int file = target[0] - 'a';
            int rank = target[1] - '1';
            enPassantTarget_ = rank * Size + file;
        }
    }

    std::string getEnPassantTargetString() const {
        if (enPassantTarget_ == -1)
            return "-";

        // Convert the en passant target square from index to algebraic notation
        int file = enPassantTarget_ % Size;
        int rank = enPassantTarget_ / Size;
        char fileChar = 'a' + file;
        char rankChar = '1' + rank;
        std::string target;
        target += fileChar;
        target += rankChar;
        return target;
    }
};

int main() {
    Chessboard board;

    // Print the chessboard
    board.print();

    std::cout << "FEN: " << board.getFEN() << std::endl;

    return 0;
}
