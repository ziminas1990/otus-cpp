#pragma once

#include <stdint.h>
#include <array>

namespace picasso
{

/// \struct Point
/// \brief Describes a point on surface
struct Point
{
  Point();
  Point(double x, double y);
  Point(const Point& other);

  double x;
  double y;
};


/// \struct Color
/// \brief Describes a colot in RGB format
/// \details It is recommended to use static methods of color, to create well-known
///          colors
struct Color
{
  // Factory method pattern
  static Color Black() { return Color(0,    0,    0   ); }
  static Color Red()   { return Color(0xFF, 0,    0   ); }
  static Color Green() { return Color(0,    0xFF, 0   ); }
  static Color Blue()  { return Color(0,    0,    0xFF); }
  static Color White() { return Color(0xFF, 0xFF, 0xFF); }

  Color() : red(0), green(0), blue(0) {}
  Color(uint8_t nRed, uint8_t nGreen, uint8_t nBlue);
  Color(const Color& other);

  uint8_t red;
  uint8_t green;
  uint8_t blue;
};


/// \class Transform
/// \brief Describe an transformation matrix, that can be used to move, scale and rotate
///        different objects on scheme
/// \details Object of this class could be passed to ICanvas or applied to a groups of
/// objects
///
/// You can use built-in "Builder" pattern to construct object, for example:
/// ```cpp
/// Group someGroup;
/// someGroup.setTransformation(
///   Transform()
///     .scale(2)
///     .translate(70, -25)
///     .rotate(0.707)
/// );
/// ```
class Transform
{
public:
  Transform() : matrix({1, 1, 0, 1, 1, 0, 0, 0, 1}) {}
  Transform(const Transform& other);

  // Simplified (or built-in) "Builder" pattern
  Transform& translate(double dx, double dy);
  Transform& scale(double x, double y);
  Transform& rotate(double rad);
  Transform& rotate(double rad, double cx, double cy)
  {
    return translate(cx, cy).rotate(rad).translate(-cx, -cy);
  }
  Transform& append(const Transform& other);

  void  applyTo(Point& point) const;
  Point transform(const Point& point) const;

private:
  std::array<double, 9> matrix;
};

} // namespace picaspo
