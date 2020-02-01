#pragma once
#include "vendor/imgui/imgui.h"

namespace Renderer
{
class Color
{
public:
    Color() = default;
    Color(ImU32 col)
    {
        // Get a [0..1] val for each color.
        m_col.x = float((col & 0xFF000000) >> 24) / 256.f;  // R
        m_col.y = float((col & 0x00FF0000) >> 16) / 256.f;  // G
        m_col.z = float((col & 0x0000FF00) >> 8) / 256.f;   // B
        m_col.w = float((col & 0x000000FF)) / 256.f;        // A
    }
    Color(const ImVec4& col) : m_col(col)
    {
    }
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : m_col(ImVec4(r, g, b, a))
    {
    }

    inline ImU32 Full() const
    {
        return ImGui::GetColorU32(m_col);
    }

    inline float R() const
    {
        return m_col.x;
    }

    inline float G() const
    {
        return m_col.y;
    }

    inline float B() const
    {
        return m_col.z;
    }

    inline float A() const
    {
        return m_col.w;
    }
private:
    ImVec4 m_col = ImVec4();
};
}