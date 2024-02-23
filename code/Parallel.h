#pragma once

#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using u_int = unsigned int;

class Matrix;
/** get the product of a matrix. */
auto productOf(const Matrix &m1, const Matrix &m2) -> Matrix;

/** sometimes you need to calculate the trace of the product of two matrices. */
auto traceOfProductOf(const Matrix &m1, const Matrix &m2) -> long;

/** simple 2D matrix class */
class Matrix {
 private:
  /** construct the matrix. */
  void construct(u_int r, u_int c, int elem);  
  /** construct using that matrix. */
  void construct(const Matrix &that);
  /** clear all data memebers. */
  void destruct();

 public:
  int **data_{nullptr};
  unsigned int rows_{0U};   // number of rows.
  unsigned int cols_{0U};   // number of columns.

  Matrix() = default;
  Matrix(const Matrix &that) { construct(that); }

  /**
   * @brief construct matrix using row size and col size.
   * @param elem(optional): the value of all entries in the matrix(default 0).
   */
  Matrix(unsigned int r, unsigned int c, int elem = 0) {
    construct(r, c, elem);
  }
  Matrix(unsigned int r, int elem = 0) {
    construct(r, r, elem);
  }

  void construct(u_int r) {
    construct(r, r, 0);
  }
  auto numRows() const -> unsigned int { return rows_; }
  auto elementAt(int r = 0, int c = 0) -> int & { return data_[r][c]; }
  auto elementAt(int r = 0, int c = 0) const -> const int & { return data_[r][c]; }

  auto operator=(const Matrix &that) -> Matrix & {
    if (this == &that) { return *this; }
    if (static_cast<bool>(data_)) { destruct(); }
    construct(that);
    return *this;
  }

  /** the product of this and that. */
  auto productOf(const Matrix &that) const -> Matrix {
    return ::productOf(*this, that);
  }
  /** the trace of this and that. */
  auto traceOfProductOf(const Matrix &that) -> long {
    return ::traceOfProductOf(*this, that);
  }

  ~Matrix() {
    destruct();
  }
  
  /** if you are done with a matrix. */
  void clear() { destruct(); }

  /** print the matrix to std::cout. */
  void display() const;
};

/** Print matrix to output stream. */
auto operator<<(std::ostream &os, const Matrix &m) -> std::ostream &;

/** get the sum of two matrices */
auto sumOf(const Matrix &m1, const Matrix &m2) -> Matrix;

/** get the trace of a matrix. */
auto traceOf(const Matrix &m) -> long;
