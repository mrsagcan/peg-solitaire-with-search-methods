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
}
void Node::count_remaining_pegs()
{
	int count = 0;
	for (int i = 0; i < state.size(); i++)
	{
		if (state.at(i).at(1) == 1)
		{
			count++;
		}
	}
	remaining_pegs = count;
}

std::string Node::to_string()
{
	std::string text_state;
	text_state += "Current Depth: " + std::to_string(depth) + "\n";
	text_state += "  | | | | | | | |\n";
	for (int i = 0; i < 7; i++)
	{
		text_state += "-- ";
		for (int j = 0; j < 7; j++)
		{
			if (state.at(i * 7 + j).at(1) == 1)
			{
				text_state += "X ";
			}
			else if (state.at(i * 7 + j).at(1) == 0)
			{
				text_state += "O ";
			}
			else if (state.at(i * 7 + j).at(1) == 2)
			{
				text_state += "  ";
			}
		}
		text_state += "--\n";
	}
	text_state += "  | | | | | | | |\n";
	return text_state;
}

void Node::set_heuristic_point()
{
	if (moved_peg_index % 7 == 0 || moved_peg_index % 7 == 6)
	{
		heuristic_point = 0.8;
	}
	else if (moved_peg_index % 7 == 1 || moved_peg_index % 7 == 5)
	{
		heuristic_point = 0.6;
	}
	else if (moved_peg_index % 7 == 2 || moved_peg_index % 7 == 4)
	{
		heuristic_point = 0.4;
	}
	else if (moved_peg_index % 7 == 3)
	{
		heuristic_point = 0.2;
	}
	if (remaining_pegs < 7)
	{
		heuristic_point = 1 - heuristic_point;
	}
}



