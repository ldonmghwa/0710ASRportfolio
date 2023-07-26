#pragma once
class ASRGuided : public ASRBullet
{
public:
	ASRGuided(wstring _wstr);
	~ASRGuided();

	void Update(Vector2 destPos);
	void Render() override;
};

