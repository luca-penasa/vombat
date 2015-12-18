#ifndef CC_VIRTUAL_OUTCROP_H
#define CC_VIRTUAL_OUTCROP_H


#include <ccoutofcore/ccSPCElementShell.h>
#include <QIcon>

#include <spc/elements/VirtualOutcrop.h>

class ccVirtualOutcrop:  public ccSPCElementShell
{
public:

    ccVirtualOutcrop(): ccSPCElementShell (spc::VirtualOutcrop::Ptr(new spc::VirtualOutcrop))
    {

    }

    ccVirtualOutcrop(spc::VirtualOutcrop::Ptr outcrop): ccSPCElementShell(outcrop)
    {

    }

    ~ccVirtualOutcrop()
    {

    }

    //inherited methods (ccHObject)
    virtual bool hasColors() const { return true; }
    virtual ccBBox getMyOwnBB()
    {

		ccBBox bb;
        return bb;
    }

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/outcrop.png"));
    }

    //inherited from ccSerializableObject
    virtual bool isSerializable() const
    {
        return true;
    }

protected:

    virtual void drawMeOnly(CC_DRAW_CONTEXT &context)
    {

    }


    spc::VirtualOutcrop::Ptr getVirtualOutcrop() const
    {
        return getSPCElement<spc::VirtualOutcrop>();
    }

};//end class

#endif // CCPLANEORIENTATION_H
