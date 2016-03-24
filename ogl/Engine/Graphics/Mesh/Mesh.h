#pragma once
#ifndef _CMesh_
#define _CMesh_

#include "Types.h"
#include "Geometry.h"
#include "Effect.h"

class CMesh
{
public:
  CMesh();
  virtual ~CMesh();
  void Render();
protected:
  CGeometrySPtr mGeometry;
  CEffectSPtr   mEffect;

private:
  DISALLOW_COPY_AND_ASSIGN(CMesh);
};

typedef std::shared_ptr< CMesh > CMeshSPtr;

#endif