#include <iostream>
#include <fstream>
#include "board/Board.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "wrong number of arguments";
        return -1;
    }
    std::ifstream inFile(argv[1]);

    if (!inFile) {
        std::cerr << "unable to open input file: "
                  << argv[1] << " --bailing out! \n";
        return -1;
    }

    Board board = Board();
    inFile >> board;
    board.print();

    return 0;
}