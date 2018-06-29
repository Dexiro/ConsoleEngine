#pragma once
#include "CommonIncludes.h"
#include "Console.h"
#include "SDLInput.h"
#include "Obj.h"

class ConsoleEngine
{
private:
	bool m_quit;

	//Core
	SDL_Renderer* m_renderer;
	CConsole* m_console;
	Vec2I m_screenSize;

	//Input
	SDLInput input;

	//Objects
	vector<Obj*> m_objects;

public:
	ConsoleEngine();
	~ConsoleEngine();

	//Init
	void Init();

	//Update
	void Update(double dt);
	void Update_Scene(double dt);

	void Draw();

public:
	bool GetQuit(){ return m_quit; }
};

