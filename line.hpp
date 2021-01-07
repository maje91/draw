#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace draw {
class Line {
 public:
  explicit Line(std::initializer_list<glm::vec2> points);
  explicit Line(std::vector<glm::vec2> points);

  [[nodiscard]] size_t vertex_size() const;
  [[nodiscard]] size_t vertices_count() const;
  [[nodiscard]] size_t indices_count() const;

  void build(float* vertices, unsigned int* indices) const;

 private:
  [[nodiscard]] size_t segments_count() const;
  [[nodiscard]] size_t intersections_count() const;

  std::vector<glm::vec2> points;
};
}// namespace draw
