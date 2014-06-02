#ifndef CC_SINGLE_ATTITUDE_MODEL_H
#define CC_SINGLE_ATTITUDE_MODEL_H

#include <ccHObject.h>

#include <spc/elements/StratigraphicModelSingleAttitude.h>
#include <ccCylinder.h>
#include <ccoutofcore/ccEditableHObject.h>

#include <QDialog>

#include <ccoutofcore/ccMyBaseObject.h>
#include <QIcon>
#include <ccPointCloud.h>

#include <ccoutofcore/ccAttitude.h>

#include "ccDynamicScalarFieldGenerator.h"

/**
 * @brief The ccSingleAttitudeModel class is a specialization of a ccDynamicScalarFieldGenerator that add some
 * visualization capabilities in CloudCompare for the scalar field generator spc::SingleAttitudeModel
 */
class ccSingleAttitudeModel: public ccDynamicScalarFieldGenerator
{
    Q_OBJECT

public:
    ccSingleAttitudeModel(const char * name = 0);

    // copy const
    ccSingleAttitudeModel(const ccSingleAttitudeModel &model);

    ccSingleAttitudeModel(const spc::Attitude & att);

    ccSingleAttitudeModel(const ccAttitude & att);

    virtual bool isSerializable() const { return true; }

    virtual bool hasColors() const { return true; }

    virtual ccBBox getMyOwnBcB() {return ccBBox();}

    void updateInternals()
    {
        updateMajorBreaks();
    }
    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/AttitudeToModel.png"));
    }

    spc::StratigraphicModelSingleAttitude::Ptr getModel() const
    {
        // we are sure it is of this type, arent we?
        spc::StratigraphicModelSingleAttitude::Ptr qua  = spcDynamicPointerCast<spc::StratigraphicModelSingleAttitude> (m_generator_);
        return qua;
    }

    void setModel(spc::StratigraphicModelSingleAttitude::Ptr model)
    {
        m_generator_ = spcStaticPointerCast<spc::VariableScalarFieldBase> (model);
    }

protected:
    virtual QString getSPCClassName() const
    {
        return "ccSingleAttitudeModel";
    }



public slots:

    float getMinSp() const;
    void setMinSp(float min_sp);

    float getMaxSp() const;
    void setMaxSp(float max_sp);

    float getStep() const;
    void setStep(float step);

    int getLineWidth() const;
    void setLineWidth(int line_width);

    float getMajorThicksLength() const;
    void setMajorThickLength(float major_thick_length);

    void setAdditionalShiftSlot(double additional_shift)
    {
        // we know this generator is a spc::SingleAttitudeModel
        getModel()->setAdditionalShift((float) additional_shift);
        updateMajorBreaks();
    }



signals:
    void needRedrawing();


protected:



    virtual void drawMeOnly(CC_DRAW_CONTEXT &context);

    void drawMajorThicks(CC_DRAW_CONTEXT &context);

    void drawMajorThicksText(CC_DRAW_CONTEXT &context);

    virtual void applyGLTransformation(const ccGLMatrix& trans) {}

    virtual void setGLTransformation(const ccGLMatrix& trans) {}

//    ccCylinder getScalePiece( const colorType *color,const float min_sp, const float max_sp);


    void initParameters();

    virtual void initEditDlg();



    void updateMajorBreaks() ;


    ////// user accessible props ////////////////////
    float m_min_sp;
    float m_max_sp;
    float m_step;

    int m_line_width;

    float m_major_thicks_length;

    //// these for internal use only /////////////////
    std::vector<float> m_breaks;

    std::vector<Eigen::Vector3f> m_major_thicks_positions;

    Eigen::Vector3f m_major_thicks_vector;

    float m_dynamic_scale;

protected:
    virtual bool toFile_MeOnly(QFile &out) const
    {

        ccDynamicScalarFieldGenerator::toFile_MeOnly(out);

        QDataStream outs(&out);
        outs << m_min_sp;
        outs << m_max_sp;
        outs << m_step;
        outs << m_line_width;
        outs << m_major_thicks_length;
        return 1;
    }
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags)
    {
        ccDynamicScalarFieldGenerator::fromFile_MeOnly(in, dataVersion, flags);

        QDataStream ins(&in);
        ins >> m_min_sp;
        ins >> m_max_sp;
        ins >> m_step;
        ins >> m_line_width;
        ins >> m_major_thicks_length;

        updateMajorBreaks();

        return 1;
    }

    // ccDrawableObject interface

    // ccSerializableObject interface
};



#endif // CC_SINGLE_ATTITUDE_MODEL_H
