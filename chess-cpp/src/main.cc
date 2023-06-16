/*

int main()
{
    std::cout<<"Hello World";

    return 0;
}
*/
#include <iostream>
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

class Chessboard {
public:
    static const int Size = 8;

    Chessboard() {
        board_.resize(Size, std::vector<Piece>(Size, Piece::None));
        color_.resize(Size, std::vector<Color>(Size, Color::None));
    }

    void setPiece(int row, int col, Piece piece, Color color) {
        board_[row][col] = piece;
        color_[row][col] = color;
    }

void print() const {
    for (int row = 0; row < Size; ++row) {
        int emptyCount = 0; // Count of consecutive empty squares
        for (int col = 0; col < Size; ++col) {
            Piece piece = board_[row][col];
            Color color = color_[row][col];
            char symbol = pieceToSymbol(piece);

            if (symbol != '.') {
                if (emptyCount > 0) {
                    std::cout << emptyCount;
                    emptyCount = 0;
                }

                if (color == Color::White) {
                    std::cout << symbol;
                } else if (color == Color::Black) {
                    std::cout << (char)(symbol + 32); // Convert to lowercase for black pieces
                }
            } else {
                emptyCount++;
            }

            if (col == Size - 1 && emptyCount > 0) {
                std::cout << emptyCount;
            }

            std::cout << " ";
        }
        std::cout << std::endl;
    }
}


private:
    std::vector<std::vector<Piece>> board_;
    std::vector<std::vector<Color>> color_;

    char pieceToSymbol(Piece piece) const {
        if (piece == Piece::Pawn) {
            return 'P';
        } else if (piece == Piece::Rook) {
            return 'R';
        } else if (piece == Piece::Knight) {
            return 'N';
        } else if (piece == Piece::Bishop) {
            return 'B';
        } else if (piece == Piece::Queen) {
            return 'Q';
        } else if (piece == Piece::King) {
            return 'K';
        } else {
            return '.';
        }
    }
};

int main() {
    Chessboard board;

    // Set up the starting position
    board.setPiece(0, 0, Piece::Rook, Color::White);
    board.setPiece(0, 1, Piece::Knight, Color::White);
    board.setPiece(0, 2, Piece::Bishop, Color::White);
    board.setPiece(0, 3, Piece::Queen, Color::White);
    board.setPiece(0, 4, Piece::King, Color::White);
    board.setPiece(0, 5, Piece::Bishop, Color::White);
    board.setPiece(0, 6, Piece::Knight, Color::White);
    board.setPiece(0, 7, Piece::Rook, Color::White);

    for (int col = 0; col < Chessboard::Size; ++col) {
        board.setPiece(1, col, Piece::Pawn, Color::White);
    }

    // Print the chessboard
    board.print();

    return 0;
}
