#include "tspanelement.h"
#include "layoutcontext.h"
#include "parser.h"

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

    //LengthContext lengthContext(this);
    //auto _x1 = lengthContext.valueForLength(x1(), LengthMode::Width);
    //auto _y1 = lengthContext.valueForLength(y1(), LengthMode::Height);
    //auto _x2 = lengthContext.valueForLength(x2(), LengthMode::Width);
    //auto _y2 = lengthContext.valueForLength(y2(), LengthMode::Height);

    if (current->id != LayoutId::Text) {
        return;
    }
    auto text = static_cast<LayoutText*>(current);

    auto tspan = std::make_unique<LayoutTSpan>();

    tspan->family = text->family;
    tspan->color = text->color;
    tspan->size_px = text->size_px;
    tspan->weight = text->weight;
    tspan->style = text->style;

    tspan->transform = text->transform;

    for (const auto& length : Parser::parseLengthList(
            get(PropertyId::X), AllowNegativeLengths)) {
        tspan->x_px.push_back(length.value(100.0));
    }
    tspan->y_px = Parser::parseLength(
        get(PropertyId::Y), AllowNegativeLengths, Length::Zero
    ).value(100.0);
    tspan->y_px -= tspan->size_px;

    auto prText = properties.get(PropertyId::Text);
    if (prText != nullptr) {
        tspan->text.buffer = &text->textBuffer;
        tspan->text.offset = static_cast<uint32_t>(text->textBuffer.size());
        tspan->text.size = static_cast<uint32_t>(prText->value.size());
        // move or copy?
        text->textBuffer.insert(text->textBuffer.end(), prText->value.begin(), prText->value.end());
        prText->value.clear();
    }

    current->addChild(std::move(tspan));
}

std::unique_ptr<Node> TSpanElement::clone() const
{
    return cloneElement<TSpanElement>();
}

} // namespace lunasvg
