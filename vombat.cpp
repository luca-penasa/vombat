#include "vombat.h"


#include <ccPointCloud.h>
#include <BaseFilter.h>
//#include <ComputeTimeSeries.h>
//#include <ComputeStratigraphicPosition.h>
//#include <FitAttitude.h>
//#include <AttitudeToModel.h>
//#include <Edit.h>
//#include <SaveSPCElement.h>
//#include <LoadSPCElement.h>

//#include <EvaluateStratigraphicPosition.h>
//#include <Properties.h>
//#include <CloudToPlanarSelection.h>
//#include <SetUpNewSeries.h>
//#include <split_point_cloud.h>
#include <OpenPlotsDialog.h>
//#include <OpenPlots2DDialog.h>
//#include <ExportToAscii.h>
//#include <ApplyCorrection.h>
//#include <test.h>
//
//#include <SendTo2DPlot.h>
//
//#include <PlotterDlg.h>
//
//#include <CalibrateDevice.h>
//
//#include <GaussianFilter.h>

#include <spc/methods/time_series_generator.h>


#include <boost/foreach.hpp>


static vombat * qgeo_instance = 0;

vombat::vombat()
{
    qgeo_instance = this;
    spc::TimeSeriesGenerator gen;
    std::cout << "generator created!" << std::endl;

}

vombat::~vombat()
{
	while (!m_filters.empty())
	{
		delete m_filters.back();
		m_filters.pop_back();
	}
}

void vombat::handleNewEntity(ccHObject* entity)
{
	assert(entity && m_app);
    entity->setSelected(true);
	m_app->addToDB(entity);


}

void vombat::handleEntityChange(ccHObject* entity)
{
	assert(entity && m_app);
	entity->prepareDisplayForRefresh_recursive();
	m_app->refreshAll();
	m_app->updateUI();
}

void vombat::handleErrorMessage(QString message)
{
	assert(m_app);

	m_app->dispToConsole(qPrintable(message),ccMainAppInterface::ERR_CONSOLE_MESSAGE);
}

void vombat::getActions(QActionGroup& group)
{
    if (m_filters.empty())
    {
        //ADD FILTERS
//        addFilter(new FitAttitude(this));
//        addFilter(new AttitudeToModel(this));
//        addFilter(new EvaluateStratigraphicPosition(this));
//        addFilter(new Edit(this));
//
//
//        addFilter(new OpenPlotsDialog(this));
//        addFilter(new OpenPlots2DDialog(this));
//
////        m_plotter = openPlot->getPlotterDlg();
//
//
//
//        addFilter(new SetUpNewSeries(this));
//        addFilter(new SaveSPCElement(this));
//        addFilter(new LoadSPCElement(this));
//        addFilter(new Test(this));
//
//        addFilter(new CalibrateDevice(this));
//        addFilter(new ApplyCorrection(this));
//
//
//        addFilter(new SendTo2DPlot(this));
//
////        addFilter( new ComputeStratigraphicPosition(this) );
////        addFilter( new ComputeTimeSeries(this));
////        addFilter(new SplitPointCloud(this));
//
////        addFilter(new EvaluateStratigraphicPosition(this));
////        addFilter(new Properties(this));
//        addFilter(new CloudToPlanarSelection(this));
//        addFilter(new ExportToAscii(this));
//        addFilter(new GaussianFilter(this));
//
////        addFilter(new ApplyCorrection(this));
//
//
//
    }

    for (std::vector<BaseFilter*>::const_iterator it = m_filters.begin(); it != m_filters.end(); ++it)
        group.addAction((*it)->getAction());
}

int vombat::addFilter(BaseFilter * filter)
{
    assert(filter);
    filter->setMainAppInterface(m_app);

    QAction *action = filter->getAction();
    if (!action)
        return 0;

    //filter already inserted?
    if (std::find(m_filters.begin(),m_filters.end(),filter) != m_filters.end())
        return 0;

    m_filters.push_back(filter);

    //connect signals
    connect(filter, SIGNAL(newEntity(ccHObject*)),          this,   SLOT(handleNewEntity(ccHObject*)));
    connect(filter, SIGNAL(entityHasChanged(ccHObject*)),   this,   SLOT(handleEntityChange(ccHObject*)));
    connect(filter, SIGNAL(newErrorMessage(QString)),       this,   SLOT(handleErrorMessage(QString)));

    return 1;
}



ccHObject::Container vombat::getSelected() const
{
    return m_selected;
}

ccHObject::Container vombat::getSelectedThatHaveMetaData(const QString key) const
{
    ccHObject::Container sel = getSelected();
    ccHObject::Container new_sel;

    BOOST_FOREACH(ccHObject * obj, sel)
    {
        if (obj->hasMetaData(key))
            new_sel.push_back(obj);

    }

    return new_sel;

}

