#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Mutal.h"
#include "Scene2.h"

extern int CreateCount;
mutex value_mutex;

Scene2::Scene2()
{
	CreateCount++;
	map = new ObIso();
	map->file = "map2.txt";
	map->Load();
	map->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
	value_mutex.lock();
	Sleep(100);
	CreateCount++;
	value_mutex.unlock();

	map->CreateTileCost();
	Sleep(100);
	CreateCount++;
	Sleep(100);
	CreateCount++;

	mutal = new Mutal();
	mutal->SetPos(Vector2(0, -225));
	Sleep(100);
	CreateCount++;
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	pl->Init(Vector2(25, 25));
}

void Scene2::Release()
{
}

void Scene2::Update()
{
	ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());


	if (INPUT->KeyDown(VK_F1))
	{
		if (map->PathFinding(mutal->col->GetWorldPos(),
			pl->GetWorldPivot(), mutal->way))
		{
			mutal->Move(mutal->way.back()->Pos);
			/*system("cls");
			cout << "±æ ÀÖÀ½" << endl;
			for (int i = 0; i < mutal->way.size(); i++)
			{
				cout << "X " << mutal->way[i]->Pos.x;
				cout << "Y " << mutal->way[i]->Pos.y;
				cout << endl;
			}*/
		}
	}

	if (INPUT->KeyDown('1'))
	{
		SCENE->ChangeScene("SC1");
	}

	pl->Update();
	map->Update();
	mutal->Update();
	CAM->position = pl->GetWorldPos();
}

void Scene2::LateUpdate()
{
	if (map->GetTileState(pl->GetFoot()) == TILE_WALL)
	{
		pl->GoBack();
	}
}

void Scene2::Render()
{
	map->Render();
	pl->Render();
	mutal->Render();
}

void Scene2::ResizeScreen()
{
}
