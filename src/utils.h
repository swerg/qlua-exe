#pragma once

std::string ConvertToConsole(const char* szAnsiText);
#if LUA_VERSION_NUM < 502
// This function is got from sources Lua 5.3
const char *luaL_tolstring(lua_State *L, int idx, size_t *len);
#endif
