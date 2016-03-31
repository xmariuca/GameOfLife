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
//        GameOfLife gof(5, 5);
        gof.seedRandom();
//        gof.seedBlinker();
        outStream << gof.getWidth() << " " << gof.getHeight() << "\n";
        gof.writeToFile(outStream);
        while (gof.getFrame() < 50) {
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
