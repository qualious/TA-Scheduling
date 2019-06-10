/* Deniz Seyidoglu S010506 Department of Computer Science */
#include <climits>
#include <vector>
#include <numeric>
#include <string>
#include <functional>

#include "../headers/OptimalSolver.h"
#include "../../framework/headers/Logger.h"

OptimalSolver::OptimalSolver(std::vector<Assistant> assistants, std::vector<Course> courses) :
                            assistants{assistants},
                            courses{courses} { }

void
OptimalSolver::solve() {
    Logger& logger = Logger::instance();
    std::vector<std::tuple<Course, Assistant*, int, int>> maxRewards{};

    if (courses.size() == 0 || assistants.size() == 0) {
        // We found every course!
        // Or we failed miserably and removed all assistants.
        return;
    }

    for (auto course : courses) {
        std::vector<std::tuple<Assistant*, int, int>> rewards{};

        for (Assistant& assistant : assistants) {
            // dry run first in order to calculate the hours.
            int assignedHours = course.assign(assistant, true);
            if (assignedHours > 0) {
                int reward = calculateReward(assistant, course, assignedHours);
                auto rewardTuple = std::make_tuple(&assistant, reward, assignedHours);
                rewards.push_back(rewardTuple);

                std::ostringstream msg;
                msg << "OptimalSolver" << std::endl;
                msg << "Assigned Assistant: " << assistant << std::endl;
                msg << "For Course: " << course << std::endl;
                msg << "For " << assignedHours << " hours" << std::endl;
                logger.info(msg.str());
            }
        }

        auto assistant = Assistant{};
        std::tuple<Assistant*, int, int> max = std::make_tuple(&assistant, INT_MIN, 0);
        for (auto reward : rewards) {
            if (std::get<1>(reward) > std::get<1>(max)) {
                max = reward;
            }
        }
        auto maxTuple = std::make_tuple(course, std::get<0>(max), std::get<2>(max), std::get<1>(max));
        maxRewards.push_back(maxTuple);
    }

    static auto orderer = [](const std::tuple<Course, Assistant*, int, int>& lhs,
        const std::tuple<Course, Assistant*, int, int>& rhs) {
            return std::get<3>(lhs) > std::get<3>(rhs);
    };

    std::sort(std::begin(maxRewards), std::end(maxRewards), orderer);
    auto maxReward = maxRewards.at(0);
    // Commit the maximum performant assistant to course
    this->commit(maxReward);
}

void
OptimalSolver::commit(std::tuple<Course, Assistant*, int, int> maxReward) {
    auto course = std::get<0>(maxReward);
    auto assistant = std::get<1>(maxReward);
    int assignedHours = std::get<2>(maxReward);
    auto assistingCourses = assistant->getAssistingCourses();
    const bool alreadyAssisted = (
        std::find(assistingCourses.begin(),
            assistingCourses.end(),
            course.getCode()
        ) != assistingCourses.end()
    );

    course.commit(assistant, assignedHours, alreadyAssisted);
    reservedAssistants.push_back(std::pair<Assistant, int>{*assistant, assignedHours});
    const int cummulatedSoFar = std::accumulate(reservedAssistants.begin(),reservedAssistants.end(),0,[](auto &a, auto &b){return a + b.second; });
    if (course.getMinRequiredHours() <= 0 || cummulatedSoFar > course.getMinTAHours()) {
        courses.erase(
            std::remove_if(
                courses.begin(),
                courses.end(),
                [course](auto _course) {
                    return _course.getCode() == course.getCode();
                }
            ),
            courses.end()
        );
        assistants.erase(
            std::remove_if(
                assistants.begin(),
                assistants.end(),
                [](auto assistant) {
                    return assistant.getFreeHours() == 0;
                }
            ),
            assistants.end()
        );
        auto solution = Solution{course, reservedAssistants};
        solutions.push_back(solution);
        reservedAssistants.clear();
    }
    this->solve();
}

int
OptimalSolver::calculateReward(Assistant assistant, Course course, int assignedHours) {
    int points = 0;
    auto prev = assistant.getPrevAssistedCourses();
    const bool prevAssisted = (std::find(prev.begin(), prev.end(), course.getCode()) != prev.end());
    if (!prevAssisted) {
        points -= 5;
    }
    auto curr = assistant.getAssistingCourses();
    switch (curr.size()) {
        case 0:
            break;
        // Already assigned 1. If we commit this too,
        // we will have 2 assigned. -5
        case 1:
            points -= 5;
            break;
        default:
            points -= 20;
            break;
    }
    auto required = course.getMinRequiredHours();
    if (required > 0) {
        points -= 100;
    }

    points += (assistant.getFreeHours() - assignedHours);
    return points;
}

std::vector<Solution>
OptimalSolver::getSolutions() const {
    return solutions;
}
