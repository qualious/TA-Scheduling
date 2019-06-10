/*	Deniz Seyidoglu S010506 Department of Computer Science */
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception {
public:
	Exception(const std::string, const std::string&);
	~Exception();
	std::string what() const;
private:
	std::string msg;
};

#endif  // EXCEPTION
