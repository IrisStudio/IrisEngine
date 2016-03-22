#pragma once
#ifndef _CBoxMesh_
#define _CBoxMesh_

#include "Types.h"
#include "Mesh.h"

class CBoxMesh : public CMesh
{
public:
  CBoxMesh();
  virtual ~CBoxMesh();
protected:
  
private:
  DISALLOW_COPY_AND_ASSIGN(CBoxMesh);
};

typedef std::shared_ptr< CBoxMesh > CBoxMeshSPtr;

#endif