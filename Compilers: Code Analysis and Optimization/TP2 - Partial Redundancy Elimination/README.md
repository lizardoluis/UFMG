* TP2: Partial Redundancy Elimination *

- Lucas Duarte Prates
- Luis Eduardo Oliveira Lizardo

Command line to run the pass:
	
	opt -stats -load /llvm/Debug+Asserts/lib/RangeAnalysis.so -load /llvm/Debug+Asserts/lib/DeadCodeElimination.so -deadcode-elimination filename.essa.bc
