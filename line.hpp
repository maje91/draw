#pragma once

#include "render.hpp"

#include <colex/colex.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

using namespace colex;

namespace draw::line {

/**
 * Returns how many elements each vertex has
 */
size_t vertex_size();

/**
 * Base class for line shapes
 */
template<typename T>
class Base {
  /**
   * Returns how many vertices that must be drawn
   */
  [[nodiscard]] size_t vertices_count() const {
    return static_cast<const T &>(*this).vertices_count();
  }

  /**
   * Returns how many elements that must be drawn
   */
  [[nodiscard]] size_t indices_count() const {
    return static_cast<const T &>(*this).indices_count();
  }

  /**
   * Builds the line into a drawable shape
   */
  [[nodiscard]] render::Line build(float width) const {
    return static_cast<const T &>(*this).build(width);
  }

  /**
   * Fills `vertices` and `indices` with the line. `v0` is the index
   * of the first vertex.
   */
  void fill(float *vertices, unsigned int *indices, unsigned int v0) const {
    return static_cast<const T &>(*this).fill(vertices, indices, v0);
  }
};

/**
 * A multi-segmented line as described in `theory/`
 */
class Line : public Base<Line> {
 public:
  /**
   * Creates a line from an initializer list
   */
  Line(std::initializer_list<glm::vec2> points);

  /**
   * Creates a line from a vector
   */
  explicit Line(std::vector<glm::vec2> points);

  /**
   * Creates a single segmented line from (x1, y1) to (x2, y2)
   */
  Line(float x1, float y1, float x2, float y2);

  /**
   * Creates a line from an iterator
   */
  template<typename I>
  explicit Line(iterator::Iterator<I> &&points)
      : points(std::move(points) | collect<std::vector>()) {}

  [[nodiscard]] size_t vertices_count() const;
  [[nodiscard]] size_t indices_count() const;

  [[nodiscard]] render::Line build(float width) const;
  void fill(float *vertices, unsigned int *indices, unsigned int v0) const;

 private:
  [[nodiscard]] size_t segments_count() const;
  [[nodiscard]] size_t intersections_count() const;

  std::vector<glm::vec2> points;
};

/**
 * A composition of shapes. The composed elements
 * can be lines or previously composed lines. Hence,
 * arbitrarily complex line-shapes can be created
 */
template<typename L, typename R>
class Composition : public Base<Composition<L, R>> {
 public:
  Composition(Base<L> &&a, Base<R> &&b)
      : a(static_cast<L &&>(a))
      , b(static_cast<R &&>(b)) {}

  [[nodiscard]] size_t vertices_count() const {
    return a.vertices_count() + b.vertices_count();
  }

  [[nodiscard]] size_t indices_count() const {
    return a.indices_count() + b.indices_count();
  }

  void fill(float *vertices, unsigned int *indices, unsigned int v0) const {
    a.fill(vertices, indices, v0);
    b.fill(vertices + vertex_size() * a.vertices_count(),
      indices + a.indices_count(), v0 + a.vertices_count());
  }

  [[nodiscard]] render::Line build(float width) const {
    std::vector<float> vertices(vertex_size() * vertices_count());
    std::vector<unsigned int> indices(indices_count());

    fill(vertices.data(), indices.data(), 0);

    return render::Line(std::move(vertices), std::move(indices), width);
  }

 private:
  L a;
  R b;
};

/**
 * Composes two shapes through the `&` operator
 */
template<typename L, typename R>
Composition<L, R> operator&(Base<L> &&a, Base<R> &&b) {
  return Composition<L, R>(std::move(a), std::move(b));
}

}  // namespace draw::line
