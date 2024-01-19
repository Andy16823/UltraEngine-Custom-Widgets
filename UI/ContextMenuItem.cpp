#include "UltraEngine.h"
#include "ContextMenuItem.h"

/// <summary>
/// Creates a new context menu item
/// </summary>
/// <param name="name"></param>
/// <param name="text"></param>
/// <param name="action"></param>
/// <returns></returns>
shared_ptr<ContextMenuItem> ContextMenuItem::CreateContextMenuItem(string name, string text, std::function<void()> action) {
	auto item = std::make_shared<ContextMenuItem>();
	item->SetName(name);
	item->SetText(text);
	item->SetAction(action);
	return item;
}
