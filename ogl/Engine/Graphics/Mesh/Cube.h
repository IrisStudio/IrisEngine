#pragma once
#ifndef _CCube_
#define _CCube_

#include "Types.h"
#include "Mesh.h"

class CCube : public CMesh
{
public:
  CCube();
  virtual ~CCube();

  void Init(float aLenght, float aWidht, float aHeight);

protected:
  
private:
  DISALLOW_COPY_AND_ASSIGN(CCube);
};

typedef std::shared_ptr< CCube > CCubeSPtr;

#endif