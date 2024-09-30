#pragma once

#include "Body.h"
#include "Joint.h"
#include "Point.h"
#include "SystemState.h"
#include "ForceGenerator.h"

#include <SFML/Graphics.hpp>

#include <vector>

#define DEFINE_MODELS void Application::loadModels()

#define DBG_APP
#ifdef  DBG_APP
#define DGB_APP_CALL(x) x
#else
#define DGB_APP_CALL(x)
#endif

class Application
{
public:
	Application(double rate = 1000, double fps = 75);
	~Application();

	void initialize();
	void run();

	void loadModels();
	inline void addBodies(std::vector<Body*>  bodiesIn) { m_bodies = bodiesIn; }
	inline void addPoints(std::vector<Point*> pointsIn) { m_points = pointsIn; }
	inline void addForces(std::vector<ForceGenerator*> forcesIn) { m_forces = forcesIn; }
	inline void addJoints(std::vector<Joint*> jointsIn) { m_joints = jointsIn; }

	inline void applyGravity(bool ans, double val = 9.81) { m_applyGravity = ans; }
	inline bool isRunning() const { return m_isRunning; }

private:
	void update();
	void render();
	void finalize();
	
	void updateBodies();
	void updatePoints();
	void updateJoints();

	std::vector<Body*>  m_bodies;
	std::vector<Point*> m_points;
	std::vector<Joint*> m_joints;
	std::vector<ForceGenerator*> m_forces;
	SystemState m_sysState;

	int m_nB;	// number of bodies
	int m_nP;	// number of points
	int m_nJ;	// number of joints
	int m_nF;	// number of forces

	bool m_applyGravity;	// should gravity be applied to all bodies?
	double m_gravAcc;		// m/s^2, acceleration due to gravity
	bool m_isRunning;		// is application currently running?
	const double m_rate;	// Hz, update rate system physics
	const double m_fps;		// Hz, update rate of rendering
	const double m_1_rate;  // sec, inverse of rate
	const double m_1_fps;	// sec, inverse of render rate
	const double m_timeEnd; // sec, temporary variable, time to end sim
	double m_time;			// sec, time of the previous frame
	double m_updateTimer;	// timer for update loop
	double m_renderTimer;	// timer for render loop
	Clock m_clock;			// application clock


	void handleEvents();

	struct winSettings
	{
		winSettings() : 
			pos(Vec2d(50)),
			size(Vec2d(800, 600)),
			show(true),
			title("Planar Multibody Dynamic Simulator"),
			bkColor(sf::Color(12, 12, 12)),
			fps(144)
		{}

		Vec2d pos;
		Vec2d size;
		bool show;
		const char* title;
		sf::Color bkColor;
		double fps;
	};

	bool m_useGui;
	sf::RenderWindow m_win;
	winSettings m_winSettings;
	sf::Event m_event;

	// debugging
	DGB_APP_CALL(unsigned long m_updateCounter);
	DGB_APP_CALL(unsigned long m_renderCounter);
};