// matrix.cpp — your implementation file
//
// BEFORE YOU START: read through Matrix.h carefully. Every method listed there
// needs an implementation here.
//
// SUGGESTED ORDER:
//   1. Constructor(size_t, size_t)  +  Destructor   — get memory working first
//   2. operator()(row, col)                          — verify you can read/write
//   3. Copy constructor + copy assignment            — test with a simple copy
//   4. Move constructor + move assignment            — test with std::move(mat)
//   5. fill(), print()                               — useful for all later tests
//   6. operator+=, operator-=, operator*=, operator/=
//   7. matmul()                                      — the tricky one
//   8. apply(), transpose()
//   9. Static factories: zeros(), ones(), random(), identity()
//  10. Non-member operators (+, -, *, /)             — thin wrappers, should be short

#include "Matrix.h"
#include <iostream>
#include <random>
#include <stdexcept>
#include <iomanip>

// Remember: because Matrix is a template, every method definition needs the
// template prefix and the <T> suffix on the class name, e.g.:
//
//   template <typename T>
//   Matrix<T>::Matrix(size_t rows, size_t cols) { ... }

// TODO: implement all methods declared in Matrix.h



// =============================================================================
// Explicit template instantiations — keep at the bottom of the file.
// This tells the compiler to generate concrete code for float and double.
// Without this, the linker will not find the symbols when matrix.cpp is a
// separate translation unit.
// =============================================================================
template class Matrix<float>;
template class Matrix<double>;
