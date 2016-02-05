#include "GenericFilterQt.h"
#include <ccSPCElementShell.h>
//#include <ccVombatObjectsFactory.h>
#include <ccTimeSeries.h>
#include <spc/elements/TimeSeriesEquallySpaced.h>

#include <vombat.h>
GenericFilterQt::GenericFilterQt(spc::GenericFilter::Ptr filter, QObject *parent): QObject(parent), filter_(filter)
{
//    connect(THIS)

    connect (this, SIGNAL(doCompute()), this, SLOT(doComputations()));
}

QString GenericFilterQt::getFilterName() const
{
    return QString::fromStdString(filter_->getName());
}

void GenericFilterQt::doComputations()
{

    LOG(INFO) << "Launching computations";
    filter_->doComputations();

    compute_ = false;

    LOG(INFO) << "Computations Done";

    for (spc::ElementBase::Ptr el: filter_->getOutput())
    {

        if (el->isA(&spc::TimeSeriesEquallySpaced::Type))
        {
            ccTimeSeries * ts = new ccTimeSeries(spcDynamicPointerCast<spc::TimeSeriesEquallySpaced>(el));
            vombat::theInstance()->handleNewEntity(ts);

        }

    }

}

void GenericFilterQt::activate(bool toggle)
{

    LOG(INFO) << "activating filter";
    emit activated(this);
}

bool GenericFilterQt::canCompute()
{
    LOG(INFO) << "canCompute? ";

    std::vector<spc::ElementBase::Ptr> inputs;


    LOG(INFO) << "start for? ";

    for (QObject * obj: current_selection)
    {
        if (!obj)
            continue;

        LOG(INFO) << "processin obj " << obj;

        ccSPCElementShell * asElShell = dynamic_cast<ccSPCElementShell *> (obj);

        LOG(INFO) << "done dynamic casting " << obj;

        if (asElShell != nullptr)
        {
            LOG(INFO) << "got a good element to be used as input ---------->";
            inputs.push_back(asElShell->getSPCElement());
        }
    }

    filter_->setInput(inputs);

    LOG(INFO) << "input extracted ";


    return filter_->canCompute();
}

