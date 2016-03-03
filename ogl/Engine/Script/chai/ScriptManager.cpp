#include "ScriptManager.h"

#include "chaiscript/chaiscript.hpp"

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

class TestClass
{
public:
  TestClass() : a(100), b(1000) {};
  virtual ~TestClass() {};

  int TestMethod() { return a + b; };

private:
  int a;
  int b;
};

void CScriptManagerImpl::Init()
{
  static chaiscript::ChaiScript mInterpreter;
  mInterpreter.add(chaiscript::fun(&TestFunc), "TestFunc");
  mInterpreter.add(chaiscript::user_type<TestClass>(), "TestClass");
  mInterpreter.add(chaiscript::constructor<TestClass()>(), "TestClass");
  mInterpreter.add(chaiscript::fun(&TestClass::TestMethod), "TestMethod");
}

void CScriptManagerImpl::ExecuteInstruction(std::string aInstruction)
{
  static chaiscript::ChaiScript mInterpreter;
  mInterpreter.eval(aInstruction);
}

int32 CScriptManagerImpl::ExecuteInstructionAndGet(std::string aInstruction)
{
  static chaiscript::ChaiScript mInterpreter;
  return mInterpreter.eval<int>(aInstruction);
}

void CScriptManagerImpl::ExecuteFile(std::string aFilePath)
{
  static chaiscript::ChaiScript mInterpreter;
  mInterpreter.eval_file(aFilePath);
}