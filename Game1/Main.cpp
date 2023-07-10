#include "stdafx.h"
#include "Main.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Player.h"

Main::Main()
{
	

}

Main::~Main()
{

}

void Main::Init()
{
}

void Main::Release()
{
   
}

void Main::Update()
{
}

void Main::LateUpdate()
{
}

void Main::Render()
{
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(800.0f,600.0f);
    app.background = Color(0.0, 0.0, 0.0);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}