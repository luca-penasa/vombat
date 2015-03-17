#ifndef Q_VOMBAT_PLUGIN_HEADER
#define Q_VOMBAT_PLUGIN_HEADER


#include <ccStdPluginInterface.h>

#include <QObject>
#include <QtGui>

#include <spc/core/DtiClass.h>
#include <spc/elements/ElementBase.h>

class PlotterDlg;
//class QToolBar;
class QMenu;
class OpenPlotsDialog;
class Plotter2DDlg;
class ccSPCElementShell;
class BaseFilter;

//! PCL bridge plugin
class vombat : public QObject, public ccStdPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(ccStdPluginInterface)

#ifdef CC_QT5
	Q_PLUGIN_METADATA(IID "cccorp.cloudcompare.plugin.vombat")
#endif

public:
    //! Default constructor
    vombat();

    //!Destructor
    virtual ~vombat();


    virtual QString getName() const { return "vombat"; }
    virtual QString getDescription() const { return "Geologic stuff for qCC"; }
    virtual QIcon getIcon() const;

    static vombat *theInstance();

    QString getErrorMessage(int errorCode/*, LANGUAGE lang*/);

    virtual void onNewSelection(const ccHObject::Container& selectedEntities);
    virtual void getActions(QActionGroup& group);

	//! Adds a filter
    int addFilter(BaseFilter* filter);

    //! Return a plotter object for plotting things
    //! for now only one plotter at a time is possible!
//    PlotterDlg *getPlotterDlg();

//    OpenPlotsDialog * getPlotTool();

    QMainWindow * getMainWindow();


    PlotterDlg * getPlotterDlg();

    Plotter2DDlg * getPlotter2DDlg();





    ///////// ACCESS TO DBTREE ///////////////////////////////
    /// \brief getSelected
    /// \return
    /// NOTE these implementation ahre always late!!!
    ///  so notice that you got the "previously selected stuff - I must find what is wrong
    ccHObject::Container getSelected() const;
    ccHObject::Container getSelectedThatHaveMetaData(const QString key) const;
    ccHObject::Container getSelectedThatAre(CC_CLASS_ENUM ThisType) const;
    ccHObject::Container getSelectedKindOf(CC_CLASS_ENUM ThisType);


    ccHObject::Container getAllObjectsInTree();
    ccHObject::Container getAllObjectsInTreeBySPCDti(const DtiClassType * dti);


    ccHObject::Container getAllObjectsSelectedBySPCDti(const DtiClassType * dti);

    ccHObject::Container getAllObjectsInTreeThatHaveMetaData(const QString key,
                                                             const QString value = QString() );
    ccHObject::Container getAllObjectsInTreeThatAre(CC_CLASS_ENUM ThisType);

    ccHObject * getObjectFromElement(const spc::ElementBase::Ptr el);

    static ccHObject::Container getAllChildren(ccHObject * object);




    ///////// STATIC FILTERS //////////////////////////////////
    static ccHObject::Container filterObjectsByType(const ccHObject::Container &in, const CC_CLASS_ENUM ThisType);

    /** if value is not set ALL the objects which has the key will be returned,
     * while if a value is set the metadata at key should be == value
     **/
    static ccHObject::Container filterObjectsByMetaData (const ccHObject::Container &in,
                                                         const QString key,
                                                         const QString value = QString());


    static ccHObject::Container filterObjectsByKind(const ccHObject::Container &in, const CC_CLASS_ENUM ThisType);



signals:
    void selectionChanged(ccHObject::Container & selection);

public slots:
	//! Handles new entity
	void handleNewEntity(ccHObject*);

	//! Handles entity (visual) modification
	void handleEntityChange(ccHObject*);

	//! Handles new error message
	void handleErrorMessage(QString);
	

protected:
	//! Loaded filters
	std::vector<BaseFilter*> m_filters;

    ccHObject::Container m_selected;

    ccExternalFactory * m_factory;

     ccPluginInterface * interface;
public:
    ccExternalFactory *getCustomObjectsFactory() const
    {
        return m_factory;
    }
};


#endif//END Q_VOMBAT_PLUGIN_HEADER
