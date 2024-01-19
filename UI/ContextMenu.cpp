#include "UltraEngine.h"
#include "ContextMenu.h"

void ContextMenu::AddMenuItem(shared_ptr<ContextMenuItem> item) 
{
	m_items.push_back(item);
	this->Resize();
}

bool ContextMenu::Initialize(const WString& text, const int x, const int y, const int width, const int height, shared_ptr<Widget> parent, const int style)
{
	return Widget::Initialize(text, x, y, width, height, parent, style);
}

void ContextMenu::Draw(const int x, const int y, const int width, const int height)
{
	blocks.clear();
	AddBlock(iVec2(x, y), iVec2(width, height), Vec4(0.2, 0.2, 0.2, 1.0));

	for (int i = 0; i < m_items.size(); i++) {
		int iY = y + (i * m_itemHeight);
		auto item = m_items[i];
		if (m_hoverItem == i) {
			AddBlock(iVec2(x, iY), iVec2(width, m_itemHeight), Vec4(0.16, 0.47, 1, 1));
		}
		else {
			AddBlock(iVec2(x, iY), iVec2(width, m_itemHeight), Vec4(0.2, 0.2, 0.2, 1.0));
		}
		AddBlock(item->GetText(), iVec2(x + 5, iY), iVec2(width - 10, m_itemHeight), Vec4(1), TextAlignment::TEXT_LEFT | TextAlignment::TEXT_MIDDLE);
		AddBlock(iVec2(x, iY), iVec2(width, m_itemHeight), Vec4(0, 0, 0, 1.0), true);
	}

	AddBlock(iVec2(x, y), iVec2(width, height), Vec4(0, 0, 0, 1.0), true);
}

shared_ptr<ContextMenu> CreateContextMenu(const WString& text, const int x, const int y, const int width, shared_ptr<Widget> parent)
{
	auto menu = std::make_shared<ContextMenu>();
	menu->Initialize(text, x, y, width, 1, parent, 0);
	return menu;
}

void ContextMenu::Resize() {
	int height = m_items.size() * m_itemHeight;
	this->SetShape(this->position, iVec2(this->size.x, height));
}
