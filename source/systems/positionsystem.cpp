#include "positionsystem.hpp"

#include "../core.hpp"

void MovementUpdate(float dt)
{
    auto view = registry.view<Position, Velocity, Active>();

    for (auto &entity : view)
    {
        auto &&[pos, vel] = view.get<Position, Velocity>(entity);
        pos.position.Set(pos.position.x() + vel.x * dt, pos.position.y() + vel.y * dt);
    }
}

void GravitationUpdate(float dt)
{
    auto view = registry.view<Gravity, Velocity>();

    for (auto &entity : view)
    {
        auto &&[vel, grav] = view.get<Velocity, Gravity>(entity);

        if(grav.active)
            vel.y -=Gravity::grav;

    }

}
