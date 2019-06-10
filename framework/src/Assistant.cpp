/*	Deniz Seyidoglu S010506 Department of Computer Science */
#include "../headers/Assistant.h"
#include "../headers/Exception.h"
#include "../headers/Logger.h"

Assistant::Assistant() : name{""},
                         hoursToAssist{0},
                         maxCoursesToAssist{0},
                         prevAssistedCourses{std::vector<std::string>()},
                         freeHours{0},
                         assistingCourses{std::vector<std::string>()} {
                             Logger& logger = Logger::instance();
                             logger.info("Assistant created without any parameters!");
                         };

Assistant::Assistant(
                      std::string name,
                      ulong hoursToAssist,
                      uint maxCoursesToAssist,
                      std::vector<std::string> prevAssistedCourses
                    )
                    : name{name},
                      hoursToAssist{hoursToAssist},
                      maxCoursesToAssist{maxCoursesToAssist},
                      prevAssistedCourses{prevAssistedCourses},
                      freeHours{static_cast<int>(hoursToAssist)},
                      assistingCourses{std::vector<std::string>()} {
                          Logger& logger = Logger::instance();
                          logger.info("Assistant created with cotr!");
                      };

Assistant
Assistant::build(std::vector<std::string> params) {
    std::ostringstream msg;
    if (params.size() < 3) {
      msg << "Wrong parameters: " << std::endl;
      msg << "Given parameters were: " << std::endl;
      std::copy(params.begin(), params.end(), std::ostream_iterator<std::string>(msg, ", "));
      msg << std::endl;
      auto exception = Exception("Assistant::build(std::string)", msg.str());
      throw exception;
    }

    std::string _name = params.at(0);

    if (!_name.size()) {
      msg << "Wrong parameters: " << std::endl;
      msg << "name length is zero" << std::endl;
      auto exception = Exception("Assistant::build(std::string)", msg.str());
      throw exception;
    }

    int _hoursToAssist = 0;
    int _maxCoursesToAssist = 0;

    try {
      _hoursToAssist = std::stoi(params.at(1), nullptr);
      _maxCoursesToAssist = std::stoi(params.at(2), nullptr);
    } catch(std::exception e) {
      msg << "Error while converting string to integer!" << std::endl;
      msg << "From: " << params.at(1) << params.at(2) << std::endl;
      msg << e.what() << std::endl;
      auto exception = Exception("Assistant::build(std::string)", msg.str());
      throw exception;
    }

    if (_hoursToAssist <= 0 || _maxCoursesToAssist <= 0) {
      msg << "Wrong parameters: " << std::endl;
      msg << "hoursToAssist or maxCoursesToAssist is negative or 0" << std::endl;
      msg << "hoursToAssist: " << _hoursToAssist << std::endl;
      msg << "maxCoursesToAssist: " << _maxCoursesToAssist << std::endl;
      auto exception = Exception("Assistant::build(std::string)", msg.str());
      throw exception;
    }

    std::vector<std::string> _prevAssistedCourses;
    for (size_t i = 3; i < params.size(); ++i) {
      _prevAssistedCourses.push_back(params.at(i));
    }

    auto assistant = Assistant{ _name,
                                static_cast<ulong>(_hoursToAssist),
                                static_cast<uint>(_maxCoursesToAssist),
                                _prevAssistedCourses
                              };

    msg << "Assistant updated with build!" << std::endl;
    msg << assistant << std::endl;
    Logger& logger = Logger::instance();
    logger.info(msg.str());

    return assistant;
}

std::ostream& operator<<(std::ostream &ostrm, const Assistant &assistant) {
    ostrm << std::endl;
    ostrm << "name:" << assistant.name << ",";
    // ostrm << "hoursToAssist: " << assistant.hoursToAssist << ",";
    // ostrm << "maxCoursesToAssist: " << assistant.maxCoursesToAssist << std::endl;
    ostrm << "prevAssistedCourses: ";
    std::copy(
      assistant.prevAssistedCourses.begin(),
      assistant.prevAssistedCourses.end(),
      std::ostream_iterator<std::string>(ostrm, ",")
    );
    ostrm << "assistingCourses: ";
    std::copy(
      assistant.assistingCourses.begin(),
      assistant.assistingCourses.end(),
      std::ostream_iterator<std::string>(ostrm, ",")
    );
    ostrm << std::endl;
    return ostrm;
}

void
Assistant::print() const {
    std::cout << "Assistant(" << name << ")" << std::endl;
}

std::string
Assistant::_getMetaName() const { return _metaName; }

Assistant::~Assistant() {
    Logger& logger = Logger::instance();
    logger.info("Assistant::Destructor was called!");
}

// TODO: Do I really need these?
// // Copy-Cotr
// Assistant::Assistant(const Assistant& other) :
//                                     name{other.name},
//                                     hoursToAssist{other.hoursToAssist},
//                                     maxCoursesToAssist{other.maxCoursesToAssist},
//                                     prevAssistedCourses{other.prevAssistedCourses},
//                                     { };
//
//
// void
// Assistant::swap(Assistant& first, Assistant& second) {
//     using std::swap;
//     swap(first.name, second.name);
//     swap(first.hoursToAssist, second.hoursToAssist);
//     swap(first.maxCoursesToAssist, second.maxCoursesToAssist);
//     first.prevAssistedCourses.swap(second.prevAssistedCourses);
// }
//
// // Move-Ctor
// Assistant::Assistant(Assistant&& other) : Assistant() {
//     swap(*this, other);
// };
//
// void
// Assistant::operator=(Assistant other) {
//     swap(*this, other);
// }
