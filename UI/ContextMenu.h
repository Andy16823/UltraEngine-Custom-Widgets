#pragma once
#include "UltraEngine.h"
#include "../Utils.h"
#include "ContextMenuItem.h"

using namespace UltraEngine;

class ContextMenu : public Widget
{
private:
    int m_itemHeight = 30;
    int m_hoverItem = -1;
    std::vector<shared_ptr<ContextMenuItem>> m_items;

    void Resize();

public:

    virtual void MouseDown(const MouseButton button, const int x, const int y)
    {
        if (button == MOUSE_LEFT) {
            for (int i = 0; i < m_items.size(); i++) {
                int iY = i * m_itemHeight;
                if (Utils::Contains(0, iY, size.x, m_itemHeight, x, y)) {
                    m_items[i]->CallAction();
                    this->SetHidden(true);
                }
            }
        }
    }

    virtual void MouseLeave(const int x, const int y)
    {
        m_hoverItem = -1;
        this->Redraw();
    }

    virtual void MouseMove(const int x, const int y)
    {
        for (int i = 0; i < m_items.size(); i++) {
            int iX, iY, width, height;
            iX = this->position.x;
            iY = i * m_itemHeight;
            if (Utils::Contains(0, iY, size.x, m_itemHeight, x, y)) {
                m_hoverItem = i;
                this->Redraw();
                break;
            }
        }
    }

    virtual shared_ptr<ContextMenuItem> GetMenuItem(int i)
    {
        if (m_items.size() > i) {
            return m_items[i];
        }
        return NULL;
    }

    virtual shared_ptr<ContextMenuItem> GetMenuItem(string name)
    {
        for (auto item : m_items) {
            if (item->GetName() == name) {
                return item;
            }
        }
        return NULL;
    }

    void AddMenuItem(shared_ptr<ContextMenuItem> item);
    virtual bool Initialize(const WString& text, const int x, const int y, const int width, const int height, shared_ptr<Widget> parent, const int style);
    virtual void Draw(const int x, const int y, const int width, const int height);
    
    friend shared_ptr<ContextMenu> CreateContextMenu(const WString& text, const int x, const int y, const int width, shared_ptr<Widget> parent);
};

