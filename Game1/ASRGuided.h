#pragma once
class ASRGuided : public ASRBullet
{
private:
	Vector2 destPos;
public:
	ASRGuided(wstring _wstr, Vector2 _destPos);
	~ASRGuided();

	void Update();
	void Render() override;
};

