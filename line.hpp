#pragma once

#include "render.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace draw {

class Line {
 public:
  Line(std::initializer_list<glm::vec2> points);
  explicit Line(std::vector<glm::vec2> points);

  [[nodiscard]] size_t vertex_size() const;
  [[nodiscard]] size_t vertices_count() const;
  [[nodiscard]] size_t indices_count() const;

  render::Line build() const;

 private:
  [[nodiscard]] size_t segments_count() const;
  [[nodiscard]] size_t intersections_count() const;

  std::vector<glm::vec2> points;
};
}// namespace draw
