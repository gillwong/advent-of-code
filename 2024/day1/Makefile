SORTIMPL := STL

CXX = clang++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -MMD -I ../lib/ -D"$(SORTIMPL)"
ifeq ($(OPTIMIZE),1)
	CXXFLAGS += -O2 -g0
else
	CXXFLAGS += -O0 -gfull
endif


EXEC := day1

SOURCES := $(wildcard *.cc) $(wildcard ../lib/*.cc)
OBJECTS := $(SOURCES:.cc=.o)
DEPENDS := $(OBJECTS:.o=.d)

.PHONY : all clean
.ONESHELL :

all : $(EXEC)

$(EXEC) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

-include $(DEPENDS)

clean : 
	rm -f *.d $(OBJECTS) $(EXEC)
