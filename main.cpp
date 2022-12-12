#include <iostream>
#include <vector>
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
    vector<Node> frontier;
    while (true)
    {
        if (frontier.empty())
            return;
    }
    switch (method_choice)
    {
        case 'a':
            //bfs
            break;
        case 'b':
            //dfs
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

Node* initialize_game()
{
    Node* node = new Node(NULL, NULL);
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