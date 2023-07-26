#pragma once
class ASRChest : public ObRect
{
private:
	ObImage*	open;
	enum class	GunType gunType;

	bool		isExist;
	bool		isOpen;
	bool		isGlit;
	float		disappearTime;
	float		glitteringTime;
public:
	ASRChest();
	~ASRChest();

	void Update() override;
	void Render() override;
	void OpenTheChest();

	bool GetIsExist() { return isExist;}
	enum class GunType GetItemType() { return gunType; }
};

