#include "vombat.h"




#include <ccSPCElementShell.h>
#include <ccPointCloud.h>

#include "BaseFilter.h"

#include <FitAttitude.h>
#include <AttitudeToModel.h>
#include <Edit.h>
#include <SaveSPCElement.h>
#include <LoadSPCElement.h>

#include <EvaluateDynamicScalarFieldGenerator.h>
#include <Properties.h>
#include <CloudToPlanarSelection.h>
//#include <SetUpNewSeries.h>
//#include <split_point_cloud.h>
#include <OpenPlotsDialog.h>
#include <OpenPlots2DDialog.h>
//#include <ExportToAscii.h>
#include <ApplyCorrection.h>
#include <FlipModel.h>
#include <NewRoi.h>
#include <CreateStratigraphicConstrain.h>
#include <CreateOutcrop.h>
#include <LinkModelToRubberband.h>

#include <AddSample.h>

#include <CreateTimeSeriesFromScalarFields.h>
#include <AutoComputeTimeSeries.h>
//#include <ComputeCalibrationDB.h>
//#include <test.h>

//#include <ComputeSmoothedTimeSeriesXY.h>

#include <SendTo2DPlot.h>

#include <PlotterDlg.h>

//#include <CalibrateDevice.h>

#ifdef SPC_WITH_PCL
#include <GaussianFilter.h>
#endif
#include <Properties.h>

#include <spc/methods/TimeSeriesGenerator.h>

#include <ccVombatObjectsFactory.h>

#include <boost/foreach.hpp>

#include <LoadCloudDataSource.h>

static vombat *qgeo_instance = 0;



vombat::vombat()
{

    google::InitGoogleLogging("vombat");
    DLOG(WARNING) << "Logging started";

    qgeo_instance = this;
    m_factory = new ccVombatObjectsFactory("vombat");

    DLOG(INFO) << "Vombat plugin created";
}

vombat::~vombat()
{
    while (!m_filters.empty()) {
        delete m_filters.back();
        m_filters.pop_back();
    }
}

void vombat::handleNewEntity(ccHObject *entity)
{
    assert(entity && m_app);
    m_app->addToDB(entity);
}

void vombat::handleEntityChange(ccHObject *entity)
{
    assert(entity && m_app);
    entity->prepareDisplayForRefresh_recursive();
    m_app->refreshAll();
    m_app->updateUI();
}

void vombat::handleErrorMessage(QString message)
{
    assert(m_app);

    m_app->dispToConsole(qPrintable(message),
                         ccMainAppInterface::ERR_CONSOLE_MESSAGE);
}

void vombat::getActions(QActionGroup &group)
{
    if (m_filters.empty()) {
        // ADD FILTERS

        addFilter(new CreateOutcrop(this));
        addFilter(new FitAttitude(this));
        addFilter(new AttitudeToModel(this));
        addFilter(new FlipModel(this));
//        addFilter(new LinkModelToRubberband(this));

        addFilter(new EvaluateDynamicScalarFieldGenerator(this));
        addFilter(new Edit(this));

        //        addFilter(new OpenPlotsDialog(this));

        addFilter(new OpenPlots2DDialog(this));
        addFilter(new CreateTimeSeriesFromScalarFields(this));
        addFilter(new SendTo2DPlot(this));

        //        m_plotter = openPlot->getPlotterDlg();

        //        addFilter(new ComputeSmoothedTimeSeriesXY(this));

        //        addFilter(new SetUpNewSeries(this));

        //        addFilter(new Test(this));
//        addFilter(new ComputeCalibrationDB(this));
//        addFilter(new CalibrateDevice(this));
		addFilter(new ApplyCorrection(this));

        addFilter(new AddSample(this));

        //        addFilter( new ComputeStratigraphicPosition(this) );
        //        addFilter( new ComputeTimeSeries(this));
        //        addFilter(new SplitPointCloud(this));

        //        addFilter(new EvaluateStratigraphicPosition(this));
        //        addFilter(new Properties(this));
        addFilter(new CloudToPlanarSelection(this));
        addFilter(new NewRoi(this));

#ifdef SPC_WITH_PCL
        addFilter(new GaussianFilter(this));
#endif
        addFilter(new Properties(this));

//        addFilter(new ExportToAscii(this));
        addFilter(new SaveSPCElement(this));
        addFilter(new LoadSPCElement(this));
        addFilter(new LoadCloudDataSource(this));
        addFilter(new AutoComputeTimeSeries(this));


        addFilter(new CreateStratigraphicConstrain(this));






        //        addFilter(new ApplyCorrection(this));
    }

    for (std::vector<BaseFilter *>::const_iterator it = m_filters.begin();
         it != m_filters.end(); ++it)
        group.addAction((*it)->getAction());
}

