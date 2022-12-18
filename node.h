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
	int remaining_pegs;
	int moved_peg_index;
	float heuristic_point;

	Node(Node* parent);
	int count_remaining_pegs();
	std::string to_string();
	void set_heuristic_point();
};

