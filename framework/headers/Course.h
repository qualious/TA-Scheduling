/*	Deniz Seyidoglu S010506 Department of Computer Science */
#ifndef COURSE_H
#define COURSE_H

#include <ostream>

#include "./Assistant.h"

class Course : public Data<Course> {
public:
    friend class Solution;
    Course();
	Course(const std::string, const std::string, uint, uint, uint);
    Course build(std::vector<std::string>);
    friend std::ostream& operator<<(std::ostream&, const Course&);
    int assign(Assistant&, bool);
    std::string _getMetaName() const;
    void print() const;
    // TODO: Do I really need these?
	// Course(const Course&);
	// Course(Course&&);
	// friend void swap(Course&, Course&);
	~Course();
private:
	std::string code;              // CS409
	std::string instructorName;    // Furkan Kirac
	uint minTAHours;               // 10
	uint maxTAHours;               // 20
	uint minTACount;               // 2
    uint assignedHours;

    std::string _metaName{"Course"};
};

#endif  // COURSE
