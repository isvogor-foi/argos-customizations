/**
 * @file <argos3/plugins/robots/e-puck/simulator/qtopengl_base_station.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "qtopengl_base_station.h"
#include "base_station_entity.h"
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_widget.h>

namespace argos {

   /****************************************/
   /****************************************/

   /* All measures are in meters */

   static const Real WHEEL_DIAMETER              = 0.041f;
   static const Real WHEEL_RADIUS                = WHEEL_DIAMETER * 0.5f;
   static const Real WHEEL_WIDTH                 = 0.01f;
   static const Real HALF_WHEEL_WIDTH            = WHEEL_WIDTH * 0.5f;
   static const Real INTERWHEEL_DISTANCE         = 0.053f;
   static const Real HALF_INTERWHEEL_DISTANCE    = INTERWHEEL_DISTANCE * 0.5f;

   static const Real CHASSIS_ELEVATION           = 0.005f;                            // to be checked!
   static const Real HALF_CHASSIS_LENGTH         = 0.0275f;                             // to be checked!
   static const Real HALF_CHASSIS_WIDTH          = HALF_INTERWHEEL_DISTANCE - HALF_WHEEL_WIDTH;

   static const Real BODY_RADIUS                 = 0.035f;
   static const Real BODY_ELEVATION              = WHEEL_DIAMETER + CHASSIS_ELEVATION; // to be checked!
   static const Real BODY_HEIGHT                 = 0.03f;                              // to be checked!

   static const Real LED_ELEVATION               = BODY_ELEVATION + BODY_HEIGHT;
   static const Real LED_HEIGHT                  = 0.01;                               // to be checked!
   static const Real LED_UPPER_RING_INNER_RADIUS = 0.8 * BODY_RADIUS;

   /****************************************/
   /****************************************/

   CQTOpenGLBaseStation::CQTOpenGLBaseStation() :
      m_unVertices(40),
      m_fLEDAngleSlice(360.0f / 8.0f) {
      /* Reserve the needed display lists */
      m_unLists = glGenLists(4);

      /* Assign indices for better referencing (later) */
      m_unWheelList   = m_unLists;
      m_unChassisList = m_unLists + 1;
      m_unBodyList    = m_unLists + 2;
      m_unLEDList     = m_unLists + 3;

      //loadObj("/home/ivan/Downloads/models/Wood_Fence_01.obj");


      /* Create the wheel display list */
      //glNewList(m_unWheelList, GL_COMPILE);
      //RenderWheel();
      //glEndList();

      /* Create the body display list */
      //glNewList(m_unBodyList, GL_COMPILE);
      //RenderBody();
      //glEndList();

      /* Create the chassis display list */
      glNewList(m_unChassisList, GL_COMPILE);
      RenderChassis();
      glEndList();

      /* Create the LED display list */
      //glNewList(m_unLEDList, GL_COMPILE);
      //RenderLED();
      //glEndList();

   }

   /****************************************/
   /****************************************/

   CQTOpenGLBaseStation::~CQTOpenGLBaseStation() {
      glDeleteLists(m_unLists, 4);
   }




   void CQTOpenGLBaseStation::drawElephant()
   {
	   SetGreenPlasticMaterial();
       glPushMatrix();
       //glColor3f(1.0,0.23,0.27);
       glScalef(0.1,0.1,0.1);
       glCallList(model);
       glPopMatrix();
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLBaseStation::Draw(CEBaseStationEntity& c_entity) {
      /* Place the chassis */
      /* Place the body */
      //glCallList(m_unBodyList);



      glPushMatrix();
      glTranslatef(0.0f, 0.0f, 0.001f);
	  glCallList(m_unChassisList);
      //glCallList(m_unWheelList);
      glPopMatrix();
      /*
      glPushMatrix();
      glTranslatef(0.0f, -HALF_INTERWHEEL_DISTANCE, 0.0f);
      glCallList(m_unWheelList);
      glPopMatrix();

      glPushMatrix();
      CLEDEquippedEntity& cLEDEquippedEntity = c_entity.GetLEDEquippedEntity();
      for(UInt32 i = 0; i < 8; i++) {
         const CColor& cColor = cLEDEquippedEntity.GetLED(i).GetColor();
         glRotatef(-m_fLEDAngleSlice, 0.0f, 0.0f, 1.0f);
         SetLEDMaterial(cColor.GetRed(),
                        cColor.GetGreen(),
                        cColor.GetBlue());
         glCallList(m_unLEDList);
      }
      glPopMatrix();
      */

      //glClearColor (0.0,0.0,0.0,1.0);
  		//glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  		//glLoadIdentity();
  		drawElephant();
		//glutSwapBuffers();
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLBaseStation::SetGreenPlasticMaterial() {
      const GLfloat pfColor[]     = {   0.0f, 1.0f, 0.0f, 1.0f };
      const GLfloat pfSpecular[]  = {   0.9f, 0.9f, 0.9f, 1.0f };
      const GLfloat pfShininess[] = { 100.0f                   };
      const GLfloat pfEmission[]  = {   0.0f, 0.0f, 0.0f, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLBaseStation::SetRedPlasticMaterial() {
      const GLfloat pfColor[]     = {   1.0f, 0.0f, 0.0f, 1.0f };
      const GLfloat pfSpecular[]  = {   0.9f, 0.9f, 0.9f, 1.0f };
      const GLfloat pfShininess[] = { 100.0f                   };
      const GLfloat pfEmission[]  = {   0.0f, 0.0f, 0.0f, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLBaseStation::SetCircuitBoardMaterial() {
      const GLfloat pfColor[]     = { 0.5f, 0.5f, 0.5f, 0.7f };
      const GLfloat pfSpecular[]  = { 0.5f, 0.5f, 1.0f, 1.0f };
      const GLfloat pfShininess[] = { 10.0f                  };
      const GLfloat pfEmission[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }

   void CQTOpenGLBaseStation::SetBaseMaterial() {
      const GLfloat pfColor[]     = { 0.4f, 0.4f, 0.4f, 0.7f };
      const GLfloat pfSpecular[]  = { 0.5f, 0.5f, 1.0f, 1.0f };
      const GLfloat pfShininess[] = { 10.0f                  };
      const GLfloat pfEmission[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLBaseStation::SetLEDMaterial(GLfloat f_red,
                                       GLfloat f_green,
                                       GLfloat f_blue) {
      const GLfloat fEmissionFactor = 10.0f;
      const GLfloat pfColor[]     = {                    f_red,                   f_green,                   f_blue, 0.8f };
      const GLfloat pfSpecular[]  = {                     0.0f,                      0.0f,                     0.0f, 1.0f };
      const GLfloat pfShininess[] = {                     0.0f                                                            };
      const GLfloat pfEmission[]  = {  f_red * fEmissionFactor, f_green * fEmissionFactor, f_blue * fEmissionFactor, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLBaseStation::RenderWheel() {
      /* Set material */
      SetRedPlasticMaterial();
      /* Right side */
      CVector2 cVertex(WHEEL_RADIUS, 0.0f);
      CRadians cAngle(CRadians::TWO_PI / m_unVertices);
      CVector3 cNormal(-1.0f, -1.0f, 0.0f);
      cNormal.Normalize();
      glBegin(GL_POLYGON);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
         glVertex3f(cVertex.GetX(), -HALF_WHEEL_WIDTH, WHEEL_RADIUS + cVertex.GetY());
         cVertex.Rotate(cAngle);
         cNormal.RotateY(cAngle);
      }
      glEnd();
      /* Left side */
      cVertex.Set(WHEEL_RADIUS, 0.0f);
      cNormal.Set(-1.0f, 1.0f, 0.0f);
      cNormal.Normalize();
      cAngle = -cAngle;
      glBegin(GL_POLYGON);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
         glVertex3f(cVertex.GetX(), HALF_WHEEL_WIDTH, WHEEL_RADIUS + cVertex.GetY());
         cVertex.Rotate(cAngle);
         cNormal.RotateY(cAngle);
      }
      glEnd();
      /* Tire */
      cNormal.Set(1.0f, 0.0f, 0.0f);
      cVertex.Set(WHEEL_RADIUS, 0.0f);
      cAngle = -cAngle;
      glBegin(GL_QUAD_STRIP);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
         glVertex3f(cVertex.GetX(), -HALF_WHEEL_WIDTH, WHEEL_RADIUS + cVertex.GetY());
         glVertex3f(cVertex.GetX(),  HALF_WHEEL_WIDTH, WHEEL_RADIUS + cVertex.GetY());
         cVertex.Rotate(cAngle);
         cNormal.RotateY(cAngle);
      }
      glEnd();
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLBaseStation::RenderChassis() {
	   SetCircuitBoardMaterial();
	  //float SIZE = 0.05f;
	  float height = 0.4f;
	  float radius = 0.015f;


	  CVector2 cVertex(0.1f, 0.0f);
	  CRadians cAngle(-CRadians::TWO_PI / m_unVertices);

		/* Side surface */
		cAngle = -cAngle;
		CVector2 cNormal(1.0f, 0.0f);
		cVertex.Set(radius, 0.0f);
		glBegin(GL_QUAD_STRIP);
		for(GLuint i = 0; i <= m_unVertices; i++) {
		   glNormal3f(cNormal.GetX(), cNormal.GetY(), 0.0f);
		   glVertex3f(cVertex.GetX(), cVertex.GetY(), BODY_ELEVATION + height);
		   glVertex3f(cVertex.GetX(), cVertex.GetY(), BODY_ELEVATION);
		   cVertex.Rotate(cAngle);
		   cNormal.Rotate(cAngle);
		}
		glEnd();

		SetGreenPlasticMaterial();
		// sphere
		glPushMatrix();
		//glDisable(GL_TEXTURE_2D); // Ballhack has no textures
		//glDisable(GL_DEPTH_TEST); // Makes the Balls visible through walls
		GLUquadricObj *ball;
		//glColor3f(0.0f,0.0f,1.0f); // Set Ballhack Color
		glTranslatef(0,0, height); // insert coordinates here
		ball = gluNewQuadric();
		gluQuadricNormals(ball, GLU_SMOOTH);
		gluSphere(ball, 0.05f, 16, 16);
		gluDeleteQuadric(ball);
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_TEXTURE_2D);
		glPopMatrix();

		SetBaseMaterial();

		float base_radius = 0.2f;
	      /* Top part */
	      glBegin(GL_POLYGON);
	      cVertex.Set(base_radius, 0.0f);
	      glNormal3f(0.0f, 0.0f, 1.0f);
	      for(GLuint i = 0; i <= m_unVertices; i++) {
	         glVertex3f(cVertex.GetX(), cVertex.GetY(), BODY_ELEVATION);
	         cVertex.Rotate(cAngle);
	      }
	      glEnd();

   }

   /****************************************/
   /****************************************/

   void CQTOpenGLBaseStation::RenderBody() {
      /* Set material */
      SetGreenPlasticMaterial();
      CVector2 cVertex(BODY_RADIUS, 0.0f);
      CRadians cAngle(-CRadians::TWO_PI / m_unVertices);
      /* Bottom part */
      glBegin(GL_POLYGON);
      glNormal3f(0.0f, 0.0f, -1.0f);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glVertex3f(cVertex.GetX(), cVertex.GetY(), BODY_ELEVATION);
         cVertex.Rotate(cAngle);
      }
      glEnd();
      /* Side surface */
      cAngle = -cAngle;
      CVector2 cNormal(1.0f, 0.0f);
      cVertex.Set(BODY_RADIUS, 0.0f);
      glBegin(GL_QUAD_STRIP);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glNormal3f(cNormal.GetX(), cNormal.GetY(), 0.0f);
         glVertex3f(cVertex.GetX(), cVertex.GetY(), BODY_ELEVATION + BODY_HEIGHT);
         glVertex3f(cVertex.GetX(), cVertex.GetY(), BODY_ELEVATION);
         cVertex.Rotate(cAngle);
         cNormal.Rotate(cAngle);
      }
      glEnd();

      SetRedPlasticMaterial();
      /* Top part */
      glBegin(GL_POLYGON);
      cVertex.Set(LED_UPPER_RING_INNER_RADIUS, 0.0f);
      glNormal3f(0.0f, 0.0f, 1.0f);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glVertex3f(cVertex.GetX(), cVertex.GetY(), BODY_ELEVATION + BODY_HEIGHT + LED_HEIGHT);
         cVertex.Rotate(cAngle);
      }
      glEnd();
      /* Triangle to set the direction */
      /*
      SetLEDMaterial(1.0f, 1.0f, 0.0f);
      glBegin(GL_TRIANGLES);
      glVertex3f( BODY_RADIUS * 0.7,               0.0f, BODY_ELEVATION + BODY_HEIGHT + LED_HEIGHT + 0.001f);
      glVertex3f(-BODY_RADIUS * 0.7,  BODY_RADIUS * 0.3, BODY_ELEVATION + BODY_HEIGHT + LED_HEIGHT + 0.001f);
      glVertex3f(-BODY_RADIUS * 0.7, -BODY_RADIUS * 0.3, BODY_ELEVATION + BODY_HEIGHT + LED_HEIGHT + 0.001f);
      glEnd();
      */
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLBaseStation::RenderLED() {
      /* Side surface */
      CVector2 cVertex(BODY_RADIUS, 0.0f);
      CRadians cAngle(CRadians::TWO_PI / m_unVertices);
      CVector2 cNormal(1.0f, 0.0f);
      glBegin(GL_QUAD_STRIP);
      for(GLuint i = 0; i <= m_unVertices / 8; i++) {
         glNormal3f(cNormal.GetX(), cNormal.GetY(), 0.0f);
         glVertex3f(cVertex.GetX(), cVertex.GetY(), LED_ELEVATION + LED_HEIGHT);
         glVertex3f(cVertex.GetX(), cVertex.GetY(), LED_ELEVATION);
         cVertex.Rotate(cAngle);
         cNormal.Rotate(cAngle);
      }
      glEnd();
      /* Top surface  */
      cVertex.Set(BODY_RADIUS, 0.0f);
      CVector2 cVertex2(LED_UPPER_RING_INNER_RADIUS, 0.0f);
      glBegin(GL_QUAD_STRIP);
      glNormal3f(0.0f, 0.0f, 1.0f);      
      for(GLuint i = 0; i <= m_unVertices / 8; i++) {         
         glVertex3f(cVertex2.GetX(), cVertex2.GetY(), BODY_ELEVATION + BODY_HEIGHT + LED_HEIGHT);
         glVertex3f(cVertex.GetX(), cVertex.GetY(), BODY_ELEVATION + BODY_HEIGHT + LED_HEIGHT);
         cVertex.Rotate(cAngle);
         cVertex2.Rotate(cAngle);
      }
      glEnd();
   }

   /****************************************/
   /****************************************/

   class CQTOpenGLOperationDrawEPuckNormal : public CQTOpenGLOperationDrawNormal {
   public:
      void ApplyTo(CQTOpenGLWidget& c_visualization,
                   CEBaseStationEntity& c_entity) {
         static CQTOpenGLBaseStation m_cModel;
         c_visualization.DrawRays(c_entity.GetControllableEntity());
         c_visualization.DrawEntity(c_entity.GetEmbodiedEntity());
         m_cModel.Draw(c_entity);
      }
   };

   class CQTOpenGLOperationDrawEPuckSelected : public CQTOpenGLOperationDrawSelected {
   public:
      void ApplyTo(CQTOpenGLWidget& c_visualization,
                   CEBaseStationEntity& c_entity) {
         c_visualization.DrawBoundingBox(c_entity.GetEmbodiedEntity());
      }
   };

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawNormal, CQTOpenGLOperationDrawEPuckNormal, CEBaseStationEntity);

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawSelected, CQTOpenGLOperationDrawEPuckSelected, CEBaseStationEntity);

   /****************************************/
   /****************************************/

}
