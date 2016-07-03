//============================================================================
// Name        : DCC888 - First Project: bytecodes to dot
// Authors     : Lucas Duarte Prates
//			   : Luis Eduardo Oliveira Lizardo
// Description : LLVM pass. It prints bytecode programs into the dot format.
// Reference   : http://homepages.dcc.ufmg.br/~fernando/classes/dcc888/assignment/
//============================================================================

#include "llvm/BasicBlock.h"
#include "llvm/Instructions.h"
#include "llvm/Function.h"
#include "llvm/Pass.h"
#include "llvm/User.h"
#include "llvm/Support/CFG.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/Support/Casting.h"

// @see https://llvm.org/svn/llvm-project/llvm/tags/RELEASE_32/final/include/llvm/Instruction.def

// Terminator Instructions
#define RET 1
#define BR 2
#define SWITCH 3
#define INDIRECTBR 4
#define INVOKE 5
#define RESUME 6
#define UNREACHABLE 7

// Standard binary operators
#define ADD 8
#define FADD 9
#define SUB 10
#define FSUB 11
#define MUL 12
#define FMUL 13
#define UDIV 14
#define SDIV 15
#define FDIV 16
#define UREM 17
#define SREM 18
#define FREM 19

// Logical operators
#define Shl 20
#define LShr 21
#define AShr 22
#define And 23
#define Or 24
#define Xor 25

// Memory operators
#define ALLOCA 26
#define LOAD 27
#define STORE 28
#define GET_ELEMENT_PTR 29
#define FENCE 30
#define ATOMIC_CMP_XCHG 31
#define ATOMIC_RMW 32

// Cast operators
#define TRUNC 33
#define ZEXT 34
#define SEXT 35
#define FPTOUI 36
#define FPTOSI 37
#define UITOFP 38
#define SITOFP 39
#define FPTRUNC 40
#define FPEXT 41
#define PTRTOINT 42
#define INTTOPTR 43
#define BITCAST 44

// Other operators
#define ICMP 45
#define FCMP 46
#define PHI 47
#define CALL 48
#define SELECT 49
#define USER_OP_1 50//
#define USER_OP_2 51//
#define VAARG 52
#define EXTRACT_ELEMENT 53
#define INSERT_ELEMENT 54
#define SHUFFLE_VECTOR 55
#define EXTRACT_VALUE 56
#define INSERT_VALUE 57
#define LANDINGPAD 58

using namespace llvm;

namespace {
struct DotPrint: public FunctionPass {
	static char ID;

	std::string errorOut;
	raw_fd_ostream file;

	// BasicBlocks and Operands counters.
	unsigned int BB_counter;
	unsigned int OP_counter;

	// BasicBlocks and Operands counters.
	StringMap<int> basicBlocksMap;
	StringMap<int> adressesMap;

	DotPrint() :
			FunctionPass(ID), file("out.dot", errorOut) {
		BB_counter = -1;
		OP_counter = -1;
	}

	virtual bool runOnFunction(Function &F) {

		// Open digraph
		file << "digraph \"CFG for \'" + F.getName() + "\' function\" {\n";

		// Iterates over the basic blocks
		for (Function::iterator BB_iterator = F.begin(), bb_end = F.end();
				BB_iterator != bb_end; ++BB_iterator) {
			BasicBlock* currBB = BB_iterator;
			StringRef BBName = currBB->getName();

			// Stores the basic block in the map. Each discovered basic block receives an unique number in the map.
			basicBlocksMap.GetOrCreateValue(BBName, ++BB_counter);

			file << "\tBB" << basicBlocksMap[BBName]
					<< " [shape=record, label=\"{";
			file << "BB" << basicBlocksMap[BBName] << ":\\l\\l";

			// Iterates over the instructions of the basic block.
			for (BasicBlock::iterator inst_iterator = currBB->begin(),
					inst_end = currBB->end(); inst_iterator != inst_end;
					++inst_iterator) {
				Instruction* currInst = inst_iterator;

				// Parses the instruction.
				parse_instruction(currInst);
			}

			file << "}\"];\n";  //Closes BasicBlock

			// Iterates over the successors of the basic block to print the edges between them.
			for (succ_iterator succBB_iterator = succ_begin(currBB),
					succBB_end = succ_end(currBB);
					succBB_iterator != succBB_end; ++succBB_iterator) {
				BasicBlock *succBB = *succBB_iterator;
				file << "\tBB" << basicBlocksMap[BBName] << " -> BB"
						<< basicBlocksMap[succBB->getName()] << ";\n";
			}

		}

		file << "}\n"; //Closes function

		return false;
	}

