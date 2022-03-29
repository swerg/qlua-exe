//
// Define some functions from QLua API
//

#include <windows.h>
#include <shlwapi.h>

#include <string>
#include <iostream>
#include <memory>

#include "lua.hpp"

#include "qlua_functions.h"
#include "utils.h"


static int qlua_message(lua_State *L) {
	const int n = lua_gettop(L);  // arguments quantity
	if (n > 0) {
		const char *text = luaL_tolstring(L, 1, nullptr);
		std::cout << ConvertToConsole(text) << std::endl;
	}

	return 0;
}

static int qlua_print(lua_State *L) {
	const int n = lua_gettop(L);  // arguments quantity
	for(int i = 1; i <= n; ++i) {
		const char *text = luaL_tolstring(L, i, nullptr);
		if (i > 1)
			std::cout << '\t';
		std::cout << ConvertToConsole(text);
	}

	std::cout << std::endl;

	return 0;
}

static int qlua_sleep(lua_State *L) {
	Sleep((DWORD)luaL_checkinteger(L, 1));
	return 0;
}

static int qlua_getWorkingFolder(lua_State *L) {
	char bufFilename[MAX_PATH*4];
	if (!GetModuleFileName(nullptr, bufFilename, sizeof(bufFilename))) {
		lua_pushnil(L);
		return 1;
	}

	char *szNameOfFile = PathFindFileName(bufFilename);
	if (szNameOfFile > bufFilename) {
		szNameOfFile--;
		*szNameOfFile = '\0';
	}

	lua_pushstring(L, bufFilename);
	return 1;
}

void RegisterQLuaFunctions(lua_State *L)
{
	lua_register(L, "message", qlua_message);
	lua_register(L, "print", qlua_print);  // переопределим print на свою реализациию
	lua_register(L, "sleep", qlua_sleep);
	lua_register(L, "getWorkingFolder", qlua_getWorkingFolder);
}
