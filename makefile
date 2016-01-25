WARNINGS = -Wall -Wextra -Wno-sign-compare -Wno-unused-variable -Wno-switch
STD = -std=c++1y
OPTIMIZE = -O3

CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))

CXX=g++-5

all: bfcc

debug: OPTIMIZE = -Og -g
debug: bfcc

bfcc: $(OBJ_FILES)
	@echo Linking $@
	@$(CXX) $(STD) -o $@ $^

bin/%.o: src/%.cpp
	@echo CXX $@
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) -c -o $@ $<

clean:
	rm bin/*.o
	rm bfcc
