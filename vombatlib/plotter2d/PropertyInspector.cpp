#include "PropertyInspector.h"

//#include <QtDoublePropertyManager>
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"
#include <spc/core/logging.h> //debug
#include "variantmanager.h"
#include "variantfactory.h"
#include <QMetaEnum>

#include <ExtendedVariantManager.h>

PropertyBrowser::PropertyBrowser(QWidget *parent)
    : QtTreePropertyBrowser(parent) {
    setRootIsDecorated(true);
    setAlternatingRowColors(true);

    m_manager = new ExtendedVariantManager(this);
    m_readOnlyManager = new ExtendedVariantManager(this);

    //    m_object = nullptr;

    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    setFactoryForManager(m_manager, variantFactory);

    connect(m_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this,
            SLOT(slotValueChanged(QtProperty *, const QVariant &)));
}

int PropertyBrowser::enumToInt(const QMetaEnum &metaEnum, int enumValue) const {
    QMap<int, int>
            valueMap; // dont show multiple enum values which have the same values
    int pos = 0;
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        int value = metaEnum.value(i);
        if (!valueMap.contains(value)) {
            if (value == enumValue)
                return pos;
            valueMap[value] = pos++;
        }
    }
    return -1;
}

int PropertyBrowser::intToEnum(const QMetaEnum &metaEnum, int intValue) const {
    QMap<int, bool>
            valueMap; // dont show multiple enum values which have the same values
    QList<int> values;
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        int value = metaEnum.value(i);
        if (!valueMap.contains(value)) {
            valueMap[value] = true;
            values.append(value);
        }
    }
    if (intValue >= values.count())
        return -1;
    return values.at(intValue);
}

bool PropertyBrowser::isSubValue(int value, int subValue) const {
    if (value == subValue)
        return true;
    int i = 0;
    while (subValue) {
        if (!(value & (1 << i))) {
            if (subValue & 1)
                return false;
        }
        i++;
        subValue = subValue >> 1;
    }
    return true;
}

bool PropertyBrowser::isPowerOf2(int value) const {
    while (value) {
        if (value & 1) {
            return value == 1;
        }
        value = value >> 1;
    }
    return false;
}

void PropertyBrowser::setObject(QObject *object, QList<QObject *> mirror) {

    if ((m_object == object) && (m_mirror_objects == mirror))
        return;

    if (m_object || object == nullptr) { // there was an object before.
        // clean please
        //		saveExpandedState();
        QListIterator<QtProperty *> it(m_topLevelProperties);
        while (it.hasNext()) {
            removeProperty(it.next());
        }
        m_topLevelProperties.clear();
    }

    m_object = object;
    m_mirror_objects = mirror;


    if (m_object) {
        LOG(INFO) << "adding class prop.";
        LOG(INFO) << "set object of type: " << object->metaObject()->className();

        LOG(INFO) << "we have: " << mirror.size() << " mirroring objects";

        addClassProperties(m_object->metaObject());


    }
    //		restoreExpandedState();



}

int PropertyBrowser::flagToInt(const QMetaEnum &metaEnum, int flagValue) const {
    if (!flagValue)
        return 0;
    int intValue = 0;
    QMap<int, int>
            valueMap; // dont show multiple enum values which have the same values
    int pos = 0;
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        int value = metaEnum.value(i);
        if (!valueMap.contains(value) && isPowerOf2(value)) {
            if (isSubValue(flagValue, value))
                intValue |= (1 << pos);
            valueMap[value] = pos++;
        }
    }
    return intValue;
}

int PropertyBrowser::intToFlag(const QMetaEnum &metaEnum, int intValue) const {
    QMap<int, bool>
            valueMap; // dont show multiple enum values which have the same values
    QList<int> values;
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        int value = metaEnum.value(i);
        if (!valueMap.contains(value) && isPowerOf2(value)) {
            valueMap[value] = true;
            values.append(value);
        }
    }
    int flagValue = 0;
    int temp = intValue;
    int i = 0;
    while (temp) {
        if (i >= values.count())
            return -1;
        if (temp & 1)
            flagValue |= values.at(i);
        i++;
        temp = temp >> 1;
    }
    return flagValue;
}

