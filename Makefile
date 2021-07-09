APPNAME := matrix
RM := rm -rf
CXX := g++
CXXFLAGS := -Wall -O2 -I./ 
LDFLAGS :=
LDLIBS := 
BIN := ./bin

SRCS := $(shell find . -maxdepth 2 -name "*.cpp")
OBJS := $(addprefix $(BIN)/, $(notdir $(patsubst %.cpp, %.o, $(SRCS))))
DEPS := $(addprefix $(BIN)/, $(notdir $(patsubst %.cpp, %.d, $(SRCS))))

PROGNAME := $(addprefix $(BIN)/, $(APPNAME))

.PHONY: all clean

all: $(PROGNAME)

$(PROGNAME): $(OBJS)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(PROGNAME) $(OBJS) $(LDLIBS)

$(BIN)/%.o: %.cpp
		$(CXX) -c -MMD -o $@ $< $(CXXFLAGS)

clean:
		$(RM) $(BIN)/*

-include $(DEPS)