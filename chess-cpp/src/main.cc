#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "move.hh"
#include "perft.hh"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // std::cerr << "failed args" << std::endl;
        return 1;
    }
    if (!strcmp(argv[1], "-h"))
    {
        std::cout << argv[1];
        // std::cout << "Usage : ./chessengine --perft arg" << std::endl;
        return 0;
    }
    if (!!strcmp(argv[1], "--perft"))
    {
        // std::cout << "FUCK YOU" << std::endl;
        return 0;
    }
    std::string fen;         // argv[2];
    std::string playercolor; // argv[3];
    std::string castling;    // argv[4];
    std::string depth;
    std::string enPassant;

    std::ifstream file(argv[2]);
    // std::cout<<argv[1]<<"fin";

    std::string line;

    std::getline(file, line);
    std::vector<std::string> tokens;
    std::stringstream ss(line);

    std::string token;
    int i = 0;
    while (std::getline(ss, token, ' '))
    {
        tokens.push_back(token);
        i++;
    }

    fen = tokens[0];
    playercolor = tokens[1];
    castling = tokens[2];
    enPassant = tokens[3];
    depth = tokens.back();
    Chessboard::prof = depth;

    Chessboard board;
    board.enPA = enPassant;

    if (playercolor == "w")
    {
        board.PlayerToMove = WHITE;
    }
    else if (playercolor == "b")
    {
        board.PlayerToMove = BLACK;
    }
    else
    {
        // std::cerr << "failed color" << std::endl;
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
                // std::cerr << "failed castling" << std::endl;
                return 1;
            }
        }
    }
    // DONE/ faire avec un fichier pour avoir le mm test qque dans le sujet
    // DONE/ faire bien le perft et que ca soit lui qui renvoit le bon bail
    // DONE/ avoir tt les legals move, les retester en speed et bien tt checker

    // pas oublier de gere le roque dans le perft

    /// reste le en passant a gerer, puis la promotion

    // perft fait uniquement pour la depth 1, pas oublier de gere le reste

    // ojd : fix le enpassant, fix le 44, fix la promotion
    /// 44 manque trois prom

    board.FEN(fen);
    //board.prettyPrint();

    //std::cout << "isvalidmove" << board.isValidMove( 31, 22) << std::endl;
    //std::cout << "isvalidmove" << board.isValidKingMove( 31, 22) << std::endl;

    int result = perft(board, stoi(depth), Chessboard::PlayerToMove);

    std::cout << std::endl
              << std::endl
              << result << std::endl;

    return 0;
}