void PropertyBrowser::addClassProperties(const QMetaObject *metaObject) {
    if (!metaObject)
    {
        LOG(WARNING) << "Metaobject was null";
        return;
    }
    LOG(WARNING) << "Metaobject not null";


    addClassProperties(metaObject->superClass());

    QtProperty *classProperty = m_classToProperty.value(metaObject);

    if (!classProperty) // we need to create the subproperty
    {
        DLOG(WARNING) << "Null class property";

        QString className = QLatin1String(metaObject->className());
        classProperty = m_manager->addProperty(
                    QtVariantPropertyManager::groupTypeId(), className);
        m_classToProperty[metaObject] = classProperty;
        m_propertyToClass[classProperty] = metaObject;

        for (int idx = metaObject->propertyOffset();
             idx < metaObject->propertyCount(); idx++)
        {
            QMetaProperty metaProperty = metaObject->property(idx);
            int type = metaProperty.userType();

            QtVariantProperty *subProperty = nullptr;

            if (!metaProperty.isReadable())
            {
                subProperty = m_readOnlyManager->addProperty(
                            QVariant::String, QLatin1String(metaProperty.name()));
                subProperty->setValue(QLatin1String("< Non Readable >"));
            }
            else if (metaProperty.isEnumType())
            {
                if (metaProperty.isFlagType())
                {
                    subProperty =
                            m_manager->addProperty(QtVariantPropertyManager::flagTypeId(),
                                                   QLatin1String(metaProperty.name()));
                    QMetaEnum metaEnum = metaProperty.enumerator();
                    QMap<int, bool> valueMap;
                    QStringList flagNames;
                    for (int i = 0; i < metaEnum.keyCount(); i++)
                    {
                        int value = metaEnum.value(i);
                        if (!valueMap.contains(value) && isPowerOf2(value))
                        {
                            valueMap[value] = true;
                            flagNames.append(QLatin1String(metaEnum.key(i)));
                        }
                        subProperty->setAttribute(QLatin1String("flagNames"), flagNames);
                        subProperty->setValue(
                                    flagToInt(metaEnum, metaProperty.read(m_object).toInt()));
                    }
                }
                else
                {
                    subProperty =
                            m_manager->addProperty(QtVariantPropertyManager::enumTypeId(),
                                                   QLatin1String(metaProperty.name()));
                    QMetaEnum metaEnum = metaProperty.enumerator();
                    QMap<int, bool> valueMap; // dont show multiple enum values which have
                    // the same values
                    QStringList enumNames;
                    for (int i = 0; i < metaEnum.keyCount(); i++)
                    {
                        int value = metaEnum.value(i);
                        if (!valueMap.contains(value))
                        {
                            valueMap[value] = true;
                            enumNames.append(QLatin1String(metaEnum.key(i)));
                        }
                    }
                    subProperty->setAttribute(QLatin1String("enumNames"), enumNames);
                    subProperty->setValue(
                                enumToInt(metaEnum, metaProperty.read(m_object).toInt()));
                }
            }
            else if (m_manager->isPropertyTypeSupported(type))
            {
                if (!metaProperty.isWritable())
                    subProperty = m_readOnlyManager->addProperty(
                                type, QLatin1String(metaProperty.name()) +
                                QLatin1String(" (Non Writable)"));

                if (!metaProperty.isDesignable())
                    subProperty = m_readOnlyManager->addProperty(
                                type, QLatin1String(metaProperty.name()) +
                                QLatin1String(" (Non Designable)"));
                else
                    subProperty =
                            m_manager->addProperty(type, QLatin1String(metaProperty.name()));


                subProperty->setValue(metaProperty.read(m_object));
            }
            else
            {
                LOG(WARNING) << "Property yet exists";


                addClassProperties(metaObject);
                subProperty = m_readOnlyManager->addProperty(
                            QVariant::String, QLatin1String(metaProperty.name()));
                //				subProperty->setValue(metaProperty.read(m_object));

                LOG(INFO) << "settting the value of class " << metaObject->className();
                LOG(INFO) << "settting the value of metapro " << metaProperty.name();

                //				QVariant stuff =
                //metaProperty.read(m_object);
                //				if (stuff.canConvert<QBrush>())
                //				{
                //					LOG(INFO) << "can convert!";

                //					QBrush  a =
                //stuff.value<QBrush>();

                //						LOG(INFO) << "found a good QCPAxis
                //*";
                //						const QMetaObject *mobj =
                //a.metaObject();
                //						if (mobj != NULL)
                //						{
                //							LOG(INFO) << "no
                //null!";
                //							addClassProperties(mobj);
                //						}

                //				}

                //				LOG(INFO) << stuff.typeName();

                //				if (g)
                //					LOG(INFO) << "--> we have a valid
                //scatterstyle!" ;

                subProperty->setValue(QLatin1String("< Unknown Type >"));
                subProperty->setEnabled(false);
            }

            classProperty->addSubProperty(subProperty);
            m_propertyToIndex[subProperty] = idx;
            m_classToIndexToProperty[metaObject][idx] = subProperty;
        }
    }
    else
    {
        updateClassProperties(metaObject, false);
    }

    m_topLevelProperties.append(classProperty);
        addProperty(classProperty);
}

