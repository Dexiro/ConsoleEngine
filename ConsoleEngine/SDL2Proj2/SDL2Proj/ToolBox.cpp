#include "ToolBox.h"


ToolBox::ToolBox()
{
	m_mouseState = 0;
}

ToolBox::~ToolBox()
{
	while (m_drawList.size() > 0)
	{
		delete m_drawList.back();
		m_drawList.pop_back();
	}

	while (m_grid.size() > 0)
	{
		delete m_grid.back();
		m_grid.pop_back();
	}
}

//PollEvents is called once per frame to update mouse state + m_frameEvents list
void ToolBox::PollEvents()
{
	m_frameEvents.clear();
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		UpdateMouseState(e);
		m_frameEvents.push_back(e);
	}
}
//Used by PollEvents()
void ToolBox::UpdateMouseState(SDL_Event e)
{
	SetMouseState(EMouseState::MousePress, false);
	SetMouseState(EMouseState::MouseRelease, false);
	SetMouseState(EMouseState::MouseMove, false);

	if (e.type == SDL_MOUSEMOTION)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		m_mousePos = Vec2(x, y);

		SetMouseState(EMouseState::MouseMove, true);
	}

	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (!GetMouseState(EMouseState::MouseDown))
			SetMouseState(EMouseState::MousePress, true);

		SetMouseState(EMouseState::MouseDown, true);
		SetMouseState(EMouseState::MouseUp, false);
	}

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (!GetMouseState(EMouseState::MouseUp))
			SetMouseState(EMouseState::MouseRelease, true);

		SetMouseState(EMouseState::MouseDown, false);
		SetMouseState(EMouseState::MouseUp, true);
	}
}
//Used by UpdateMouseState()
void ToolBox::SetMouseState(EMouseState state, bool b)
{
	if (b)
		m_mouseState |= (1 << (int)state);
	else
		m_mouseState &= ~(1 << (int)state);
}

//Use this to get the current state of the mouse
bool ToolBox::GetMouseState(EMouseState state)
{
	return m_mouseState & (1 << (int)state);
}

void ToolBox::CreateGrid()
{
	//Space between each particle
	float w = 10.0f;
	float h = 10.0f;

	//How many particles will fit on the screen
	int xNum = (int)(m_winW / w);
	int yNum = (int)(m_winH / h);

	for (int y = 0; y < yNum; y++)
	{
		for (int x = 0; x < xNum; x++)
		{
			SimpleParticle* p = new SimpleParticle();
			p->pos = Vec2(w * x, h * y);
			m_grid.push_back(p);
		}
	}

}

void ToolBox::Render()
{
	//Draw and clear m_drawList
	while (!m_drawList.empty())
	{
		m_drawList.back()->Draw(m_renderer);
		delete m_drawList.back();
		m_drawList.pop_back();
	}

	//Draw grid
	for each(SimpleParticle* p in m_grid)
	{
		SDL_SetRenderDrawColor(m_renderer, 0, 255, 255, 255);
		SDL_RenderDrawPoint(m_renderer, p->pos.x + p->off.x, p->pos.y + p->off.y);
	}
}

void ToolBox::Update()
{
	for each(SimpleParticle* particle in m_grid)
	{
		//Slowly decrease the offset towards 0
		if (particle->off.LengthSqr() > 0.01f)
		{
			particle->off *= 0.95f;
		}
	}
}