#include "ScriptManager.h"

#include "chaiscript/chaiscript.hpp"

static chaiscript::ChaiScript mInterpreter;

CScriptManagerImpl::CScriptManagerImpl()
{
}

CScriptManagerImpl::~CScriptManagerImpl()
{

}

int TestFunc(int aArgument)
{
  return aArgument * 2;
}

void CScriptManagerImpl::Init()
{
  mInterpreter.add(chaiscript::fun(&TestFunc), "TestFunc");
}

int32 CScriptManagerImpl::ExecuteInstruction(std::string aInstruction)
{
  return mInterpreter.eval<int>(aInstruction);
}