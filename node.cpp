#include "node.h"
#include <vector>

Node::Node(Node *parent)
{
	Node::parent = parent;
}