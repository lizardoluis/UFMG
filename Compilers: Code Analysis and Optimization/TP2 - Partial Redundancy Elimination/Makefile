# Makefile for DeadCodeElimination pass

# Path to top level of LLVM hierarchy
LEVEL = ../../..

# Path to test level
TEST = test

# Name of the library to build
LIBRARYNAME = DeadCodeElimination

# Make the shared library become a loadable module so the tools can
# dlopen/dlsym on the resulting library.
LOADABLE_MODULE = 1

# Include the makefile implementation stuff
include $(LEVEL)/Makefile.common

# Make the .c test file
file:
	clang -c -emit-llvm $(TEST)/test.c -o $(TEST)/test.bc
	opt -instnamer -mem2reg -break-crit-edges $(TEST)/test.bc -o $(TEST)/test.bc
	opt -load $(LEVEL)/Debug+Asserts/lib/vSSA.so -vssa $(TEST)/test.bc -o $(TEST)/test.essa.bc
	
# Run the pass in the test file
run:
	opt -stats -load $(LEVEL)/Debug+Asserts/lib/RangeAnalysis.so -load $(LEVEL)/Debug+Asserts/lib/DeadCodeElimination.so -deadcode-elimination $(TEST)/test.essa.bc

# Run the range_analysis pass	
range:
	opt -load $(LEVEL)/Debug+Asserts/lib/RangeAnalysis.so -load $(LEVEL)/Debug+Asserts/lib/ClientRA.so -client-ra $(TEST)/test.essa.bc