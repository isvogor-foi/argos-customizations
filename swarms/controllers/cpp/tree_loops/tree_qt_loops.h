#ifndef TREE_QT_FUNCTIONS_H
#define TREE_QT_FUNCTIONS_H

//#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/loop_functions.h>
//#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/simulator/visualizations/qt-mod/qtopengl_mod_user_functions.h"
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/simulator/efootbot_entity.h"
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/base-station/simulator/base_station_entity.h"
#include "/home/ivan/dev/buzz-ext/buzz/src/buzz/argos/buzz_controller_base_station.h"
//#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_main_window.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/simulator/visualizations/qt-mod/qtopengl_mod_main_window.h"
#include <argos3/core/simulator/simulator.h>
#include <vector>
#include <string>
#include <sstream>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QSize>
#include <QPoint>
#include <QRect>
#include <QStyleOptionButton>
#include <QPainter>
#include <QStyle>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>

#include <argos3/core/utility/math/rng.h>


using namespace argos;
 
class TreeQtFunctions : public CQTOpenGLModUserFunctions, public CLoopFunctions {

public:

	class Edge {
	public:
		CVector3 m_nodeStart;
		CVector3 m_nodeEnd;
		inline Edge(CVector3 nodeStart, CVector3 nodeEnd){
			m_nodeStart = nodeStart;
			m_nodeEnd = nodeEnd;
		}
	};

	TreeQtFunctions();

	virtual ~TreeQtFunctions() {}

	void Draw(CEFootBotEntity& c_entity);
	void Draw(CEBaseStationEntity& c_entity);
	void DrawInWorld();
	void KeyPressed(QKeyEvent* pc_event);
	void DrawOverlay(QPainter& c_painter);


private:
	std::vector<std::string> Split(std::string str, char delimiter);

	CBuzzControllerBaseStation* m_pcController;
	CEBaseStationEntity* m_pcBaseStation;
	CEFootBotEntity* m_pcFb;
	std::vector<Edge> treeEdges;
	bool m_treeDrawn;
	bool menuDrawn;
	CRandom::CRNG* m_pcRNG;
	int GetRandomInteger(int min, int max, CRandom::CRNG* pcRNG);
	//QTextEdit *myTxt;
};
 
#endif
