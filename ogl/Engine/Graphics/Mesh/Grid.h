#pragma once
#ifndef _CGrid_
#define _CGrid_

#include "Types.h"
#include "Mesh.h"

class CGrid : public CMesh
{
public:
  CGrid();
  virtual ~CGrid();
  void Init( uint32 aRows, uint32 aCols, float aGap );
protected:
  
private:
  DISALLOW_COPY_AND_ASSIGN(CGrid);
};

typedef std::shared_ptr< CGrid > CGridSPtr;

#endif