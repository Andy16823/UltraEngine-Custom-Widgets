#include "UltraEngine.h"
#include "GridView.h"

/// <summary>
/// Initial the widget
/// </summary>
/// <returns></returns>
bool GridView::Initialize(const WString& text, const int x, const int y, const int width, const int height, shared_ptr<Widget> parent, const int style)
{
    return Widget::Initialize(text, x, y, width, height, parent, style);
}

/// <summary>
/// Renders the widget
/// </summary>
void GridView::Draw(const int x, const int y, const int width, const int height)
{
    blocks.clear();
    Vec4 color = Vec4(0.9, 0.9, 0.9, 0.3);
    
    for (int i = 0; i < m_GridCells.size(); i++)
    {
        auto cell = m_GridCells[i];
        iVec2 pos;
        pos.x = x + cell.x;
        pos.y = y + cell.y;
        AddBlock(pos, iVec2(m_cellWidth, m_cellHeight), color);

        if (m_items.size() > i) {
            auto item = m_items[i];
            if (item != nullptr) {
                this->RenderGridItem(item, pos.x, pos.y, m_cellWidth, m_cellHeight);
            }
        }

        if (m_selectedIndex != i) {
            AddBlock(pos, iVec2(m_cellWidth, m_cellHeight), Vec4(0, 0, 0, 1), true);
        }
        else {
            AddBlock(pos, iVec2(m_cellWidth, m_cellHeight), Vec4(0.16, 0.47, 1, 1), true);
        }
    }
}

void GridView::RenderGridItem(shared_ptr<GridItem> item, int x, int y, int width, int height)
{
    // Render the image
    int block = AddBlock(item->GetItemIcon(), iVec2(x, y), Vec4(1));
    blocks[block].size = iVec2(width, height);

    if (item->GetGridItemStyle() != GRID_ITEM_TEXT_NO_BG) {
        AddBlock(iVec2(x, y + (height - 18)), iVec2(width, 18), item->GetTextBackgroundColor());
    }
    AddBlock(this->GetText(), iVec2(x, y + (height - 15)), iVec2(width, 15), item->GetTextColor(), item->GetTextAlignment());
}

/// <summary>
/// Calculates the size for the grid view
/// Note: Is only need to call after seting the Grid Data with SetGridData
/// </summary>
/// <returns></returns>
shared_ptr<Vec2> GridView::CalculateSize() {
    Vec2 size;
    size.x = (m_cellsX * m_cellWidth) + (m_cellsX * m_gap);
    size.y = (m_cellsY * m_cellHeight) + (m_cellsX * m_gap);
    return std::make_shared<Vec2>(size);
}

/// <summary>
/// Sets the data values for the grid
/// </summary>
void GridView::SetGridDefinition(int cellsX, int cellsY, int cellWidth, int cellHeight)
{
    this->SetGridDefinition(cellsX, cellsY, cellWidth, cellHeight, 5);
}

/// <summary>
/// Sets the data values for the grid
/// </summary>
void GridView::SetGridDefinition(int cellsX, int cellsY, int cellWidth, int cellHeight, int gap)
{
    m_cellsX = cellsX;
    m_cellsY = cellsY;
    m_cellWidth = cellWidth;
    m_cellHeight = cellHeight;
    m_gap = gap;
}

/// <summary>
/// Create a new shared pointer for the widget
/// </summary>
shared_ptr<GridView> CreateGridView(const WString& text, const int x, const int y, const int cellsX, const int cellsY, const int cellWidth, const int cellHeight, shared_ptr<Widget> parent, const GridViewStyle style)
{
    auto widget = std::make_shared<GridView>();
    widget->SetGridDefinition(cellsX, cellsY, cellWidth, cellHeight);
    widget->BuildGrid();
    auto size = widget->CalculateSize();
    widget->Initialize(text, x, y, size->x, size->y, parent, style);
    return widget;
}

