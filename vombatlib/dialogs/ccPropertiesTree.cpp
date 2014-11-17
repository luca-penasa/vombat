#include "ccPropertiesTree.h"
#include "ui_ccPropertiesTree.h"

#include <ccSample.h>

#include <QtVariantPropertyManager>

#include <ccAddNewVariantProperty.h>

ccPropertiesTree::ccPropertiesTree(QWidget *parent)
    : QWidget(parent), ui(new Ui::ccPropertiesTree), m_addPropDialog(0),
      m_topProperty(0)
{
    ui->setupUi(this);
    variantManager = new QtVariantPropertyManager(this);

    connect(variantManager,
            SIGNAL(valueChanged(QtProperty *, const QVariant &)), this,
            SLOT(updateObjectWithProperties(QtProperty *, QVariant)));

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addNewVariantProperty()));

    connect(ui->btnRefresh, SIGNAL(clicked()), this, SLOT(refresh()));

    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);

    ui->treeView->setFactoryForManager(variantManager, variantFactory);
}

ccPropertiesTree::~ccPropertiesTree()
{
    delete ui;
}

void ccPropertiesTree::addProperty(QtProperty *property, const QString &id)
{
    propertyToId[property] = id;
    idToProperty[id] = property;
    QtBrowserItem *item = ui->treeView->addProperty(property);
    //    if (idToExpanded.contains(id))
    //        propertyEditor->setExpanded(item, idToExpanded[id]);
}

void
ccPropertiesTree::addPropertyFromMovableElement(spc::Point3D::Ptr el,
                                            QtVariantProperty *parent)
{

    QtVariantPropertyManager *man = dynamic_cast
        <QtVariantPropertyManager *>(parent->propertyManager());

    // a new property group
    QtVariantProperty *property = man->addProperty( QtVariantPropertyManager::groupTypeId());

    // named position, with code position
    property->setPropertyName("Position");
//    property->setPropertyId("Position");

    // write the eigen vector
    Eigen::Vector3f p = el->getPosition();
    addPropertyFromEigenVector(p, property);

    // add as a subprop
    parent->addSubProperty(property);
}

void
ccPropertiesTree::setPropertyMovableElement(QtVariantProperty *property,
                                            const spc::Point3D::Ptr obj)
{
    // managing position
    Eigen::Vector3f p = obj->getPosition();
    fromPropertyToEigenVector(property, p);
    obj->setPosition(p);
}

void
ccPropertiesTree::addPropertyFromEigenVector(const Eigen::Vector3f &v,
                                             QtVariantProperty *parent)
{

    QtVariantPropertyManager *man = dynamic_cast
        <QtVariantPropertyManager *>(parent->propertyManager());

//    QtVariantProperty *property = man->addProperty(
//        QtVariantPropertyManager::groupTypeId(), "EigenVector3f");
//    property->setPropertyId("EigenVector3f");

    QtVariantProperty *x
        = man->addProperty(QVariant::Double, QLatin1String("x"));
//    x->setPropertyId("x");

    QtVariantProperty *y
        = man->addProperty(QVariant::Double, QLatin1String("y"));
//    y->setPropertyId("y");

    QtVariantProperty *z
        = man->addProperty(QVariant::Double, QLatin1String("z"));
//    z->setPropertyId("z");

    x->setValue(v(0));

    y->setValue(v(1));

    z->setValue(v(2));

    parent->addSubProperty(x);
    parent->addSubProperty(y);
    parent->addSubProperty(z);

//    parent->addSubProperty(property);

//    return property;
}

void ccPropertiesTree::fromPropertyToEigenVector(QtVariantProperty *property,
                                              Eigen::Vector3f &p)
{

    QList<QtProperty *> list = property->subProperties();
    for (int i = 0; i < list.size(); ++i) {
        QtVariantProperty *cur_prop = dynamic_cast
            <QtVariantProperty *>(list.at(i));

        if (cur_prop->propertyName() == "x")
            p(0) = cur_prop->value().toDouble();
        else if (cur_prop->propertyName() == "y")
            p(1) = cur_prop->value().toDouble();
        else if (cur_prop->propertyName() == "z")
            p(2) = cur_prop->value().toDouble();
    }
}

void ccPropertiesTree::addPropertyFromSelectionRubberband( const spc::SelectionRubberband::Ptr &sel,
                                                          QtVariantProperty *property)
{
    QtVariantPropertyManager *man = dynamic_cast
        <QtVariantPropertyManager *>(property->propertyManager());

    QtVariantProperty *group = man->addProperty( QtVariantPropertyManager::groupTypeId());
    group->setPropertyName("Rubberband Selection");


    QtVariantProperty *max_distance
        = man->addProperty(QVariant::Double, QLatin1String("Max Distance"));


    max_distance->setValue(sel->getMaxDistance());
    group->addSubProperty(max_distance);

    property->addSubProperty(group);
}

