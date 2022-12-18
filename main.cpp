#include "main.h"

using namespace std;

//TODO: garbage collection



int main()
{
    cout << "Please choose a search method:\n\n";
    cout << "a. Breadth-First Search\n";
    cout << "b. Depth-First Search\n";
    cout << "c. Iterative Deepening Search\n";
    cout << "d. Depth-First Search with Random Selection\n";
    cout << "e. Depth-First Search with a Node Selection Heuristic\n";

    char method_choice{};
    cin >> method_choice;
    
    while (method_choice != 'a' && method_choice != 'b' && method_choice != 'c' && method_choice != 'd' && method_choice != 'e')
    {
        cout << "Please enter a valid input (a,b,c,d,e)\n";
        cin >> method_choice;
    }

    cout << "Enter the time limit in (minutes): ";
    cin >> time_limit;
    Node* initial = initialize_game();

    auto start_time = chrono::high_resolution_clock::now();

    cout << "Timer started: ";
    if (method_choice == 'a')
        cout << "Breadth-First Search ";
    if (method_choice == 'b')
        cout << "Depth-First Search ";
    if (method_choice == 'c')
        cout << "Iterative Deepening Search ";
    if (method_choice == 'd')
        cout << "Depth-First Search with Random Selection";
    if (method_choice == 'e')
        cout << "Depth-First Search with a Node Selection Heuristic";
    cout << "\nTime Limit: " << time_limit << " Minutes" << endl;

    tree_search(method_choice, initial, start_time);


    if (sub_optimal_solution->remaining_pegs == 1)
    {
        //means optimal
        cout << "Optimum solution found." << endl; 
    }
    else
    {
        cout << "Sub-optimum Solution Found with " << min_remaining_pegs << " remaining pegs." << endl;
    }
    
    print_solution_steps();
    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop_time - start_time);
    cout << "The time spent: " << duration.count() << " seconds" << endl;
    cout << "Number of nodes expanded during the search: " << explored_node_count << endl;
    cout << "Max number of nodes stored in the memory during the search: " << max_frontier_size << endl;
    

    return 0;
}



void tree_search(char method_choice, Node* initial, chrono::steady_clock::time_point start_time)
{
    vector<Node*> frontier;
    frontier.push_back(initial);

    switch (method_choice)
    {
        //bfs
        case 'a':
        {
            while (true)
            {
                Node* front = frontier.front();
                frontier.erase(frontier.begin());


                explored_node_count++;


                auto stop_time = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::minutes>(stop_time - start_time);
                if (duration.count() >= time_limit)
                {
                    cout << "Time limit reached!" << endl;
                    break;
                }

                fill_children(front);

                if(check_optimal_solution(front)) 
                    break;

                for (Node* child : front->children)
                {
                    frontier.push_back(child);
                }
                max_frontier_size = frontier.size() > max_frontier_size ? frontier.size() : max_frontier_size;
            }
            break;
        }
        //dfs
        case 'b':
        {
            while (true)
            {

                Node* top = frontier.front();
                frontier.erase(frontier.begin());

                explored_node_count++;


                auto stop_time = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::minutes>(stop_time - start_time);
                if (duration.count() >= time_limit)
                {
                    cout << "Time limit reached!" << endl;

                    break;
                }

                fill_children(top);

                if(check_optimal_solution(top))
                    break;

                for (int i = top->children.size() - 1; i >= 0 ; i--)
                {
                    frontier.emplace(frontier.begin(), top->children.at(i));
                }

                max_frontier_size = frontier.size() > max_frontier_size ? frontier.size() : max_frontier_size;
            }
            break;
        }
        //ids
        case 'c':
        {
            int depth_limit = 0;
            bool cutoff = false;
            while (true)
            {
                while (true)
                {

                    Node* top = frontier.front();
                    frontier.erase(frontier.begin());

                    explored_node_count++;

                    if (depth_limit > top->depth)
                    {
                        fill_children(top);

                        if (check_optimal_solution(top))
                        {
                            cutoff = true;
                            break;
                        }
                        for (int i = top->children.size() - 1; i >= 0; i--)
                        {
                            frontier.emplace(frontier.begin(), top->children.at(i));
                        }
                    }

                    max_frontier_size = frontier.size() > max_frontier_size ? frontier.size() : max_frontier_size;

                    if (frontier.empty())
                        break;
                    
                }
                depth_limit++;
                frontier.push_back(initial);

                if (cutoff)
                {
                    break;
                }
                auto stop_time = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::minutes>(stop_time - start_time);
                if (duration.count() >= time_limit)
                {
                    cout << "Time limit reached!" << endl;

                    break;
                }
            }
            break;
        }
        //dfs w/random
        case 'd':
        {
            while (true)
            {
                Node* top = frontier.front();
                frontier.erase(frontier.begin());

                explored_node_count++;


                auto stop_time = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::minutes>(stop_time - start_time);
                if (duration.count() >= time_limit)
                {
                    cout << "Time limit reached!" << endl;

                    break;
                }

                fill_children(top);

                if (check_optimal_solution(top))
                    break;

                vector<Node*> shuffled_children = top->children;

                unsigned seed = chrono::system_clock::now().time_since_epoch().count();
                shuffle(shuffled_children.begin(), shuffled_children.end(), default_random_engine(seed));

                for (Node* child : shuffled_children)
                {
                    frontier.emplace(frontier.begin(), child);
                }

                max_frontier_size = frontier.size() > max_frontier_size ? frontier.size() : max_frontier_size;
            }
            break;
        }
        //dfs with node selection heuristic
        case 'e':
        {
            while (true)
            {
                Node* top = frontier.front();
                frontier.erase(frontier.begin());

                explored_node_count++;


                auto stop_time = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::minutes>(stop_time - start_time);
                if (duration.count() >= time_limit)
                {
                    cout << "Time limit reached!" << endl;
                    break;
                }

                fill_children(top);

                if (check_optimal_solution(top))
                    break;

                for (int i = 0; i < top->children.size(); i++)
                {
                    top->children.at(i)->set_heuristic_point();
                }
                vector<Node*> sorted_children = top->children;
                sort(sorted_children.begin(), sorted_children.end(), compare);

                for (int i = sorted_children.size() - 1; i >= 0; i--)
                {
                    frontier.emplace(frontier.begin(), sorted_children.at(i));
                }

                max_frontier_size = frontier.size() > max_frontier_size ? frontier.size() : max_frontier_size;
            }
            break;
        }
    }
}

