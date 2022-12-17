#pragma once

#include <vector>
#include <string>

class Node
{
public:
	std::vector<std::vector<int>> state;
	Node* parent;
	std::vector<Node*> children;
	int depth;
	int remainingPegs;

	Node(Node* parent);
	int CountRemainingPegs();
	std::string ToString();
};

