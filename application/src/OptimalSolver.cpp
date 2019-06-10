/*	Deniz Seyidoglu S010506 Department of Computer Science */
#include "../headers/OptimalSolver.h"

OptimalSolver::OptimalSolver(
                            std::vector<Assistant> assistants,
                            std::vector<Course> courses
                          ) :
                            assistants{assistants},
                            courses{courses} { }

std::vector<Solution>
OptimalSolver::solve() const {
    std::cout << "Solving in OptimalSolver" << std::endl;
    auto solutions = std::vector<Solution>{};
    return solutions;
}
