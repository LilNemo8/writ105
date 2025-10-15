# ====== config ======
CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -MMD -MP
INCLUDES := -I. -Ihelper -Iciphers -Ivisuals
LDFLAGS  :=
LDLIBS   :=

TARGET   := manager
MAIN     := manager.cpp

# ====== sources ======
# Pick up ALL .cpp files in helper/, ciphers/, visuals/ and ONE nesting level in visuals/*/
# (This will include visuals/visuals_manager.cpp and visuals/donut/donut.cpp, etc.)
LIB_SRCS := \
  $(wildcard helper/*.cpp) \
  $(wildcard ciphers/*.cpp) \
  $(wildcard visuals/*.cpp) \
  $(wildcard visuals/*/*.cpp)

# Final source list = main + libs
SRC      := $(MAIN) $(LIB_SRCS)

# Objects live under build/ mirroring the source dirs
OBJ      := $(patsubst %.cpp,build/%.o,$(SRC))
DEPS     := $(OBJ:.o=.d)

# ====== rules ======
.PHONY: all run clean print

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# build/<path>.o from <path>.cpp (auto-create subdirs)
build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build $(TARGET)

print:
	@echo "Main:      " $(MAIN)
	@echo "Lib srcs:  " $(LIB_SRCS)
	@echo "Objects:   " $(OBJ)

# auto header deps
-include $(DEPS)
