#pragma once

#include <Eigen/Dense>
#include <glm/glm.hpp>

namespace draw::transform {

struct Decomposed {
  double theta;
  Eigen::Vector2f scaling;
  Eigen::Vector2f translation;
};

class Transformation {
 public:
  Transformation();
  static Transformation scaling(double x, double y);
  static Transformation translation(double x, double y);
  static Transformation rotation(double theta);

  Transformation &translate(double x, double y);
  Transformation &translate_x(double x);
  Transformation &translate_y(double y);

  Transformation &scale(double x, double y);
  Transformation &scale_x(double x);
  Transformation &scale_y(double y);

  Transformation &rotate(double theta);

  [[nodiscard]] Decomposed decompose() const;

  [[nodiscard]] const Eigen::Matrix3d &get() const;
  [[nodiscard]] Eigen::Matrix3d get_inverse() const;

  [[nodiscard]] glm::mat2 get_A_glm() const;
  [[nodiscard]] glm::vec2 get_b_glm() const;

  friend Transformation operator*(const Transformation &lhs, const Transformation &rhs);

 private:
  explicit Transformation(Eigen::Matrix3d A_prime);
  Eigen::Matrix3d A_prime;
};

}  // namespace draw::transform