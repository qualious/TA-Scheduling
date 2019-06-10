/*	Deniz Seyidoglu S010506 Department of Computer Science */
#include "../headers/Course.h"
#include "../headers/Exception.h"
#include "../headers/Logger.h"

Course::Course() :
    code{""},
    instructorName{""},
    minTAHours{0},
    maxTAHours{0},
    minTACount{0},
    assignedHours{0} {
        Logger& logger = Logger::instance();
        logger.info("Course created without any parameters!");
    };

Course::Course(
    const std::string code,
    const std::string instructorName,
    uint minTAHours,
    uint maxTAHours,
    uint minTACount
    ) : code{code},
    instructorName{instructorName},
    minTAHours{minTAHours},
    maxTAHours{maxTAHours},
    minTACount{minTACount},
    assignedHours{0} {
        Logger& logger = Logger::instance();
        logger.info("Course created with cotr!");
    };

int
Course::assign(Assistant& assistant, bool dry = false) {
    int hoursToAssist = 0;
    const int remainingAvailability = assistant.maxCoursesToAssist - assistant.assistingCourses.size();
    const bool noMoreFreeHours = assistant.freeHours <= 0;
    const bool alreadyAssisted = (
        std::find(assistant.assistingCourses.begin(),
        assistant.assistingCourses.end(),
        this->code) != assistant.assistingCourses.end()
    );
    if (remainingAvailability > 0 || alreadyAssisted || !noMoreFreeHours) {
        const int remainingMinTAHours = minTAHours - assignedHours;
        if (remainingMinTAHours < 0) {
            Logger& logger = Logger::instance();
            std::ostringstream msg;
            msg << "Minimum TA hours already covered for Course: " << this->code;
            msg << "\nAlbeit continuing..." << std::endl;
            logger.info(msg.str());
        }

        const int remainingMaxTAHours = maxTAHours - assignedHours;
        if (remainingMaxTAHours < 0) {
            std::ostringstream msg;
            msg << "AssignedHours is bigger than Maximum TA hours!" << std::endl;
            msg << "For the Course: " << this->code << std::endl;
            msg << "This shouldn't have happened. Exiting..." << std::endl;
            auto exception = Exception("Course::assign(Assistant)", msg.str());
            throw exception;
        }

        if (remainingMinTAHours > 0){
            hoursToAssist = remainingMinTAHours > assistant.freeHours ? assistant.freeHours : remainingMinTAHours;
        }
    }
    if (!dry && (this->assignedHours + hoursToAssist) <= this->maxTAHours) {
        this->assignedHours += hoursToAssist;
        assistant.freeHours -= hoursToAssist;
        if (!alreadyAssisted && hoursToAssist > 0) {
            assistant.assistingCourses.push_back(this->code);
        }
    }
    return hoursToAssist;
}

void
Course::print() const {
    std::cout << "Course(" << code << ")" << std::endl;
}

Course
Course::build(std::vector<std::string> params) {
    std::ostringstream msg;

    if (params.size() != 5) {
        msg << "Wrong parameters: " << std::endl;
        msg << "Given parameters were: " << std::endl;
        std::copy(params.begin(), params.end(), std::ostream_iterator<std::string>(msg, ", "));
        msg << std::endl;
        auto exception = Exception("Course::build(std::string)", msg.str());
        throw exception;
    }

    std::string _code = params.at(0);

    if (!_code.size()) {
        msg << "Wrong parameters: " << std::endl;
        msg << "code length is zero" << std::endl;
        auto exception = Exception("Course::build(std::string)", msg.str());
        throw exception;
    }

    std::string _instructorName = params.at(1);

    if (!_instructorName.size()) {
        msg << "Wrong parameters: " << std::endl;
        msg << "instructorName length is zero" << std::endl;
        auto exception = Exception("Course::build(std::string)", msg.str());
        throw exception;
    }

    int _minTAHours = 0;
    int _maxTAHours = 0;
    int _minTACount = 0;

    try {
        _minTAHours = std::stoi(params.at(2), nullptr);
        _maxTAHours = std::stoi(params.at(3), nullptr);
        _minTACount = std::stoi(params.at(4), nullptr);
    } catch(std::exception e) {
        msg << "Error while converting string to integer!" << std::endl;
        msg << "From: " << params.at(2) << params.at(3) << params.at(4) << std::endl;
        msg << e.what() << std::endl;
        auto exception = Exception("Course::build(std::string)", msg.str());
        throw exception;
    }

    if (_minTAHours <= 0 || _maxTAHours <= 0 || _minTACount <= 0) {
        msg << "Wrong parameters: " << std::endl;
        msg << "minTAHours, maxTAHours or minTACount is negative or 0" << std::endl;
        msg << "minTAHours: " << _minTAHours << std::endl;
        msg << "maxTAHours: " << _maxTAHours << std::endl;
        msg << "minTACount: " << _minTACount << std::endl;
        auto exception = Exception("Course::build(std::string)", msg.str());
        throw exception;
    }

    auto course = Course{
        _code,
        _instructorName,
        static_cast<uint>(_minTAHours),
        static_cast<uint>(_maxTAHours),
        static_cast<uint>(_minTACount)
    };

    msg << "Course updated with build!" << std::endl;
    msg << course << std::endl;
    Logger& logger = Logger::instance();
    logger.info(msg.str());

    return course;

}

std::ostream& operator<<(std::ostream &ostrm, const Course &course) {
    ostrm << course.code << ",";
    ostrm << course.instructorName << ",";
    ostrm << course.minTAHours << ",";
    ostrm << course.maxTAHours << ",";
    ostrm << course.minTACount << std::endl;
    return ostrm;
}

std::string
Course::_getMetaName() const { return _metaName; }

Course::~Course() {
    Logger& logger = Logger::instance();
    logger.info("Course::Destructor was called");
}

// TODO: Do I really need these?
// Course::Course(
//                 const Course& other
//                 )
//                 : code{other.code},
//                   instructorName{other.instructorName},
//                   minTAHours{other.minTAHours},
//                   maxTAHours{other.maxTAHours},
//                   minTACount{other.minTACount}
//                   { };
//
// void
// Course::swap(Course& first, Course& second) {
//   using std::swap;
//   swap(first.code, second.code);
//   swap(first.instructorName, second.instructorName);
//   swap(first.minTAHours, second.minTAHours);
//   swap(first.maxTAHours, second.maxTAHours);
//   swap(first.minTACount, second.minTACount);
// };
//
// Course::Course(Course&& other) : Course() {
//   std::swap(*this, other);
// };
//
// void
// Course::operator=(Course other) {
//   std::swap(*this, other);
// }
