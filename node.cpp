#include "node.h"

Node::Node()  
{
     this->g_State = std::unique_ptr<Board>(new Board(10,10));
}

Node::~Node()
{
 
}