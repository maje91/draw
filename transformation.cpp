#include "transformation.hpp"

using namespace Eigen;

namespace draw::transform {

static Matrix3d translation_matrix(double x, double y) {
  Matrix3d A;
  A << 1, 0, x, 0, 1, y, 0, 0, 1;

  return A;
}

static Matrix3d scaling_matrix(double x, double y) {
  Matrix3d A;
  A << x, 0, 0, 0, y, 0, 0, 0, 1;

  return A;
}

static Matrix3d rotatation_matrix(double theta) {
  Matrix3d A;
  A << std::cos(theta), -std::sin(theta), 0, std::sin(theta), std::cos(theta),
    0, 0, 0, 1;

  return A;
}

Transformation::Transformation()
    : A_prime(Eigen::Matrix3d::Identity()) {}

Transformation::Transformation(Eigen::Matrix3d A_prime)
    : A_prime(std::move(A_prime)) {}

Transformation Transformation::scaling(double x, double y) {
  return Transformation(scaling_matrix(x, y));
}
Transformation Transformation::translation(double x, double y) {
  return Transformation(translation_matrix(x, y));
}
Transformation Transformation::rotation(double theta) {
  return Transformation(rotatation_matrix(theta));
}

Transformation &Transformation::translate(double x, double y) {
  A_prime = translation_matrix(x, y) * A_prime;
  return *this;
}

Transformation &Transformation::translate_x(double x) {
  return translate(x, 0.f);
}

Transformation &Transformation::translate_y(double y) {
  return translate(0.f, y);
}

Transformation &Transformation::scale(double x, double y) {
  A_prime = scaling_matrix(x, y) * A_prime;
  return *this;
}

Transformation &Transformation::scale_x(double x) { return scale(x, 1.f); }

Transformation &Transformation::scale_y(double y) { return scale(1.f, y); }

Transformation &Transformation::rotate(double theta) {
  A_prime = rotatation_matrix(theta) * A_prime;
  return *this;
}

Decomposed Transformation::decompose() const {
  double theta;
  if (A_prime(1, 0) < A_prime(1, 1)) {
    theta = -std::atan(A_prime(0, 1) / A_prime(1, 1));
  } else {
    theta = std::atan(A_prime(0, 0) / A_prime(1, 0));
  }

  double sx = A_prime(0, 0) / std::cos(theta);
  double sy = A_prime(1, 1) / std::cos(theta);

  return Decomposed{.theta = theta,
    .scaling = Vector2f(sx, sy),
    .translation = Vector2f(A_prime(0, 2), A_prime(1, 2))};
}

const Matrix3d &Transformation::get() const { return A_prime; }

Eigen::Matrix3d Transformation::get_inverse() const {
  return A_prime.inverse();
}

[[nodiscard]] glm::mat2 Transformation::get_A_glm() const {
  return glm::mat2(A_prime(0, 0), A_prime(0, 1), A_prime(1, 0), A_prime(1, 1));
}

[[nodiscard]] glm::vec2 Transformation::get_b_glm() const {
  return glm::vec2(A_prime(0, 2), A_prime(1, 2));
}

Transformation operator*(const Transformation &lhs, const Transformation &rhs) {
  return Transformation(lhs.A_prime * rhs.A_prime);
}

}  // namespace draw::transform