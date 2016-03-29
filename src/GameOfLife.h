//
// Created by Maria Ruxandra Robu on 24/03/2016.
//

#ifndef GAMEOFLIFE_GAMEOFLIFE_H
#define GAMEOFLIFE_GAMEOFLIFE_H

#include <vector>
#include <string>
#include "defs.h"

namespace GameOfLifeNS {
    class GameOfLife {
    public:
        GameOfLife(int sizex = 5,
                   int sizey = 5);

        const std::vector<std::vector<STATE> > &getGrid() const;

        int getFrame();

        void seedBlinker();

        void seedRandom();

        void writeToFile(std::ofstream &outStream);

        STATE evaluateCell(int x, int y);

        int getAliveNeighbours(int x, int y);

        void updateGrid();

        int getWidth() { return m_sizex; }

        int getHeight() { return m_sizey; }


    private:
        int m_sizex;
        int m_sizey;
        int m_frame;
        std::vector<std::vector<STATE> > m_grid;
        std::vector<std::vector<STATE> > *m_gridP;

    };

}// namespace GameOfLifeNS
#endif //GAMEOFLIFE_GAMEOFLIFE_H
