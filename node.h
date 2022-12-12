#pragma once
class Node
{
	public:
		vector<vector<int>> state;
		Node& parent;
		Node& child;
		Node(Node* aparent, Node* achild);

};

