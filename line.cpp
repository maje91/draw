//
// Created by Martin Jensen on 28/12/2020.
//

#include "line.hpp"

#include <colex.hpp>
#include <utility>
#include <functional>

using namespace colex;

namespace draw {

Line::Line(std::initializer_list<glm::vec2> points) : points(points) {}

Line::Line(std::vector<glm::vec2> points) : points(std::move(points)) {}

size_t Line::segments_count() const {
  return std::max<size_t>(0, points.size() - 1);
}

size_t Line::intersections_count() const {
  return std::max<size_t>(0, segments_count() - 1);
}

size_t Line::vertex_size() const {
  return 4;
}

size_t Line::vertices_count() const {
  return 4 * segments_count();
}

size_t Line::indices_count() const {
  return 6 * segments_count() + 6 * intersections_count();
}

void Line::build(float *vertices, unsigned int *indices) const {
  iter(points) | pairwise() | fold(vertices, [](float *vertices, auto x) {
    const glm::vec2 &a = x.first;
    const glm::vec2 &b = x.second;

    float l = glm::distance(a, b);

    glm::vec2 d = (b - a) / l;

    // a
    vertices[0] = a.x;
    vertices[1] = a.y;
    vertices[2] = -d.y;
    vertices[3] = d.x;

    // b
    vertices[4] = a.x;
    vertices[5] = a.y;
    vertices[6] = d.y;
    vertices[7] = -d.x;

    // c
    vertices[8] = b.x;
    vertices[9] = b.y;
    vertices[10] = d.y;
    vertices[11] = -d.x;

    // d
    vertices[12] = b.x;
    vertices[13] = b.y;
    vertices[14] = -d.y;
    vertices[15] = d.x;

    return vertices + 16;
  });

  auto set_segment_indices = [](unsigned int* indices, unsigned int v0) {
    indices[0] = v0;      // a
    indices[1] = v0 + 1;  // b
    indices[2] = v0 + 2;  // c

    indices[3] = v0;      // a
    indices[4] = v0 + 2;  // c
    indices[5] = v0 + 3;  // d
  };

  auto set_intersection_indices = [](unsigned int* indices, unsigned int v0) {
    indices[6] = v0 + 2;  // c
    indices[7] = v0 + 4;  // e
    indices[8] = v0 + 3;  // d

    indices[9] = v0 + 3;  // d
    indices[10] = v0 + 5; // f
    indices[11] = v0 + 2; // c
  };

  auto* last_segment_indices = range<unsigned int>(0, points.size() - 2)
          | fold(indices, [&](auto* indices, auto i) {
    unsigned int v0 = 4 * i;

    set_segment_indices(indices, v0);
    set_intersection_indices(indices, v0);

    return indices + 12;
  });

  set_segment_indices(last_segment_indices, 4 * (points.size() - 2));
}

}  // namespace draw
