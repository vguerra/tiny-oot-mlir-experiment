#include "fold-add-zero-rewrite.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Matchers.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "llvm/Support/LogicalResult.h"

using namespace mlir;
using namespace llvm;

namespace {

struct FoldAddZero final : OpRewritePattern<arith::AddIOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult
  matchAndRewrite(arith::AddIOp op,
                  PatternRewriter &rewriter) const override {
    if (matchPattern(op.getLhs(), m_Zero())) {
      // If the right operand is zero, replace the add with the left.
      rewriter.replaceOp(op, op.getRhs());
      return success();
    }
    
    if (matchPattern(op.getRhs(), m_Zero())) {
      // If the left operand is zero, replace the add with the right.
      rewriter.replaceOp(op, op.getLhs());
      return success();
    }
    
    // Report a match failure if neither operand is zero.
    return rewriter.notifyMatchFailure(op, "neither of arguments are Zero");
  }
};

struct FoldAddZeroPass final
    : PassWrapper<FoldAddZeroPass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(FoldAddZeroPass)

  StringRef getArgument() const final { return "fold-add-zero"; }

  StringRef getDescription() const final {
    return "Replace integer additions with zero";
  }

  void runOnOperation() override {
    RewritePatternSet patterns(&getContext());
    patterns.add<FoldAddZero>(&getContext());

    if (failed(applyPatternsGreedily(
            getOperation(), std::move(patterns))))
      signalPassFailure();
  }
};

} // namespace

void mlir::registerFoldAddZeroPass() {
  static PassRegistration<FoldAddZeroPass> registration;
}