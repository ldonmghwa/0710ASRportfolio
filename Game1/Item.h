#pragma once
class Item
{
protected:
	ObImage* img;
	ObRect* col;
	enum class ItemType type;
public:
	Item();
	~Item();
	virtual void Update();
	virtual void Render();

	void VisibleOff() { img->isVisible = false; col->isVisible = false; }
	void VisibleOn() { img->isVisible = true; col->isVisible = true; }
	ObRect* GetCol() { return col; }
};

