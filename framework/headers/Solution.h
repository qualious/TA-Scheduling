/*	Deniz Seyidoglu S010506 Department of Computer Science */
#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <ostream>

#include "./Course.h"

class Solution: public Data<Solution> {
public:
	Solution();
	Solution(Course, std::vector<std::pair<Assistant, int>>);
	std::string _getMetaName() const;
    void print() const;
	// TODO: Do I really need these?
	// Solution(const Solution& other);
	// Solution(Solution&& other);
	// friend void swap(Solution& first, Solution& second);
	~Solution();
private:
	Course course;
	std::vector<std::pair<Assistant, int>> reservedAssistants;
	std::string _metaName {"Solution"};
    std::string getCourseName() const;
};

#endif  // SOLUTION
