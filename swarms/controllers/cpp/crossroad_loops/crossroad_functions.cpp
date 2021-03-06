#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include "crossroad_functions.h"
#include <QImage>


static const Real POV_HEIGHT = 0.2f;

CCrossroadFunctions::CCrossroadFunctions() :
		m_pcController(NULL),
		m_pcEFootBot(NULL){}

/****************************************/
/****************************************/

void CCrossroadFunctions::Init(TConfigurationNode& t_node) {
	//m_pcEFootBot = new CEFootBotEntity(
	//      "fb",    // entity id
	//      "fdc"    // controller id as set in the XML
	//      );
	//AddEntity(*m_pcEFootBot);
	m_pcEFootBot = dynamic_cast<CEFootBotEntity*>(&GetSpace().GetEntity("fu0"));
	m_pcController = &dynamic_cast<CEFootBotDiffusion&>(m_pcEFootBot->GetControllableEntity().GetController());
}

/****************************************/
/****************************************/

void CCrossroadFunctions::SetPovCamera()
{
    m_Renderer = dynamic_cast<CQTOpenGLRender*>(&GetSimulator().GetVisualization());
    m_Camera = &m_Renderer->GetMainWindow().GetOpenGLWidget().GetCamera();
    CQTOpenGLWidget *m_OpenGlWidget = &m_Renderer->GetMainWindow().GetOpenGLWidget();
    CQTOpenGLWidget::SFrameGrabData *frame = &m_OpenGlWidget->GetFrameGrabData();

    // http://doc.qt.io/qt-4.8/qimage.html#bits
    // save image
    /*
    m_OpenGlWidget->grabFrameBuffer().save("test.jpg", 0, frame->Quality);
    QImage img = m_OpenGlWidget->grabFrameBuffer();
    uchar* bits = img.bits();
    std::cout<< "Bits: " << sizeof(bits) << " byteCount: " << img.byteCount() << std::endl;
    */

    if(m_pcController != NULL){
    	m_pcController->img_bits = m_OpenGlWidget->grabFrameBuffer().bits();
    	m_pcController->bytesCount = m_OpenGlWidget->grabFrameBuffer().byteCount();
		m_pcController->bytesPerLine = m_OpenGlWidget->grabFrameBuffer().bytesPerLine();
    }



    m_CameraSettings = &m_Camera->GetActiveSettings();
    m_SelectedEntity = dynamic_cast<CEFootBotEntity*>(m_Renderer->GetMainWindow().GetOpenGLWidget().GetSelectedEntity());

    if(m_SelectedEntity != NULL){
        // get robot position and orientation
        CVector3 pos_vec = m_SelectedEntity->GetEmbodiedEntity().GetOriginAnchor().Position;
        CQuaternion orientation = m_SelectedEntity->GetEmbodiedEntity().GetOriginAnchor().Orientation;

        // get robot angle
        CRadians cZAngle, cYAngle, cXAngle;
        orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);

        // calculate camera direction vector
        double x = pos_vec.GetX() + cos(cZAngle.GetValue());
        double y = pos_vec.GetY() + sin(cZAngle.GetValue());
        // fixate X so you don't get tilt
        m_CameraSettings->Up.SetX(0);

        // set position and viewpoint target
        m_CameraSettings->Position.Set((double)(pos_vec.GetX()), (double)(pos_vec.GetY()), POV_HEIGHT);
        m_CameraSettings->Target.Set(x, y, POV_HEIGHT);
    }
}

/****************************************/
/****************************************/

void CCrossroadFunctions::PostStep(){
	ResetPosition();
    SetPovCamera();

	//CSpace::TMapPerType& boxes = GetSpace().GetEntitiesByType("box");
	//for(CSpace::TMapPerType::iterator it = boxes.begin(); it != boxes.end(); ++it) {
	//	CBoxEntity& box = *any_cast<CBoxEntity*>(it->second);
		//box.EnableLEDs(med);
	//}
}

/****************************************/
/****************************************/

void CCrossroadFunctions::ResetPosition(){
	CSpace::TMapPerType& m_cFootbots = GetSpace().GetEntitiesByType("efootbot");

	if(m_pcController != NULL){
		m_pcController->positions_all.clear();
	}

	for(CSpace::TMapPerType::iterator it = m_cFootbots.begin(); it != m_cFootbots.end(); ++it) {
		CEFootBotEntity& cFootBot = *any_cast<CEFootBotEntity*>(it->second);

		CQuaternion qOrientation = cFootBot.GetEmbodiedEntity().GetOriginAnchor().Orientation;
		CVector3 vPosition = cFootBot.GetEmbodiedEntity().GetOriginAnchor().Position;

		if(m_pcController != NULL){
	    	m_pcController->positions_all.insert(std::make_pair(cFootBot.GetId(), vPosition));
	    }

		// check up/down robots
		if(vPosition.GetX() >= 4.7 || vPosition.GetX() <= -4.7){ // map edge
			vPosition.SetX(vPosition.GetX() - (vPosition.GetX() * 2));
		}
		// check left/right robots
		if(vPosition.GetY()>= 4.7 || vPosition.GetY() <= -4.7){
			vPosition.SetY(vPosition.GetY() - (vPosition.GetY() * 2));
		}
		cFootBot.GetEmbodiedEntity().MoveTo(vPosition, qOrientation, false);
	}
}


REGISTER_LOOP_FUNCTIONS(CCrossroadFunctions, "crossroad_functions")
