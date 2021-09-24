#include "textelement.h"
#include "layoutcontext.h"
#include "parser.h"

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

    text->pos_px.x = Parser::parseLength(
        get(PropertyId::X), AllowNegativeLengths, Length::Zero
    ).value(100.0);

    text->pos_px.y = Parser::parseLength(
        get(PropertyId::Y), AllowNegativeLengths, Length::Zero
    ).value(100.0);
    text->pos_px.y -= text->size_px;

    text->family = get(PropertyId::Font_Family);
    text->color = Parser::parseColor(get(PropertyId::Fill), this, Color::Black);
    text->size_px = Parser::parseLength(
        get(PropertyId::Font_Size), ForbidNegativeLengths, Length::Zero
    ).value(100.0);
    auto sizeAdjust = Parser::parseLength(
        get(PropertyId::Font_Size_Adjust), ForbidNegativeLengths, Length::Zero
    );
    auto stretch = get(PropertyId::Font_Stretch);
    auto style = get(PropertyId::Font_Style);
    if (style == "normal") {
        text->style = FontStyle::Normal;
    }
    else if (style == "italic") {
        text->style = FontStyle::Italic;
    }
    else if (style == "oblique") {
        text->style = FontStyle::Oblique;
    }
    else {
        assert(style.empty());
    }
    auto variant = get(PropertyId::Font_Variant);
    auto weight = get(PropertyId::Font_Weight);
    if (weight == "normal") {
        text->weight = FontWeight::Normal;
    }
    else if (weight == "bold") {
        text->weight = FontWeight::Bold;
    }
    else if (weight == "bolder") {
        text->weight = FontWeight::Bolder;
    }
    else if (weight == "lighter") {
        text->weight = FontWeight::Lighter;
    }
    else if (!weight.empty()) {
        auto w = Parser::parseLength(weight, ForbidNegativeLengths, Length::Zero);
        if (w.isValid()) {
            // uint8_t overflow not checked
            text->weight = static_cast<FontWeight>(w.value(100.0));
        }
    }

    text->transform = Parser::parseTransform(get(PropertyId::Transform));

    auto prText = properties.get(PropertyId::Text);
    if (prText != nullptr) {
        // move or copy?
        text->textBuffer = std::move(prText->value);
        text->text.buffer = &text->textBuffer;
        text->text.size = static_cast<uint32_t>(text->textBuffer.size());
    }

    layoutChildren(context, text.get());
    current->addChild(std::move(text));
}

std::unique_ptr<Node> TextElement::clone() const
{
    return cloneElement<TextElement>();
}

} // namespace lunasvg
