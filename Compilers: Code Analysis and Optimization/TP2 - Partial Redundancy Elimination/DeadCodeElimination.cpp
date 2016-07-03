#include "llvm/Function.h"
#include "llvm/Pass.h"
#include "llvm/User.h"
#include "llvm/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/CFG.h"
#include "../RangeAnalysis/RangeAnalysis.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Local.h"

#define ALWAYS_TRUE 1
#define ALWAYS_FALSE -1
#define UNKNOWN 0


using namespace llvm;

STATISTIC(instEliminated, "Number of instructions eliminated");
STATISTIC(bbEliminated, "Number of basic blocks entirely eliminated");

class DeadCodeElimination: public llvm::FunctionPass {
public:
	static char ID;

	DeadCodeElimination() : FunctionPass(ID) {
	}

	virtual bool runOnFunction(Function &F) {

		bbEliminated += countBasicBlocks(&F);
		instEliminated += countInstructions(&F);

		for (Function::iterator BB_iterator = F.begin(), bb_end = F.end(); BB_iterator != bb_end; ++BB_iterator) {
			BasicBlock* bb = BB_iterator;
			simplifyBranches(bb);
		}

		mergeRecursivelyBasicBlocks(dyn_cast<BasicBlock>(F.begin()));

		bbEliminated -= countBasicBlocks(&F);
		instEliminated -= countInstructions(&F);

		return false;
	}

	virtual void getAnalysisUsage(AnalysisUsage &AU) const {
		//AU.setPreservesAll();
		AU.addRequired<InterProceduralRA<Cousot> >();
	}

private:

	void simplifyBranches(BasicBlock *bb) {
		// Get the Basic Block terminator
		Instruction *inst = dyn_cast<Instruction>(bb->getTerminator());

		// If the terminator is a branch
		if (BranchInst *branch = dyn_cast<BranchInst>(inst))
		{
			// if it is a conditional branch
			if (branch->isConditional())
			{
				BasicBlock *predecessor = branch->getParent();
				BasicBlock *successor;
				BasicBlock *deadblock;

				// if the condition is ICMP
				if(ICmpInst *icmp = dyn_cast<ICmpInst>(branch->getCondition())){

					int ICmpStatus = isDeadICmp(icmp);
					if ( ICmpStatus == UNKNOWN ){
						return;
					}
					else if ( ICmpStatus == ALWAYS_TRUE ) {
						deadblock = branch->getSuccessor(1);
						successor = branch->getSuccessor(0);
					}
					else {
						deadblock = branch->getSuccessor(0);
						successor = branch->getSuccessor(1);
					}

					// Creates a unconditional branch
					BranchInst::Create(successor, predecessor);

					// Deletes the old branch
					deleteInstruction(branch);

					// Deletes the icmp instruction
					deleteInstruction(icmp);

					// Delete the dead basic Block
					deleteBasicBlock(deadblock);

				}
				else {
					// if the branch condition is constant true
					if(cast<ConstantInt>(branch->getCondition())->getZExtValue()){
						deadblock = branch->getSuccessor(1);
						successor = branch->getSuccessor(0);
					}
					// if the branch condition is constant false
					else{
						deadblock = branch->getSuccessor(0);
						successor = branch->getSuccessor(1);
					}

					// Creates a unconditional branch
					BranchInst::Create(successor, predecessor);

					// Deletes the old branch
					deleteInstruction(branch);

					// Delete the dead basic Block
					deleteBasicBlock(deadblock);
				}
			}
		}
	}

	/*
	 * Delete an Instruction.
	 */
	void deleteInstruction(Instruction *inst){
		inst->eraseFromParent();
	}

	/*
	 * Delete a Basic Block.
	 */
	void deleteBasicBlock(BasicBlock *bb){
		for (succ_iterator succBB_iterator = succ_begin(bb), succBB_end = succ_end(bb); succBB_iterator != succBB_end; ++succBB_iterator) {
			BasicBlock *succBB = *succBB_iterator;
			resolvePHI(succBB, bb);
		}
		SimplifyInstructionsInBlock(bb);
		bb->eraseFromParent();
	}

	/*
	 * Remove PHI entries of Basic Blocks that is successor of the Basic Block that will be delete.
	 */
	void resolvePHI(BasicBlock *bb, BasicBlock *toDelete){
		for (BasicBlock::iterator inst_iterator = bb->begin(), inst_end = bb->end(); inst_iterator != inst_end; ++inst_iterator) {
			if (PHINode *phiNode = dyn_cast<PHINode>(inst_iterator)) {
				for (unsigned i = 0; i < phiNode->getNumIncomingValues(); i++) {
					if (phiNode->getIncomingBlock(i) == toDelete) {
						phiNode->removeIncomingValue(i, true);
					}
				}
			}
		}
	}

