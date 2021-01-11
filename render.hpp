#pragma once

#include <utility>
#include <vector>
#include <glm/glm.hpp>

namespace draw::render {

class Line {
 public:
  Line(std::vector<float> vertices, std::vector<unsigned int> indices, float width);

  void draw();

  void set_A(glm::mat2 A);
  void set_b(glm::vec2 b);
  void set_width(float width);

 private:
  std::vector<float> m_vertices;
  std::vector<unsigned int> m_indices;

  unsigned int m_vao;
  unsigned int m_vbo;
  unsigned int m_ebo;
  unsigned int m_program;

  float m_width;
  glm::mat2 m_A;
  glm::vec2 m_b;
  unsigned int width_location;
  unsigned int A_location;
  unsigned int b_location;
};

}  // namespace render