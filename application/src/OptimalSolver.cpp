/* Deniz Seyidoglu S010506 Department of Computer Science */
#include "../headers/OptimalSolver.h"

OptimalSolver::OptimalSolver(
                            std::vector<Assistant> assistants,
                            std::vector<Course> courses
                          ) :
                            assistants{assistants},
                            courses{courses} { }

std::vector<Solution>
OptimalSolver::solve() const {
    // Define a cost function “C = penalty – bonus” as below:
    // Assistant with old course experience assigned to a new course -> 5 pts penalty per unexperienced course
    // Assistant assigned to 2 courses at the same time -> 5 pts penalty
    // Assistant assigned to 3 or more courses at the same time -> 20 pts penalty
    // Course requirement not met -> 100 pts penalty
    // For each X h/week unassigned assistant time -> X pts bonus
    std::cout << "Solving in OptimalSolver" << std::endl;
    auto solutions = std::vector<Solution>{};
    return solutions;
}
