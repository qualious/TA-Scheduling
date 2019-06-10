/*	Deniz Seyidoglu S010506 Department of Computer Science */
#ifndef OPTIMAL_SOLVER_H
#define OPTIMAL_SOLVER_H

#include "../../framework/headers/Assistant.h"
#include "../../framework/headers/Course.h"
#include "../../framework/headers/Solution.h"

class OptimalSolver {
public:
    OptimalSolver(std::vector<Assistant>, std::vector<Course>);
    std::vector<Solution> solve() const;
protected:
private:
    std::vector<Assistant> assistants;
    std::vector<Course> courses;
};

#endif  // OPTIMAL_SOLVER
