#ifndef SPC_BASE_TIME_SERIES_H
#define SPC_BASE_TIME_SERIES_H


#include <string>
#include <vector>
#include <assert.h>

namespace spc
{

///
/// \defgroup time_series Time Series Objects
///
using namespace std;
template <typename ScalarT>
///
/// \brief The GenericTimeSeries class is a Generic class for time series-like (TS) objects.
/// \ingroup time_series
///
class GenericTimeSeries
{
public:
    ///
    /// \brief Base Constructor
    ///
    GenericTimeSeries();

    ///
    /// \brief getName each time series may have an associated name
    /// \return the name as string
    ///
    string getName () const {return m_name;}

    ///
    /// \brief setName to set the name of Time Series
    ///
    void setName(string name_) {m_name = name_;}

    ///
    /// \brief getNumberOfSamples in time series
    /// \return the number of samples
    ///

    size_t getNumberOfSamples() const {return y.size();}

    ///
    /// \brief getX positions
    /// \return a vector of x positions
    ///
    virtual auto getX() -> vector<ScalarT> = 0;

    ///
    /// \brief getY values
    /// \return a vector of the y values associated with x
    ///
    auto getY() -> vector<ScalarT> ;

    ///
    /// \brief setY values
    ///
    void setY(vector<ScalarT> y_) {y = y_;}

    ///
    /// \brief Provide a way to resize the time series
    /// \param size_ number of samples
    /// It resizes the vector of y values
    ///
    virtual void resize(size_t size_) = 0;

    ///
    /// \brief getMinX for the lowest value of the x positions
    /// \return the min value of the x positions
    /// Must be implemented in each derived class
    ///
    virtual auto getMinX() -> ScalarT const = 0 ;

    ///
    /// \brief getMaxX for the higher value of the x positions
    /// \return the max value of the x positions
    /// Must be implemented in each derived class
    ///
    virtual auto getMaxX() -> ScalarT const = 0;




protected:
    ///
    /// \brief m_name is the name associated with the time series
    ///
    string m_name;

    ///
    /// \brief y is the vector of values of the TS
    ///
    std::vector<ScalarT> y;

};



} //end namespace spc
#endif // GENERICTIMESERIES_H