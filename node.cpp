#include "node.h"
#include <vector>
using namespace std;

class Node
{
	public:
		vector<vector<int>> state;
		Node *parent;
		Node *child;
		Node(Node *aparent, Node *achild)
		{
			parent = aparent;
			child = achild;
		}

};