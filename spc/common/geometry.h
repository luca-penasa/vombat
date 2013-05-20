#ifndef SPC_GEOMETRY_H
#define SPC_GEOMETRY_H


#include <pcl/point_cloud.h>


//Specialize point types
#include "point_types.h"


/** \brief Compute distances from origin for a given cloud.
 * 
 * As origin the origin attribute of the cloud is used
 *
 * \param[in] incloud the name of the file to load
 * \param[out] outcloud resultant point cloud dataset
 * 
 */

template <typename PointT>
void 
computeDistanceFromOrigin(const pcl::PointCloud<PointT> &incloud,
													pcl::PointCloud<PointD> &outcloud);


#endif