	void parse_instruction(Instruction* inst) {

		StringRef instName;

		// Get instruction name
		if (inst->hasName()) {
			instName = inst->getName();
			adressesMap.GetOrCreateValue(instName, ++OP_counter);
		} else {
			instName = "";
		}

		// Switch over the instruction opcode. The defined opcode numbers are for release 3.2.
		// @see https://llvm.org/svn/llvm-project/llvm/tags/RELEASE_32/final/include/llvm/Instruction.def
		switch (inst->getOpcode()) {

		case RET:
		case RESUME: {
			file << inst->getOpcodeName() << " ";
			if (inst->getNumOperands() == 1) {
				StringRef value = inst->getOperand(0)->getName();
				file << value;
			}
			file << "\\l";
			break;
		}

		case BR: {
			if (inst->getNumOperands() == 3) {
				StringRef cond = inst->getOperand(0)->getName();
				StringRef iftrue = inst->getOperand(1)->getName();
				StringRef iffalse = inst->getOperand(2)->getName();

				adressesMap.GetOrCreateValue(cond, ++OP_counter);
				basicBlocksMap.GetOrCreateValue(iftrue, ++BB_counter);
				basicBlocksMap.GetOrCreateValue(iffalse, ++BB_counter);

				file << inst->getOpcodeName() << " %" << adressesMap[cond]
						<< " BB" << basicBlocksMap[iftrue] << " BB"
						<< basicBlocksMap[iffalse] << "\\l";

			} else {
				StringRef dest = inst->getOperand(0)->getName();
				basicBlocksMap.GetOrCreateValue(dest, ++BB_counter);
				file << inst->getOpcodeName() << " BB" << basicBlocksMap[dest]
						<< "\\l";
			}
			break;
		}

		case SWITCH: {
			StringRef value = inst->getOperand(0)->getName();
			StringRef label = inst->getOperand(1)->getName();

			adressesMap.GetOrCreateValue(value, ++OP_counter);
			basicBlocksMap.GetOrCreateValue(label, ++BB_counter);

			file << inst->getOpcodeName() << " %" << adressesMap[value] << " BB"
					<< basicBlocksMap[label] << " [";

			for (unsigned i = 2; i < inst->getNumOperands(); i += 2) {
				value = inst->getOperand(i)->getName();
				label = inst->getOperand(i + 1)->getName();
				adressesMap.GetOrCreateValue(value, ++OP_counter);
				basicBlocksMap.GetOrCreateValue(label, ++BB_counter);

				file << " %" << adressesMap[value] << ", BB"
						<< basicBlocksMap[label] << " ";
			}

			file << "]\\l";

			break;
		}

		case INDIRECTBR: {
			StringRef address = inst->getOperand(0)->getName();

			basicBlocksMap.GetOrCreateValue(address, ++BB_counter);

			file << inst->getOpcodeName() << " BB" << adressesMap[address]
					<< " [";

			for (unsigned i = 1; i < inst->getNumOperands(); ++i) {
				address = inst->getOperand(i)->getName();
				basicBlocksMap.GetOrCreateValue(address, ++BB_counter);

				file << " BB" << adressesMap[address];
			}

			file << "]\\l";

			break;
		}

		case INVOKE: {
			InvokeInst *invoke = dyn_cast<InvokeInst>(inst);

			if (instName != "") {
				file << "%" << adressesMap[instName] << " = ";
			}

			file << inst->getOpcodeName() << " @"
					<< invoke->getCalledFunction()->getName() << "(";
			for (unsigned i = 0; i < invoke->getNumArgOperands(); ++i) {
				StringRef arg = invoke->getArgOperand(i)->getName();
				if (arg != "") {
					adressesMap.GetOrCreateValue(arg, ++OP_counter);
					file << " %" << adressesMap[arg] << " ";
				}
			}
			file << "),";

			StringRef normal = inst->getOperand(1)->getName();
			StringRef exception = inst->getOperand(2)->getName();
			basicBlocksMap.GetOrCreateValue(normal, ++BB_counter);
			basicBlocksMap.GetOrCreateValue(exception, ++BB_counter);

			file << " BB" << basicBlocksMap[normal] << ", BB"
					<< basicBlocksMap[exception] << "\\l";

			break;
		}

		case UNREACHABLE: {
			file << inst->getOpcodeName() << "\\l";
			break;
		}

			// two operands instructions
		case ADD:
		case FADD:
		case SUB:
		case FSUB:
		case MUL:
		case FMUL:
		case UDIV:
		case SDIV:
		case FDIV:
		case UREM:
		case SREM:
		case FREM:
		case Shl:
		case LShr:
		case AShr:
		case And:
		case Or:
		case Xor: {
			StringRef op1 = inst->getOperand(0)->getName();
			StringRef op2 = inst->getOperand(1)->getName();

			adressesMap.GetOrCreateValue(op1, ++OP_counter);
			adressesMap.GetOrCreateValue(op2, ++OP_counter);

			file << "%" << adressesMap[instName] << " = "
					<< inst->getOpcodeName() << " %" << adressesMap[op1]
					<< ", %" << adressesMap[op2] << "\\l";

			break;
		}

		case STORE:
		case ATOMIC_RMW: {

			StringRef op1 = inst->getOperand(0)->getName();
			StringRef op2 = inst->getOperand(1)->getName();

			adressesMap.GetOrCreateValue(op1, ++OP_counter);
			adressesMap.GetOrCreateValue(op2, ++OP_counter);

			file << inst->getOpcodeName() << " %" << adressesMap[op1] << ", %"
					<< adressesMap[op2] << "\\l";

			break;
		}

		case ATOMIC_CMP_XCHG: {
			StringRef op1 = inst->getOperand(0)->getName();
			StringRef op2 = inst->getOperand(1)->getName();
			StringRef op3 = inst->getOperand(2)->getName();

			adressesMap.GetOrCreateValue(op1, ++OP_counter);
			adressesMap.GetOrCreateValue(op2, ++OP_counter);
			adressesMap.GetOrCreateValue(op3, ++OP_counter);

			file << inst->getOpcodeName() << " %" << adressesMap[op1] << ", %"
					<< adressesMap[op2] << ", %" << adressesMap[op3] << "\\l";

			break;
		}

		case ALLOCA:
		case LOAD:
		case GET_ELEMENT_PTR:
		case TRUNC:
		case ZEXT:
		case SEXT:
		case FPTOUI:
		case FPTOSI:
		case UITOFP:
		case SITOFP:
		case FPTRUNC:
		case FPEXT:
		case PTRTOINT:
		case INTTOPTR:
		case BITCAST:
		case EXTRACT_VALUE:
		case INSERT_VALUE:
		case LANDINGPAD:
		case EXTRACT_ELEMENT:
		case INSERT_ELEMENT:
		case SHUFFLE_VECTOR:
		case VAARG: {
			file << "%" << adressesMap[instName] << " = "
					<< inst->getOpcodeName();
			for (unsigned i = 0; i < inst->getNumOperands(); ++i) {
				StringRef op = inst->getOperand(i)->getName();
				if (op != "") {
					adressesMap.GetOrCreateValue(op, ++OP_counter);
					file << " %" << adressesMap[op];
				}
			}
			file << "\\l";
			break;
		}

		case FENCE: {
			file << inst->getOpcodeName();
			StringRef op1 = inst->getOperand(0)->getName();

			adressesMap.GetOrCreateValue(op1, ++OP_counter);

			file << " %" << adressesMap[op1] << "\\l";
			break;
		}

		case ICMP: {
			StringRef cond = handle_icmp(inst);
			StringRef op1 = inst->getOperand(0)->getName();
			StringRef op2 = inst->getOperand(1)->getName();

			adressesMap.GetOrCreateValue(op1, ++OP_counter);
			adressesMap.GetOrCreateValue(op2, ++OP_counter);

			file << "%" << adressesMap[instName] << " = "
					<< inst->getOpcodeName() << "-" << cond << " %"
					<< adressesMap[op1] << ", %" << adressesMap[op2] << "\\l";
			break;
		}

		case FCMP: {
			StringRef cond = handle_fcmp(inst);
			StringRef op1 = inst->getOperand(0)->getName();
			StringRef op2 = inst->getOperand(1)->getName();

			adressesMap.GetOrCreateValue(op1, ++OP_counter);
			adressesMap.GetOrCreateValue(op2, ++OP_counter);

			file << "%" << adressesMap[instName] << " = "
					<< inst->getOpcodeName() << "-" << cond << " %"
					<< adressesMap[op1] << ", %" << adressesMap[op2] << "\\l";
			break;
		}

		case PHI: {
			PHINode *phi = dyn_cast<PHINode>(inst);
			file << "%" << adressesMap[instName] << " = "
					<< inst->getOpcodeName();

			for (unsigned i = 0; i < phi->getNumOperands(); ++i) {
				StringRef value = phi->getIncomingValue(i)->getName();
				StringRef block = phi->getIncomingBlock(i)->getName();

				adressesMap.GetOrCreateValue(value, ++OP_counter);
				basicBlocksMap.GetOrCreateValue(block, ++BB_counter);

				if (i > 0) {
					file << ",";
				}
				file << " [ %" << adressesMap[value] << ", BB"
						<< basicBlocksMap[block] << " ]";
			}
			file << "\\l";
			break;
		}

		case CALL: {
			CallInst *call = dyn_cast<CallInst>(inst);

			file << "%" << adressesMap[instName] << " = "
					<< inst->getOpcodeName() << " @"
					<< call->getCalledFunction()->getName() << "(";
			for (unsigned i = 0; i < call->getNumArgOperands(); ++i) {
				StringRef arg = call->getArgOperand(i)->getName();
				if (arg != "") {
					adressesMap.GetOrCreateValue(arg, ++OP_counter);
					file << " %" << adressesMap[arg] << " ";
				}
			}
			file << ")\\l";
			break;
		}

		case SELECT: {
			StringRef cond = inst->getOperand(0)->getName();
			StringRef val1 = inst->getOperand(1)->getName();
			StringRef val2 = inst->getOperand(2)->getName();

			adressesMap.GetOrCreateValue(cond, ++OP_counter);
			adressesMap.GetOrCreateValue(val1, ++OP_counter);
			adressesMap.GetOrCreateValue(val2, ++OP_counter);

			file << "%" << adressesMap[instName] << " = "
					<< inst->getOpcodeName() << " %" << adressesMap[cond]
					<< ", %" << adressesMap[val1] << ", %" << adressesMap[val2]
					<< "\\l";

			break;
		}

		default:
			file << *inst << "\\l";
			break;
		}

	}

