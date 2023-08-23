# Compiler
COMP = g++

# Output
OUT = ./build/mockup.exe

# Sources
SRCS = ./mockup.cpp ./lib/compiler/compiler.cpp ./lib/scopeTree/scopeTree.cpp ./lib/scopeTree/treeNode.cpp ./lib/scopeTree/treeBuilder.cpp

all: $(OUT)

$(OUT): $(SRCS)
	$(COMP) $(SRCS) -o $(OUT)

clean:
	rm -f $(OUT)

.PHONY: clean