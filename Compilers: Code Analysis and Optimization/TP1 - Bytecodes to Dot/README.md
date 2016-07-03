# TP1: Bytecodes to Dot

Lucas Duarte Prates
Luis Eduardo Oliveira Lizardo

Command line to run the pass:

	opt -instnamer -load /llvm/Release+Asserts/lib/dotprint.so -dotprint < fileName.bc > /dev/null

The output of the pass will be printed on the out.dot file, on the current directory.
