WARNINGS = -Wall -Wextra -Wno-sign-compare -Wno-unused-variable -Wno-switch
STD= -std=gnu++14
OPTIMIZE= -march=native -mtune=native -Og -g

CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))

CXX=g++-5

all: bfcc

bfcc: $(OBJ_FILES)
	@echo Linking $@
	@$(CXX) $(STD) -o $@ $^

bin/%.o: src/%.cpp
	@echo CXX $@
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) -c -o $@ $<

clean:
	rm bin/*.o
