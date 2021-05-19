BUILDDIR = build
LDFLAGS =
CXX = clang++
CXXFLAGS = -I. -Isrc/ -Ipublic/cpp/ -Wall -std=c++17 -g3
FLATC = flatc

UNAME_S := $(shell uname -s)

SOURCES := $(shell find src -type f -name '*.cpp' -maxdepth 1)
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.cpp=%.o))

LIBRARY = libvm_math.so

build: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CXX) -shared $(LDFLAGS) $(OBJECTS) -o build/$(LIBRARY)
	bindgen public/cpp/vm_math.hpp -o public/rust/vm_math/src/vm_math.rs
	cd public/rust/vm_math && cargo clippy

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(BUILDDIR)/$(dir $<)
	$(CXX) $(CXXFLAGS) $(IMGUI_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)
