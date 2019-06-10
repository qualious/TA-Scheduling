/*	Deniz Seyidoglu S010506 Department of Computer Science */
#ifndef OPTIMAL_SOLVER_H
#define OPTIMAL_SOLVER_H

#include "../../framework/headers/Assistant.h"
#include "../../framework/headers/Course.h"
#include "../../framework/headers/Solution.h"

// Warning: Not so optimal
class OptimalSolver {
public:
    OptimalSolver(std::vector<Assistant>, std::vector<Course>);
    int calculateReward(Assistant, Course, int);
    void solve();
    void commit(std::tuple<Course, Assistant*, int, int>);
    std::vector<Solution> getSolutions() const;
protected:
private:
    std::vector<Assistant> assistants;
    std::vector<Course> courses;
    std::vector<Solution> solutions;
    std::vector<std::pair<Assistant, int>> reservedAssistants;
};

#endif  // OPTIMAL_SOLVER
