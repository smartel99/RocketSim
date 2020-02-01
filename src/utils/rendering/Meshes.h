#pragma once
#include "utils/rendering/Color.h"
#include "vendor/imgui/imgui.h"
#include "widgets/Logger.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>

namespace Renderer
{

/**
 * @class   Triangle
 * @brief   A class that represent a triangle, usually part of a mesh.
 *          Triangle coordinates are in the [0..1] range and are in Mesh coordinates,
 *          not absolute coordinates. (They represent where in the mesh the triangle is,
 *          not where it is in the world.)
 */
class Triangle
{
public:
    Triangle() = default;
    Triangle(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImVec4 col) :
        m_p1(p1), m_p2(p2), m_p3(p3), m_col(col)
    {

    }
    Triangle(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col) :
        m_p1(p1), m_p2(p2), m_p3(p3), m_col(col)
    {
    }

    /**
     * @brief   Draw (Render) the triangle in the frame.
     * @param   screenPos: Absolute coordinates of the top-left point of the mesh
     * @param   meshSize: The parent mesh's size in pixels
     */
    inline void Draw(const ImVec2& screenPos, const ImVec2& meshSize, ImVec2& anchor)
    {
        ImVec2 p1 = ComputeRotation(m_p1, m_rotation);
        ImVec2 p2 = ComputeRotation(m_p2, m_rotation);
        ImVec2 p3 = ComputeRotation(m_p3, m_rotation);
        // Translate the mesh-coordinates of the triangle into absolute coordinates.
        p1 = ((p1 * meshSize) + screenPos) - (anchor * meshSize);
        p2 = ((p2 * meshSize) + screenPos) - (anchor * meshSize);
        p3 = ((p3 * meshSize) + screenPos) - (anchor * meshSize);

        ImGui::GetWindowDrawList()->AddTriangleFilled(p1, p2, p3, m_col.Full());
    }
    inline void Scale(float percent)
    {
        //! @TODO Implement scaling.
    }

    inline void Rotate(float amount)
    {
        m_rotation = amount;
    }

#pragma region Accessors
    inline const ImVec2& P1() const
    {
        return m_p1;
    }
    void P1(const ImVec2& val)
    {
        m_p1 = val;
    }

    const ImVec2& P2() const
    {
        return m_p2;
    }
    void P2(const ImVec2& val)
    {
        m_p2 = val;
    }

    const ImVec2& P3() const
    {
        return m_p3;
    }
    void P3(const ImVec2& val)
    {
        m_p3 = val;
    }

    inline const ImU32& Col() const
    {
        return m_col.Full();
    }
    inline void Col(ImU32 val)
    {
        m_col = val;
    }
#pragma endregion

private:
    ImVec2 m_p1 = ImVec2();
    ImVec2 m_p2 = ImVec2();
    ImVec2 m_p3 = ImVec2();
    Color m_col = Color();
    float m_rotation = 0.0f;

    /**
     * @brief   Apply rotation to the triangle by an amount between -360.0f and 360.0f.
     *          This is accomplished by individually taking each point.
     *          We treat a point like a Cartesian vector (x, y) and convert it to Polar (r, t).
     *          We then add the desired angle to the new vector and translate it back to Cartesian.
     * @param   from: A vector to apply the rotation to.
     * @param   rot: The number of degrees to rotate the triangle by.
     */
    inline ImVec2 ComputeRotation(ImVec2 from, float rot)
    {
        static const float pi = 3.14159265359;
        // If from == (0,0), the transformation will be erronous, so return.
        if (from.x == 0 && from.y == 0)
        {
            return from;
        }
        float r = sqrt(pow(from.x, 2.f) + pow(from.y, 2.f));
        float t = atan(from.y / from.x) * 180 / pi;
        t += rot;
        float x = r * cos((t * pi) / 180.0f); // cos takes radians, not degrees.
        float y = r * sin((t * pi) / 180.0f); // sin takes radians, not degrees.

        return ImVec2(x, y);
    }
};


class Mesh
{
public:
    Mesh() = default;
    Mesh(const std::vector<Triangle>& triangles, const ImVec2& size, const ImVec2& pos, const ImVec2& anchor = ImVec2()) :
        m_triangles(triangles), m_size(size), m_pos(pos), m_anchor(anchor)
    {
    }

    inline void Draw()
    {
        ImVec2 drawPos = ImVec2(m_pos.x - (m_anchor.x * m_size.x),
                                m_pos.y - (m_anchor.y * m_size.y));
        for (auto& triangle : m_triangles)
        {
            triangle.Draw(m_pos, m_size, m_anchor);
        }

        // Draw boundaries for virtual and actual sizes.
        ImGui::GetWindowDrawList()->AddRect(m_pos, ImVec2(m_pos.x + m_size.x, m_pos.y + m_size.y), 0xFFFF0000);
        ImGui::GetWindowDrawList()->AddRect(drawPos, ImVec2(drawPos.x + m_size.x, drawPos.y + m_size.y), 0xFF00FF00);
    }

    inline void Size(const ImVec2& size)
    {
        m_size = size;
    }
    inline const ImVec2& Size() const
    {
        return m_size;
    }

    inline void Pos(const ImVec2& pos)
    {
        m_pos = pos;
    }
    inline const ImVec2& Pos() const
    {
        return m_pos;
    }

    inline void Anchor(const ImVec2& anchor)
    {
        m_anchor = anchor;
    }
    inline const ImVec2& Anchor() const
    {
        return m_anchor;
    }

    inline void Rotation(float rot)
    {
        m_rotation = rot;
        for (auto& tri : m_triangles)
        {
            tri.Rotate(rot);
        }
    }
    inline float Rotation() const
    {
        return m_rotation;
    }

private:
    std::vector<Triangle> m_triangles = std::vector<Triangle>();
    ImVec2 m_size = ImVec2();   //!< Size in pixels.
    ImVec2 m_pos = ImVec2();    //!< Screen position of the mesh.
    ImVec2 m_anchor = ImVec2(); //!< Where in mesh coordinates is m_pos. [0..1] range.
    float m_rotation = 0;
};
}