/*	Deniz Seyidoglu S010506 Department of Computer Science */
#include  <vector>
#include  <iterator>

#include "../headers/Exception.h"
#include "../headers/Logger.h"
#include "../headers/Solution.h"

Solution::Solution() :
    course{Course{}},
    reservedAssistants{std::vector<std::pair<Assistant, int>>{}} {
        Logger& logger = Logger::instance();
        logger.info("Solution created without any parameters!");
    };

Solution::Solution(
    Course course,
    std::vector<std::pair<Assistant, int>> reservedAssistants
    ) :
    course{course},
    reservedAssistants{reservedAssistants} {
        Logger& logger = Logger::instance();
        logger.info("Solution created with cotr!");
    };

void
Solution::print() const {
    // std::cout << "Solution(" << std::endl << course.code << ", ";
    // for (const auto &p : reservedAssistants) {
    //     std::cout << std::endl << "Assistant: ";
    //     std::cout << p.first << "Hours: ";
    //     std::cout << p.second << ", " << std::endl;
    // }
    // std::cout << std::endl << "))" << std::endl;

    std::cout << course.code << ", ";
    for (const auto &p : reservedAssistants) {
        std::cout << p.first.name << ", " << p.second << ", ";
    }
    std::cout << std::endl;
}

std::string
Solution::_getMetaName() const { return _metaName; }

Solution::~Solution() {
    Logger& logger = Logger::instance();
    logger.info("Course::Destructor was called");
}

// TODO: Do I really need these?
// Solution::Solution(
//                 const Solution& other
//                 )
//                 : code{other.code},
//                   instructorName{other.instructorName},
//                   minTAHours{other.minTAHours},
//                   maxTAHours{other.maxTAHours},
//                   minTACount{other.minTACount}
//                   { };
//
// void
// Solution::swap(Solution& first, Solution& second) {
//   using std::swap;
//   swap(first.code, second.code);
//   swap(first.instructorName, second.instructorName);
//   swap(first.minTAHours, second.minTAHours);
//   swap(first.maxTAHours, second.maxTAHours);
//   swap(first.minTACount, second.minTACount);
// };
//
// Solution::Solution(Solution&& other) : Solution() {
//   std::swap(*this, other);
// };
//
// void
// Solution::operator=(Solution other) {
//   std::swap(*this, other);
// }
