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
    auto greedySolutions = greedy.solve();
    std::cout << "===============================================" << std::endl;
    std::cout << "greedySolutions: " << std::endl;
    for (auto& solution : greedySolutions) {
        solution.print();
        solution.writeToFile("./data/GREEDY_SOLUTION.csv");
    }
    std::cout << "===============================================" << std::endl;
    auto optimal = OptimalSolver{assistants, courses};
    optimal.solve();
    auto optimalSolutions = optimal.getSolutions();
    std::cout << "optimalSolutions: " << std::endl;
    for (auto& solution : optimalSolutions) {
        solution.print();
        solution.writeToFile("./data/OPTIMAL_SOLUTION.csv");
    }
    std::cout << "===============================================" << std::endl;

    return 0;
}
