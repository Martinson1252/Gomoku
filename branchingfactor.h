#pragma once
#include <iostream>

class BranchingFactor {
public:            
    BranchingFactor();
    ~BranchingFactor(); 
    unsigned int moves = 0;
    unsigned int sumOfPossibleMoves = 0;
    unsigned int avgPossibleMoves = 0;
    unsigned int totalMoves = 0;
    unsigned int totalAvgPossibleMoves = 0;
    unsigned int gamesToPlay = 0;
};