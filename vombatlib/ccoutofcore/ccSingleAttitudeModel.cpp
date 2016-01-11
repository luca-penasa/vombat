#include "ccSingleAttitudeModel.h"
#include <ccPointCloud.h>
#include <dialogs/ccSingleAttitudeModelEditorDlg.h>
#include <ccGenericGLDisplay.h>



#include <iomanip>




void ccSingleAttitudeModel::drawMeOnly(CC_DRAW_CONTEXT &context)
{
	m_dynamic_scale = context.labelMarkerSize;

    //we draw here a little 3d representation of the sensor
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
        std::stringstream s;
        s << std::setprecision(2) << val;

        Vector3f pos = m_major_thicks_positions.at(i);
        Vector3f end = pos + m_major_thicks_vector;


		QFont font(context._win->getTextDisplayFont()); // takes rendering zoom into
		// account!
		font.setPointSize(font.pointSize());
		font.setBold(true);



		glDisable(GL_DEPTH_TEST);
        if (isSelected())
			context._win->display3DLabel(s.str().c_str(), CCVector3::fromArray(end.data()), ccColor::red.rgba, font);
        else
			context._win->display3DLabel(s.str().c_str(), CCVector3::fromArray(end.data()), ccColor::blue.rgba, font);
		glEnable(GL_DEPTH_TEST);

	}

}






//ccCylinder ccSingleAttitudeModel::getScalePiece(const colorType *color,const float min_sp, const float max_sp)
//{
//    Vector3f b = getPointAtStratigraphicPosition(min_sp);

//    float height = max_sp - min_sp;

//    ccGLMatrix  T ;
//    T.setTranslation(CCVector3(0,0,height*0.5)); //now the base of the cyclinder is in 0 0 0

//    //the rotation aligning the cyclinder with the normal
//    ccGLMatrix R = ccGLMatrix::FromToRotation(CCVector3(getUnitNormal().data()), CCVector3(0.0,0.0,1.0));
//    //the rotation must be applied on the center
//    R.shiftRotationCenter(CCVector3(0,0,0));

//    ccGLMatrix T2;
//    T2.setTranslation(CCVector3(b.data())); // now move the cylinder to its positionS

//    ccGLMatrix finalTr = T2*R*T;



//    ccCylinder cyl = ccCylinder(m_pipe_radius, height, &finalTr);

//    std::cout << "height: " << height << std::endl;

//    std::cout << "building piece" << cyl.size() <<std::endl;


//    ccPointCloud * verts = static_cast<ccPointCloud*>(cyl.getAssociatedCloud());

//    //set per vertex color
//    for (int i = 0 ; verts->size(); ++i)
//    {
//        verts->setPointColor(i, color);
//    }

//    return cyl;
//}

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

    m_max_sp = getModel()->getStratigraphicShift() + m_size_;
    m_min_sp = getModel()->getStratigraphicShift() - m_size_;
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
