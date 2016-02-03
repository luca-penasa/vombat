#include "ccStratigraphicPositionableElement.h"



#include <spc/elements/StratigraphicPositionableElement.h>


ccStratigraphicPositionableElement::ccStratigraphicPositionableElement(spc::StratigraphicPositionableElementPtr el, const QString &name): ccSPCElementShell(el, name)
{
}

double ccStratigraphicPositionableElement::getStratigraphicPosition()
{
    return this->getSPCElement<spc::StratigraphicPositionableElement>()->getStratigraphicPosition();
}

void ccStratigraphicPositionableElement::setStratigraphicPosition(const double sp)
{
    this->getSPCElement<spc::StratigraphicPositionableElement>()->setStratigraphicPosition(sp);
}

void ccStratigraphicPositionableElement::setManual(const bool status)
{
    this->getSPCElement<spc::StratigraphicPositionableElement>()->setManual(status);
}

bool ccStratigraphicPositionableElement::getManual()
{
    return this->getSPCElement<spc::StratigraphicPositionableElement>()->getManual();
}
