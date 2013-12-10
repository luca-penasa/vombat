#include <test.h>

#include <spc/methods/time_series_generator.h>
#include <spc/stratigraphy/single_attitude_model.h>
#include <vombat.h>


Test::Test(ccPluginInterface *parent_plugin) : BaseFilter(FilterDescription(   "Test",
                                                                               "Test",
                                                                               "test",
                                                                               ":/toolbar/icons/time_series.png"), parent_plugin )
{



}

int Test::compute()
{

//    spc::TimeSeriesGenerator generator;

//    spc::spcPCLCloud<pcl::PointXYZ>::Ptr cloud (new spc::spcPCLCloud<pcl::PointXYZ>);

//    cloud->resize(100);
//    for (int i = 0 ; i < cloud->size(); ++i)
//    {
//        cloud->at(i).x = i*0.2;
//        cloud->at(i).y = i*0.4;
//        cloud->at(i).z = i*0.1;
//    }

//    spc::spcSingleAttitudeModel::Ptr model(new  spc::spcSingleAttitudeModel);
//    generator.setInputCloud(cloud);
//    generator.setLogFieldName("z");
//    generator.setStratigraphicModel(model);
//    generator.compute();

//    ccLog::Print("DONE!");


    return 1;
}

int Test::checkSelected()
{
    return 1;
}
