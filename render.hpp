#pragma once

#include <utility>
#include <vector>

namespace draw::render {

class Shape {
 public:
  Shape(std::vector<float> vertices, std::vector<unsigned int> indices);

  void draw();

 private:
  std::vector<float> m_vertices;
  std::vector<unsigned int> m_indices;

  unsigned int m_vao;
  unsigned int m_vbo;
  unsigned int m_ebo;
  unsigned int m_program;
  unsigned int width_location;
  unsigned int A_location;
  unsigned int b_location;
};

}  // namespace render