#ifndef CANVAS_H
#define CANVAS_H

#include "canvas_base.h"
#include "plutovg.h"

#include <memory>

namespace lunasvg {

class Canvas : public CanvasBase
{
public:
    std::shared_ptr<CanvasBase> create(
        unsigned char* data, unsigned int width, unsigned int height, unsigned int stride) override;
    std::shared_ptr<CanvasBase> create(
        double x, double y, double width, double height) override;
    std::shared_ptr<CanvasBase> create(
        const Rect& box) override;

    void setColor(const Color& color) override;
    void setLinearGradient(double x1, double y1, double x2, double y2,
        const GradientStops& stops, SpreadMethod spread, const Transform& transform) override;
    void setRadialGradient(double cx, double cy, double r, double fx, double fy,
        const GradientStops& stops, SpreadMethod spread, const Transform& transform) override;
    void setTexture(const CanvasBase* source, TextureType type, const Transform& transform) override;

    void fill(const Path& path, const Transform& transform, WindRule winding,
        BlendMode mode, double opacity) override;
    void stroke(const Path& path, const Transform& transform, double width,
        LineCap cap, LineJoin join, double miterlimit, const DashData& dash,
        BlendMode mode, double opacity) override;
    void blend(const CanvasBase* source, BlendMode mode, double opacity) override;
    void mask(const Rect& clip, const Transform& transform) override;

    void clear(unsigned int value) override;
    void rgba() override;
    void luminance() override;

    unsigned int width() const override;
    unsigned int height() const override;
    unsigned int stride() const override;
    unsigned char* data() const override;
    Rect box() const override;

    Canvas();
    ~Canvas();
    Canvas(unsigned char* data, int width, int height, int stride);
    Canvas(int x, int y, int width, int height);

private:
    plutovg_surface_t* surface;
    plutovg_t* pluto;
    plutovg_matrix_t translation;
    plutovg_rect_t rect;
};

} // namespace lunasvg

#endif // CANVAS_H
