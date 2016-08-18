#ifndef __LUA_SCRIPT__H__
#define __LUA_SCRIPT__H__

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <luabind/luabind.hpp>
#include <luabind/function.hpp>
#include <luabind/class.hpp>
#include <luabind/operator.hpp>

int LuaScriptLog(lua_State * aLS)
{
	size_t len;
	const char* cstr = lua_tolstring(aLS, -1, &len);
	printf("%s", cstr);
	lua_pop(aLS, 1);
	return 0;
}

class CLuaScript
{
public:
	CLuaScript() : mLS(luaL_newstate())
	{
		luaL_openlibs(mLS);
		luabind::open(mLS);
		lua_register(mLS, "LogApplication", LuaScriptLog);
	}

	CLuaScript::~CLuaScript()
	{
		if (mLS)
			lua_close(mLS);
	}

	inline bool CLuaScript::Open(const char* aFilename)
	{
		int status = luaL_dofile(mLS, aFilename);
#if LUA_VERSION_NUM >= 502
		auto const lua_ok = LUA_OK;
#else
		auto const lua_ok = 0;
#endif
		if (status == lua_ok)
			return true;
		else
		{
			if (status != lua_ok)
			{
				const char *msg = lua_tostring(mLS, -1);
				const char *type = "";
				if (status == LUA_ERRSYNTAX)	type = "syntax error";
				else if (status == LUA_ERRFILE) type = "file error";
				printf("[%s] %s", type, msg);
			}

			status = lua_pcall(mLS, 0, LUA_MULTRET, 0);

			const char *msg = lua_tostring(mLS, -1);
			printf("[dofile failed] %s", msg);
		}

		return false;
	}

	/* call a function `f' defined in Lua */
	double f(double x, double y)
	{
		double z;

		int var1 = 0, var2 = 0;
		lua_getglobal(mLS, "var1");
		lua_getglobal(mLS, "var2");
		if (!lua_isnumber(mLS, -2)) {
			printf("`var1' should be a number\n");
			return -1;
		}
		if (!lua_isnumber(mLS, -1))
		{
			printf("`var2 should be a number\n");
			return -1;
		}
		var1 = (int)lua_tonumber(mLS, -2);
		var2 = (int)lua_tonumber(mLS, -1);
		printf("var1: %d\nvar2: %d\n", var1, var2);
		return z;
	}

private:
	lua_State* mLS;
};
#endif //__LUA_SCRIPT__H__