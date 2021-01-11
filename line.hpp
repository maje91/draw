#pragma once

#include "render.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <colex.hpp>

using namespace colex;

namespace draw::line {

size_t vertex_size();

template<typename T>
class LineBase {
  [[nodiscard]] size_t vertices_count() const {
    return static_cast<const T &>(*this).vertices_count();
  }

  [[nodiscard]] size_t indices_count() const {
    return static_cast<const T &>(*this).indices_count();
  }

  [[nodiscard]] render::Line build() const {
    return static_cast<const T &>(*this).build();
  }

  void fill(float* vertices, unsigned int* indices, unsigned int v0_index) const {
    return static_cast<const T&>(*this).fill(vertices, indices, v0_index);
  }
};

class Line : public LineBase<Line> {
 public:
  Line(std::initializer_list<glm::vec2> points);
  explicit Line(std::vector<glm::vec2> points);

  [[nodiscard]] size_t vertices_count() const;
  [[nodiscard]] size_t indices_count() const;

  [[nodiscard]] render::Line build() const;
  void fill(float* vertices, unsigned int* indices, unsigned int v0_index) const;

 private:
  [[nodiscard]] size_t segments_count() const;
  [[nodiscard]] size_t intersections_count() const;

  std::vector<glm::vec2> points;
};

template<typename L, typename R>
class Composition : public LineBase<Composition<L, R>> {
 public:
  Composition(LineBase<L> &&a, LineBase<R> &&b)
      : a(static_cast<L &&>(a)), b(static_cast<R &&>(b)) {}

  [[nodiscard]] size_t vertices_count() const {
    return a.vertices_count() + b.vertices_count();
  }

  [[nodiscard]] size_t indices_count() const {
    return a.indices_count() + b.indices_count();
  }

  void fill(float* vertices, unsigned int* indices, unsigned int v0_index) const {
    a.fill(vertices, indices, v0_index);
    b.fill(vertices + vertex_size() * a.vertices_count(), indices + a.indices_count(), v0_index + a.vertices_count());
  }

  [[nodiscard]] render::Line build() const {
    std::vector<float> vertices(vertex_size() * vertices_count());
    std::vector<unsigned int> indices(indices_count());

    fill(vertices.data(), indices.data(), 0);

    std::cout << "Vertices count: " << vertices.size() << std::endl;
    iter(vertices) | for_each([](auto x) { std::cout << x << std::endl; });

    std::cout << std::endl;

    std::cout << "Indices count: " << indices.size() << std::endl;
    iter(indices) | for_each([](auto x) { std::cout << x << std::endl; });

    return render::Line(std::move(vertices), std::move(indices));
  }

 private:
  L a;
  R b;
};

template<typename L, typename R>
Composition<L, R> operator&(LineBase<L> &&a, LineBase<R> &&b) {
  return Composition<L, R>(std::move(a), std::move(b));
}
}  // namespace draw
