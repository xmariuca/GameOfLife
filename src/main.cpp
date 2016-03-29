#include <iostream>
#include "defs.h"
#include "GameOfLife.h"
#include <fstream>


using namespace GameOfLifeNS;

int main() {
    std::cout << "***Start!\n";
    std::ofstream outStream("output.txt");
    if (outStream.is_open()) {
        GameOfLife gof(55, 55);
        gof.seedRandom();
        outStream << gof.getWidth() << " " << gof.getHeight() << "\n";
        while (gof.getFrame() < 30) {
            gof.updateGrid();
            gof.writeToFile(outStream);
        }
    }
    else {
        std::cout << "Couldn't open the output file.\n";
    }
    outStream.close();

    std::cout << "***Magic!\n";
    return SUCCESS;
}