void ccPropertiesTree::fromPropertyToSelectionRubberband(spc::SelectionRubberband::Ptr sel, const QtVariantProperty *property)
{

    QList<QtProperty *>list =property->subProperties();
    for (QtProperty * prop : list)
    {
        QtVariantProperty *var_p = dynamic_cast<QtVariantProperty *>(prop);

        if (var_p->propertyName() == "Max Distance")
            sel->setMaxDistance(var_p->value().toDouble()) ;

     }




}

void ccPropertiesTree::addPropertyFromStratigraphicPositionableElement(spc::StratigraphicPositionableElement::Ptr el, QtVariantProperty *parent_prop)
{
    QtVariantPropertyManager *man = dynamic_cast<QtVariantPropertyManager *>(parent_prop->propertyManager());


    QtVariantProperty *group = man->addProperty( QtVariantPropertyManager::groupTypeId());
    group->setPropertyName("Stratigraphic Positionable Element");




    QtVariantProperty *automatic = man->addProperty(QVariant::Bool, QLatin1String("Manual"));
    automatic->setValue(el->getManual());



    QtVariantProperty *sp
        = man->addProperty(QVariant::Double, QLatin1String("Stratigraphic Position"));

    if (!el->getManual())
        sp->setEnabled(false);

    float sp_ = el->getStratigraphicPosition();
    sp->setValue(sp_);



    group->addSubProperty(automatic);
    group->addSubProperty(sp);

    parent_prop->addSubProperty(group);
}


void ccPropertiesTree::setPropertyToStratigraphicPositionableElement(    QtVariantProperty *parent_prop, spc::StratigraphicPositionableElement::Ptr el)
{
    QList<QtProperty *>list =parent_prop->subProperties();
    for (QtProperty * prop : list)
    {
        QtVariantProperty *var_p = dynamic_cast<QtVariantProperty *>(prop);

        if (var_p->propertyName() == "Manual")
            el->setManual(var_p->value().toBool());

        else if (var_p->propertyName() == "Stratigraphic Position" && el->getManual())
            el->setStratigraphicPosition(var_p->value().toDouble());

     }

}

void ccPropertiesTree::addPropertyFromVariantDataRecord(
        spc::ElementWithVariantProperties::Ptr el, QtVariantProperty *parent)
{





    spc::VariantPropertiesRecord record = el->getVariantPropertiesRecord();
    std::vector<std::string> klist = record.getKeysList();

    if (klist.empty())
        return;

    // new group etc
    QtVariantPropertyManager *man = dynamic_cast
        <QtVariantPropertyManager *>(parent->propertyManager());

    QtVariantProperty *property = man->addProperty(
        QtVariantPropertyManager::groupTypeId());

    // named position, with code position
    property->setPropertyName("Variant Proprieties");


    for(std::string k: klist)
    {
        QtVariantProperty *prop(0);

        spc::VariantProperty spcprop = record.property(k);
        int ty = spcprop.value().which();
        if (ty == 0) // int
        {
            int value = boost::get<int>(spcprop.value());
            prop = man->addProperty(QVariant::Int, QLatin1String(k.c_str()));
            prop->setValue(value);

        } else if (ty == 1) // float
        {
            float value = boost::get<float>(spcprop.value());
            prop = man->addProperty(QVariant::Double, QLatin1String(k.c_str()));
            prop->setValue(value);

        } else if (ty == 2) // string
        {
            std::string value = boost::get<std::string>(spcprop.value());
            prop = man->addProperty(QVariant::String, QLatin1String(k.c_str()));
            prop->setValue(value.c_str());

        } else if (ty == 3) // vector 3d
        {
            Eigen::Vector3f value = boost::get<Eigen::Vector3f>(spcprop.value());
            prop = man->addProperty(QtVariantPropertyManager::groupTypeId());
            addPropertyFromEigenVector(value, prop);

        }
        else
            continue; // and do nothing



        prop->setPropertyName(k.c_str());
        property->addSubProperty(prop);
    }

    parent->addSubProperty(property);


}

void ccPropertiesTree::addPropertySpcElement(spc::ElementBase::Ptr el, QtVariantProperty *parent)
{

}

