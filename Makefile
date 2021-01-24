BUILDDIR = build
LDFLAGS =
CXX = clang++
CXXFLAGS = -I. -Isrc/ -Ipublic/ -Wall -std=c++17 -g3

UNAME_S := $(shell uname -s)

SOURCES := $(shell find src -type f -name '*.cpp' -maxdepth 1)
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.cpp=%.o))

LIBRARY = libvm_math.so

build: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CXX) -shared $(LDFLAGS) $(OBJECTS) -o build/$(LIBRARY)

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(BUILDDIR)/$(dir $<)
	$(CXX) $(CXXFLAGS) $(IMGUI_FLAGS) -c $< -o $@

run: $(LIBRARY)
	./$(BUILDDIR)/$(LIBRARY)

clean:
	rm -rf $(BUILDDIR)
