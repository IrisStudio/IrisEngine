/* hello.c */
#include <stdio.h>
#include "RenderSystem.h"
#include "Effect.h"
#include "EffectLibrary.h"

int main(void)
{
  printf("Hello World\n");
  renderer::CRenderer mRenderer;
  CEffectLibrary library;
  CEffectSPtr lEffect = library.CreateEffect("../data/effects/effect01.xml");

  if (mRenderer.Create( 1600, 800 ))
  {
    while (mRenderer.Execute() )
    {
    }
  }
  mRenderer.Terminate();
  return 0;
}