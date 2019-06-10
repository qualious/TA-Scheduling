/*	Deniz Seyidoglu S010506 Department of Computer Science */
#include <iostream>

#include "../framework/headers/Assistant.h"
#include "../framework/headers/Course.h"
#include "../framework/headers/Solution.h"
#include "./headers/GreedySolver.h"
#include "./headers/OptimalSolver.h"

using namespace std;

int
main(void) {
    auto assistants = Data<Assistant>::loadFromFile("./data/ASSISTANTS.csv");
    auto courses = Data<Course>::loadFromFile("./data/COURSES.csv");
    auto greedy = GreedySolver{assistants, courses};
    greedy.solve();
    // auto optimal = OptimalSolver{assistants, courses};
    // auto optimalSolutions = optimal.solve();
    return 0;
}
