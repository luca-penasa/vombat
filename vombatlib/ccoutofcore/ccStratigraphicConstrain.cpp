#include "ccStratigraphicConstrain.h"



void ccStratigraphicConstrain::drawMeOnly(CC_DRAW_CONTEXT &context)
{




	if (!this->constrain_)
		return;


	if (MACRO_Draw3D(context))
	{
		bool pushName = MACRO_DrawEntityNames(context);
		if (pushName) {
			// not particularily fast
			if (MACRO_DrawFastNamesOnly(context))
				return;
			glPushName(getUniqueIDForDisplay());
		}

		//        const float c_sizeFactor = 4.0f;
		//        bool loop = false;

		//        if (!c_unitPointMarker || c_unitPointMarker->getRadius() != m_radius_) {
		//            c_unitPointMarker = QSharedPointer
		//                    <ccSphere>(new ccSphere(m_radius_, 0, "PointMarker", 12));
		//            c_unitPointMarker->showColors(true);
		//            c_unitPointMarker->setVisible(true);
		//            c_unitPointMarker->setEnabled(true);


		//        }

		//        // build-up point maker own 'context'
		//        CC_DRAW_CONTEXT markerContext = context;
		//        markerContext.flags
		//                &= (~CC_DRAW_ENTITY_NAMES); // we must remove the 'push name flag' so
		//        // that the sphere doesn't push its own!
		//        markerContext._win = 0;

		//        if (isSelected() && !pushName)
		//            c_unitPointMarker->setTempColor(ccColor::green);
		//        else
		//            c_unitPointMarker->setTempColor(ccColor::magenta);


		//        for (int i =0; i < constrain_->getNumberOfConstrains(); ++i)
		//        {

		//            Eigen::Vector3f point = constrain_->getPolyLineRep().getPoint(i);

		//            glMatrixMode(GL_MODELVIEW);

		//            glPushMatrix();

		//            ccGL::Translate(point(0), point(1), point(2));
		//            glScalef(context.pickedPointsRadius, context.pickedPointsRadius,
		//                     context.pickedPointsRadius);

		////            m_current_scaling_ = context.pickedPointsRadius;

		//            c_unitPointMarker->draw(markerContext);


		//            glPopMatrix();

		//        }

		glPushAttrib(GL_LINE_BIT);


		if (isSelected())
		{
			glColor3ubv(ccColor::red.rgba);
			glLineWidth(5);
			glLineStipple(5, 0xAAAA);

		}
		else
		{
			glLineWidth(2);
			glColor3ubv(ccColor::orange.rgba);
			glLineStipple(2, 0xAAAA);

		}

		glEnable(GL_LINE_STIPPLE);

		glBegin(GL_LINE_STRIP);
		for (int i =0; i < constrain_->getNumberOfConstrains(); ++i)
		{
			Eigen::Vector3f point = constrain_->getPolyLineRep().getPoint(i);
			ccGL::Vertex3v(point.data());
		}
		glEnd();


		glPopAttrib();

		if (pushName)
			glPopName();

	}

}
