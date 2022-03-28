void RegisterQLuaFunctions(lua_State *L)
{
	lua_register(L, "message", qlua_message);
	lua_register(L, "print", qlua_print);  // переопределим print на свою реализациию
	lua_register(L, "sleep", qlua_sleep);
	lua_register(L, "getWorkingFolder", qlua_getWorkingFolder);
}
