# FoldAddZero RewritePattern
message(STATUS "Configuring Fold Add Zero Pass")
add_mlir_library(FoldAddZeroPass
    fold-add-zero-rewrite.cpp

    LINK_LIBS PUBLIC
    MLIRArithDialect
    MLIRFuncDialect
    MLIRPass
    MLIRTransforms
)
