# my-opt tool
message(STATUS "Configuring my-opt")
set (LIBS
    FoldAddZeroPass
    MLIROptLib
    MLIRArithDialect
    MLIRFuncDialect
)

add_llvm_executable(my-opt my-opt.cpp)
llvm_update_compile_flags(my-opt)
target_link_libraries(my-opt PRIVATE ${LIBS})

mlir_check_all_link_libraries(my-opt)