	/*
	 * Returns the number of basic blocks in the function;
	 */
	int countBasicBlocks(Function *F){
		return F->size();
	}

	/*
	 * Returns the number of instructions in the function;
	 */
	int countInstructions(Function *F){
		int numInst = 0;
		for (Function::iterator it = F->begin(), bb_end = F->end(); it != bb_end; ++it) {
			BasicBlock* bb = it;
			numInst += bb->size();
		}
		return numInst;
	}

	/*
	 * Merge the Basic Blocks recursively if it is possible.
	 */
	StringMap <bool> visited;
	void mergeRecursivelyBasicBlocks(BasicBlock *bb){

		if(!visited[bb->getName()]){
			visited[bb->getName()] = true;
			for (succ_iterator PI = succ_begin(bb), E = succ_end(bb); PI != E; ++PI) {
				BasicBlock *succ = *PI;

				mergeRecursivelyBasicBlocks(succ);
			}
		}
		MergeBlockIntoPredecessor(bb);
	}

	/*
	 * Checks by Range Analysis if the branch condition is always true, always false or unknown;
	 */
	int isDeadICmp(ICmpInst *I) {

		InterProceduralRA<Cousot> &ra = getAnalysis<InterProceduralRA<Cousot> >();

		Range range1 = ra.getRange(I->getOperand(0));
		Range range2 = ra.getRange(I->getOperand(1));

		switch (I->getPredicate()) {

		case ICmpInst::ICMP_EQ: // equal
			if (range1.getLower().eq(range1.getUpper()) && range1.getLower().eq(range2.getLower()) && range1.getUpper().eq(range2.getUpper())) return ALWAYS_TRUE;
			if (range1.getUpper().slt(range2.getLower()) || range2.getUpper().slt(range1.getLower())) return ALWAYS_FALSE;
			return UNKNOWN;

		case ICmpInst::ICMP_NE: // not equal
			if (range1.getUpper().slt(range2.getLower()) || range2.getUpper().slt(range1.getLower())) return ALWAYS_TRUE;
			if (range1.getLower().eq(range1.getUpper()) && range1.getLower().eq(range2.getLower()) && range1.getUpper().eq(range2.getUpper())) return ALWAYS_FALSE;
			return UNKNOWN;

		case ICmpInst::ICMP_UGT: // unsigned greater than
			if (range1.getLower().uge(range2.getUpper())) return ALWAYS_TRUE;
			if (range2.getLower().uge(range1.getUpper())) return ALWAYS_FALSE;
			return UNKNOWN;

		case ICmpInst::ICMP_UGE: // unsigned greater or equal
			if (range1.getLower().ugt(range2.getUpper())) return ALWAYS_TRUE;
			if (range2.getLower().ugt(range1.getUpper())) return ALWAYS_FALSE;
			return UNKNOWN;

		case ICmpInst::ICMP_ULT: // unsigned less than
			if (range1.getUpper().ult(range2.getLower())) return ALWAYS_TRUE;
			if (range1.getLower().uge(range2.getLower())) return ALWAYS_FALSE;
			return UNKNOWN;

		case ICmpInst::ICMP_ULE: // unsigned less or equal
			if (range1.getUpper().ule(range2.getLower())) return ALWAYS_TRUE;
			if (range1.getLower().ugt(range2.getLower())) return ALWAYS_FALSE;
			return UNKNOWN;

		case ICmpInst::ICMP_SGT: // signed greater than
			if (range1.getLower().sge(range2.getUpper())) return ALWAYS_TRUE;
			if (range2.getLower().sge(range1.getUpper())) return ALWAYS_FALSE;
			return UNKNOWN;

		case ICmpInst::ICMP_SGE: // signed greater or equal
			if (range1.getLower().sgt(range2.getUpper())) return ALWAYS_TRUE;
			if (range2.getLower().sgt(range1.getUpper())) return ALWAYS_FALSE;
			return UNKNOWN;

		case ICmpInst::ICMP_SLT:  // signed less than
			if (range1.getUpper().slt(range2.getLower())) return ALWAYS_TRUE;
			if (range1.getLower().sge(range2.getLower())) return ALWAYS_FALSE;
			return UNKNOWN;

		case ICmpInst::ICMP_SLE:  // signed less or equal
			if (range1.getUpper().sle(range2.getLower())) return ALWAYS_TRUE;
			if (range1.getLower().sgt(range2.getLower())) return ALWAYS_FALSE;
			return UNKNOWN;

		default:
			return UNKNOWN;
		}
	}
};

char DeadCodeElimination::ID = 0;
static RegisterPass<DeadCodeElimination> X("deadcode-elimination", "Deadcode elimination", false, false);
