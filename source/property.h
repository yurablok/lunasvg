#ifndef PROPERTY_H
#define PROPERTY_H

#include <vector>
#include <string>
#include <array>

namespace lunasvg {

enum class Display : uint8_t
{
    Inline,
    None
};

enum class Visibility : uint8_t
{
    Visible,
    Hidden
};

enum class Overflow : uint8_t
{
    Visible,
    Hidden
};

enum class LineCap : uint8_t
{
    Butt,
    Round,
    Square
};

enum class LineJoin : uint8_t
{
    Miter,
    Round,
    Bevel
};

enum class WindRule : uint8_t
{
    NonZero,
    EvenOdd
};

enum class Units : uint8_t
{
    UserSpaceOnUse,
    ObjectBoundingBox
};

enum class SpreadMethod : uint8_t
{
    Pad,
    Reflect,
    Repeat
};

enum class MarkerUnits : uint8_t
{
    StrokeWidth,
    UserSpaceOnUse
};

enum class TextureType : uint8_t
{
    Plain,
    Tiled
};

enum class BlendMode : uint8_t
{
    Src,
    Src_Over,
    Dst_In,
    Dst_Out
};

enum class FontStyle : uint8_t
{
    Normal,
    Italic,
    Oblique
};

// https://developer.mozilla.org/en-US/docs/Web/SVG/Attribute/font-weight
// https://drafts.csswg.org/css-fonts-4/#valdef-font-weight-number-1-1000
enum class FontWeight : uint16_t
{
    //Thin      = 100, // CSS Thin
    Lighter     = 200, // CSS ExtraLight | UltraLight
    //Light     = 300, // CSS Light
    Normal      = 400, // CSS Normal
    //Medium    = 500, // CSS Medium
    //SemiBold  = 600, // CSS SemiBold | DemiBold
    Bold        = 700, // CSS Bold
    //ExtraBold = 800, // CSS ExtraBold | UltraBold
    Bolder      = 900, // CSS Black | Heavy
};

struct string_index_view
{
    const std::string* buffer = nullptr;
    uint32_t offset = 0;
    uint32_t size = 0;
};

class Color
{
public:
    Color() = default;
    Color(double r, double g, double b, double a = 1);

    bool isNone() const { return  a == 0.0; }

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Transparent;

public:
    double r{0};
    double g{0};
    double b{0};
    double a{1};
};

class Paint
{
public:
    Paint() = default;
    Paint(const Color& color);
    Paint(const std::string& ref, const Color& color);

    const Color& color() const { return m_color; }
    const std::string& ref() const { return m_ref; }
    bool isNone() const { return m_ref.empty() && m_color.isNone(); }

public:
    Color m_color{Color::Transparent};
    std::string m_ref;
};

class Point
{
public:
    Point() = default;
    Point(double x, double y);

public:
    double x{0};
    double y{0};
};

using PointList = std::vector<Point>;

class Rect
{
public:
    Rect() = default;
    Rect(double x, double y, double w, double h);

    Rect operator&(const Rect& rect) const;
    Rect operator|(const Rect& rect) const;

    Rect& intersect(const Rect& rect);
    Rect& unite(const Rect& rect);

    bool empty() const { return w <= 0.0 || h <= 0.0; }
    bool valid() const { return w >= 0.0 && h >= 0.0; }

    static const Rect Empty;
    static const Rect Invalid;

public:
    double x{0};
    double y{0};
    double w{0};
    double h{0};
};

// https://developer.mozilla.org/en-US/docs/Web/CSS/transform
class Transform
{
public:
    Transform() = default;
    Transform(double m00, double m10, double m01, double m11, double m02, double m12);

    Transform inverted() const;
    Transform operator*(const Transform& transform) const;
    Transform& operator*=(const Transform& transform);

    Transform& premultiply(const Transform& transform);
    Transform& postmultiply(const Transform& transform);
    Transform& rotate(double angle_deg);
    Transform& rotate(double angle_deg, double cx, double cy);
    Transform& scale(double sx, double sy);
    Transform& shear(double shx, double shy);
    Transform& translate(double tx, double ty);
    Transform& transform(double m00, double m10, double m01, double m11, double m02, double m12);
    Transform& identity();
    Transform& invert();
    double rotation_rad() const;
    double rotation_deg() const;

    void map(double x, double y, double* _x, double* _y) const;
    Point map(double x, double y) const;
    Point map(const Point& point) const;
    Rect map(const Rect& rect) const;

