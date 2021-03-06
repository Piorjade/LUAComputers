#include "Lua_Terminal.h"
#include <iostream>
#include <cmath>

using namespace LuaComputers::Lua;

LuaComputers::Terminal* Terminal::the_terminal;
LuaComputers::Color* Terminal::colors;


void Terminal::initColors()
{
	colors = new LuaComputers::Color[16];
	for(int i = 0; i < 16; i++)
	{
		colors[i].setLCColor(static_cast<int>(pow(2, i)));
		switch(i)
		{
			case 0:
				colors[i].setSFColor(sf::Color(25, 25, 25));
				break;
			case 1:
				colors[i].setSFColor(sf::Color(242, 178, 51));
				break;
			case 2:
				colors[i].setSFColor(sf::Color(229, 127, 216));
				break;
			case 3:
				colors[i].setSFColor(sf::Color(153, 178, 242));
				break;
			case 4:
				colors[i].setSFColor(sf::Color(222, 222, 108));
				break;
			case 5:
				colors[i].setSFColor(sf::Color(127, 204, 25));
				break;
			case 6:
				colors[i].setSFColor(sf::Color(242, 178, 204));
				break;
			case 7:
				colors[i].setSFColor(sf::Color(76,76,76));
				break;
			case 8:
				colors[i].setSFColor(sf::Color(153, 153, 153));
				break;
			case 9:
				colors[i].setSFColor(sf::Color(76, 153, 178));
				break;
			case 10:
				colors[i].setSFColor(sf::Color(178, 102, 229));
				break;
			case 11:
				colors[i].setSFColor(sf::Color(51, 102, 204));
				break;
			case 12:
				colors[i].setSFColor(sf::Color(127, 102, 76));
				break;
			case 13:
				colors[i].setSFColor(sf::Color(87, 166, 78));
				break;
			case 14:
				colors[i].setSFColor(sf::Color(204, 76, 76));
				break;
			case 15:
				colors[i].setSFColor(sf::Color(240, 240, 240));
				break;
			default:
				colors[i].setSFColor(sf::Color(25, 25, 25));
		}
	}
}

sf::Color Terminal::asSFColor(int lc_color)
{
	for(int i = 0; i < 16; i++)
	{
		if(colors[i].getLCColor() == lc_color)
		{
			return colors[i].getSFColor();
		}
	}
	return sf::Color::Black;
}

int Terminal::getPixel(lua_State* L)
{
	if(lua_gettop(L) >= 2)
	{
		int y = lua_tonumber(L, -1);
		int x = lua_tonumber(L, -1);
		lua_pop(L, -1);
		lua_pop(L, -1);
		sf::Color bg_color = the_terminal->getPixelColor(x, y);
		int lc_bg_color = 0;
		
		for(int i = 0; i < 16; i++)
		{
			if(colors[i].getSFColor() == bg_color)
			{
				lc_bg_color = colors[i].getLCColor();
			}
		}
		lua_pushnumber(L, lc_bg_color);
	}else
	{
		luaL_error(L, "expected int, int");
	}
	
	//We return 1 value (color)
	return 1;
}

int Terminal::setPixel(lua_State* L)
{
	if(lua_gettop(L) >= 3)
	{
		int lc_bg_color = lua_tonumber(L, -1);
		int y = lua_tonumber(L, -2);
		int x = lua_tonumber(L, -3);
		lua_pop(L, -1);
		lua_pop(L, -1);
		lua_pop(L, -1);
		sf::Color bg_color = asSFColor(lc_bg_color);
		the_terminal->setPixel(x, y, bg_color);
		return 0;
	}else
	{
		luaL_error(L, "expected int, int, int");
		return 1;
	}
}

int Terminal::clear(lua_State* L)
{
	if(lua_gettop(L) >= 1)
	{
		int lc_color = lua_tonumber(L, -1);
		lua_pop(L, -1);
		sf::Color col = asSFColor(lc_color);
		the_terminal->clear(col);
		return 0;
	}else
	{
		luaL_error(L, "expected int");
		return 1;
	}
	
}

int Terminal::clearLine(lua_State* L)
{
	if(lua_gettop(L) >= 2)
	{
		int lc_color = lua_tonumber(L, -1);
		int y = lua_tonumber(L, -2);
		lua_pop(L, -1);
		lua_pop(L, -1);
		sf::Color col = asSFColor(lc_color);
		the_terminal->clearLine(y, col);
		return 0;
	}else
	{
		luaL_error(L, "expected int, int");
		return 1;
	}
}

int Terminal::clearArea(lua_State* L)
{
	if(lua_gettop(L) >= 5)
	{
		int lc_color = lua_tonumber(L, -1);
		int height = lua_tonumber(L, -2);
		int width = lua_tonumber(L, -3);
		int y = lua_tonumber(L, -4);
		int x = lua_tonumber(L, -5);
		lua_pop(L, -1);
		lua_pop(L, -1);
		lua_pop(L, -1);
		lua_pop(L, -1);
		lua_pop(L, -1);
		std::cout << x << ";" << y << ";" << width << ";" << height << std::endl;
		sf::Color col = asSFColor(lc_color);
		the_terminal->clearArea(x, y, width, height, col);
		return 0;
	}else
	{
		luaL_error(L, "expected int, int, int, int, int");
		return 1;
	}
	
}