void ccPropertiesTree::updateWithObject(ccHObject *obj)
{
    clear();

    ccSPCElementShell *test = dynamic_cast<ccSPCElementShell *>(obj);
    if (!test) {
        m_currentItem = 0; // no current item
        return;            // it is not an object from vombat!
    }

    if (m_topProperty)
        delete m_topProperty;

    m_topProperty = variantManager->addProperty(
        QtVariantPropertyManager::groupTypeId(), "Vombat Object");

    spc::ElementBase::Ptr element = test->getSPCElement();



    DtiClassType * type = element->getType();


    while (type->getParent())
    {

        if (*type == spc::Point3D::Type)
            addPropertyFromMovableElement(spcDynamicPointerCast<spc::Point3D> (element), m_topProperty);

        if (*type == spc::SelectionRubberband::Type)
            addPropertyFromSelectionRubberband(spcDynamicPointerCast<spc::SelectionRubberband>(element), m_topProperty);

        if (* type == spc::StratigraphicPositionableElement::Type)
            addPropertyFromStratigraphicPositionableElement(spcDynamicPointerCast<spc::StratigraphicPositionableElement>(element), m_topProperty);

        type = type->getParent();

    }

    // now infos coming from interfaces
    if (element->hasVariantProperties())
        addPropertyFromVariantDataRecord(spcDynamicPointerCast<spc::ElementWithVariantProperties> (element), m_topProperty);

    QtBrowserItem *item = ui->treeView->addProperty(m_topProperty);
}

void ccPropertiesTree::updateObjectWithProperties(QtProperty *property,
                                                  const QVariant &value)
{
    if (!m_currentItem)
        return;

    QList<QtProperty *> current_props = m_topProperty->subProperties();

    for (int i = 0; i < current_props.size(); ++i) {
        QtProperty *prop = current_props.at(i);
        QtVariantProperty *varProp = dynamic_cast<QtVariantProperty *>(prop);

        ccSPCElementShell *myobj = dynamic_cast<ccSPCElementShell *>(m_currentItem);

        if (!myobj)
        {
            LOG(ERROR) << "Trying to set the properties on a NON-spc element! This should never happen.";
            return;
        }

        if (varProp->propertyName() == "Position")
        {

            spc::Point3D::Ptr movable = spcDynamicPointerCast<spc::Point3D>(myobj->getSPCElement());
            setPropertyMovableElement(varProp, movable);
        }

        if (varProp->propertyName() == "Rubberband Selection")
        {
            spc::SelectionRubberband::Ptr sel = spcDynamicPointerCast<spc::SelectionRubberband>(myobj->getSPCElement());
            fromPropertyToSelectionRubberband(sel, varProp);
        }

        if (varProp->propertyName() == "Stratigraphic Positionable Element")
        {
            spc::StratigraphicPositionableElement::Ptr my= spcDynamicPointerCast<spc::StratigraphicPositionableElement>(myobj->getSPCElement());
            setPropertyToStratigraphicPositionableElement(varProp, my);
        }

        LOG(INFO) << "PROP NAME: " << varProp->propertyName().toStdString();

        if (varProp->propertyName() == "Max Distance")
        {

            spc::SelectionRubberband::Ptr sel = spcDynamicPointerCast<spc::SelectionRubberband>(myobj->getSPCElement());
             LOG(INFO) << "updating in object";
            fromPropertyToSelectionRubberband(sel, varProp);
        }
    }


}

void ccPropertiesTree::selectionChanged(const ccHObject::Container &sel)
{

    m_currentItem = 0;
    clear();
    if (!sel.empty()) {
        ccHObject *first = sel.at(0); // only first object in selection for now
        this->updateWithObject(first);
        m_currentItem = first;
    }
}

void ccPropertiesTree::addNewVariantProperty()
{

    if (!m_currentItem)
        return;

    if (!m_addPropDialog)
        m_addPropDialog = new ccAddNewVariantProperty(this);
    int accepted = m_addPropDialog->exec();

    if (!accepted)
        return;

    QString name = m_addPropDialog->getName();

    int typ = m_addPropDialog->getType();

    if (m_currentItem->getMetaData("class_name") == "ccSample") {
        ccSample *sam = dynamic_cast<ccSample *>(m_currentItem);
        spc::ElementWithVariantProperties::Ptr spc_sample = sam->getSample();

        if (!spc_sample)
            return;

        spc::VariantProperty::VarianT value;

        if (typ == 0)
            value = 0;
        else if (typ == 1)
            value = 0.0f;
        else if (typ == 2)
            value = std::string("");


        spc_sample->getVariantPropertiesRecord().property(name.toStdString()) = value;
    }
}

void ccPropertiesTree::forceUpdate()
{
    //    clear();
    if (!m_currentItem) {
        return;
    }

    updateWithObject(m_currentItem);
}

void ccPropertiesTree::clear()
{
    propertyToId.clear();
    idToProperty.clear();
    ui->treeView->clear();
}

void ccPropertiesTree::refresh()
{
    if (m_currentItem)
        emit objectChanged(m_currentItem);
}



