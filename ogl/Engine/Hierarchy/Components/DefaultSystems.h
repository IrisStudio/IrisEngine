#ifndef __DEFAULT_SYSTEMS__
#define __DEFAULT_SYSTEMS__

#include "Types.h"

#include "DefaultComponents.h"

#include "entityx\System.h"

struct MovementSystem : public entityx::System<MovementSystem>
{
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override
    {
        es.each<Transform, Velocity>([dt](entityx::Entity entity, Transform &transform, Velocity &velocity)
        {
            transform.position += velocity.direction * (float)( velocity.speed * dt );
        });
    };
};

#endif //__DEFAULT_SYSTEMS__