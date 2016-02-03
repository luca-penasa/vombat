#include "ccSingleAttitudeModel.h"
#include <ccPointCloud.h>
#include <dialogs/ccSingleAttitudeModelEditorDlg.h>
#include <ccGenericGLDisplay.h>



#include <iomanip>




void ccSingleAttitudeModel::drawMeOnly(CC_DRAW_CONTEXT &context)
{

    // force recomputatio when stratigraphic shift changes
    if (this->getModel()->getStratigraphicShift() != m_current_shift)
    {
        this->updateInternals();
        m_current_shift = this->getModel()->getStratigraphicShift();
    }

    m_dynamic_scale = context.labelMarkerSize;

    if (MACRO_Draw3D(context))
    {
        bool pushName = MACRO_DrawEntityNames(context);

        if (pushName)
        {
            //not particulary fast
            if (MACRO_DrawFastNamesOnly(context))
                return;
            glPushName(getUniqueID());
        }


        glPushAttrib(GL_LINE_BIT);
        glLineWidth(m_line_width);


        //we draw the segments
        if (isSelected())
            glColor3ubv(ccColor::red.rgba);
        else
            glColor3ubv(ccColor::blue.rgba);

        Eigen::Vector3f start = getModel()->getPointAtStratigraphicPosition(m_min_sp);
        Eigen::Vector3f end = getModel()->getPointAtStratigraphicPosition(m_max_sp);


        glBegin(GL_LINES);

        glVertex3fv( start.data() );
        glVertex3fv( end.data() );


        glEnd();

        glPopAttrib();



        drawMajorThicks(context);
        drawMajorThicksText(context);

        if (pushName)
            glPopName();
    }

}

void ccSingleAttitudeModel::drawMajorThicks(CC_DRAW_CONTEXT &context)
{

    glPushAttrib(GL_LINE_BIT);
    glLineWidth(m_line_width);

    //we draw the segments
    if (isSelected())
        glColor3ubv(ccColor::red.rgba);
    else
        glColor3ubv(ccColor::blue.rgba);


    glBegin(GL_LINES);

    for (int i = 0 ; i < m_major_thicks_positions.size(); ++i)
    {
        Eigen::Vector3f pos = m_major_thicks_positions.at(i);
        Eigen::Vector3f end = pos + m_major_thicks_vector;
        glVertex3fv( pos.data() );
        glVertex3fv( end.data() );
    }


    glEnd();
    glPopAttrib();


}

void ccSingleAttitudeModel::drawMajorThicksText(CC_DRAW_CONTEXT &context)
{
    for (int i = 0; i < m_breaks.size(); i++)
    {
        float val = m_breaks.at(i);
//        std::stringstream s;
//        s << std::setprecision(2) << val;

        QString s = QString::number(val, 'g', 4);

        Vector3f pos = m_major_thicks_positions.at(i);
        Vector3f end = pos + m_major_thicks_vector;


        QFont font(context._win->getTextDisplayFont()); // takes rendering zoom into
        // account!
        font.setPointSize(font.pointSize());
        font.setBold(true);



        glDisable(GL_DEPTH_TEST);
        if (isSelected())
            context._win->display3DLabel(s, CCVector3::fromArray(end.data()), ccColor::red.rgba, font);
        else
            context._win->display3DLabel(s, CCVector3::fromArray(end.data()), ccColor::blue.rgba, font);
        glEnable(GL_DEPTH_TEST);

    }

}



void ccSingleAttitudeModel::initParameters()
{
    setEditDlgsFreezesUi(false); //it have a non-modal edit dlg
    m_min_sp =-10;
    m_max_sp = 10;
    m_step = 1;
    m_line_width = 2;
    m_major_thicks_length = 0.1;
    setVisible(true);
    updateMajorBreaks();
}




void ccSingleAttitudeModel::updateMajorBreaks()
{

    //    m_max_sp = getModel()->getStratigraphicShift() + m_size_;
    //    m_min_sp = getModel()->getStratigraphicShift() - m_size_;
    if(m_max_sp <= m_min_sp)
        return; // do nothing

    m_major_thicks_positions.clear(); //ensure is clean
    m_breaks.clear();

    float intpart;
    std::modf((m_min_sp / m_step), &intpart);
    float start_break = intpart * m_step;

    //    breaks.push_back(m_min_sp);
    float curr_pos = start_break;
    while (curr_pos <= m_max_sp)
    {
        m_breaks.push_back(curr_pos);
        m_major_thicks_positions.push_back(getModel()->getPointAtStratigraphicPosition(curr_pos));

        curr_pos +=m_step;
    }

    // also update the vector representing a major thick
    m_major_thicks_vector = getModel()->getAttitude().getDipVector() * m_major_thicks_length;

}


//------------------------------ SETTERS AND GETTERS ///////////////////////////

float ccSingleAttitudeModel::getMajorThicksLength() const
{
    return m_major_thicks_length;
}

void ccSingleAttitudeModel::setMajorThickLength(float major_thick_length)
{
    m_major_thicks_length = major_thick_length;
    updateMajorBreaks();
}

int ccSingleAttitudeModel::getLineWidth() const
{
    return m_line_width;
}

void ccSingleAttitudeModel::setLineWidth(int line_width)
{
    m_line_width = line_width;
}

float ccSingleAttitudeModel::getStep() const
{


    return m_step;
}

void ccSingleAttitudeModel::setStep(float step)
{

    m_step = step;
    updateMajorBreaks();

}

float ccSingleAttitudeModel::getMaxSp() const
{

    return m_max_sp;
}

void ccSingleAttitudeModel::setMaxSp(float max_sp)
{

    m_max_sp = max_sp;
    updateMajorBreaks();

}


ccSingleAttitudeModel::ccSingleAttitudeModel():
    ccDynamicScalarFieldGenerator(spc::StratigraphicModelSingleAttitude::Ptr(new spc::StratigraphicModelSingleAttitude))
{
    m_selectionBehavior = SELECTION_IGNORED;

    initParameters();

}

ccSingleAttitudeModel::ccSingleAttitudeModel(StratigraphicModelSingleAttitude::Ptr model):  ccDynamicScalarFieldGenerator(model)
{
    m_selectionBehavior = SELECTION_IGNORED;


    initParameters();
}

double ccSingleAttitudeModel::getStratigraphicShift() const
{
    return this->getModel()->getStratigraphicShift();
}

void ccSingleAttitudeModel::setStratigraphicShift(const double shift)
{
    this->getModel()->setStratigraphicShift(shift);
}

float ccSingleAttitudeModel::getMinSp() const
{
    return m_min_sp;
}

void ccSingleAttitudeModel::setMinSp(float min_sp)
{
    m_min_sp = min_sp;
    updateMajorBreaks();

}


void ccSingleAttitudeModel::initEditDlg()
{
    m_edit_dlg = new ccSingleAttitudeModelEditorDlg(this);
}
