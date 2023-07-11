#include "stdafx.h"
#include "Main.h"
#include "ASRMap.h"
#include "Player.h"

Main::Main()
{
	asrMap = new ASRMap();
	

}

Main::~Main()
{

	delete asrMap;
}

void Main::Init()
{
	asrMap->Init();
}

void Main::Release()
{
   
}

void Main::Update()
{
	if (INPUT->KeyPress('W'))
	{
		CAM->position += UP * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('S'))
	{
		CAM->position += DOWN * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('A'))
	{
		CAM->position += LEFT * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('D'))
	{
		CAM->position += RIGHT * 300.0f * DELTA;
	}
	asrMap->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	asrMap->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1600.0f,1000.0f);
    app.background = Color(0.0, 0.0, 0.0);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}