int vombat::addFilter(BaseFilter *filter)
{
    assert(filter);
    filter->setMainAppInterface(m_app);

    QAction *action = filter->getAction();
    if (!action)
        return 0;

    // filter already inserted?
    if (std::find(m_filters.begin(), m_filters.end(), filter)
        != m_filters.end())
        return 0;

    m_filters.push_back(filter);

    // connect signals
    connect(filter, SIGNAL(newEntity(ccHObject *)), this,
            SLOT(handleNewEntity(ccHObject *)));
    connect(filter, SIGNAL(entityHasChanged(ccHObject *)), this,
            SLOT(handleEntityChange(ccHObject *)));
    connect(filter, SIGNAL(newErrorMessage(QString)), this,
            SLOT(handleErrorMessage(QString)));

    return 1;
}

ccHObject::Container vombat::getSelected() const
{
    return m_selected;
}

ccHObject::Container
vombat::getSelectedThatHaveMetaData(const QString key) const
{

    ccHObject::Container new_sel;

    for(ccHObject * obj: m_selected)
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

ccHObject::Container vombat::filterObjectsByType(const ccHObject::Container &in,
                                                 const CC_CLASS_ENUM ThisType)
{
    if (in.empty())
        return in;

    ccHObject::Container out;
    for(ccHObject * obj: in)
    {
        if (obj->isA(ThisType)) {
            out.push_back(obj);
        }
    }

    return out;
}

ccHObject::Container vombat::filterObjectsByKind(const ccHObject::Container &in,
                                                 const CC_CLASS_ENUM ThisType)
{
    if (in.empty())
        return in;

    ccHObject::Container out;
    for(ccHObject * obj: in)
    {
        if (obj->isKindOf(ThisType)) {
            out.push_back(obj);
        }
    }

    return out;
}

ccHObject::Container
vombat::getAllObjectsInTreeThatHaveMetaData(const QString key,
                                            const QString value /*= QString() */)
{

    ccHObject::Container all = this->getAllObjectsInTree();
    return vombat::filterObjectsByMetaData(all, key, value);
}

ccHObject::Container vombat::getAllObjectsInTreeThatAre(CC_CLASS_ENUM ThisType)
{
    ccHObject::Container all = getAllObjectsInTree();
    std::cout << "in tree " << all.size() << std::endl;
    return vombat::filterObjectsByType(all, ThisType);
}

ccHObject *vombat::getObjectFromElement(const ElementBase::Ptr el)
{
    ccHObject * root = this->theInstance()->getMainAppInterface()->dbRootObject();

    std::stack<ccHObject *> tocheck;
    tocheck.push(root);

    while (!tocheck.empty())
    {
        ccHObject * obj = tocheck.top();
        tocheck.pop();

        ccSPCElementShell * asmine = dynamic_cast<ccSPCElementShell *> (obj);

        if (asmine != NULL)
        {
            if (asmine->getSPCElement() == el)
                return asmine;
        }

        for(int i = 0; i < obj->getChildrenNumber(); ++i)
        {
            tocheck.push(obj->getChild(i));
        }
    }

    // if we are here nothing was found
    return NULL;
}

ccHObject::Container vombat::getAllChildren(ccHObject *object)
{
    int n = object->getChildrenNumber();
    ccHObject::Container cont;
    for (int i = 0; i < n; ++i) {
        cont.push_back(object->getChild(i));
    }
    return cont;
}

ccHObject::Container vombat::filterObjectsByMetaData(const ccHObject::Container &in,
                                                     const QString key,
                                                     const QString value /*= QString()*/)
{
    ccHObject::Container out;
    for(ccHObject * obj: in)
    {
        if (obj->hasMetaData(key))
        {
            if (value.isEmpty())
                out.push_back(obj);
            else
            {
                if (obj->getMetaData(key) == value)
                    out.push_back(obj);
            }
        }
    }


    return out;
}

ccHObject::Container vombat::getAllObjectsInTree()
{
    //    ccHObject::Container cont;

    ccHObject *dbroot = this->getMainAppInterface()->dbRootObject();
    ccHObject::Container tovisit;
    tovisit.push_back(dbroot);

    ccHObject::Container out;

    while (!tovisit.empty()) {
        ccHObject *last = tovisit.back();
        tovisit.pop_back();

        out.push_back(last);

        ccHObject::Container sons = getAllChildren(last);

        for(ccHObject * obj: sons)
        {
            tovisit.push_back(obj);
        }
    }
    return out;
}

ccHObject::Container vombat::getAllObjectsInTreeBySPCDti(const DtiClassType *dti)
{
    ccHObject::Container all = getAllObjectsInTree();
    ccHObject::Container out;
    for (ccHObject * obj: all)
    {
        ccSPCElementShell * asvombat = dynamic_cast<ccSPCElementShell *> (obj);
        if (asvombat!= NULL)
        {
            // isa  vomabt object
            if(asvombat->getSPCElement()->isA(dti))
                out.push_back(obj);
        }
    }

    return out;
}

ccHObject::Container vombat::getAllObjectsSelectedBySPCDti(const DtiClassType *dti)
{
    ccHObject::Container all = getSelected();
    ccHObject::Container out;
    for (ccHObject * obj: all)
    {
        ccSPCElementShell * asvombat = dynamic_cast<ccSPCElementShell *> (obj);
        if (asvombat!= NULL)
        {
            // isa  vomabt object
            if(asvombat->getSPCElement()->isA(dti))
                out.push_back(obj);
        }
    }

    return out;
}

void vombat::onNewSelection(const ccHObject::Container &selectedEntities)
{
    //! always substitute m_selected with the new selection,
    //! before to notify the plugins. Some plugins get access to the
    //! current selection from vombat::theInstance()->...
    m_selected = selectedEntities;

    for (unsigned i = 0; i < m_filters.size(); ++i)
        m_filters[i]->updateSelectedEntities(selectedEntities);

    emit selectionChanged(m_selected);
}

QIcon vombat::getIcon() const
{
    return QIcon(QString::fromUtf8(":plugin/icons/vombat.png"));
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
    for(BaseFilter * f: m_filters)
    {
        if (typeid(*f) == typeid(OpenPlotsDialog)) {

            PlotterDlg *plotterdlg = static_cast
                                     <OpenPlotsDialog *>(f)->getPlotterDlg();

            return plotterdlg;
        }
    }
    return 0;
}

Plotter2DDlg *vombat::getPlotter2DDlg()
{
    for(BaseFilter * f: m_filters)
    {
        if (typeid(*f) == typeid(OpenPlots2DDialog)) {

            Plotter2DDlg *plotterdlg
                = static_cast<OpenPlots2DDialog *>(f)->getPlotterDlg();
            if (plotterdlg)
                return plotterdlg;
        }
    }
    return 0;
}



#ifndef CC_QT5
Q_EXPORT_PLUGIN2(vombat,vombat);
#endif
