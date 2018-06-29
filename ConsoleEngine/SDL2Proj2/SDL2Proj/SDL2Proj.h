#pragma once
#include "SDL.h"
#include <string>
#include <vector>

#include "ToolBox.h"

using namespace std;

class SDL2Proj
{
private:
	bool m_quit;

	ToolBox* m_toolBox;

public:
	SDL2Proj();
	~SDL2Proj();

	//Init
	void Init();
	void LoadXMLScene(string path);

	//Update
	void Update(double dt);
	void Update_Input(double dt);
	void Update_Scene(double dt);

	//Draw
	void Draw();

public:
	bool GetQuit(){ return m_quit; }

};

