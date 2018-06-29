#include "SDL2Proj.h"

SDL2Proj::SDL2Proj()
{
	m_quit = false;
}

SDL2Proj::~SDL2Proj()
{
}


//Init Methods
void SDL2Proj::Init()
{
	m_quit = false;

	//Toolbox = shit class with rendering + particle stuff in it
	m_toolBox = new ToolBox();
	m_toolBox->m_winW = 1200;
	m_toolBox->m_winH = 900;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		m_quit = true;
	}
	else
	{
		//Init SDL Window and Renderer
		m_toolBox->m_window = SDL_CreateWindow("Ultimate Window", 100, 100, m_toolBox->m_winW, m_toolBox->m_winH, SDL_WINDOW_RESIZABLE);
		m_toolBox->m_renderer = SDL_CreateRenderer(m_toolBox->m_window, -1, SDL_RENDERER_SOFTWARE);
		SDL_SetRenderDrawColor(m_toolBox->m_renderer, 0, 0, 0, 0);
	}

	m_toolBox->CreateGrid();
}

//Update Methods
void SDL2Proj::Update(double dt)
{
	Update_Input(dt);
	Update_Scene(dt);
}

static bool bMouseDown = false;

void SDL2Proj::Update_Input(double dt)
{
	m_toolBox->PollEvents();
	vector<SDL_Event> events = m_toolBox->m_frameEvents;

	if (m_toolBox->GetMouseState(EMouseState::MouseDown))
	{
		m_toolBox->m_drawList.push_back(new DrawCircle(m_toolBox->GetMousePos(), 3.0f, 255, 0, 0));
		m_toolBox->m_drawList.push_back(new DrawCircle(m_toolBox->GetMousePos(), 6.0f, 180, 0, 0));
		m_toolBox->m_drawList.push_back(new DrawCircle(m_toolBox->GetMousePos(), 9.0f, 60, 0, 0));

		//m_toolBox->Explode(m_toolBox->m_mousePos);
		for each(SimpleParticle* p in m_toolBox->m_grid)
		{
			Vec2 pos = m_toolBox->GetMousePos();
			//Vec2 diff = p->pos - pos;
			Vec2 diff = pos - p->pos;

			float push = (1000 - diff.Length());
			if (push < 0){ push = 0; }

			p->off = (diff.Normalize() * push)/20;
		}
	}

	for each(SDL_Event e in events)
	{
		if (e.type == SDL_QUIT)
		{
			m_quit = true;
		}
	}
}

void SDL2Proj::Update_Scene(double dt)
{
	m_toolBox->Update();
}


//Draw Methods
void SDL2Proj::Draw()
{
	SDL_SetRenderDrawColor(m_toolBox->m_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(m_toolBox->m_renderer);

	m_toolBox->Render();

	SDL_RenderPresent(m_toolBox->m_renderer);
}