//
// https://github.com/swerg/qlua-exe
//

#include <windows.h>

#include <string>
#include <iostream>

#include "lua.hpp"

#include "qlua_functions.h"
#include "utils.h"


int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		std::cout << "err: File is required as argument" << std::endl
			<< "Usage:" << std::endl
			<< "   qlua.exe <filename.lua> {<arg1> <arg2> ...}" << std::endl;
		return 2;
	}

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	RegisterQLuaFunctions(L);

	int error = luaL_loadfile(L, argv[1]);
	if (!error)
	{
		// pass lua-file name and extra arguments into a global 'arg' table
		lua_newtable(L);
		for (int i = 1; i < argc; ++i)
		{
			lua_pushstring(L, argv[i]);
			lua_rawseti(L, -2, i - 1);
		}
		lua_setglobal(L, "arg");

		error = lua_pcall(L, 0, LUA_MULTRET, 0);
	}
	if (error)
	{
		const char *error = lua_tostring(L, -1);
		std::cout << "err: " << ConvertToConsole(error) << std::endl;
	}

	lua_close(L);

	return error;
}
