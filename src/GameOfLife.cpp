//
// Created by Maria Ruxandra Robu on 24/03/2016.
//
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "GameOfLife.h"

namespace GameOfLifeNS {
    GameOfLife::GameOfLife(int sizex, int sizey) :
            m_sizex(sizex),
            m_sizey(sizey),
            m_grid(sizex, std::vector<STATE>(sizey, 0)),
            m_gridP(&m_grid),
            m_frame(0) { }

    int GameOfLife::getFrame() {
        return m_frame;
    }

    const std::vector<std::vector<STATE> > &GameOfLife::getGrid() const {
        return *m_gridP;
    }

    void GameOfLife::writeToFile(std::ofstream &outStream) {
        for (int ix = 0; ix < m_sizex; ix++) {
            for (int iy = 0; iy < m_sizey; iy++) {
                outStream << m_grid[ix][iy] << "\t";
            }
            outStream << std::endl;
        }
        outStream << std::endl;

    }

    void GameOfLife::updateGrid() {
        std::vector<std::vector<STATE>> tempGrid(m_sizex, std::vector<STATE>(m_sizey));
#pragma omp parallel for collapse(2)
            for (int ix = 0; ix < m_sizex; ix++) {
                for (int iy = 0; iy < m_sizey; iy++) {
                    tempGrid[ix][iy] = evaluateCell(ix, iy);
                }
            }
        ////            if (m_frame == 1) {
//#ifdef _OPENMP
//#pragma omp single
//                {
//                int numThreads = omp_get_num_threads();
//                std::cout << "Number of threads:" << numThreads << std::endl;
//                }
//#endif
//            }
//#pragma omp for collapse(2)
        //collapse(2)
        // omp implicit barrier that waits for all threads to finish their jobs
        // swap grids
        std::vector<std::vector<STATE>> aux(tempGrid);
        tempGrid = m_grid;
        m_grid = aux;

        // update the frame number
        m_frame++;
    }

    void GameOfLife::seedBlinker() {
        for (int ix = 0; ix < m_sizex; ix++) {
            for (int iy = 0; iy < m_sizey; iy++) {
                if (iy >= 1 && iy <= 3) m_grid[2][iy] = ALIVE;
                else m_grid[ix][iy] = DEAD;
            }
        }
        // update the frame number
        m_frame++;
    }

    STATE GameOfLife::evaluateCell(int x, int y) {
        int aliveN = getAliveNeighbours(x, y);
        if (m_grid[x][y] == ALIVE) {
            if (aliveN < 2)
                return DEAD; // under-population
            if (aliveN > 3)
                return DEAD; // over-population
        }
        else// if (m_grid[x][y] == DEAD)
        {
            if (aliveN == 3)
                return ALIVE;
        }
        return m_grid[x][y]; // nothing changes
    }

    int GameOfLife::getAliveNeighbours(int x, int y) {
        int total = 0;
        // TODO: omp reduction?
        for (int ix = x - 1; ix <= x + 1; ix++) {
            for (int iy = y - 1; iy <= y + 1; iy++) {
                // only evaluate the valid neighbours
                if (ix >= 0 && iy >= 0 && ix < m_sizex && iy < m_sizey) {
                    if (ix != x || iy != y) {
                        if (m_grid[ix][iy] == ALIVE) {
                            total++;
                        }
                    }
                }
            }
        }
        return total;
    }

    void GameOfLife::seedRandom() {
//        int numThreads = 0;
//#pragma omp parallel shared(m_grid), shared(numThreads)
//        {
//#ifdef _OPENMP
//            #pragma omp single
//            {
//            numThreads = omp_get_num_threads();
//            std::cout << "Number of threads:" << numThreads << std::endl;
//            }
//#endif
//#pragma omp for collapse(2)
        for (int ix = 0; ix < m_sizex; ix++) {
            for (int iy = 0; iy < m_sizey; iy++) {
                m_grid[ix][iy] = std::rand() % 2;
            }

        }
//        }
        m_frame++;
    }


}// namespace GameOfLifeNS

