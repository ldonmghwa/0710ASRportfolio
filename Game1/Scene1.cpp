#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Mutal.h"
#include "Scene1.h"
#include "Scene2.h"

int CreateCount = 0;
ObRect* rc[1000];
void Func1()
{
	for (int i = 0; i < 1000; i++)
	{
		rc[i] = new ObRect();
		CreateCount++;
		Sleep(1);
	}
}

void Func2()
{
	
	Scene2* sc2 = new Scene2();
	SCENE->AddScene("SC2", sc2);
	
	/*for (int i = 0; i < 1000; i++)
	{
		rc[i] = new ObRect();
		CreateCount++;
		Sleep(1);
	}*/
}

Scene1::Scene1()
{
	map = new ObIso();
	map->file = "map1.txt";
	map->Load();
	map->color = Color(0.5f, 0.5f, 0.5f, 0.5f);

	map->CreateTileCost();

	//pl = new Player();

	mutal = new Mutal();
	mutal->SetPos(Vector2(0, -225));

	//t1 = new thread(Func1);
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	pl->Init(Vector2(25, 25));
}

void Scene1::Release()
{
	LIGHT->lightColor.x = 0.5f;
		LIGHT->lightColor.y = 0.5f;
		LIGHT->lightColor.z = 0.5f;
}

void Scene1::Update()
{
	ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());

	if (INPUT->KeyDown(VK_F2))
	{
	
		t1 = new thread(Func2);
		
		
	}
	if (CreateCount == 5)
	{
		reinterpret_cast<Scene2*>(SCENE->GetScene("SC2"))->pl = pl;
		t1->join();
		delete t1;
		SCENE->ChangeScene("SC2");
		return;
	}
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
		SCENE->ChangeScene("SC2",1.0f);
		fadeout = 1.0f;
	}

	if (fadeout > 0.0f)
	{
		fadeout -= DELTA;
		LIGHT->lightColor.x = fadeout / 2.0f;
		LIGHT->lightColor.y = fadeout / 2.0f;
		LIGHT->lightColor.z = fadeout / 2.0f;
	}


	pl->Update();
	map->Update();
	mutal->Update();
	CAM->position = pl->GetWorldPos();
}

void Scene1::LateUpdate()
{
	if (map->GetTileState(pl->GetFoot()) == TILE_WALL)
	{
		pl->GoBack();
	}
}

void Scene1::Render()
{
	map->Render();
	pl->Render();
	mutal->Render();

	pl->color.x = CreateCount / 5.0f;
	pl->color.y = CreateCount / 5.0f;
	pl->color.z = CreateCount / 5.0f;
}

void Scene1::ResizeScreen()
{
}
