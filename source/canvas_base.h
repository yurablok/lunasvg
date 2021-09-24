#ifndef CANVAS_BASE_H
#define CANVAS_BASE_H

#include <memory>
#include "property.h"

namespace lunasvg {

class LayoutObject;

class CanvasBase
{
public:
    virtual std::shared_ptr<CanvasBase> create(
        unsigned char* data, unsigned int width, unsigned int height, unsigned int stride
    ) { return nullptr; }
    virtual std::shared_ptr<CanvasBase> create(
        double x, double y, double width, double height
    ) { return nullptr; }
    virtual std::shared_ptr<CanvasBase> create(
        const Rect& box
    ) { return nullptr; }

    virtual void setObject(const LayoutObject* object = nullptr) {}
    virtual void setColor(const Color& color) {}
    virtual void setLinearGradient(double x1, double y1, double x2, double y2,
        const GradientStops& stops, SpreadMethod spread, const Transform& transform) {}
    virtual void setRadialGradient(double cx, double cy, double r, double fx, double fy,
        const GradientStops& stops, SpreadMethod spread, const Transform& transform) {}
    virtual void setTexture(const CanvasBase* source, TextureType type, const Transform& transform) {}

    virtual void fill(const Path& path, const Transform& transform, WindRule winding,
        BlendMode mode, double opacity) {}
    virtual void stroke(const Path& path, const Transform& transform, double width,
        LineCap cap, LineJoin join, double miterlimit, const DashData& dash,
        BlendMode mode, double opacity) {}
    virtual void blend(const CanvasBase* source, BlendMode mode, double opacity) {}
    virtual void mask(const Rect& clip, const Transform& transform) {}

    virtual void clear(uint32_t value) {}
    virtual void rgba() {}
    virtual void luminance() {}

    virtual uint32_t width() const { return 0; }
    virtual uint32_t height() const { return 0; }
    virtual uint32_t stride() const { return 0; }
    virtual uint8_t* data() const { return nullptr; }
    virtual Rect box() const { return {}; }

    //CanvasBase();
    //virtual ~CanvasBase();
    //CanvasBase(unsigned char* data, int width, int height, int stride);
    //CanvasBase(int x, int y, int width, int height);
private:
};

} // namespace lunasvg

#endif // CANVAS_BASE_H
