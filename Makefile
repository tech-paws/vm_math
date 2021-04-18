BUILDDIR = build
LDFLAGS =
CXX = clang++
CXXFLAGS = -I. -Isrc/ -Ipublic/cpp/ -Wall -std=c++17 -g3
FLATC = flatc

UNAME_S := $(shell uname -s)

SOURCES := $(shell find src -type f -name '*.cpp' -maxdepth 1)
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.cpp=%.o))
SCHEMES := $(shell find public/schemes -type f -name '*.fbs')


LIBRARY = libvm_math.so

build: flatbuffers $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CXX) -shared $(LDFLAGS) $(OBJECTS) -o build/$(LIBRARY)
	bindgen public/cpp/vm_math.hpp -o public/rust/vm_math/src/vm_math.rs
	cd public/rust/vm_math && cargo clippy

flatbuffers:
	$(FLATC) -o public/cpp --cpp $(SCHEMES)
	$(FLATC) -o public/rust/vm_math/src --rust $(SCHEMES)

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(BUILDDIR)/$(dir $<)
	$(CXX) $(CXXFLAGS) $(IMGUI_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)
