#include <iostream>
#include <algorithm>
#include <stack>
#include <chrono>
#include <random>

#include "node.h"


void tree_search(char, Node*, std::chrono::steady_clock::time_point);
Node* initialize_game();
void fill_children(Node*);
bool check_optimal_solution(Node*);
bool compare(Node*, Node*);
void print_solution_steps();

Node* sub_optimal_solution;
int explored_node_count = 0;
int time_limit = 60;
int min_remaining_pegs = 32;
int max_frontier_size = 0;