/// <summary>
/// Creates a new shared pointer for the widget with the gap
/// </summary>
shared_ptr<GridView> CreateGridView(const WString& text, const int x, const int y, const int cellsX, const int cellsY, const int cellWidth, const int cellHeight, const int gap, shared_ptr<Widget> parent, const GridViewStyle style)
{
    auto widget = std::make_shared<GridView>();
    widget->SetGridDefinition(cellsX, cellsY, cellWidth, cellHeight, gap);
    widget->BuildGrid();
    auto size = widget->CalculateSize();
    widget->Initialize(text, x, y, size->x, size->y, parent, style);
    return widget;
}

/// <summary>
/// Returns the selected cell index
/// </summary>
/// <returns></returns>
int GridView::GetSelectedIndex()
{
    return m_selectedIndex;
}

/// <summary>
/// Sets the selected index of the grid
/// </summary>
void GridView::SelectCell(int x, int y)
{
    int i = 0;
    for (auto cell : m_GridCells) {
        if (this->Contains(cell, x, y)) {
            m_selectedIndex = i;
            break;
        }
        i++;
    }
}

/// <summary>
/// Adds an block into the widget
/// </summary>
void GridView::AddBlockExt(const iVec2& position, const iVec2& size, const Vec4& color, const bool wireframe, const float radius, const float gradient)
{
    AddBlock(position, size, color, wireframe, radius, gradient);
}

/// <summary>
/// Adds an block into the widget
/// </summary>
void GridView::AddBlockExt(const WString& text, const iVec2& position, const iVec2& size, const Vec4& color, const TextAlignment alignment)
{
    AddBlock(text, position, size, color, alignment);
}

/// <summary>
/// Adds an block into the widget
/// </summary>
void GridView::AddBlockExt(shared_ptr<Pixmap> pixmap, const iVec2& position, const Vec4& color)
{
    AddBlock(pixmap, position, color);
}

/// <summary>
/// Adds an block into the widget
/// </summary>
void GridView::AddBlockExt(shared_ptr<Pixmap> pixmap, const iVec2& position, const iVec2& size, const Vec4& color)
{
    int block = AddBlock(pixmap, position, color);
    blocks[block].size = size;
}

/// <summary>
/// Adds an gridview item
/// </summary>
/// <param name="item"></param>
void GridView::AddGridItem(shared_ptr<GridItem> item)
{
    m_items.push_back(item);
    this->Redraw();
}

/// <summary>
/// Removes the grid items
/// </summary>
void GridView::ClearGridItems()
{
    m_items.clear();
}

/// <summary>
/// Gets the grid item at the given index
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
shared_ptr<GridItem> GridView::GetGridItem(int index)
{
    if (m_items.size() > index) {
        return m_items[index];
    }
    return NULL;
}

/// <summary>
/// Gets the selected item
/// </summary>
/// <returns></returns>
shared_ptr<GridItem> GridView::GetSelectedGridItem()
{
    if (m_items.size() > m_selectedIndex) {
        return m_items[m_selectedIndex];
    }
    return NULL;
}

/// <summary>
/// Builds the grid
/// </summary>
void GridView::BuildGrid() 
{
    m_GridCells.clear();
    for (int ty = 0; ty < m_cellsY; ty++) {
        for (int tx = 0; tx < m_cellsX; tx++) {
            GridCell cell;
            cell.x = (tx * m_cellWidth) + (tx * m_gap);
            cell.y = (ty * m_cellHeight) + (ty * m_gap);
            cell.width = m_cellWidth;
            cell.height = m_cellHeight;
            m_GridCells.push_back(cell);
        }
    }
}

/// <summary>
/// Checks if the given cell contains the cords
/// </summary>
bool GridView::Contains(GridCell cell, int x, int y) 
{
    int cellX = cell.x;
    int cellY = cell.y;
    if (x > cellX && x < (cellX + cell.width) && y > cellY && y < (cellY + cell.height)) {
        return true;
    }
    return false;
}

