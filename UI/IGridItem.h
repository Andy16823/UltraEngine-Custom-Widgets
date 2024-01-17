#pragma once
#include "UltraEngine.h"

class GridView;
using namespace UltraEngine;


class IGridItem
{
private:
    string m_name;
    string m_text;
public:

    virtual void SetName(string name) {
        m_name = name;
    }

    virtual void SetText(string text) {
        m_text = text;
    }

    virtual string GetName() {
        return m_name;
    }

    virtual string GetText() {
        return m_text;
    }

    virtual void RenderItem(GridView* gridview, int x, int y, int width, int height) = 0;
};
