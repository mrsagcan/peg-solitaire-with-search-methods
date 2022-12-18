#include "node.h"

Node::Node(Node *parent)
{
	Node::parent = parent;
	if (parent != NULL)
	{
		depth = parent->depth + 1;
	}
	else
		depth = 0;
	remaining_pegs = count_remaining_pegs();
}
int Node::count_remaining_pegs()
{
	int count = 0;
	for (int i = 0; i < state.size(); i++)
	{
		if (state.at(i).at(1) == 1)
		{
			count++;
		}
	}

	return count;
}

std::string Node::to_string()
{
	std::string temp_state;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			temp_state += std::to_string(state.at(i*7 + j).at(1)) + " ";
		}
		temp_state += '\n';
	}
	temp_state += "\nCurrent Depth: " + std::to_string(depth);
	return temp_state;
}

void Node::set_heuristic_point()
{
	if (moved_peg_index % 7 == 0 || moved_peg_index % 7 == 6)
	{
		heuristic_point = 0.8;
	}
	if (moved_peg_index % 7 == 1 || moved_peg_index % 7 == 5)
	{
		heuristic_point = 0.6;
	}
	if (moved_peg_index % 7 == 2 || moved_peg_index % 7 == 4)
	{
		heuristic_point = 0.4;
	}
	if (moved_peg_index % 7 == 3)
	{
		heuristic_point = 0.2;
	}
	if (remaining_pegs < 7)
	{
		heuristic_point = 1 - heuristic_point;
	}
}



