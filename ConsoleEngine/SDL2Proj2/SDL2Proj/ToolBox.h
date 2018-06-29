#pragma once
#include <SDL.h>
#include <vector>
#include "Vec2.h"

using namespace std;

enum EMouseState { MousePress, MouseRelease, MouseDown, MouseUp, MouseMove };

struct SimpleParticle
{
	Vec2 pos;
	Vec2 off;
};

struct DrawObj
{
	virtual void Draw(SDL_Renderer* renderer){}
};

struct DrawCircle : public DrawObj
{
	int r, g, b;
	Vec2 pos;
	float radius;
	int nPoints;

	DrawCircle(Vec2 _pos, float _radius, int _r, int _g, int _b, int _nPoints = 0)
	{
		pos = _pos; 
		radius = _radius;
		r = _r; g = _g; b = _b;
		nPoints = _nPoints;
	}

	//Draws a bunch of SDL_Line's to create a circle
	void Draw(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);

		if (nPoints == 0)
		{
			nPoints = (PI * 2)*radius / 2;
		}

		float d_a = (PI * 2) / nPoints;
		float angle = d_a;

		Vec2 start, end;
		end.x = radius;
		end.y = 0.0f;
		end = end + pos;
		for (int i = 0; i != nPoints; i++)
		{
			start = end;
			end.x = cos(angle) * radius;
			end.y = sin(angle) * radius;
			end = end + pos;
			angle += d_a;
			SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
		}
	}
};

struct ToolBox
{
	ToolBox();
	~ToolBox();

	//Renderer
	SDL_Renderer* m_renderer;

	vector<DrawObj*> m_drawList;
	vector<SimpleParticle*> m_grid;

	//Window
	SDL_Window* m_window;
	int m_winW;
	int m_winH;

	//Input
	vector<SDL_Event> m_frameEvents;
	void PollEvents();

	bool ToolBox::GetMouseState(EMouseState state);
	Vec2 ToolBox::GetMousePos(){ return m_mousePos; }

	void CreateGrid();

	void Update();
	void Render();

private:
	Vec2 m_mousePos;
	uint8_t m_mouseState;
	void UpdateMouseState(SDL_Event e);
	void SetMouseState(EMouseState state, bool b);

};
