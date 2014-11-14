#ifndef CCPROPERTIESTREE_H
#define CCPROPERTIESTREE_H

#include <QWidget>
#include <ccHObject.h>
#include <QtVariantProperty>
#include <ccMyBaseObject.h>
#include <spc/elements/MovableElement.h>
#include <spc/elements/ElementWithVariantProperties.h>
#include <spc/elements/SelectionRubberband.h>

#include <spc/elements/StratigraphicPositionableElement.h>

class ccAddNewVariantProperty;

namespace Ui
{
class ccPropertiesTree;
}

class ccPropertiesTree : public QWidget
{
    Q_OBJECT

public:
    explicit ccPropertiesTree(QWidget *parent = 0);
    ~ccPropertiesTree();

    void addProperty(QtProperty *property, const QString &id);

    ///// getters and setters for properties
    /// in a future we may want to move these to SPC if it had Qt support,
    /// so keep them static

    //! MOVABLE ELEMENT
    static void addPropertyFromMovableElement(spc::Point3D::Ptr el,
                                                 QtVariantProperty *parent);

    static void setPropertyMovableElement(QtVariantProperty *property,
                                          const spc::Point3D::Ptr obj);


    static void addPropertyFromStratigraphicPositionableElement(spc::StratigraphicPositionableElement::Ptr el,
                                                                 QtVariantProperty *parent_prop);

    static void setPropertyToStratigraphicPositionableElement(QtVariantProperty *parent_prop, spc::StratigraphicPositionableElement::Ptr el);

    static void addPropertyFromEigenVector(const Eigen::Vector3f &v,
                                           QtVariantProperty *parent);

    static void fromPropertyToEigenVector(QtVariantProperty *property,
                                       Eigen::Vector3f &p);


    static void addPropertyFromSelectionRubberband(const spc::SelectionRubberband::Ptr &sel, QtVariantProperty *property);


    static void fromPropertyToSelectionRubberband( spc::SelectionRubberband::Ptr sel, const QtVariantProperty *property);



    //! BOOST-VARIANT BASED PROPERTIES ELEMENT
    static void addPropertyFromVariantDataRecord(spc::ElementWithVariantProperties::Ptr el,
                                                 QtVariantProperty *parent);

    static void setPropertyVariantDataRecord(
        QtProperty *property, const QVariant value,
        const spc::ElementWithVariantProperties::Ptr obj)
    {
    }

    static void addPropertySpcElement(spc::ElementBase::Ptr el,
                                      QtVariantProperty *parent);

public
slots:
    void updateWithObject(ccHObject *obj);

    void updateObjectWithProperties(QtProperty *property,
                                    const QVariant &value);

    void selectionChanged(const ccHObject::Container &sel);

    void addNewVariantProperty();

    void forceUpdate();

    void clear();

    void refresh();

signals:
    void objectChanged(ccHObject *);

private:
    Ui::ccPropertiesTree *ui;

    class QtVariantPropertyManager *variantManager;

    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtProperty *> idToProperty;
    QMap<QString, bool> idToExpanded;

    ccHObject *m_currentItem;

    ccAddNewVariantProperty *m_addPropDialog;

    QtVariantProperty *m_topProperty;
};

#endif // CCPROPERTIESTREE_H
