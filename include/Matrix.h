#pragma once  // Modern include guard — preferred over #ifndef in C++17

#include <vector>
#include <stdexcept>
#include <string>
#include <functional>
#include <iostream>

// =============================================================================
// Matrix<T> — a 2D matrix backed by a heap-allocated flat array
//
// LEARNING GOALS FOR THIS FILE:
//   1. Templates     — Matrix works for float, double, int, etc.
//   2. RAII          — resource (the data array) is tied to object lifetime
//   3. Rule of Five  — if you manage a resource, define all five special methods
//   4. Operator overloading — make math feel natural
//   5. const-correctness   — mark methods that don't mutate 'const'
// =============================================================================

template <typename T>
class Matrix {
public:

    // -------------------------------------------------------------------------
    // Constructors & Destructor  (Rule of Five — #1 and #2)
    // -------------------------------------------------------------------------

    // Default constructor — creates an empty (0×0) matrix.
    // TIP: use member-initialiser lists (the `: rows_(0), ...` syntax), not
    //      assignments inside the body. It's faster and required for const members.
    Matrix();

    // Construct a rows×cols matrix. All elements should be initialised to 0.
    // CONCEPT: this is where you allocate heap memory. Use 'new T[...]' here
    //          (just this once, so you understand what smart pointers replace).
    Matrix(size_t rows, size_t cols);

    // Construct and fill every element with 'fill_value'.
    Matrix(size_t rows, size_t cols, T fill_value);

    // // Destructor — free the heap memory you allocated above.
    // // CONCEPT: RAII — the destructor is the "release" side of acquire-in-constructor.
    // ~Matrix();

    // Copy constructor — deep-copy another matrix.
    // CONCEPT: without this, the compiler copies the raw pointer, giving two
    //          Matrix objects that think they own the same memory. Disaster.
    Matrix(const Matrix& other);

    // Copy-assignment operator — same idea, but the object already exists.
    // CONCEPT: always handle self-assignment (mat = mat) safely.
    //          Pattern: check, allocate new, copy, free old, update.
    Matrix& operator=(const Matrix& other);

    // Move constructor — "steal" the resource from a temporary Matrix.
    // CONCEPT: instead of copying all data, you take the pointer and leave the
    //          source in a valid-but-empty state (null pointer, zero dimensions).
    //          The 'noexcept' tells the compiler this never throws — important
    //          for STL containers to use moves instead of copies.
    Matrix(Matrix&& other) noexcept;

    // Move-assignment operator — same, for assignment from a temporary.
    Matrix& operator=(Matrix&& other) noexcept;


    // -------------------------------------------------------------------------
    // Element access
    // -------------------------------------------------------------------------

    // Return a reference so callers can write: mat(0, 1) = 3.14f;
    // CONCEPT: two overloads — one for mutable, one for const objects.
    //          The const version returns 'const T&' so the value can't be modified.
    T& operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;

    // Bounds-checked access — throw std::out_of_range if indices are invalid.
    T& at(size_t row, size_t col);
    const T& at(size_t row, size_t col) const;


    // -------------------------------------------------------------------------
    // Shape / metadata  (all const — they don't change the matrix)
    // -------------------------------------------------------------------------

    size_t rows() const;
    size_t cols() const;
    size_t size() const;   // total number of elements (rows * cols)
    bool   empty() const;

    // Raw pointer access — needed later when integrating with BLAS / GPU libs.
    // CONCEPT: returning T* from a const method would let callers mutate data
    //          through a const object — so we need both versions again.
    T*       data();
    const T* data() const;


    // -------------------------------------------------------------------------
    // Arithmetic operators
    // -------------------------------------------------------------------------

    // CONCEPT: member operators (op= variants) modify *this and return *this&.
    //          Free (friend) operators create a new object — implement them in
    //          terms of op= to avoid duplicating logic.

    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator*=(T scalar);       // element-wise scalar multiply
    Matrix& operator/=(T scalar);


    // -------------------------------------------------------------------------
    // Matrix operations (declared here, defined in matrix.cpp)
    // -------------------------------------------------------------------------

    // Matrix multiplication — returns a new (this->rows × rhs.cols) matrix.
    // Throw std::invalid_argument if dimensions are incompatible.
    Matrix matmul(const Matrix& rhs) const;

    // Element-wise operations — apply a unary function to every element.
    // CONCEPT: std::function<T(T)> is a type-erased callable — it can hold a
    //          lambda, a function pointer, or a functor.
    Matrix apply(std::function<T(T)> fn) const;

    // Transpose — return a new matrix with rows and cols swapped.
    Matrix transpose() const;

    // Fill every element with 'value' (useful for zeroing gradients).
    void fill(T value);

    // Print a human-readable representation to stdout (handy for debugging).
    void print(const std::string& label = "") const;


    // -------------------------------------------------------------------------
    // Static factory helpers
    // -------------------------------------------------------------------------

    // Return a rows×cols matrix filled with zeros.
    static Matrix zeros(size_t rows, size_t cols);

    // Return a rows×cols matrix filled with ones.
    static Matrix ones(size_t rows, size_t cols);

    // Return a rows×cols matrix with values drawn from a uniform distribution
    // on [low, high).  You can use <random> from the standard library.
    static Matrix random(size_t rows, size_t cols, T low = T(0), T high = T(1));

    // Return an n×n identity matrix.
    static Matrix identity(size_t n);


private:

    // -------------------------------------------------------------------------
    // Data members
    // -------------------------------------------------------------------------

    size_t rows_;   // number of rows
    size_t cols_;   // number of columns
    T*     data_;   // heap-allocated flat array, row-major order
                    // element (r, c)  lives at  data_[r * cols_ + c]

    // -------------------------------------------------------------------------
    // Private helper
    // -------------------------------------------------------------------------

    // Bounds check — call this from at() and operator().
    // Throwing from a helper keeps the public methods clean.
    void check_bounds(size_t row, size_t col) const;
};


// =============================================================================
// Non-member arithmetic operators
//
// CONCEPT: these are free functions, not members, so both operands are treated
//          symmetrically.  Implement each in terms of the op= member above.
// =============================================================================

template <typename T>
Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs);  // note: lhs by value (copy)

template <typename T>
Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs);

template <typename T>
Matrix<T> operator*(Matrix<T> lhs, T scalar);

template <typename T>
Matrix<T> operator*(T scalar, Matrix<T> rhs);               // scalar * Matrix

template <typename T>
Matrix<T> operator/(Matrix<T> lhs, T scalar);


// =============================================================================
// Common type aliases  — use these throughout the rest of the project
// =============================================================================

using Matrixf = Matrix<float>;   // single precision (default for NNs)
using Matrixd = Matrix<double>;  // double precision
