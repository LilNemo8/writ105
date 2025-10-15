# ====== config ======
CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -MMD -MP
INCLUDES := -I. -Ihelper -Iciphers -Ivisuals -Igames
LDFLAGS  :=
LDLIBS   :=

TARGET   := manager
MAIN     := manager.cpp

# ====== sources ======
# Collect all .cpp files from helper, ciphers, visuals, games (and one level deeper)
LIB_ALL  := \
  $(wildcard helper/*.cpp) \
  $(wildcard ciphers/*.cpp) \
  $(wildcard visuals/*.cpp) \
  $(wildcard visuals/*/*.cpp) \
  $(wildcard games/*.cpp) \
  $(wildcard games/*/*.cpp)

# Exclude donut.cpp (standalone)
LIB_SRCS := $(filter-out visuals/donut/donut.cpp,$(LIB_ALL))

SRC      := $(MAIN) $(LIB_SRCS)

OBJ      := $(patsubst %.cpp,build/%.o,$(SRC))
DEPS     := $(OBJ:.o=.d)

# ====== rules ======
.PHONY: all run clean print manager donut

all: manager

manager: $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Optional standalone build for donut (if you still use it)
DONUT_SRC := visuals/donut/donut.cpp
DONUT_OBJ := $(patsubst %.cpp,build/%.o,$(DONUT_SRC))
donut: CXXFLAGS += -DBUILD_STANDALONE
donut: $(DONUT_OBJ) $(patsubst %.cpp,build/%.o,$(LIB_SRCS))
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Compile rule
build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build $(TARGET) donut

print:
	@echo "Main:" $(MAIN)
	@echo "Lib srcs:" $(LIB_SRCS)
	@echo "Excluded from manager:" visuals/donut/donut.cpp
	@echo "Objects:" $(OBJ)

-include $(DEPS)
