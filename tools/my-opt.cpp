#include "lib/fold-add-zero-rewrite.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"

int main(int argc, char **argv) {
    mlir::DialectRegistry registry;

    registry.insert<
        mlir::arith::ArithDialect,
        mlir::func::FuncDialect
    >();

    mlir::registerFoldAddZeroPass();

    return mlir::asMainReturnCode(
        mlir::MlirOptMain(argc, argv, "My OPT Pass Driver", registry));
}