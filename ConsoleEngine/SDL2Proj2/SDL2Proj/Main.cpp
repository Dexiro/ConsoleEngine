#include "SDL2Proj.h"

using namespace std;

SDL2Proj* m_sdlProj;

int main(int argc, char **argv)
{
	m_sdlProj = new SDL2Proj();
	m_sdlProj->Init();

	while ( !m_sdlProj->GetQuit() )
	{
		m_sdlProj->Update( 0 );
		m_sdlProj->Draw();
	}

	return 0;
}