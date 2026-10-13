// RUN: my-opt %s -fold-add-zero | FileCheck %s

// CHECK-LABEL: func.func @rhs_zero
// CHECK-NOT: artih.addi
// CHECK: return %[[X:.*]] : i32
func.func @rhs_zero(%x: i32) -> i32 {
    %zero = arith.constant 0 : i32
    %sum = arith.addi %x, %zero : i32
    func.return %sum : i32
}

// CHECK-LABEL: func.func @rhs_zero
// CHECK-NOT: artih.addi
// CHECK: return %[[X:.*]] : i32
func.func @lhs_zero(%x: i32) -> i32 {
    %zero = arith.constant 0 : i32
    %sum = arith.addi %zero, %x : i32
    func.return %sum : i32
}

// CHECK-LABEL: func.func @non_zero
// CHECK: %[[SUM:.*]] = arith.addi %[[X:.*]], %[[Y:.*]] : i32
// CHECK: return %[[SUM]] : i32
func.func @non_zero(%x: i32, %y: i32) -> i32 {
  %sum = arith.addi %x, %y : i32
  return %sum : i32
}