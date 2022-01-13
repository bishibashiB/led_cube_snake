
#include <array>

#include "config.h"
#include "snake_types.hpp"

/*
        ---------
        |   3   |
        |2  B  4|
        |   1  x|
-------------------------
|   4  x|x  1   |   2   |
|3  C  1|4  A  2|1  E  3|
|   2   |   3   |x  4   |
-------------------------
        |x  1   |
        |4  D  2|
        |   3   |
        ---------
x = origin ([0,0]-coordinate) of each panel
*/

// fwd declarations (extern to be able to use incomplete-const )
extern const PanelCfg panelA;
extern const PanelCfg panelB;
extern const PanelCfg panelC;
extern const PanelCfg panelD;
extern const PanelCfg panelE;

const PanelCfg panelA{
    {{&panelB, PanelSides::Side1},
     {&panelE, PanelSides::Side1},
     {&panelD, PanelSides::Side1},
     {&panelC, PanelSides::Side1}},
    {{0, 0}, {Matrix_X - 1, Matrix_Y - 1}}};

const PanelCfg panelB{
    {{&panelA, PanelSides::Side1},
     {&panelC, PanelSides::Side4},
     {&panelD, PanelSides::Side3},
     {&panelE, PanelSides::Side2}},
    {{Matrix_X, 0}, {Matrix_X * 2 - 1, Matrix_Y - 1}}};

const PanelCfg panelC{
    {{&panelA, PanelSides::Side4},
     {&panelD, PanelSides::Side4},
     {&panelE, PanelSides::Side3},
     {&panelB, PanelSides::Side2}},
    {{Matrix_X * 2, 0}, {Matrix_X * 3 - 1, Matrix_Y - 1}}};

const PanelCfg panelD{
    {{&panelA, PanelSides::Side3},
     {&panelE, PanelSides::Side4},
     {&panelB, PanelSides::Side3},
     {&panelC, PanelSides::Side2}},
    {{Matrix_X * 3, 0}, {Matrix_X * 4 - 1, Matrix_Y - 1}}};

const PanelCfg panelE{
    {{&panelA, PanelSides::Side2},
     {&panelB, PanelSides::Side4},
     {&panelC, PanelSides::Side3},
     {&panelD, PanelSides::Side2}},
    {{Matrix_X * 4, 0}, {Matrix_X * 5 - 1, Matrix_Y - 1}}};

// this array will be used also to resolve the pixel address resolution from 'total' to 'panel' level
// it's needed to align 2d matrix layout to 3d cube
const std::array<PanelCfg, TileNum_X *TileNum_Y> PanelArray = {panelA,
                                                               panelB,
                                                               panelC,
                                                               panelD,
                                                               panelE};

