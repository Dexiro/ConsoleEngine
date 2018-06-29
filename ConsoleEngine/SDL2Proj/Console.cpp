#include "Console.h"

void CConsole::Init()
{
	lucon = TTF_OpenFont("lucon.TTF", 12);
	TTF_SetFontHinting(lucon, TTF_HINTING_MONO);
}

void CConsole::InitWindow(const char* name, int x, int y, int w, int h)
{
	m_winW = w;
	m_winH = h;
	m_window = SDL_CreateWindow(name, x, y, m_winW, m_winH, NULL);
}

void CConsole::InitCharField(int fieldW, int fieldH, int charW, int charH)
{
	m_fieldW = fieldW;
	m_fieldH = fieldH;
	m_charW = charW;
	m_charH = charH;

	for (int i = 0; i < m_fieldH; i++)
	{
		string a = "";

		for (int j = 0; j < m_fieldW; j++)
		{
			a.append(" ");
		}

		m_screen.push_back(a);
	}
}

void CConsole::Clear()
{
	for (int i = 0; i < m_fieldH; i++)
	{
		m_screen[i] = "";

		for (int j = 0; j < m_fieldW; j++)
		{
			m_screen[i].append(" ");
		}
	}
}

void CConsole::AddChar(char c, int x, int y)
{
	if (x >= m_fieldW || y >= m_fieldH || y < 0 || x < 0) return;

	m_screen[y].erase(x, 1);
	m_screen[y].insert(x, &c);
}

void CConsole::AddCharAtPos(char c, float x, float y)
{
	x = cx(x);
	y = cy(y);

	if (x >= m_fieldW || y >= m_fieldH || y < 0 || x < 0) return;

	m_screen[(int)y].erase((int)x, 1);
	m_screen[(int)y].insert((int)x, &c);
}

void CConsole::AddString(string s, int x, int y)
{
	if (x >= m_fieldW || y >= m_fieldH || y < 0 || x < 0) return;

	m_screen[y].erase(x, s.size());
	m_screen[y].insert(x, s);
}

void CConsole::Draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < m_fieldH; i++)
	{
		SDL_Surface* surface = nullptr;
		if (i < m_screen.size())
		{
			SDL_Color White = { 255, 255, 255 };
			surface = TTF_RenderText_Solid(lucon, m_screen[i].c_str(), White);
		}
		if (surface)
		{
			SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface);

			SDL_Rect Message_rect;
			Message_rect.x = 0;
			Message_rect.y = i * m_charH;
			Message_rect.w = surface->w;
			Message_rect.h = surface->h;

			SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

			SDL_FreeSurface(surface);
		}
	}
}

void CConsole::DrawLine(Vec2 p1, Vec2 p2)
{
	Vec2 r1 = p2 - p1;
	float rayCount = r1.Length();

	Vec2 r2 = (p2 - p1) / rayCount;

	for (int ray = 0; ray < rayCount; ray++)
	{
		Vec2 p = p1 + (r2 * ray);
		
		AddCharAtPos('.', p.x, p.y);
	}
}

void CConsole::DrawCircle(Vec2 p, float radius)
{
	float res = 360.0f;
	float angle = 360.0f / res;

	Vec2 up = Vec2(0, -radius);

	for (int i = 0; i < res; i++)
	{
		up.Rotate(angle);
		Vec2 np = p + up;

		AddCharAtPos('.', np.x, np.y);
	}
}

double CConsole::cx(float x)
{
	return SDL_floor((float)x / (float)m_charW);
}

double CConsole::cy(float y)
{
	return SDL_floor((float)y / (float)m_charH);
}

void CConsole::cxy(float &x, float &y)
{
	x = cx(x);
	y = cy(y);
}
