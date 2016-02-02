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

void CScriptManagerImpl::ExecuteInstruction(std::string aInstruction)
{
  mInterpreter.eval(aInstruction);
}

int32 CScriptManagerImpl::ExecuteInstructionAndGet(std::string aInstruction)
{
  return mInterpreter.eval<int>(aInstruction);
}

void CScriptManagerImpl::ExecuteFile(std::string aFilePath)
{
  mInterpreter.eval_file(aFilePath);
}