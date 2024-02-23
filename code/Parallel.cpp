#include <stdexcept>

#include "Parallel.h"

/************************************************
 *            Helper Functions
 ************************************************/
void Matrix::construct(u_int r, u_int c, int elem) {
  rows_ = r;
  cols_ = c;
  data_ = new int*[rows_];
  for (u_int r = 0; r < rows_; ++r ) {
    data_[r] = new int[cols_];
    for (u_int c = 0; c < cols_; ++c) {
      data_[r][c] = elem;
    }
  }
}
void Matrix::construct(const Matrix &that) {
  rows_ = that.rows_;
  cols_ = that.cols_;
  data_ = new int*[rows_];
  for (u_int r = 0; r < rows_; ++r ) {
    data_[r] = new int[cols_];
    for (u_int c = 0; c < cols_; ++c) {
      data_[r][c] = that.data_[r][c];
    }
  }
}
void Matrix::destruct() {
  for (u_int r = 0; r < rows_; ++r) {
    delete[] data_[r];
  }
  delete[] data_;
  rows_ = cols_ = 0U;
}

/************************************************
 *            Matrix Operations 
 ************************************************/
auto operator<<(std::ostream &os, const Matrix &m) -> std::ostream & {
  for (u_int r = 0; r < m.rows_; ++r) {
    os << m.data_[r][0];
    for (u_int c = 1; c < m.cols_; ++c) {
      os << ' ' << m.data_[r][c];
    }
    os << std::endl;
  }
  return os;
}
void Matrix::display() const { std::cout << *this << std::endl; }

auto sumOf(const Matrix &m1, const Matrix &m2) -> Matrix {
  if (m1.rows_ != m2.rows_) {
    throw std::domain_error("rows of m1 and m2 don't match?? Impossible!");
  }
  if (m1.cols_ != m2.cols_) {
    throw std::domain_error("columns of m1 and m2 don't match?? Impossible!");
  }

  Matrix res = {m1.rows_, m2.cols_};
  u_int r;
  u_int c;
  #pragma omp parallel for private(r, c)
  for (r = 0; r < m1.rows_; ++r) {
    for (c = 0; c < m1.cols_; ++c) {
      res.data_[r][c] = m1.data_[r][c] + m2.data_[r][c];
    }
  }
  return res;
}

auto traceOf(const Matrix &m) -> long {
  if (m.rows_ != m.cols_) {
    throw std::domain_error("get the trace of matrix with differet rows and cols?? Impossible!");
  }
  long res = 0;
  std::vector<std::thread> threads;
  #pragma omp parallel for reduction(+ : res)
  for (u_int r = 0; r < m.rows_; ++r) {
    res += m.data_[r][r];
  }
  return res;
}

/** implementation of matrix product */
constexpr u_int num_threads = 16U;
/**
 * @return false if reaches end.
 */
auto productHelper(const Matrix &m1, const Matrix &m2, Matrix &res, u_int current) -> bool {
  u_int r;
  u_int c;
  u_int k;
  int sum;
  if (current >= m1.rows_) { return false; }
  /** is_end seems to should have been named 'is_not_end', anyway...*/
  bool is_end = num_threads + current < m1.rows_;
  u_int end = is_end ? num_threads + current : m1.rows_;
  #pragma omp parallel for private(r, sum, c, k)
  for (r = current; r < end; ++r) {
    for (c = 0; c < m2.cols_; ++c) {
      // pitfall: don't jump outside #pragma block.
      // res.data_[r][c] = naiveDotProduct(m1, m2, r, c);
      sum = 0;
      for (k = 0; k < m1.cols_; ++k) {
        sum += m1.data_[r][k] * m2.data_[k][c];
      }
      res.data_[r][c] = sum;
    }
  }
  return is_end;
}
auto productOf(const Matrix &m1, const Matrix &m2) -> Matrix {
  if (m1.cols_ != m2.rows_) {
    throw std::domain_error("size mismatch?? Impossible!");
  }

  Matrix res = {m1.rows_, m2.cols_};
  u_int current = 0U;
  while(productHelper(m1, m2, res, current)) {
    current += num_threads;
  }
  
  return res;
}

auto traceProductHelper(const Matrix &m1, const Matrix &m2, int *cache, u_int current) -> bool {
  u_int r;
  u_int k;
  if (current >= m1.rows_) { return false; }
  bool has_next = m1.rows_ > current + num_threads;
  u_int end = has_next ? current + num_threads : m1.rows_;
  int temp;

  #pragma omp parallel private(r, k, temp)
  for (r = current; r < end; ++r ) {
    temp = 0;
    for (k = 0; k < m1.rows_; ++k) {
      temp += m1.data_[r][k] * m2.data_[k][r];
    }
    cache[r] = temp;
  }
  return has_next;
}
auto traceOfProductOf(const Matrix &m1, const Matrix &m2) -> long {
  long res = 0;
  // without checking.
  int *cache = new int[m1.rows_];
  u_int current = 0U;

  while (traceProductHelper(m1, m2, cache, current)) {
    current += num_threads;
  }

  // calculate the sum of caches.
  for (u_int r = 0; r < m1.rows_; ++r) {
    res += static_cast<long>(cache[r]);
  }

  delete[] cache;
  return res;
}
