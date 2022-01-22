#include <iostream>
#include <cmath>
#include <vector>

/// Точка
template <class Number>
class Point {
  using ThisT = Point;
 public:
  Point(Number x, Number y) : x(x), y(y) {}
  Point() : ThisT(static_cast<Number>(0), static_cast<Number>(0)) {}

  Number const x;
  Number const y;
};


/// Проверка валидности параметров эллиптической группы
template <class Integer>
bool IsValidGroupParams(Integer a, Integer b, Integer modulus) {
  static auto const isPrime = [](Integer m){ return true; };

  if (a >= modulus || b >= modulus || !isPrime(modulus))
    return false;

  Integer r = static_cast<Integer>(4 * std::pow(a, 3) + 27 * std::pow(b, 2)) % modulus;
  return 0 != r;
}


/// Эллиптическая группа
template <class Integer>
class CurveGroup {
 public:
  CurveGroup(Integer a, Integer b, Integer modulus) : a(a), b(b), M(modulus) {
    if (!IsValidGroupParams(a, b, modulus))
      throw std::runtime_error("Invalid arguments");
  }

  Integer GetNegative(Integer v) const {
    return M - v;
  }

  std::vector<Integer> GetSqrt(Integer v) const {
    using RT = std::vector<Integer>;

    for (Integer s = 0; s < M; ++s) {
      if ((s * s) % M == v)
        return s == 0 ? RT{0} : RT{s, GetNegative(s)};
    }
    return {};
  }

  std::vector<Point<Integer>> GetPoints() const {
    std::vector<Point<Integer>> points;

    for (Integer x = 0; x < M; ++x) {
      Integer y_pow = static_cast<Integer>(std::pow(x, 3) + a * x + b) % M;
      for (auto y : GetSqrt(y_pow))
        points.push_back(Point<Integer>(x, y));
    }

    return points;
  }

  Integer const a;
  Integer const b;
  Integer const M;
};


int main() {
  int a = 1;
  int b = 1;
  int M = 73;
  CurveGroup<int> group(a, b, M);
  auto points = group.GetPoints();

  std::cout << "a: " << a << std::endl;
  std::cout << "b: " << b << std::endl;
  std::cout << "M: " << M << std::endl;
  std::cout << "Calculated " << points.size() << " points:" << std::endl;

  for (auto [x, y] : points) {
    std::cout << x << " " << y << std::endl;
  }

  return 0;
}
