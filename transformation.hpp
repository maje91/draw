#pragma once

#include <glm/glm.hpp>

namespace draw::transform {
class Transformation {
 public:
  Transformation();

  Transformation &translate(float x, float y);
  Transformation &translate_x(float x);
  Transformation &translate_y(float y);

  Transformation &scale(float x, float y);
  Transformation &scale_x(float x);
  Transformation &scale_y(float y);

  Transformation &rotate(float theta);

  [[nodiscard]] glm::mat2 get_A() const;
  [[nodiscard]] glm::vec2 get_b() const;

 private:
  glm::mat3 A_prime;
};
}  // namespace draw::transform