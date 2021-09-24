#ifndef TSPANELEMENT_H
#define TSPANELEMENT_H

#include "styledelement.h"

namespace lunasvg {

class TSpanElement : public StyledElement
{
public:
    TSpanElement();

    void layout(LayoutContext* context, LayoutContainer* current) const override;

    std::unique_ptr<Node> clone() const;
};

} // namespace lunasvg

#endif // TSPANELEMENT_H
