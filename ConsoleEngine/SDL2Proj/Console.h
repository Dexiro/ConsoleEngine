#pragma once
#include "CommonIncludes.h"

class CConsole
{
public:
	vector<string> m_screen;
	SDL_Window* m_window;
	TTF_Font* lucon;

	//pixel size of window
	int m_winW;
	int m_winH;

	//pixel size of on-screen characters
	int m_charW;
	int m_charH;

	//size of character grid
	int m_fieldW;
	int m_fieldH;

	CConsole(){}
	~CConsole(){}

	//Init/Reset Functions
	void Init();
	void InitWindow(const char* name, int x, int y, int w, int h);
	void InitCharField(int fieldW, int fieldH, int charW, int charH);
	void Clear();

	//Convert pixel position to grid position
	double cx(float x);
	double cy(float y);
	void cxy(float &x, float &y);

	//Grid manipulation
	void AddChar(char c, int x, int y);
	void AddCharAtPos(char c, float x, float y);
	void AddString(string s, int x, int y);

	//Draw Functions
	void Draw(SDL_Renderer* renderer);
	void DrawLine(Vec2 p1, Vec2 p2);
	void DrawCircle(Vec2 p, float radius);

	//Getters/Setters
	SDL_Window* GetWindow(){ return m_window; }
};