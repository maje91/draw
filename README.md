# Draw
This C++ library provides functionality for drawing low-level things through OpenGL.
We will refer to these as _primitives_. This is a work in progress and I will implement
more primitives as I need them for other projects.

## Usage
All the stuff you need is found in the `draw` namespace. It is assumed to be
`using`-ed for all code in this document. To include the library, a single
header is provided
```cpp
#include <draw/draw.hpp>
```
The first step to draw something is to initialize the window. This opens a
window on the screen and initializes OpenGL.
```cpp
window::init(window::Spec {
    .width = 1000,
    .height = 1000,
    .name = "Example"
});
```
Next, we must define a shape. We can define a line as
```cpp
auto a = Line(0.f, 0.f, 1.f, 1.f); // Type: line::Line
```
This defines a single segmented line. We can also define a
multisegmented line through a vector or initializer list of `glm::vec2`s. For
instance
```cpp
auto b = Line({{0.1f, 0.0f}, {1.1f, 1.0f}, {2.1f, 0.0f}}) // type: line::Line
```
Finally, we can compose lines with the `&`-operator
```cpp
auto c = std::move(a) & std::move(b) // type: Composition<Line, Line>
```
`a`, `b`, and `c` are _descriptors_ for how a shape should be drawn,
but the GPU needs more specific instructions. Hence, we have to `build`
the final shape.
```cpp
auto shape = c.build(0.005) // type: render::Line. The argument is the line width
```
We can transform the shape if we want to
```cpp
shape.transform().translate(-1.0, -0.5).scale(0.5, 0.5);
```
We draw the shape in the main loop
```cpp
while (window::advance()) {  // Advances to the next frame. This clears the screen
    shape.draw();
}
```
This should draw a something like this `//\` at the center of the window. Finally, we
have to clean up when the window should close
```cpp
window::destroy();

return 0;
```

## Available Primitives
### `Line`
A line with straight segments defined by points it has to pass through.
An example of it is provided in the **Usage** section.

