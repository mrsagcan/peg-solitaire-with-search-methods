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
	remainingPegs = CountRemainingPegs();
}
int Node::CountRemainingPegs()
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

std::string Node::ToString()
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



