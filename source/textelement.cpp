#include "textelement.h"
#include "layoutcontext.h"

namespace lunasvg {

TextElement::TextElement()
    : StyledElement(ElementId::Text)
{
}

void TextElement::layout(LayoutContext* context, LayoutContainer* current) const
{
    if (isDisplayNone())
        return;

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
    //current->addChild(std::move(shape));

    auto text = std::make_unique<LayoutText>();

    //auto prText = properties.get(PropertyId::Text);
    //if (prText != nullptr) {
    //    // move or copy?
    //    text->text = std::move(prText->value);
    //}

    layoutChildren(context, text.get());
    current->addChild(std::move(text));
}

std::unique_ptr<Node> TextElement::clone() const
{
    return cloneElement<TextElement>();
}

} // namespace lunasvg
