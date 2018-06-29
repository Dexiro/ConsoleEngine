#include "ConsoleEngine.h"

ConsoleEngine::ConsoleEngine()
{
	m_quit = false;
}

ConsoleEngine::~ConsoleEngine()
{
}

//Init Methods
void ConsoleEngine::Init()
{
	m_quit = false;

	m_console = new CConsole();
	m_screenSize = Vec2I(80, 30);

	input.Init();

	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
	{
		m_quit = true;
	}
	else
	{
		m_console->Init();
		m_console->InitCharField(m_screenSize.x, m_screenSize.y, 7, 10);

		m_console->InitWindow("Ultimate Window", 2400, 600, m_screenSize.x * m_console->m_charW, m_screenSize.y * m_console->m_charH);

		m_renderer = SDL_CreateRenderer(m_console->GetWindow(), -1, SDL_RENDERER_SOFTWARE);
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	}
}

//Update Methods
void ConsoleEngine::Update(double dt)
{
	input.Update();
	Update_Scene(dt);
}

void ConsoleEngine::Update_Scene(double dt)
{
	m_console->Clear();
}

//Draw Methods
void ConsoleEngine::Draw()
{
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(m_renderer);

	m_console->Draw(m_renderer);

	SDL_RenderPresent(m_renderer);
}
