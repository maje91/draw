#pragma once

#include <Eigen/Dense>
#include <glm/glm.hpp>

namespace draw::transform {

struct Decomposed {
  float theta;
  Eigen::Vector2f scaling;
  Eigen::Vector2f translation;
};

class Transformation {
 public:
  Transformation();
  static Transformation scaling(float x, float y);
  static Transformation translation(float x, float y);
  static Transformation rotation(float theta);

  Transformation &translate(float x, float y);
  Transformation &translate_x(float x);
  Transformation &translate_y(float y);

  Transformation &scale(float x, float y);
  Transformation &scale_x(float x);
  Transformation &scale_y(float y);

  Transformation &rotate(float theta);

  [[nodiscard]] Decomposed decompose() const;

  [[nodiscard]] const Eigen::Matrix3f &get() const;
  [[nodiscard]] Eigen::Matrix3f get_inverse() const;

  [[nodiscard]] glm::mat2 get_A_glm() const;
  [[nodiscard]] glm::vec2 get_b_glm() const;

  friend Transformation operator*(const Transformation &lhs, const Transformation &rhs);

 private:
  Transformation(Eigen::Matrix3f A_prime);
  Eigen::Matrix3f A_prime;
};

}  // namespace draw::transform