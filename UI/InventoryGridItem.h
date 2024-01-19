#pragma once
#include "../Utils.h"
#include "IGridItem.h"

enum InventoryGridItemStyle {
	STYLE_DEFAULT,
	STYLE_SHOW_PROGRESS_BAR
};

class InventoryGridItem : public IGridItem
{
private:
	int m_progress = 60;
	Vec4 m_pbBackground = Vec4(0.2, 0.2, 0.2, 1);
	Vec4 m_pbColor = Utils::ToFloatColor(0, 255, 104, 255);
	string m_stackSize = "0";
	shared_ptr<Pixmap> m_itemIcon;
	Vec4 m_textColor = Vec4(1);
	Vec4 m_textBackground = Vec4(0.2, 0.2, 0.2, 1);
	TextAlignment m_textAlignment = TextAlignment::TEXT_CENTER;
	InventoryGridItemStyle m_style = InventoryGridItemStyle::STYLE_DEFAULT;

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

	virtual void SetGridItemStyle(InventoryGridItemStyle style) {
		m_style = style;
	}

	virtual void SetTextBackground(Vec4 color) {
		m_textBackground = color;
	}

	virtual shared_ptr<Pixmap> GetItemIcon() {
		return m_itemIcon;
	}

	virtual InventoryGridItemStyle GetGridItemStyle() {
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

	virtual void SetStackSize(string stackSize) {
		m_stackSize = stackSize;
	}

	virtual string GetStackSize() {
		return m_stackSize;
	}

	virtual void SetProgress(int progress) {
		m_progress = progress;
	}

	virtual int GetProgress() {
		return m_progress;
	}

	void RenderItem(GridView* gridView, int x, int y, int width, int height);
	static shared_ptr<InventoryGridItem> CreateInventoryGridItem(string name, string stackSize, shared_ptr<Pixmap> itemIcon);
	static shared_ptr<InventoryGridItem> CreateInventoryGridItem(string name, string stackSize, string icontPath);
	static shared_ptr<InventoryGridItem> CreateInventoryGridItem(string name, string stackSize, string icontPath, InventoryGridItemStyle style);
	static shared_ptr<InventoryGridItem> CreateInventoryGridItem(string name, string stackSize, shared_ptr<Pixmap> icon, InventoryGridItemStyle style);
};