void PropertyBrowser::updateClassProperties(const QMetaObject *metaObject,
                                            bool recursive) {

    LOG(INFO) << "begin of updateClassProperties";

    if (metaObject == NULL) {
        LOG(INFO) << "META OBJECt is null! returning.";
        return;
    }

    LOG(INFO) << "after null checking, recusrsive is  " << recursive;

    if (recursive) {
        LOG(INFO) << metaObject->className();
        LOG(INFO) << "going to get the superclass";
        const QMetaObject *superclass = metaObject->superClass();
        if (superclass != NULL) {
            LOG(INFO)
                    << "going to call updateClassProperties again with the superclass: "
                    << superclass->className();
            updateClassProperties(superclass, recursive);
            LOG(INFO) << "done";
        }
    }

    LOG(INFO) << "going ahead";

    QtProperty *classProperty = m_classToProperty.value(metaObject);
    if (!classProperty)
        return;

    for (int idx = metaObject->propertyOffset();
         idx < metaObject->propertyCount(); idx++) {
        QMetaProperty metaProperty = metaObject->property(idx);
        if (metaProperty.isReadable()) {
            if (m_classToIndexToProperty.contains(metaObject) &&
                    m_classToIndexToProperty[metaObject].contains(idx)) {
                QtVariantProperty *subProperty =
                        m_classToIndexToProperty[metaObject][idx];
                if (metaProperty.isEnumType()) {
                    if (metaProperty.isFlagType())
                        subProperty->setValue(
                                    flagToInt(metaProperty.enumerator(),
                                              metaProperty.read(m_object).toInt()));
                    else
                        subProperty->setValue(
                                    enumToInt(metaProperty.enumerator(),
                                              metaProperty.read(m_object).toInt()));
                } else {
                    subProperty->setValue(metaProperty.read(m_object));
                }
            }
        }
    }
}

void PropertyBrowser::saveExpandedState() {}

void PropertyBrowser::restoreExpandedState() {}

//! this write into the object
void PropertyBrowser::slotValueChanged(QtProperty *property,
                                       const QVariant &value) {

    LOG(INFO) << "SLOT VALUE CHANGED";
    if (!m_propertyToIndex.contains(property))
        return;

    int idx = m_propertyToIndex.value(property);

    const QMetaObject *metaObject = m_object->metaObject();
    QMetaProperty metaProperty = metaObject->property(idx);
    if (metaProperty.isEnumType()) {
        if (metaProperty.isFlagType())
            metaProperty.write(m_object,
                               intToFlag(metaProperty.enumerator(), value.toInt()));
        else
            metaProperty.write(m_object,
                               intToEnum(metaProperty.enumerator(), value.toInt()));
    } else {
        metaProperty.write(m_object, value);
    }

    LOG(INFO) << "going to update" << metaObject->className();

        if (!m_mirror_objects.empty()) // we try to update this property on
//        mirror objects
        {
            for (QObject * obj : m_mirror_objects)
            {
                const QMetaObject *metaObject = obj->metaObject();

                for (int i = 0 ; i < metaObject->propertyCount(); ++i)
                {
                    QMetaProperty metaProp = metaObject->property(i);

                    if(metaProp.name() == property->propertyName())
                    {
                        LOG(INFO) << "Found corresponding prop for "<<
                        metaProp.name();

                        if (metaProp.isEnumType()) {
                            if (metaProp.isFlagType())
                                metaProp.write(obj,
                                intToFlag(metaProp.enumerator(),
                                value.toInt()));
                            else
                                metaProp.write(obj,
                                intToEnum(metaProp.enumerator(),
                                value.toInt()));
                        } else {
                            metaProp.write(obj, value);
                        }
                    }

                }
            }
        }

    updateClassProperties(metaObject, true);
}
