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
//    double timeO;
    double timeIterO;
//    clock_t timeC;
    clock_t timeIterC;
    double finalTime, timeIter;
//#ifdef _OPENMP
//    timeO = omp_get_wtime();
//#else
//    timeC = clock();
//#endif
    std::cout << "***Start!\n";
    std::ofstream outStream("output.txt");
    if (outStream.is_open()) {
        GameOfLife gof(3000, 3000);
//        GameOfLife gof(15, 15);
        gof.seedRandom();
//        gof.seedBlinker();
        outStream << gof.getWidth() << " " << gof.getHeight() << "\n";
        gof.writeToFile(outStream);
        while (gof.getFrame() < 2) {
            if (gof.getFrame() == 1) {
#ifdef _OPENMP
                timeIterO = omp_get_wtime();
#else
                timeIterC = clock();
#endif
                gof.updateGrid();

#ifdef _OPENMP
                timeIterO = omp_get_wtime() - timeIterO;
                printf("Time iter OMP = %f sec\n", timeIterO);
#else
                timeIter = double(clock() - timeIterC) / CLOCKS_PER_SEC;
                printf("Time iter SERIAL = %f sec\n", timeIter);
#endif
            }
            else {
                gof.updateGrid();
            }

            gof.writeToFile(outStream);
        }
    }
    else {
        std::cout << "Couldn't open the output file.\n";
    }
    outStream.close();

//#ifdef _OPENMP
//    finalTime = omp_get_wtime() - timeO;
//#else
//    finalTime = double(clock() - timeC)
//                / CLOCKS_PER_SEC;
//#endif
//    printf("Final time %f sec\n", finalTime);

    std::cout << "***Magic!\n";
    return SUCCESS;
}
