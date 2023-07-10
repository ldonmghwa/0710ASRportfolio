#include "stdafx.h"
#include "Mutal.h"

Mutal::Mutal()
{
	// 0������ �ݽð�� 360��
	dir[0] = 4;
	dir[1] = 5;
	dir[2] = 6;
	dir[3] = 7;
	dir[4] = 8;

	dir[5] = 7;
	dir[6] = 6;
	dir[7] = 5;
	dir[8] = 4;

	dir[9] = 3;
	dir[10] = 2;
	dir[11] = 1;
	dir[12] = 0;

	dir[13] = 1;
	dir[14] = 2;
	dir[15] = 3;


	img = new ObImage(L"mutalisk.png");
	img->scale.x = img->imageSize.x / 9.0f;
	img->scale.y = img->imageSize.y / 5.0f;
	img->maxFrame.x = 9;
	img->maxFrame.y = 5;
	img->ChangeAnim(ANIMSTATE::LOOP, 0.1f, false);

	col = new ObCircle();
	col->scale = img->scale * 0.5f;
	col->isFilled = false;
	img->SetParentT(*col);
	index = 0;

	
	weight = 1.0f;
}

void Mutal::Update()
{
	//���� ������
	if (way.size() > 0)
	{
		//������ �ȳ����ٸ�
		if (weight < 1.0f)
		{
			//�ʴ� ��Ÿ�� �̵�
			/*weight += DELTA *moveSpeed / (target-source).Length();
			col->SetWorldPos(Vector2::Lerp(source, target, weight));*/

			weight += DELTA * 2.0f;
			col->SetWorldPos(Vector2::Lerp(col->GetWorldPos()
				, target, weight));


			//�������� ��������
			if (weight >= 1.0f)
			{
				way.pop_back();
				//�������� �ִٸ�
				if (way.size() > 0)
				{
					weight = 0.0f;
					source = target;
					target = way.back()->Pos;
					Move(target);
				}
				else
				{
					weight = 0.0f;
					source = target;
				}
			}
		}
	}
	



	//col->MoveWorldPos(moveDir * moveSpeed * DELTA);

	//-180~180


	

	col->Update();
	img->Update();
	img->frame.x = dir[index];

	/*if ((target - col->GetWorldPos()).Length() < 5)
	{
		moveSpeed = 0.0f;
	}*/
}

void Mutal::Render()
{
	col->Render();
	img->Render();
}

void Mutal::Move(Vector2 TargetPos)
{
	Unit::Move(TargetPos);


	moveSpeed = 200.0f;

	//0 ~ 2PI -> 0 ~ 15
	index =
		round((Utility::DirToRadian(moveDir) + PI) / (22.5f * ToRadian));
	if (index == 16)index = 0;

	//img->rotation.z = Utility::DirToRadian(moveDir)-90*ToRadian;
	if (index < 4 or index > 12)
	{
		img->rotation.y = PI;
	}
	else
	{
		img->rotation.y = 0.0f;
	}
}

void Unit::Move(Vector2 TargetPos)
{
	weight = 0.0f;
	target = TargetPos;
	moveDir = target - col->GetWorldPos();
	moveDir.Normalize();
}

void Unit::Attack(Vector2 TargetPos)
{
}

void Unit::SetPos(Vector2 TargetPos)
{
	source = TargetPos;
	target = TargetPos;
	weight = 0.0f;
	col->SetWorldPos(TargetPos);
}

void Unit::Spread(Unit* targetOb)
{
	float dis =100.0f/ (target - col->GetWorldPos()).Length();
	Vector2 dir = col->GetWorldPos() -targetOb->col->GetWorldPos();
	dir.Normalize();
	dir += -moveDir;
	dir.Normalize();

	//dis = max(dis, 0);

	col->MoveWorldPos(dir * dis * DELTA);
}
