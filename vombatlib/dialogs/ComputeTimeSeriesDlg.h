#ifndef COMPUTETIMESERIESDLG_H
#define COMPUTETIMESERIESDLG_H

#include "ui_ComputeTimeSeriesDlg.h"


#include <spc/elements/PointCloudBase.h>

class FieldDescriptor
{
public:

    FieldDescriptor(): iscolor_(false), name_("Field"), color_channel (spc::PointCloudBase::COLORS_ENUM::R)
    {

    }

    FieldDescriptor(const FieldDescriptor & other)
    {
        iscolor_ = other.iscolor_;
        name_ = other.name_;
        color_channel = other.color_channel;
    }

    FieldDescriptor(const std::string & name, const bool &iscolorfield = false, spc::PointCloudBase::COLORS_ENUM channel= spc::PointCloudBase::COLORS_ENUM::R)
    {
        iscolor_ = iscolorfield;
        name_  = name;
        color_channel = channel;
    }

    ~FieldDescriptor()
    {

    }

    bool operator <(const FieldDescriptor &b) const
    {
        return (name_ < b.name_);
    }

    bool operator ==(const FieldDescriptor &b) const
    {
        return ((name_ > b.name_) && (iscolor_ == b.iscolor_));
    }



    bool iscolor_ ;
    std::string name_;
    spc::PointCloudBase::COLORS_ENUM color_channel;
};



class ComputeTimeSeriesDlg : public QDialog, public Ui::ComputeTimeSeriesDlg
{
    Q_OBJECT

public:
    explicit ComputeTimeSeriesDlg(QWidget *parent = 0);

public slots:
    void changedCloudSelection(int n);
};

Q_DECLARE_METATYPE (FieldDescriptor)

#endif // COMPUTETIMESERIESDLG_H