	/*
	 * Receives an icmp instruction and returns its predicate as string.
	 */
	StringRef handle_icmp(Instruction* inst) {
		if (const ICmpInst *ICC = dyn_cast<ICmpInst>(inst)) {
			switch (ICC->getSignedPredicate()) {

			case CmpInst::ICMP_EQ:
				return "eq";
				break; // equal
			case CmpInst::ICMP_NE:
				return "ne";
				break; // not equal
			case CmpInst::ICMP_UGT:
				return "ugt";
				break; // unsigned greater than
			case CmpInst::ICMP_UGE:
				return "uge";
				break; // unsigned greater or equal
			case CmpInst::ICMP_ULT:
				return "uge";
				break; // unsigned less than
			case CmpInst::ICMP_ULE:
				return "uge";
				break; // unsigned less or equal
			case CmpInst::ICMP_SGT:
				return "sgt";
				break; // signed greater than
			case CmpInst::ICMP_SGE:
				return "sge";
				break; // signed greater or equal
			case CmpInst::ICMP_SLT:
				return "slt";
				break; // signed less than
			case CmpInst::ICMP_SLE:
				return "sle";
				break; // signed less or equal
			default:
				return "";

			}
		}
		return "";
	}

	/*
	 * Receives an fcmp instruction and returns its predicate as string.
	 */
	StringRef handle_fcmp(Instruction* inst) {
		if (const FCmpInst *ICC = dyn_cast<FCmpInst>(inst)) {
			switch (ICC->getPredicate()) {

			case FCmpInst::FCMP_FALSE:
				return "false";
				break;
			case FCmpInst::FCMP_OEQ:
				return "oeq";
				break;
			case FCmpInst::FCMP_OGE:
				return "oge";
				break;
			case FCmpInst::FCMP_OGT:
				return "ogt";
				break;
			case FCmpInst::FCMP_OLE:
				return "ole";
				break;
			case FCmpInst::FCMP_OLT:
				return "olt";
				break;
			case FCmpInst::FCMP_ONE:
				return "one";
				break;
			case FCmpInst::FCMP_ORD:
				return "ord";
				break;
			case FCmpInst::FCMP_TRUE:
				return "true";
				break;
			case FCmpInst::FCMP_UEQ:
				return "ueq";
				break;
			case FCmpInst::FCMP_UGE:
				return "uge";
				break;
			case FCmpInst::FCMP_UGT:
				return "ugt";
				break;
			case FCmpInst::FCMP_ULE:
				return "ule";
				break;
			case FCmpInst::FCMP_ULT:
				return "ult";
				break;
			case FCmpInst::FCMP_UNE:
				return "une";
				break;
			case FCmpInst::FCMP_UNO:
				return "uno";
				break;
			default:
				return "";

			}
		}
		return "";
	}

};
}

char DotPrint::ID = 0;
static RegisterPass<DotPrint> X("dotprint", "Bytecode to Dot Pass");

