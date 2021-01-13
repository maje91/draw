#pragma once

#include "transformation.hpp"

#include <glm/glm.hpp>
#include <utility>
#include <vector>

namespace draw::render {

/**
 * A line that is ready to be drawn by the GPU
 */
class Line {
 public:
  /**
   * Constructs a line from `vertices` and `indices` with a given `width`.
   */
  Line(std::vector<float> vertices, std::vector<unsigned int> indices,
    float width);

  /**
   * Draws the entire line
   */
  void draw();

  /**
   * Draws a subset of the line. Draws `segment_count` segments starting from `start_index`
   */
  void draw(unsigned int start_index, unsigned int segment_count);

  /**
   * Returns a reference to the line's current transformation
   * @return
   */
  transform::Transformation &transform();

 private:
  std::vector<float> m_vertices;
  std::vector<unsigned int> m_indices;

  unsigned int m_vao;
  unsigned int m_vbo;
  unsigned int m_ebo;
  unsigned int m_program;

  float m_width;
  transform::Transformation m_transformation;
  unsigned int width_location;
  unsigned int A_location;
  unsigned int b_location;
};

}  // namespace draw::render