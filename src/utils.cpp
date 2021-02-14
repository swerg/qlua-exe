//
// Define some functions from QLua API
//

#include <windows.h>
#include <shlwapi.h>

#include <string>
#include <iostream>
#include <memory>

#include "lua.hpp"

#include "utils.h"


std::string ConvertToConsole(const char* szAnsiText) {
	const DWORD lenText = (DWORD)strlen(szAnsiText) + 1;
	auto bufOem = std::make_unique<char[]>(lenText);
	CharToOemBuff(szAnsiText, bufOem.get(), lenText);
	return bufOem.get();
}

#if LUA_VERSION_NUM < 502
// This function is got from sources Lua 5.3
const char *luaL_tolstring(lua_State *L, int idx, size_t *len) {
	if (luaL_callmeta(L, idx, "__tostring")) {  /* metafield? */
		if (!lua_isstring(L, -1))
			luaL_error(L, "'__tostring' must return a string");
	}
	else {
		switch (lua_type(L, idx)) {
		case LUA_TNUMBER: {
			lua_pushfstring(L, "%f", (LUAI_UACNUMBER)lua_tonumber(L, idx));
			break;
		}
		case LUA_TSTRING:
			lua_pushvalue(L, idx);
			break;
		case LUA_TBOOLEAN:
			lua_pushstring(L, (lua_toboolean(L, idx) ? "true" : "false"));
			break;
		case LUA_TNIL:
			lua_pushliteral(L, "nil");
			break;
		default: {
			int tt = luaL_getmetafield(L, idx, "__name");  /* try name */
			const char *kind = (tt == LUA_TSTRING) ? lua_tostring(L, -1) :
				luaL_typename(L, idx);
			lua_pushfstring(L, "%s: %p", kind, lua_topointer(L, idx));
			if (tt != LUA_TNIL)
				lua_remove(L, -2);  /* remove '__name' */
			break;
		}
		}
	}
	return lua_tolstring(L, -1, len);
}
#endif
