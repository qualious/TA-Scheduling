appname := run
CXX := gcc
CXXFLAGS := -Wall -std=c++17 -lc++

srcfiles := $(shell find . -name "*.cpp")
headers := $(shell find . -name "*.h")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects) $(headers)
	$(CXX) $(CXXFLAGS) -o $(appname) $(objects)

clean:
	rm -f $(objects)
