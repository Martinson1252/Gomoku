#pragma once
#include <vector>
#include "board.h"
#include <memory>
class Node {
public:
   Node();
   ~Node();
   std::vector< Node* > nodes;
   std::unique_ptr<Board> g_State;
};

 
