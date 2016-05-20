#ifndef __DEFAULT_SYSTEMS__
#define __DEFAULT_SYSTEMS__

#include "Types.h"

#include "DefaultComponents.h"

#include "entityx\System.h"

#include "Camera\CameraManager.h"

#include "Types.h"

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
            CCameraManager::Instance().GetCurrentCamera()->Update();

            for (uint32 iMat = 0, lMatCount = renderer.mMaterial->GetSubMaterialsCount(); iMat < lMatCount; ++iMat)
            {
                renderer.mMaterial->Apply(iMat);
                renderer.mMesh->Render(iMat);
            }

            ogl::CheckOGLError("End loop");
        });
    };
};

#include "Input/InputManager.h"

struct CameraSystem : public entityx::System<CameraSystem>
{
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override
    {
        es.each<Transform, CCamera, Controllable>([dt](entityx::Entity entity, Transform &transform, CCamera &camera, Controllable &controllable)
        {
            CInputManager& lInput = CInputManager::Instance();

            float lSpeed = 5.0f;

            if (lInput.DoAction(Run))
            {
                lSpeed *= 4.0f;
            }

            if (lInput.DoAction(Forward))
            {
                transform.position += transform.rotation * lSpeed * (float)dt;
            }

            if (lInput.DoAction(Backward))
            {
                transform.position -= transform.rotation * lSpeed * (float)dt;
            }

            float3 lUp(0.0f, 1.0f, 0.0f);
            float3 lSide = glm::cross(transform.rotation, lUp);

            if (lInput.DoAction(Right))
            {
                transform.position += lSide * lSpeed * (float)dt;
            }

            if (lInput.DoAction(Left))
            {
                transform.position -= lSide * lSpeed * (float)dt;
            }

            if (lInput.DoAction(Up))
            {
                transform.position += lUp * lSpeed * (float)dt;
            }

            if (lInput.DoAction(Down))
            {
                transform.position -= lUp * lSpeed * (float)dt;
            }

            if (lInput.DoAction(Fire))
            {
                float lYaw;

                if (lInput.DoAction(MouseX, lYaw))
                {
                    quaternion qYaw = glm::angleAxis(lYaw, lUp);
                    transform.rotation = glm::cross(transform.rotation, qYaw);
                }

                float lPitch;

                if (lInput.DoAction(MouseY, lPitch))
                {
                    quaternion qPitch = glm::angleAxis(lPitch, lSide);
                    transform.rotation = glm::cross(transform.rotation, qPitch);
                }
            }

            camera.SetPosition(transform.position);
            camera.SetLookAt(transform.position + transform.rotation);
        });
    };
};

#endif //__DEFAULT_SYSTEMS__