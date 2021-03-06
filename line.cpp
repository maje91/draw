//
// Created by Martin Jensen on 28/12/2020.
//

#include "line.hpp"

#include <utility>

using namespace colex;

namespace draw::line {

size_t vertex_size() { return 5; }

Line::Line(std::initializer_list<glm::vec2> points)
    : points(points) {}

Line::Line(std::vector<glm::vec2> points)
    : points(std::move(points)) {}

Line::Line(float x1, float y1, float x2, float y2)
    : points({{x1, y1}, {x2, y2}}) {}

size_t Line::segments_count() const {
  return std::max<size_t>(0, points.size() - 1);
}

size_t Line::intersections_count() const {
  return std::max<size_t>(0, segments_count() - 1);
}

size_t Line::vertices_count() const { return 4 * segments_count(); }

size_t Line::indices_count() const {
  return 6 * segments_count() + 6 * intersections_count();
}

void Line::fill(float *vertices, unsigned int *indices, unsigned int v0) const {
  iter(points) | pairwise() | fold(vertices, [](float *vertices, auto x) {
    const glm::vec2 &a = x.first;
    const glm::vec2 &b = x.second;

    glm::vec2 d = b - a;

    // a
    vertices[0] = a.x;
    vertices[1] = a.y;
    vertices[2] = d.x;
    vertices[3] = d.y;
    vertices[4] = 1.f;

    // b
    vertices[5] = a.x;
    vertices[6] = a.y;
    vertices[7] = d.x;
    vertices[8] = d.y;
    vertices[9] = -1.f;

    // c
    vertices[10] = b.x;
    vertices[11] = b.y;
    vertices[12] = d.x;
    vertices[13] = d.y;
    vertices[14] = -1.f;

    // d
    vertices[15] = b.x;
    vertices[16] = b.y;
    vertices[17] = d.x;
    vertices[18] = d.y;
    vertices[19] = 1.f;

    return vertices + 20;
  });

  auto set_segment_indices = [](unsigned int *indices, unsigned int v0) {
    indices[0] = v0;      // a
    indices[1] = v0 + 1;  // b
    indices[2] = v0 + 2;  // c

    indices[3] = v0;      // a
    indices[4] = v0 + 2;  // c
    indices[5] = v0 + 3;  // d
  };

  auto set_intersection_indices = [](unsigned int *indices, unsigned int v0) {
    indices[6] = v0 + 2;  // c
    indices[7] = v0 + 4;  // e
    indices[8] = v0 + 3;  // d

    indices[9] = v0 + 3;   // d
    indices[10] = v0 + 5;  // f
    indices[11] = v0 + 2;  // c
  };

  auto *last_segment_indices = range<unsigned int>(0, points.size() - 2, 1)
                             | fold(indices, [&](auto *indices, auto i) {
                                 set_segment_indices(indices, v0 + 4 * i);
                                 set_intersection_indices(indices, v0 + 4 * i);

                                 return indices + 12;
                               });

  set_segment_indices(last_segment_indices, v0 + 4 * (points.size() - 2));
}

render::Line Line::build(float width) const {
  std::vector<float> vertices(vertex_size() * vertices_count());
  std::vector<unsigned int> indices(indices_count());

  fill(vertices.data(), indices.data(), 0);

  return render::Line(std::move(vertices), std::move(indices), width);
}

}  // namespace draw::line
