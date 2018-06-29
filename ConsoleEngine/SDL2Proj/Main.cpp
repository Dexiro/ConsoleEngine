#include "ConsoleEngine.h"

using namespace std;

ConsoleEngine* m_sdlProj;

int main(int argc, char **argv)
{
	m_sdlProj = new ConsoleEngine();
	m_sdlProj->Init();

	while ( !m_sdlProj->GetQuit() )
	{
		m_sdlProj->Update( 0 );
		m_sdlProj->Draw();
	}

	return 0;
}