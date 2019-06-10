/*	Deniz Seyidoglu S010506 Department of Computer Science */
#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <typeinfo>

#include "../headers/Exception.h"

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

template<class Derived>
class Data {
public:

	void print() const {
        static_cast<Derived*>(this)->print();
    }

    std::string getMetaName() {
        return static_cast<Derived*>(this)->_getMetaName();
    }

    void destroy() {
        static_cast<Derived*>(this)->~Derived();
    }

    template<typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    Derived prepareAndBuild(std::string line) {
        std::vector<std::string> params = split(line, ',');
        return static_cast<Derived*>(this)->build(params);
    }

    // MILESTONE: maybe read the file in bulks with threads
    // in order to increase efficiency?
    static auto loadFromFile(const std::string filename) {
        std::ifstream file(filename);
        std::vector<Derived> data{};
        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                try {
                    // TODO: this looks bad.
                    auto derived = Derived{}.prepareAndBuild(line);
                    data.push_back(derived);
                } catch(std::exception e) {
                    std::cout << "Exception: " << e.what() << std::endl;
                }
            }
        } else {
            std::ostringstream msg;
            msg << "Cannot open file: " << filename << std::endl;
            std::cout << "ERROR!: " << msg.str() << std::endl;
            auto exception = Exception{"Data::load", msg.str()};
            throw exception;
        }
        file.close();
        return data;
    }

    void writeToFile(const std::string filename) {
        std::ofstream file;
        file.open(filename, std::ios_base::app);
        if (file.is_open()) {
            try {
                file << static_cast<Derived*>(this)->toString() << std::endl;
            } catch(std::exception& e) {
                std::ostringstream msg;
                msg << "You have to override operator<< in class :";
                msg << this->getMetaName() << std::endl;
                msg << "Error is: " << std::endl;
                msg << e.what() << std::endl;
                std::cout << "ERROR!: " << msg.str() << std::endl;
                auto exception = Exception{"Data::write", msg.str()};
                throw exception;
            }
        } else {
            std::ostringstream msg;
            msg << "Cannot open file: ";
            msg << filename << std::endl;
            std::cout << "ERROR!: " << msg.str() << std::endl;
            auto exception = Exception{"Data::write", msg.str()};
            throw exception;
        }
        file.close();
    };

};

#endif  // DATA
