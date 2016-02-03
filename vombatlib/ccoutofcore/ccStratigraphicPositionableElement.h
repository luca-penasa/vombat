#ifndef CCSTRATIGRAPHICPOSITIONABLEELEMENT_H
#define CCSTRATIGRAPHICPOSITIONABLEELEMENT_H

#include <ccSPCElementShell.h>


namespace spc
{
spcFwdDeclSharedPtr(StratigraphicPositionableElement)

}

class ccStratigraphicPositionableElement: public ccSPCElementShell
{
    Q_OBJECT

public:

    Q_PROPERTY(bool Manual READ getManual WRITE setManual)

    Q_PROPERTY(double StratigraphicPosition READ getStratigraphicPosition WRITE setStratigraphicPosition)


    ccStratigraphicPositionableElement(spc::StratigraphicPositionableElementPtr el, const QString& name = QString(""));


    double getStratigraphicPosition();

    void setStratigraphicPosition( const double sp);


    void setManual(const bool status);

    bool getManual();



};

#endif // CCSTRATIGRAPHICPOSITIONABLEELEMENT_H
