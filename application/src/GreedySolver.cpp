/*	Deniz Seyidoglu S010506 Department of Computer Science */
#include "../headers/GreedySolver.h"
#include "../../framework/headers/Logger.h"

GreedySolver::GreedySolver(
                            std::vector<Assistant> assistants,
                            std::vector<Course> courses
                          ) :
                            assistants{assistants},
                            courses{courses}
                            { }

std::vector<Solution>
GreedySolver::solve() {
    Logger& logger = Logger::instance();
    std::vector<Solution> solutions;
    for (auto course : courses) {
        std::vector<std::pair<Assistant, int>> reservedAssistants{};
        for (Assistant& assistant : assistants) {
            int assignedHours = course.assign(assistant, false);
            if (assignedHours > 0) {
                auto pair = std::pair<Assistant, int>{assistant, assignedHours};
                reservedAssistants.push_back(pair);
                std::ostringstream msg;
                msg << "Assigned Assistant: " << assistant << std::endl;
                msg << "For Course: " << course << std::endl;
                msg << "For " << assignedHours << " hours" << std::endl;
                logger.info(msg.str());
            }
        }
        // TODO: don't ignore not fully assigned courses?
        // Do something here?
        auto solution = Solution{course, reservedAssistants};
        solutions.push_back(solution);
    }

    std::cout << "FOUND SOLUTIONS: " << std::endl;

    for (auto solution : solutions) {
        solution.print();
    }

    return solutions;
}
