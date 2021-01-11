#include "transformation.hpp"

namespace draw::transform {

Transformation::Transformation() : A_prime(glm::mat3(1.f)) {}

Transformation &Transformation::translate(float x, float y) {
  A_prime[0][2] += x;
  A_prime[1][2] += y;

  return *this;
}

Transformation &Transformation::translate_x(float x) {
  return translate(x, 0.f);
}

Transformation &Transformation::translate_y(float y) {
  return translate(0.f, y);
}

Transformation &Transformation::scale(float x, float y) {
  A_prime[0][0] *= x;
  A_prime[1][0] *= x;

  A_prime[0][1] *= y;
  A_prime[1][1] *= y;

  return *this;
}

Transformation &Transformation::scale_x(float x) {
  return scale(x, 1.f);
}

Transformation &Transformation::scale_y(float y) {
  return scale(1.f, y);
}

Transformation &Transformation::rotate(float theta) {
  float a00 = std::cos(theta) * A_prime[0][0] - std::sin(theta) * A_prime[1][0];
  float a01 = std::cos(theta) * A_prime[0][1] - std::sin(theta) * A_prime[1][1];
  float a10 = std::sin(theta) * A_prime[0][0] + std::cos(theta) * A_prime[1][0];
  float a11 = std::sin(theta) * A_prime[0][1] + std::cos(theta) * A_prime[1][1];

  A_prime[0][0] = a00;
  A_prime[0][1] = a01;
  A_prime[1][0] = a10;
  A_prime[1][1] = a11;

  return *this;
}

[[nodiscard]] glm::mat2 Transformation::get_A() const {
  return glm::mat2(A_prime[0][0], A_prime[0][1], A_prime[1][0], A_prime[1][1]);
}

[[nodiscard]] glm::vec2 Transformation::get_b() const {
  return glm::vec2(A_prime[0][2], A_prime[1][2]);
}

}