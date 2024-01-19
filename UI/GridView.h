#pragma once
#include "UltraEngine.h"
#include "GridItem.h"

using namespace UltraEngine;

enum GridViewStyle
{
    GridView_DEFAULT = 0
};

struct GridCell {
    int x, y, width, height;
};

class GridView : public Widget
{
private:
    std::vector<shared_ptr<IGridItem>> m_items;
    std::vector<GridCell> m_GridCells;
    int m_cellsX, m_cellsY, m_cellWidth, m_cellHeight, m_gap;
    int m_selectedIndex;

    void BuildGrid();
    void RenderGridItem(shared_ptr<IGridItem> item, int x, int y, int width, int height);
    bool Contains(GridCell cell, int x, int y);
public:

    virtual void MouseDown(const MouseButton button, const int x, const int y)
    {
        if (button == MOUSE_LEFT) {
            this->SelectCell(x, y);
            EmitEvent(EVENT_WIDGETACTION, Self(), 1, x, y);
            this->Redraw();
        }
        else if (button == MOUSE_RIGHT) {
            this->SelectCell(x, y);
            EmitEvent(EVENT_WIDGETACTION, Self(), 2, x, y);
            this->Redraw();
        }
    }

    virtual void SetGridItems(std::vector<shared_ptr<IGridItem>> items) {
        m_items = items;
    }

    virtual bool Initialize(const WString& text, const int x, const int y, const int width, const int height, shared_ptr<Widget> parent, const int style);
    virtual void Draw(const int x, const int y, const int width, const int height);
    void SetGridDefinition(int cellsX, int cellsY, int cellWidth, int cellHeight);
    void SetGridDefinition(int cellsX, int cellsY, int cellWidth, int cellHeight, int gap);
    void SelectCell(int x, int y);
    void AddBlockExt(const iVec2& position, const iVec2& size, const Vec4& color = Vec4(0), const bool wireframe = false, const float radius = 0.0f, const float gradient = 1.0f);
    void AddBlockExt(const WString& text, const iVec2& position, const iVec2& size, const Vec4& color, const TextAlignment alignment = TextAlignment::TEXT_LEFT);
    void AddBlockExt(shared_ptr<Pixmap> pixmap, const iVec2& position, const Vec4& color = 1.0f);
    void AddBlockExt(shared_ptr<Pixmap> pixmap, const iVec2& position, const iVec2& size, const Vec4& color = 1.0f);
    void AddGridItem(shared_ptr<IGridItem> item);
    void ClearGridItems();

    shared_ptr<IGridItem> GetGridItem(int index);
    shared_ptr<IGridItem> GetSelectedGridItem();
    int GetSelectedIndex();
    shared_ptr<Vec2> CalculateSize();
    friend shared_ptr<GridView> CreateGridView(const WString&, const int x, const int y, const int cellsX, const int cellsY, const int cellWidth, const int cellHeight, shared_ptr<Widget> parent, const GridViewStyle style);
    friend shared_ptr<GridView> CreateGridView(const WString&, const int x, const int y, const int cellsX, const int cellsY, const int cellWidth, const int cellHeight, const int gap, shared_ptr<Widget> parent, const GridViewStyle style);
};

