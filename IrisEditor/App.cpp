/* hello.c */
#include <stdio.h>
#include "RenderSystem.h"

int main(void)
{
  printf("Hello World\n");
  renderer::CRenderer mRenderer;
  if (mRenderer.Create( 1600, 800 ))
  {
    while (mRenderer.Execute() )
    {
    }
  }
  mRenderer.Terminate();
  return 0;
}