#include "lualib.h"
#include "lua.h"
#include "lauxlib.h"
#include "md5.h"


static int
linput(lua_State *L){
	MD5_CTX *ctx = lua_touserdata(L,1);
	int type = lua_type(L,2);
	if(type == LUA_TSTRING){
		size_t n = 0;
		const char *s = lua_tolstring(L,2,&n);
		MD5Update(ctx,(unsigned char*)s,n);
	}
	else if(type == LUA_TLIGHTUSERDATA){
		luaL_checktype(L,3,LUA_TNUMBER);
		void *s = lua_touserdata(L,2);
		unsigned int n = lua_tointeger(L,3);
		MD5Update(ctx,s,n);
	}
	return 0;
}

static int
lfinal(lua_State *L){
	MD5_CTX *ctx = lua_touserdata(L,1);
	MD5Final(ctx);
	char md5[32];
	MD5Hex(ctx,md5);
	lua_pushlstring(L,md5,32);
	return 1;
}

static int
lcreate(lua_State *L){
	static luaL_Reg mf[]={
		{"input",linput},
		{"final",lfinal},
		{NULL,NULL}
	};
	MD5_CTX *ctx = lua_newuserdata(L,sizeof(*ctx));
	MD5Init(ctx);
	if(luaL_newmetatable(L,"lmd5")){
		luaL_newlib(L,mf);
		lua_setfield(L,-2,"__index");
	}
	lua_setmetatable(L,-2);
	return 1;
}

static int
lsumhex(lua_State *L){
	size_t n = 0;
	const char *s = lua_tolstring(L,1,&n);
	if(n == 0){
		lua_pushnil(L);
		return 1;
	}
	MD5_CTX ctx;
	MD5Init(&ctx);
	MD5Update(&ctx,(unsigned char *)s,n);
	MD5Final(&ctx);
	char hex[32];
	MD5Hex(&ctx,hex);
	lua_pushlstring(L,hex,32);
	return 1;
}

int
luaopen_lmd5(lua_State *L){
	static luaL_Reg f[]={
		{"sumhex",lsumhex},
		{"create",lcreate},
		{NULL,NULL}
	};
	luaL_newlib(L,f);
	return 1;
}
