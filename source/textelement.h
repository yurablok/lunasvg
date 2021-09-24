#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "styledelement.h"

namespace lunasvg {

class TextElement : public StyledElement
{
public:
    TextElement();

    void layout(LayoutContext* context, LayoutContainer* current) const override;

    std::unique_ptr<Node> clone() const override;
};

} // namespace lunasvg

#endif // TEXTELEMENT_H
