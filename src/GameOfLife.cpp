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
            m_grid(sizex, std::vector<STATE>(sizey)),
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
                outStream << (*m_gridP)[ix][iy] << "\t";
            }
            outStream << std::endl;
        }
        outStream << std::endl;

    }

    void GameOfLife::updateGrid() {
        for (int ix = 0; ix < m_sizex; ix++) {
            for (int iy = 0; iy < m_sizey; iy++) {
                m_grid[ix][iy] = evaluateCell(ix, iy);
            }
        }
        m_frame++;
    }

    void GameOfLife::seedBlinker() {
        for (int iy = 1; iy < 4; iy++) {
//            (*m_gridP)[2][iy] = ALIVE;
            m_grid[2][iy] = ALIVE;

        }
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
        return ERROR;
    }

    int GameOfLife::getAliveNeighbours(int x, int y) {
        //TODO: handle boundaries
        int total = 0;
        for (int ix = x - 1; ix < x + 1; ix++) {
            for (int iy = y - 1; iy < y + 1; iy++) {
                // only evaluate the neighbours
                if (ix != x && iy != y) {
                    if (m_grid[ix][iy] == ALIVE) {
                        total++;
                    }
                }
            }
        }
        return total;
    }

    void GameOfLife::seedRandom() {
        for (int ix = 0; ix < m_sizex; ix ++) {
            for (int iy = 0; iy < m_sizey; iy ++) {
                m_grid[ix][iy] = std::rand() % 2;
            }
        }
    }


}// namespace GameOfLifeNS

