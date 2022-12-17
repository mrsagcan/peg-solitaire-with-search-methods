#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "node.cpp"

using namespace std;

int main()
{
    cout << "Please choose a search method:\n\n";
    cout << "a. Breadth-First Search\n";
    cout << "b. Depth-First Search\n";
    cout << "c. Iterative Deepening Search\n";
    cout << "d. Depth-First Search with Random Selection\n";
    cout << "e. Depth-First Search with a Node Selection Heuristic\n";

    char method_choice{};

    while (method_choice != 'a' && method_choice != 'b' && method_choice != 'c' && method_choice != 'd' && method_choice != 'e')
    {
        cin >> method_choice;
        cout << "Please enter a valid input (a,b,c,d,e)\n";
    }
    Node* initial = initialize_game();
    tree_search(method_choice, initial);

    return 0;
}



void tree_search(char method_choice, Node* initial)
{
    stack<Node*> frontier_stack;
    queue<Node*> frontier_queue;

    frontier_stack.push(initial);
    frontier_queue.push(initial);
    while (true)
    {
        if (frontier_queue.empty())
            break;
        switch (method_choice)
        {
            case 'a':
                //bfs
                Node * front = frontier_queue.front();
                frontier_queue.pop();
                fill_children(front);
                for(Node * child : front->children)
                {
                    frontier_queue.push(child);
                }
                break;
            case 'b':
                //dfs
                Node * front = frontier_stack.top();
                frontier_stack.pop();
                fill_children(front);
                for (Node* child : front->children)
                {
                    frontier_stack.push(child);
                }
                break;
            case 'c':
                //ids
                break;
            case 'd':
                //dfs w\random
                break;
            case 'e':
                //dfs with node selection heuristic
                break;
        }
    }
    
}

Node* initialize_game()
{
    Node* node = new Node(NULL);
    node->state = 
    { 
        {-1,2}, {-1,2}, {1,1},  {2,1},  {3,1},  {-1,2}, {-1,2},
        {-1,2}, {-1,2}, {4,1},  {5,1},  {6,1},  {-1,2}, {-1,2},
        {7,1},  {8,1},  {9,1},  {10,1}, {11,1}, {12,1}, {13,1},
        {14,1}, {15,1}, {16,1}, {17,0}, {18,1}, {19,1}, {20,1},
        {21,1}, {22,1}, {23,1}, {24,1}, {25,1}, {26,1}, {27,1},
        {-1,2}, {-1,2}, {28,1}, {29,1}, {30,1}, {-1,2}, {-1,2},
        {-1,2}, {-1,2}, {31,1}, {32,1}, {33,1}, {-1,2}, {-1,2},
    };
    return node;
}

//TODO: think about moving it to Node class
void fill_children(Node* front)
{
    for (int i = 0; i < front->state.size(); i++)
    {
        vector<int> peg = front->state.at(i);

        if (peg.at(1) == 2) continue;

        if (peg.at(1) == 0)
        {
            //the order to push moves to children: up,left,right,down

            //up
            if (i > 13)
            {
                vector<int> up = front->state.at(i - 14);
                if (up.at(1) == 1)
                {
                    vector<vector<int>> new_state = front->state;
                    new_state.at(i - 14).at(1) = 0;
                    new_state.at(i - 7).at(1) = 0;
                    new_state.at(i).at(1) = 1;
                    Node* child = new Node(front);
                    child->state = new_state;
                    front->children.push_back(child);
                }
            }
            //left
            if (i % 7 < 5)
            {
                vector<int> left = front->state.at(i - 2);
                if (left.at(1) == 1)
                {
                    vector<vector<int>> new_state = front->state;
                    new_state.at(i - 2).at(1) = 0;
                    new_state.at(i - 1).at(1) = 0;
                    new_state.at(i).at(1) = 1;
                    Node* child = new Node(front);
                    child->state = new_state;
                    front->children.push_back(child);
                }
            }
            //right
            if (i % 7 > 1)
            {
                vector<int> right = front->state.at(i + 2);
                if (right.at(1) == 1)
                {
                    vector<vector<int>> new_state = front->state;
                    new_state.at(i + 2).at(1) = 0;
                    new_state.at(i + 1).at(1) = 0;
                    new_state.at(i).at(1) = 1;
                    Node* child = new Node(front);
                    child->state = new_state;
                    front->children.push_back(child);
                }
            }
            //down
            if (i < 35)
            {
                vector<int> down = front->state.at(i + 14);
                if (down.at(1) == 1)
                {
                    vector<vector<int>> new_state = front->state;
                    new_state.at(i + 14).at(1) = 0;
                    new_state.at(i + 7).at(1) = 0;
                    new_state.at(i).at(1) = 1;
                    Node* child = new Node(front);
                    child->state = new_state;
                    front->children.push_back(child);
                }
            }
        }
    }
};