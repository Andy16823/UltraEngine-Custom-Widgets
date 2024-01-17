#include "UltraEngine.h"
#include "GridItem.h"

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