#include <iostream>
#include "defs.h"
#include "GameOfLife.h"
#include <fstream>
#include <ctime>

#ifdef _OPENMP
#include <omp.h>
#endif


using namespace GameOfLifeNS;

int main() {
    double timeO;
    clock_t timeC;
    double finalTime;
#ifdef _OPENMP
    timeO = omp_get_wtime();
#else
    timeC = clock();
#endif
    std::cout << "***Start!\n";
    std::ofstream outStream("output.txt");
    if (outStream.is_open()) {
        GameOfLife gof(15, 15);
//        GameOfLife gof(5, 5);
        gof.seedRandom();
//        gof.seedBlinker();
        outStream << gof.getWidth() << " " << gof.getHeight() << "\n";
        gof.writeToFile(outStream);
        while (gof.getFrame() < 20) {
            gof.updateGrid();
            gof.writeToFile(outStream);
        }
    }
    else {
        std::cout << "Couldn't open the output file.\n";
    }
    outStream.close();

#ifdef _OPENMP
    finalTime = omp_get_wtime() - timeO;
#else
    finalTime = double(clock() - timeC)
                / CLOCKS_PER_SEC;
#endif
    printf("time %f sec\n", finalTime);

    std::cout << "***Magic!\n";
    return SUCCESS;
}