ccHObject::Container vombat::getSelectedThatAre(CC_CLASS_ENUM ThisType) const
{
    ccHObject::Container sel = getSelected(); // all selected  

    ccHObject::Container out = vombat::filterObjectsByType(sel, ThisType);

    return out;

}

ccHObject::Container vombat::getSelectedKindOf(CC_CLASS_ENUM ThisType)
{
    ccHObject::Container sel = getSelected(); // all selected

    ccHObject::Container out = vombat::filterObjectsByKind(sel, ThisType);

    return out;

}

ccHObject::Container vombat::filterObjectsByType(const ccHObject::Container &in, const CC_CLASS_ENUM ThisType)
{
    if (in.empty())
        return in;

    ccHObject::Container out;
    BOOST_FOREACH(ccHObject * obj, in)
    {
        if (obj->isA(ThisType))
        {
            out.push_back(obj);
        }
    }

    return out;
}

ccHObject::Container vombat::filterObjectsByKind(const ccHObject::Container &in, const CC_CLASS_ENUM ThisType)
{
    if (in.empty())
        return in;

    ccHObject::Container out;
    BOOST_FOREACH (ccHObject * obj, in)
    {
        if (obj->isKindOf(ThisType))
        {
            out.push_back(obj);
        }
    }

    return out;
}

ccHObject::Container vombat::getAllObjectsInTreeThatHaveMetaData( const QString key)
{

    ccHObject::Container all = this->getAllObjectsInTree();

    return vombat::filterObjectsByMetaData(all, key);
}

ccHObject::Container vombat::getAllObjectsInTreeThatAre(CC_CLASS_ENUM ThisType)
{
    ccHObject::Container all = getAllObjectsInTree();
    std::cout << "in tree " <<  all.size() << std::endl;
    return vombat::filterObjectsByType(all, ThisType);
}

ccHObject::Container vombat::getAllChildren(ccHObject *object)
{
    int n = object->getChildrenNumber();
    ccHObject::Container cont;
    for (int i = 0; i < n; ++i)
    {
        cont.push_back(object->getChild(i));
    }
    return cont;
}

ccHObject::Container vombat::filterObjectsByMetaData(const ccHObject::Container &in, const QString key)
{
    ccHObject::Container out;
   BOOST_FOREACH (ccHObject * obj, in)
    {
        if (obj->hasMetaData(key))
        {
            out.push_back(obj);
        }
    }

    return out;
}

ccHObject::Container vombat::getAllObjectsInTree()
{
//    ccHObject::Container cont;

    ccHObject* dbroot = this->getMainAppInterface()->dbRootObject();
    ccHObject::Container tovisit;
    tovisit.push_back(dbroot);

    ccHObject::Container out;

    while (!tovisit.empty())
    {
        ccHObject  * last = tovisit.back();
        tovisit.pop_back();

        out.push_back(last);

        ccHObject::Container sons = getAllChildren(last);

        BOOST_FOREACH (ccHObject * obj, sons)
        {
            tovisit.push_back(obj);
        }
    }
    return out;
}


void vombat::onNewSelection(const ccHObject::Container& selectedEntities)
{
    for (unsigned i=0;i<m_filters.size();++i)
        m_filters[i]->updateSelectedEntities(selectedEntities);

    m_selected = selectedEntities;

    emit selectionChanged(m_selected);
}

QIcon vombat::getIcon() const
{
    return QIcon(QString::fromUtf8(":/toolbar/vombat.png"));
}

vombat *vombat::theInstance()
{
    return qgeo_instance;
}

QMainWindow *vombat::getMainWindow()
{
    return getMainAppInterface()->getMainWindow();
}

PlotterDlg *vombat::getPlotterDlg()
{
    BOOST_FOREACH(BaseFilter * f, m_filters)
    {
//        OpenPlotsDialog * open_plot_filter = dynamic_cast<OpenPlotsDialog *>(f);
        if (typeid(*f) ==typeid(OpenPlotsDialog))
        {
            std::cout << "found!"<<std::endl;
            return static_cast<OpenPlotsDialog *> (f)->getPlotterDlg();
        }

    }
    return 0;
}

Plotter2DDlg *vombat::getPlotter2DDlg()
{
    BOOST_FOREACH(BaseFilter * f, m_filters)
    {
//        OpenPlotsDialog * open_plot_filter = dynamic_cast<OpenPlotsDialog *>(f);
        if (typeid(*f) ==typeid(OpenPlots2DDialog))
        {
            std::cout << "found!"<<std::endl;
            return static_cast<OpenPlots2DDialog *> (f)->getPlotterDlg();
        }

    }
    return 0;
}

//plugin export
Q_EXPORT_PLUGIN2
(vombat,vombat)
