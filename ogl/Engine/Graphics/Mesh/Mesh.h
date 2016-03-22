#pragma once
#ifndef _CMesh_
#define _CMesh_

#include "Types.h"

class CMesh
{
public:
  CMesh();
  virtual ~CMesh();
protected:
  float3* mVtx;
  
private:
  DISALLOW_COPY_AND_ASSIGN(CMesh);
};

typedef std::shared_ptr< CMesh > CMeshSPtr;

#endif