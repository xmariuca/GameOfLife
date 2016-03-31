//
// Created by Maria Ruxandra Robu on 24/03/2016.
//
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "GameOfLife.h"

using namespace GameOfLifeNS;

TEST_CASE("GameOfLife can be constructed", "[GoL-init]") {

    SECTION("Object with default values") {
        GameOfLife gof;
        REQUIRE (gof.getWidth() == 5);
        REQUIRE (gof.getHeight() == 5);
        REQUIRE (gof.getGrid().size() == gof.getWidth());
        REQUIRE (gof.getGrid()[0].size() == gof.getHeight());
    }
    SECTION("Object with modified values") {
        GameOfLife gof(100, 50);
        REQUIRE (gof.getWidth() == 100);
        REQUIRE (gof.getHeight() == 50);
        REQUIRE (gof.getGrid().size() == gof.getWidth());
        REQUIRE (gof.getGrid()[0].size() == gof.getHeight());
    }
}

TEST_CASE("Test GameOfLife methods", "[GoL-methods]") {
    GameOfLife gof(5, 5);
    // seed with blinker pattern - period of 2 frames
    gof.seedBlinker();

    SECTION("Test seedBlinker") {
        REQUIRE( gof.getGrid()[2][2] == ALIVE);
        REQUIRE( gof.getGrid()[1][2] == DEAD);
        REQUIRE( gof.getGrid()[3][2] == DEAD);
        REQUIRE( gof.getGrid()[2][1] == ALIVE);
        REQUIRE( gof.getGrid()[2][3] == ALIVE);
    }

    SECTION("Test getAliveNeighbours") {
        REQUIRE (gof.getAliveNeighbours(2, 2) == 2);
        REQUIRE (gof.getAliveNeighbours(0, 0) == 0);
        REQUIRE (gof.getAliveNeighbours(4, 4) == 0);
        REQUIRE (gof.getAliveNeighbours(2, 1) == 1);
        REQUIRE (gof.getAliveNeighbours(2, 3) == 1);
    }

    SECTION("Test evaluateCell") {
//        INFO(gof.evaluateCell(2,2));
        REQUIRE( gof.evaluateCell(2,2) == ALIVE);
        REQUIRE( gof.evaluateCell(2,1) == DEAD);
        REQUIRE( gof.evaluateCell(2,3) == DEAD);
        REQUIRE( gof.evaluateCell(4,4) == DEAD);
    }

    SECTION("Test upgradeGrid") {
        REQUIRE( gof.getFrame() == 0);
        gof.updateGrid();
        REQUIRE( gof.getGrid()[2][2] == ALIVE);
        REQUIRE( gof.getGrid()[1][2] == ALIVE);
        REQUIRE( gof.getGrid()[3][2] == ALIVE);
        REQUIRE( gof.getGrid()[2][1] == DEAD);
        REQUIRE( gof.getGrid()[2][3] == DEAD);
        REQUIRE( gof.getFrame() == 1);
    }

}