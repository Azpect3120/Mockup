# Compiler
COMP = g++

# Output
OUT = ./build/mockup.exe
OUTSRC = ./build/*

# Sources
SRCS = ./mockup.cpp ./lib/compiler/compiler.cpp ./lib/scopeTree/scopeTree.cpp ./lib/scopeTree/treeNode.cpp ./lib/scopeTree/treeBuilder.cpp

# Build the project
all: $(OUT)
$(OUT): $(SRCS)
	$(COMP) $(SRCS) -o $(OUT)

# Run the .exe output file
run: $(OUT)
	$(OUT)

# Remove the built files
clean:
	rm -f $(OUTSRC)

.PHONY: clean