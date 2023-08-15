#include "stdafx.h"
#include "ASRMap.h"
#include "Main.h"

Main::Main()
{
	asrMap = new ASRMap();

	

	/*brushImgIdx = 0;
	brushFrame.x = 0;
	brushFrame.y = 0;
	brushColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	brushState = 0;*/

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
	//ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());
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
	if (ImGui::InputInt("TileSizeX", (int*)&asrMap->maxMapTilePos.x, 1, 1000))
	{
		asrMap->ResizeTileXY();
	}
	if (ImGui::InputInt("TileSizeY", (int*)&asrMap->maxMapTilePos.y, 1, 1000))
	{
		asrMap->ResizeTileXY();
	}
	if (ImGui::InputInt("Depth", &asrMap->depth))
	{
		asrMap->bossRoomIdx = 1;
		asrMap->depth = Utility::Saturate(asrMap->depth, 2, 5);
		for (int i = 0; i < asrMap->depth - 1; i++) {
			asrMap->bossRoomIdx *= 2;
		};
		asrMap->bossRoomIdx -= 1;
	}
	if (ImGui::Button("map auto")) {
		asrMap->AutoRenderMap();
	}
	if (ImGui::Button("step")) {
		asrMap->count++;
		if (asrMap->stepIdx == 8) asrMap->stepIdx = 0;
		asrMap->StepRederMap();
		asrMap->stepIdx++;
	}
	asrMap->Update();
	////TileSize
	//if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 1000))
	//{
	//	map->ResizeTile(tileSize);
	//}
	////TileScale
	////ImGui::SliderFloat2("TileScale", (float*)&map->scale, 1.0f, 200.0f);
	//if (ImGui::InputFloat("TileScale", (float*)&map->scale.x, 1.0f, 200.0f))
	//{
	//	map->scale.y = map->scale.x;
	//}
	////TilePos
	//Vector2 pos = map->GetWorldPos();
	//if (ImGui::SliderFloat2("TilePos", (float*)&pos, -1000.0f, 1000.0f))
	//{
	//	map->SetWorldPos(pos);
	//}


	//if (GUI->FileImGui("Save", "Save Map",
	//	".txt", "../Contents/TileMap"))
	//{
	//	string path = ImGuiFileDialog::Instance()->GetFilePathName();
	//	Utility::Replace(&path, "\\", "/");
	//	size_t tok = path.find_last_of("/") + 1;
	//	path = path.substr(tok, path.length() - tok);
	//	map->file = path;
	//	map->Save();
	//}
	//ImGui::SameLine();

	//if (GUI->FileImGui("Load", "Load Map", ".txt", "../Contents/TileMap"))
	//{
	//	string path = ImGuiFileDialog::Instance()->GetFilePathName();
	//	Utility::Replace(&path, "\\", "/");
	//	size_t tok = path.find_last_of("/") + 1;
	//	path = path.substr(tok, path.length() - tok);
	//	map->file = path;
	//	map->Load();
	//	tileSize = map->GetTileSize();
	//}

	//for (int i = 0; i < 4; i++)
	//{
	//	string str = "Texture" + to_string(i);
	//	if (GUI->FileImGui(str.c_str(), str.c_str(),
	//		".jpg,.png,.bmp,.dds,.tga", "../Contents/Images"))
	//	{
	//		string path = ImGuiFileDialog::Instance()->GetFilePathName();
	//		Utility::Replace(&path, "\\", "/");
	//		size_t tok = path.find_last_of("/") + 1;
	//		path = path.substr(tok, path.length() - tok);
	//		SafeDelete(map->tileImages[i]);
	//		wstring wImgFile = L"";
	//		wImgFile.assign(path.begin(), path.end());
	//		map->tileImages[i] = new ObImage(wImgFile);
	//		break;
	//	}
	//	if (i < 3)
	//	{
	//		ImGui::SameLine();
	//	}
	//}

	////"감바스";
	////L"감바스";
	////ImgIdx
	//if (ImGui::InputInt("ImgIdx", &brushImgIdx))
	//{
	//	brushImgIdx = Utility::Saturate(brushImgIdx, 0, 3);

	//	if (not map->tileImages[brushImgIdx])
	//	{
	//		brushImgIdx = 0;
	//	}
	//}
	////maxFrame
	//ImGui::InputInt2("maxFrame", (int*)&map->tileImages[brushImgIdx]->maxFrame);

	//Int2 MF = map->tileImages[brushImgIdx]->maxFrame;
	//ImVec2 size;
	//size.x = 300.0f / (float)MF.x;
	//size.y = 300.0f / (float)MF.y;
	//ImVec2 LT, RB;
	//int index = 0;
	//for (UINT i = 0; i < MF.y; i++)
	//{
	//	for (UINT j = 0; j < MF.x; j++)
	//	{
	//		if (j != 0)
	//		{
	//			//같은줄에 배치
	//			ImGui::SameLine();
	//		}
	//		//텍스쳐 좌표
	//		LT.x = 1.0f / MF.x * j;
	//		LT.y = 1.0f / MF.y * i;
	//		RB.x = 1.0f / MF.x * (j + 1);
	//		RB.y = 1.0f / MF.y * (i + 1);

	//		ImGui::PushID(index);
	//		if (ImGui::ImageButton((void*)map->tileImages[brushImgIdx]->GetSRV()
	//			, size, LT, RB))
	//		{
	//			brushFrame.x = j;
	//			brushFrame.y = i;
	//		}
	//		index++;
	//		ImGui::PopID();
	//	}
	//}

	////TileState
	//ImGui::SliderInt("TileState", &brushState, TILE_NONE, TILE_SIZE-1);
	////TileColor
	//ImGui::ColorEdit4("TileColor", (float*)&brushColor, ImGuiColorEditFlags_PickerHueWheel);

	//if (INPUT->KeyPress(VK_LBUTTON))
	//{
	//	Int2 Idx;
	//	//?
	//	if (map->WorldPosToTileIdx(INPUT->GetWorldMousePos(), Idx))
	//	{
	//		map->SetTile(Idx, brushFrame, brushImgIdx, brushState,brushColor);
	//	}
	//}
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
    app.SetAppName(L"MapTool");
    app.SetInstance(instance);
	app.InitWidthHeight(1600.0f, 1000.0f);
    app.background = Color(0.3, 0.3, 0.3);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}