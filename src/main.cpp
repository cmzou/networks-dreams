// main.cpp — use this file as your personal scratchpad for testing.
// Each phase will give you new things to test here.
//
// HOW TO BUILD & RUN (from the project root):
//
//   mkdir -p build && cd build
//   cmake -DCMAKE_BUILD_TYPE=Debug ..
//   make -j4
//   ./nn_train
//
// The Debug build turns on AddressSanitizer automatically (see CMakeLists.txt).
// Any memory error will print a clear report instead of silently corrupting data.

#include "Matrix.h"
#include <iostream>

int main() {

    // -------------------------------------------------------------------------
    // Checkpoint 1 — construction & element access
    // Uncomment each block as you implement the corresponding methods.
    // -------------------------------------------------------------------------

    Matrixf m(3, 4);
    m.print("empty 3x4");

    // -------------------------------------------------------------------------
    // Checkpoint 2 — fill & operator()
    // -------------------------------------------------------------------------

    // Matrixf a(2, 3, 1.0f);   // fill constructor
    // a(0, 0) = 9.0f;
    // a.print("a after fill + edit");

    // -------------------------------------------------------------------------
    // Checkpoint 3 — copy semantics (should NOT share memory)
    // -------------------------------------------------------------------------

    // Matrixf b = a;           // copy constructor
    // b(0, 0) = 0.0f;
    // a.print("a (should be unchanged)");
    // b.print("b (0,0 should be 0)");

    // -------------------------------------------------------------------------
    // Checkpoint 4 — move semantics
    // -------------------------------------------------------------------------

    // Matrixf c = std::move(b);   // move constructor — b should now be empty
    // c.print("c (moved-into)");
    // std::cout << "b rows after move: " << b.rows() << "\n";  // should be 0

    // -------------------------------------------------------------------------
    // Checkpoint 5 — arithmetic
    // -------------------------------------------------------------------------

    // Matrixf x = Matrixf::ones(2, 3);
    // Matrixf y = Matrixf::ones(2, 3);
    // (x + y).print("x + y (should all be 2)");
    // (x * 3.0f).print("x * 3 (should all be 3)");

    // -------------------------------------------------------------------------
    // Checkpoint 6 — matmul
    // -------------------------------------------------------------------------

    // Matrixf A = Matrixf::random(2, 3);
    // Matrixf B = Matrixf::random(3, 4);
    // A.matmul(B).print("A @ B  (should be 2x4)");

    // -------------------------------------------------------------------------
    // Checkpoint 7 — apply & transpose
    // -------------------------------------------------------------------------

    // auto relu = [](float x) { return x > 0.0f ? x : 0.0f; };
    // Matrixf r = Matrixf::random(3, 3, -1.0f, 1.0f);
    // r.print("before relu");
    // r.apply(relu).print("after relu");
    // r.transpose().print("transposed");

    return 0;
}
