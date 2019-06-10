/*	Deniz Seyidoglu S010506 Department of Computer Science */
#ifndef GREEDY_SOLVER_H
#define GREEDY_SOLVER_H

#include "../../framework/headers/Assistant.h"
#include "../../framework/headers/Course.h"
#include "../../framework/headers/Solution.h"

class GreedySolver {
public:
    GreedySolver(std::vector<Assistant>, std::vector<Course>);
    std::vector<Solution> solve();
protected:
private:
    std::vector<Assistant> assistants;
    std::vector<Course> courses;
};

#endif  // GREEDY_SOLVER
