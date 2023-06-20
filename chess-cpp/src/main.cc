#include "move.hh"
#include "perft.hh"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

//create a new main that parse a FEN notation and store the color of the player to move,  the position of the pieces on the board, the castling ability for each player and the en passant target square
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "failed args" << std::endl;
        return 1;
    }
    if (!strcmp(argv[1],"-h"))
    {
        std::cout << argv[1];
        std::cout << "Usage : ./chessengine --perft arg" << std::endl;
        return 0;
    }
    if (!!strcmp(argv[1],"--perft"))
    {
        std::cout << "FUCK YOU" << std::endl;
        return 0;
    }
    std::string fen ;//argv[2];
    std::string playerToMove ;//argv[3];
    std::string castling ;//argv[4];


    std::ifstream file(argv[1]);
    std::string line;
    std::cout << line<< "finito" ;
    if (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> tokens;

        std::string token;
        while (std::getline(iss, token, ' '))
        {
            tokens.push_back(token);
        }

        if (tokens.size() >= 4)
        {
            fen = tokens[0];
            playerToMove = tokens[1];
            castling = tokens[2];
            //std::string token4 = tokens[3];

            // Print the variables
            std::cout << fen << std::endl;
            std::cout << "Token 2: " << playerToMove << std::endl;
            std::cout << "Token 3: " << castling << std::endl;
        }
        else
        {
            std::cerr << "Not enough tokens in the line." << std::endl;
        }
    }

    // exemple :
    //rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 1

    Chessboard board;

    //Color PlayerToMove;

    if (playerToMove == "w")
    {
        board.PlayerToMove = WHITE;
    }
    else if (playerToMove == "b")
    {
        board.PlayerToMove = BLACK;
    }
    else
    {
        std::cerr << "failed color" << std::endl;
        return 1;
    }

    if (castling == "-")
    {
        board.castlingWK = false;
        board.castlingWQ = false;
        board.castlingBK = false;
        board.castlingBQ = false;
    }
    else
    {
        for (unsigned long i = 0; i < castling.size(); ++i)
        {
            if (castling[i] == 'K')
            {
                board.castlingWK = true;
            }
            else if (castling[i] == 'Q')
            {
                board.castlingWQ = true;
            }
            else if (castling[i] == 'k')
            {
                board.castlingBK = true;
            }
            else if (castling[i] == 'q')
            {
                board.castlingBQ = true;
            }
            else
            {
                std::cerr << "failed castling" << std::endl;
                return 1;
            }
        }
    }
/// faire avec un fichier pour avoir le mm test qque dans le sujet 
// faire bien le perft et que ca soit lui qui renvoit le bon bail 
// pas oublier de gere le roque dans le perft
///reste le en passant a gerer, puis la promotion

    board.loadFEN(fen);
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

/*
int main()
{
    std::ifstream file("filename.txt");
    if (!file)
    {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::string line;
    if (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> tokens;

        // Split the line by space (' ')
        std::string token;
        while (std::getline(iss, token, ' '))
        {
            tokens.push_back(token);
        }

        if (tokens.size() >= 4)
        {
            std::string token1 = tokens[0];
            std::string token2 = tokens[1];
            std::string token3 = tokens[2];
            std::string token4 = tokens[3];

            // Print the variables
            std::cout << "Token 1: " << token1 << std::endl;
            std::cout << "Token 2: " << token2 << std::endl;
            std::cout << "Token 3: " << token3 << std::endl;
            std::cout << "Token 4: " << token4 << std::endl;
        }
        else
        {
            std::cerr << "Not enough tokens in the line." << std::endl;
        }
    }
    else
    {
        std::cerr << "File is empty." << std::endl;
    }

    return 0;
}
*/

/*
int main()
{
    Chessboard board;
    
    //board.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"); // 20
    //board.loadFEN("8/8/8/8/8/8/PPPPPPPP/RNBQKBNR"); // 20
    //board.loadFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R");//44
    //board.loadFEN("8/8/8/8/8/8/8/4K2R");//14 c bon  normalement
    board.loadFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R");//48 


    //board.loadFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8");//14
    
    //board.loadFEN("8/8/8/8/8/8/8/7R");//14
    //board.loadFEN("8/8/8/8/8/8/8/4K3");//14

    board.prettyPrint();

    //int sol = 0;
    //board.setPiece(17, PAWN, BLACK);
    //std::cout << Move::isPawnMoveLegal(board, 8, 17, WHITE) << std::endl;
    
    //board.setPiece(24, BISHOP, WHITE);
    //board.setPiece(8, BISHOP, WHITE);
    //board.prettyPrint();


    //int square  = 40;
    //std::vector<int> legalMoves = Move::getLegalMoves(board, square);
    //std::cout << legalMoves.size() << std::endl;

    std::vector<int> all = Move::generateAllLegalMoves(board);
    std::cout << all.size() << std::endl;
    //print all elements of all
    for (unsigned long i = 0; i < all.size(); ++i) {
        std::cout << Move::getSquareName(all[i]) << " ";
    }

    int result = perft(board, 1);
    std::cout << result << std::endl;

    return 0;
}
*/

/*
int main() {

    Chessboard board;
    board.loadFEN("8/8/8/8/8/8/8/8");
    //board.prettyPrint();
    
    board.setPiece(35, QUEEN, WHITE);
    board.setPiece(8, PAWN, WHITE);
    board.setPiece(17, PAWN, BLACK);

    board.setPiece(44, BISHOP, WHITE);
    board.setPiece(53, BISHOP, WHITE);
    board.setPiece(62, BISHOP, WHITE);
    board.setPiece(28, BISHOP, WHITE);
    board.setPiece(21, BISHOP, WHITE);
    board.setPiece(14, BISHOP, WHITE);
    board.setPiece(7, BISHOP, WHITE);
    board.setPiece(26, BISHOP, WHITE);
    board.setPiece(17, BISHOP, WHITE);
    board.setPiece(42, BISHOP, WHITE);
    board.setPiece(49, BISHOP, WHITE);
    board.setPiece(56, BISHOP, WHITE);

    Piece p= board.getPiece(42);
    board.setPiece(10,  PAWN, WHITE);
    Piece a = board.getPiece(10);
    board.prettyPrint();

    board.setPiece(0,p,BLACK);
    board.movePiece(42, 18);
    board.prettyPrint();
    board.undoMove(42, 18, EMPTY, EMPTY_COLOR);

    board.prettyPrint();

    int square = 35;
    std::vector<int> legalMoves = Move::getLegalMoves(board, square);
    std::cout << "Legal moves for square " << Move::getSquareName(square) << ":" << std::endl;
    std::cout << legalMoves.size();
    std::cout << std::endl;
    for (unsigned long i = 0; i < legalMoves.size(); ++i) {
        std::cout << Move::getSquareName(legalMoves[i]) << " ";
    }

    std::cout << std::endl;
    return 0;
}
*/


/*
int main()
{
    Chessboard board;

    board.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");//20
    //board.loadFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R");//44
    //board.loadFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8");//14


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

int main()
{
    std::cout<<"Hello World";
    return 0;
}
*/
