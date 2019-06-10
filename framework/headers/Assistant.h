/*	Deniz Seyidoglu S010506 Department of Computer Science */
#ifndef ASSISTANT_H
#define ASSISTANT_H

#include <vector>
#include <ostream>

#include "../src/Data.cpp"

class Assistant : public Data<Assistant> {
public:
    friend class Solution;
    friend class Course;
    Assistant();
	Assistant(const std::string, const ulong, const uint, const std::vector<std::string>);
    Assistant build(std::vector<std::string>);
    friend std::ostream& operator<<(std::ostream&, const Assistant&);
    friend std::ostream& operator<<(std::ostream&, const Assistant*);
    std::string _getMetaName() const;
    void print() const;
    std::vector<std::string> getAssistingCourses() const;
    std::vector<std::string> getPrevAssistedCourses() const;
    int getFreeHours() const;
    // TODO: Do I really need these?
	// Assistant(const Assistant& other);
	// Assistant(Assistant&& other);
	// friend void swap(Assistant& first, Assistant& second);
	~Assistant();
private:
	std::string name;                              // Baris
	ulong hoursToAssist;                           // 30
	uint maxCoursesToAssist;                       // 3
	std::vector<std::string> prevAssistedCourses;  // CS321, CS409, CS409, CS409
    int freeHours;
    // TODO: maybe make this Course class
    // instead of just the name? This is OOP afterall
    // We can't since Course is refering to Assistant
    // so we end up with cyclic dependency
    std::vector<std::string> assistingCourses;
    std::string _metaName{"Assistant"};
};

#endif  // ASSISTANT
