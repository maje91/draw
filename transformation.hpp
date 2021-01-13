#pragma once

#include <Eigen/Dense>
#include <glm/glm.hpp>

namespace draw::transform {

/**
 * Contains the decomposed parts of a transformation
 */
struct Decomposed {
  /**
   * The rotation angle
   */
  double theta;

  /**
   * The scaling in x and y directions
   */
  Eigen::Vector2f scaling;

  /**
   * The translation in x and y directions
   */
  Eigen::Vector2f translation;
};

/**
 * Represents a transformation that can be applied to a shape
 */
class Transformation {
 public:
  /**
   * Constructs a transformation that does nothing. The identity.
   */
  Transformation();

  /**
   * Constructs a scaling transformation
   */
  static Transformation scaling(double x, double y);

  /**
   * Constructs a translation transformation
   */
  static Transformation translation(double x, double y);

  /**
   * Constructs a rotation transformation
   */
  static Transformation rotation(double theta);

  /**
   * Adds translation to the transformation
   */
  Transformation &translate(double x, double y);
  Transformation &translate_x(double x);
  Transformation &translate_y(double y);

  /**
   * Adds scaling to the transformation
   */
  Transformation &scale(double x, double y);
  Transformation &scale_x(double x);
  Transformation &scale_y(double y);

  /**
   * Adds rotation to the transformation
   */
  Transformation &rotate(double theta);

  /**
   * Returns the decomposed transformation
   */
  [[nodiscard]] Decomposed decompose() const;

  /**
   * Returns the raw transformation matrix
   */
  [[nodiscard]] const Eigen::Matrix3d &get() const;

  /**
   * Returns the inverse of the transformation matrix
   */
  [[nodiscard]] Eigen::Matrix3d get_inverse() const;

  /**
   * Returns the A-submatrix as a glm type
   */
  [[nodiscard]] glm::mat2 get_A_glm() const;

  /**
   * Returns the b-subvector as a glm type
   */
  [[nodiscard]] glm::vec2 get_b_glm() const;

  /**
   * Composes two transformations
   */
  friend Transformation operator*(const Transformation &lhs, const Transformation &rhs);

 private:
  explicit Transformation(Eigen::Matrix3d A_prime);
  Eigen::Matrix3d A_prime;
};

}  // namespace draw::transform