    static Transform rotated(double angle_deg);
    static Transform rotated(double angle_deg, double cx, double cy);
    static Transform scaled(double sx, double sy);
    static Transform sheared(double shx, double shy);
    static Transform translated(double tx, double ty);

public:
    double m00{1};
    double m10{0};
    double m01{0};
    double m11{1};
    double m02{0};
    double m12{0};
};

enum class PathCommand : uint8_t
{
    MoveTo,
    LineTo,
    CubicTo,
    Close
};

class Path
{
public:
    Path() = default;

    void moveTo(double x, double y);
    void lineTo(double x, double y);
    void cubicTo(double x1, double y1, double x2, double y2, double x3, double y3);
    void close();
    void reset();
    bool empty() const;

    void quadTo(double cx, double cy, double x1, double y1, double x2, double y2);
    void arcTo(double cx, double cy, double rx, double ry, double xAxisRotation, bool largeArcFlag, bool sweepFlag, double x, double y);

    void ellipse(double cx, double cy, double rx, double ry);
    void rect(double x, double y, double w, double h, double rx, double ry);

    Rect box() const;

    const std::vector<PathCommand>& commands() const { return m_commands; }
    const std::vector<Point>& points() const { return m_points; }

private:
    std::vector<PathCommand> m_commands;
    std::vector<Point> m_points;
};

class PathIterator
{
public:
   PathIterator(const Path& path);

   PathCommand currentSegment(std::array<Point, 3>& points) const;
   bool isDone() const;
   void next();

private:
   mutable Point m_startPoint;
   const std::vector<PathCommand>& m_commands;
   const Point* m_points{nullptr};
   unsigned int m_index{0};
};

enum class LengthUnits : uint8_t
{
    Unknown,
    Number,
    Px,
    Pt,
    Pc,
    In,
    Cm,
    Mm,
    Ex,
    Em,
    Percent
};

enum LengthMode : uint8_t
{
    Width,
    Height,
    Both
};

class Element;

class Length
{
public:
    Length() = default;
    Length(double value);
    Length(double value, LengthUnits units);

    double value(double max) const;
    double value(const Element* element, LengthMode mode) const;

    bool isValid() const { return  m_units != LengthUnits::Unknown; }
    bool isZero() const { return m_value == 0.0; }
    bool isRelative() const { return m_units == LengthUnits::Percent || m_units == LengthUnits::Em || m_units == LengthUnits::Ex; }

    static const Length Unknown;
    static const Length Zero;
    static const Length One;
    static const Length ThreePercent;
    static const Length HundredPercent;
    static const Length FiftyPercent;
    static const Length OneTwentyPercent;
    static const Length MinusTenPercent;

private:
    double m_value{0};
    LengthUnits m_units{LengthUnits::Px};
};

using LengthList = std::vector<Length>;

class LengthContext
{
public:
    LengthContext(const Element* element);
    LengthContext(const Element* element, Units units);

    double valueForLength(const Length& length, LengthMode mode) const;

private:
    const Element* m_element{nullptr};
    Units m_units{Units::UserSpaceOnUse};
};

enum class Align : uint8_t
{
    None,
    xMinYMin,
    xMidYMin,
    xMaxYMin,
    xMinYMid,
    xMidYMid,
    xMaxYMid,
    xMinYMax,
    xMidYMax,
    xMaxYMax
};

enum class MeetOrSlice : uint8_t
{
    Meet,
    Slice
};

class PreserveAspectRatio
{
public:
    PreserveAspectRatio() = default;
    PreserveAspectRatio(Align align, MeetOrSlice scale);

    Transform getMatrix(double width, double height, const Rect& viewBox) const;
    Rect getClip(double width, double height, const Rect& viewBox) const;

    Align align() const { return m_align; }
    MeetOrSlice scale() const { return m_scale; }

private:
    Align m_align{Align::xMidYMid};
    MeetOrSlice m_scale{MeetOrSlice::Meet};
};

enum class MarkerOrient : uint8_t
{
    Auto,
    Angle
};

class Angle
{
public:
    Angle() = default;
    Angle(MarkerOrient type);
    Angle(double value, MarkerOrient type);

    double value() const { return m_value; }
    MarkerOrient type() const { return m_type; }

private:
    double m_value{0};
    MarkerOrient m_type{MarkerOrient::Angle};
};

using GradientStop = std::pair<double, Color>;
using GradientStops = std::vector<GradientStop>;

using DashArray = std::vector<double>;

struct DashData
{
    DashArray array;
    double offset{ 0.0 };
};

} // namespace lunasvg

#endif // PROPERTY_H
