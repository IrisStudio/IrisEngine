#ifndef __DEFAULT_SYSTEMS__
#define __DEFAULT_SYSTEMS__

#include "Types.h"

#include "DefaultComponents.h"

#include "entityx\System.h"

#include "Camera\CameraManager.h"

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

struct RenderSystem : public entityx::System<RenderSystem>
{
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override
    {
        es.each<Transform, Renderer>([dt](entityx::Entity entity, Transform &transform, Renderer &renderer)
        {
            ogl::CheckOGLError("Begin");
            /*
            renderer.mEffect->Bind();
            ogl::CheckOGLError("before setting vao");
            renderer.mGeom->Bind();
            ogl::CheckOGLError("before draw");
            glDrawArrays(GL_TRIANGLES, 0, 3);
            ogl::CheckOGLError("after draw");
            */
            CCameraManager::Instance().GetCurrentCamera()->Update();
            renderer.mQuad.Render();
            ogl::glBindVertexArray(0);
            ogl::CheckOGLError("End loop");
        });
    };
};

#endif //__DEFAULT_SYSTEMS__