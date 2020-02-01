#pragma once
#include "utils/rendering/Meshes.h"
#include "vendor/imgui/imgui.h"

namespace Renderer
{
class Object
{
public:
    Object() = default;
    Object(const Mesh& mesh, bool isVisible,
           const Mesh& collisionMesh, bool isCollidable,
           const ImVec2& position, bool isMoveable,
           const ImVec2& velocity, bool isAffectedByPhysics) :
        m_mesh(mesh), m_isVisible(isVisible),
        m_collisionMesh(collisionMesh), m_isCollidable(isCollidable),
        m_position(position), m_isMoveable(isMoveable),
        m_velocity(velocity), m_isAffectedByPhysics(isAffectedByPhysics)
    {
    }

    virtual void Render();
    virtual bool IsColliding(const Object& other);
private:
    Mesh m_mesh = Mesh();
    bool m_isVisible = false;

    Mesh m_collisionMesh = Mesh();
    bool m_isCollidable = false;

    ImVec2 m_position = ImVec2();
    bool m_isMoveable = false;

    ImVec2 m_velocity = ImVec2();
    bool m_isAffectedByPhysics = false;
};
}