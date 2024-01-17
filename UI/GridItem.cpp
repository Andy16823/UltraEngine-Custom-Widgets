#include "UltraEngine.h"
#include "GridItem.h"
#include "GridView.h"

void GridItem::RenderItem(GridView* gridView, int x, int y, int width, int height) 
{
	gridView->AddBlockExt(m_itemIcon, iVec2(x, y), iVec2(width, height), Vec4(1));
	if (m_style != GRID_ITEM_TEXT_NO_BG) {
		gridView->AddBlockExt(iVec2(x, y + (height - 18)), iVec2(width, 18), m_textBackground);
	}
	gridView->AddBlockExt(this->GetText(), iVec2(x, y + (height - 15)), iVec2(width, 15), m_textColor, m_textAlignment);
}

shared_ptr<GridItem> GridItem::CreateGridItem(string name, shared_ptr<Pixmap> itemIcon) {
	auto item = std::make_shared<GridItem>();
	item->SetName(name);
	item->SetText(name);
	item->SetItemIcon(itemIcon);
	return item;
}

shared_ptr<GridItem> GridItem::CreateGridItem(string name, string iconPath) {
	auto icon = LoadPixmap(iconPath);
	return CreateGridItem(name, icon);
}

shared_ptr<GridItem> GridItem::CreateGridItem(string name, string iconPath, GridItemStyle style) {
	auto icon = LoadPixmap(iconPath);
	auto grid = CreateGridItem(name, icon);
	grid->SetGridItemStyle(style);
	return grid;
}