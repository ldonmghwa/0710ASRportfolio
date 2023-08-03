#pragma once
class Item
{
protected:
	ObImage*			img;
	ObRect*				col;
	enum class ItemType type;
public:
	bool				isVisible;
public:
	Item();
	~Item();
	virtual void Update();
	virtual void Render();
	virtual void Render(Camera* uicam);
	ObRect* GetCol() { return col; }
};

