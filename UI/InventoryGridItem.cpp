#include "UltraEngine.h"
#include "InventoryGridItem.h"
#include "GridView.h"

void InventoryGridItem::RenderItem(GridView* gridView, int x, int y, int width, int height)
{
	gridView->AddBlockExt(m_itemIcon, iVec2(x, y), iVec2(width, height), Vec4(1));
	gridView->AddBlockExt(this->GetText(), iVec2(x, y + 4), iVec2(width, 19), m_textColor, m_textAlignment);
	gridView->AddBlockExt(this->GetStackSize(), iVec2(x + 2, y + (height - 15)), iVec2(width - 4, 15), m_textColor, TEXT_RIGHT);
	if (m_style == InventoryGridItemStyle::STYLE_SHOW_PROGRESS_BAR) {
		float pbHeight = ((float) height / 100) * (float) m_progress;
		int pbY = height - (int)pbHeight;
		gridView->AddBlockExt(iVec2(x, y), iVec2(7, height), m_pbBackground);
		gridView->AddBlockExt(iVec2(x, pbY), iVec2(7, pbHeight), m_pbColor);
	}
}

shared_ptr<InventoryGridItem> InventoryGridItem::CreateInventoryGridItem(string name, string stackSize, shared_ptr<Pixmap> itemIcon) {
	auto item = std::make_shared<InventoryGridItem>();
	item->SetName(name);
	item->SetText(name);
	item->SetItemIcon(itemIcon);
	item->SetStackSize(stackSize);
	return item;
}

shared_ptr<InventoryGridItem> InventoryGridItem::CreateInventoryGridItem(string name, string stackSize, string iconPath) {
	auto icon = LoadPixmap(iconPath);
	return CreateInventoryGridItem(name, stackSize, icon);
}

shared_ptr<InventoryGridItem> InventoryGridItem::CreateInventoryGridItem(string name, string stackSize, string iconPath, InventoryGridItemStyle style) {
	auto icon = LoadPixmap(iconPath);
	auto grid = CreateInventoryGridItem(name, stackSize, icon);
	grid->SetGridItemStyle(style);
	return grid;
}

shared_ptr<InventoryGridItem> InventoryGridItem::CreateInventoryGridItem(string name, string stackSize, shared_ptr<Pixmap> icon, InventoryGridItemStyle style) {
	auto grid = CreateInventoryGridItem(name, stackSize, icon);
	grid->SetGridItemStyle(style);
	return grid;
}
