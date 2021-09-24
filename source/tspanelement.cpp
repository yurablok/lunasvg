#include "tspanelement.h"
#include "layoutcontext.h"

namespace lunasvg {

TSpanElement::TSpanElement()
    : StyledElement(ElementId::TSpan)
{
}

void TSpanElement::layout(LayoutContext* context, LayoutContainer* current) const {
    //auto shape = std::make_unique<LayoutShape>();
    //shape->path = std::move(path);
    //shape->transform = transform();
    //shape->fillData = context->fillData(this);
    //shape->strokeData = context->strokeData(this);
    //shape->markerData = context->markerData(this, shape->path);
    //shape->visibility = visibility();
    //shape->clipRule = clip_rule();
    //shape->masker = context->getMasker(mask());
    //shape->clipper = context->getClipper(clip_path());

    auto tspan = std::make_unique<LayoutTSpan>();

    auto prText = properties.get(PropertyId::Text);
    if (prText != nullptr) {
        // move or copy?
        tspan->text = std::move(prText->value);
    }

    current->addChild(std::move(tspan));
}

std::unique_ptr<Node> TSpanElement::clone() const
{
    return cloneElement<TSpanElement>();
}

} // namespace lunasvg
