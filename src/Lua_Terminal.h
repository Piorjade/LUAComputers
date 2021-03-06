/*
 * 		Lua_Terminal.h
 * 
 * Summary:
 * 		This class is just an interface for the actual
 * 		terminal class. It is basically just the lua
 * 		variant of the corresponding methods.
 * 
 * 	Author:
 * 		Piorjade
 * 
 * 	Last Edited:
 * 		05/11/18 (MM/DD/YY)
 */

#ifndef LUA_TERMINAL_H
#define LUA_TERMINAL_H
#include "Color.h"
#include "Terminal.h"
#include <SFML/Graphics.hpp>
#include <lua.hpp>
#include <lauxlib.h>

namespace LuaComputers::Lua
{
	struct Terminal
	{
		static int setPixel(lua_State* L);
		static int getPixel(lua_State* L);
		static int clear(lua_State* L);
		static int clearLine(lua_State* L);
		static int clearArea(lua_State* L);
		static void initColors();
		static LuaComputers::Terminal* the_terminal;
		static LuaComputers::Color* colors;
		static sf::Color asSFColor(int lc_color);
	};
}

#endif