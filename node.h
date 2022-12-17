#pragma once

#include <vector>
using namespace std;

class Node
{
public:
	vector<vector<int>> state;
	Node* parent;
	vector<Node*> children;

	Node(Node* parent);
};