//TODO: Remove first numbers

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
    node->count_remaining_pegs();
    return node;
}

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
                if (front->state.at(i - 14).at(1) == 1 && front->state.at(i - 7).at(1) == 1)
                {
                    vector<vector<int>> new_state = front->state;
                    new_state.at(i - 14).at(1) = 0;
                    new_state.at(i - 7).at(1) = 0;
                    new_state.at(i).at(1) = 1;
                    Node* child = new Node(front);
                    child->state = new_state;
                    child->moved_peg_index = i -14;
                    child->count_remaining_pegs();
                    front->children.push_back(child);
                }
            }
            //left
            if (i % 7 > 1)
            {
                if (front->state.at(i - 2).at(1) == 1 && front->state.at(i - 1).at(1) == 1)
                {
                    vector<vector<int>> new_state = front->state;
                    new_state.at(i - 2).at(1) = 0;
                    new_state.at(i - 1).at(1) = 0;
                    new_state.at(i).at(1) = 1;
                    Node* child = new Node(front);
                    child->state = new_state;
                    child->moved_peg_index = i - 2;
                    child->count_remaining_pegs();
                    front->children.push_back(child);
                }
            }
            //right
            if (i % 7 < 5)
            {
                if (front->state.at(i + 2).at(1) == 1 && front->state.at(i + 1).at(1) == 1)
                {
                    vector<vector<int>> new_state = front->state;
                    new_state.at(i + 2).at(1) = 0;
                    new_state.at(i + 1).at(1) = 0;
                    new_state.at(i).at(1) = 1;
                    Node* child = new Node(front);
                    child->state = new_state;
                    child->moved_peg_index = i + 2;
                    child->count_remaining_pegs();
                    front->children.push_back(child);
                }
            }
            //down
            if (i < 35)
            {
                if (front->state.at(i + 14).at(1) == 1 && front->state.at(i + 7).at(1) == 1)
                {
                    vector<vector<int>> new_state = front->state;
                    new_state.at(i + 14).at(1) = 0;
                    new_state.at(i + 7).at(1) = 0;
                    new_state.at(i).at(1) = 1;
                    Node* child = new Node(front);
                    child->state = new_state;
                    child->moved_peg_index = i + 14;
                    child->count_remaining_pegs();
                    front->children.push_back(child);
                }
            }
        }
    }
};

bool check_optimal_solution(Node* node)
{
    if (node->remaining_pegs < min_remaining_pegs)
    {
        delete sub_optimal_solution;
        min_remaining_pegs = node->remaining_pegs;
        sub_optimal_solution = node;
    }
    else if (node->children.size() == 0)
    {
        delete node;
    }

    if (node->remaining_pegs == 1) return true;
    return false;
}

bool compare(Node* a, Node* b)
{
    return(a->heuristic_point < b->heuristic_point);
}

void print_solution_steps()
{
    stack<Node*> steps;
    Node* temp = sub_optimal_solution;
    steps.push(temp);
    while (temp->parent != NULL)
    {
        steps.push(temp->parent);
        temp = temp->parent;
    }

    while (true)
    {
        if (steps.empty())
            break;
        cout << steps.top()->to_string() << endl;
        steps.pop();
    }
}