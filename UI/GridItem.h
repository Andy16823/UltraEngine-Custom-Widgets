#pragma once
#include "UltraEngine.h"
#include "IGridItem.h"

using namespace UltraEngine;


enum GridItemStyle {
	GRID_ITEM_DEFAULT = 0,
	GRID_ITEM_TEXT_NO_BG = 1
};

class GridItem : public IGridItem
{
private:
	shared_ptr<Pixmap> m_itemIcon;
	Vec4 m_textColor = Vec4(1);
	Vec4 m_textBackground = Vec4(0.2, 0.2, 0.2, 1);
	TextAlignment m_textAlignment = TextAlignment::TEXT_CENTER;
	GridItemStyle m_style = GridItemStyle::GRID_ITEM_DEFAULT;

public:

	virtual void SetItemIcon(shared_ptr<Pixmap> icon) {
		m_itemIcon = icon;
	}

	virtual void SetTextColor(Vec4 color) {
		m_textColor = color;
	}
	
	virtual void SetTextAlignment(TextAlignment alignment) {
		m_textAlignment = alignment;
	}

	virtual void SetGridItemStyle(GridItemStyle style) {
		m_style = style;
	}

	virtual void SetTextBackground(Vec4 color) {
		m_textBackground = color;
	}

	virtual shared_ptr<Pixmap> GetItemIcon() {
		return m_itemIcon;
	}

	virtual GridItemStyle GetGridItemStyle() {
		return m_style;
	}

	virtual Vec4 GetTextColor() {
		return m_textColor;
	}

	virtual Vec4 GetTextBackgroundColor() {
		return m_textBackground;
	}

	virtual TextAlignment GetTextAlignment() {
		return m_textAlignment;
	}

	void RenderItem(GridView* gridView, int x, int y, int width, int height);
	static shared_ptr<GridItem> CreateGridItem(string name, shared_ptr<Pixmap> itemIcon);
	static shared_ptr<GridItem> CreateGridItem(string name, string icontPath);
	static shared_ptr<GridItem> CreateGridItem(string name, string icontPath, GridItemStyle style);
};

