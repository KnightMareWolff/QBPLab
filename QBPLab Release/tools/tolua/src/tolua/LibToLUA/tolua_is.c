/* tolua: functions to check types.
 ** Support code for Lua bindings.
 ** Written by Waldemar Celes
 ** TeCGraf/PUC-Rio
 ** Apr 2003
 ** $Id: tolua_is.c,v 1.5 2009/11/24 16:45:15 fabraham Exp $
 */

/* This code is free software; you can redistribute it and/or modify it.
 ** The software provided hereunder is on an "as is" basis, and
 ** the author has no obligation to provide maintenance, support, updates,
 ** enhancements, or modifications.
 */

#include "tolua.h"
#include "LibLUA/lauxlib.h"

#include <stdlib.h>
#include <string.h>

/* Push and returns the corresponding object typename */
TOLUA_API const char* tolua_typename (lua_State* L, int lo)
{
  int tag = lua_type(L,lo);
  if (tag == LUA_TNONE)
    lua_pushstring(L,"[no object]");
  else if (tag != LUA_TUSERDATA && tag != LUA_TTABLE)
    lua_pushstring(L,lua_typename(L,tag));
  else if (tag == LUA_TUSERDATA)
  {
    if (!lua_getmetatable(L,lo)) {
     lua_pushstring(L,lua_typename(L,tag));
    }
    else
    {
      lua_rawget(L,LUA_REGISTRYINDEX);
      if (!lua_isstring(L,-1))
      {
        lua_pop(L,1);
        lua_pushstring(L,"[undefined]");
      }
    }
  }
  else  /* is table */
  {
    lua_pushvalue(L,lo);
    lua_rawget(L,LUA_REGISTRYINDEX);
    if (!lua_isstring(L,-1))
    {
      lua_pop(L,1);
      lua_pushstring(L,"table");
    }
    else
    {
      lua_pushstring(L,"class ");
      lua_insert(L,-2);
      lua_concat(L,2);
    }
  }
  return lua_tostring(L,-1);
}

TOLUA_API void tolua_error (lua_State* L, const char* msg, tolua_Error* err)
{
  if (msg[0] == '#')
  {
    const char* expected = err->type;
    const char* provided = tolua_typename(L,err->index);
    if (msg[1]=='f')
    {
      int narg = err->index;
      if (err->array)
        luaL_error(L,"%s\n     argument #%d is array of '%s'; array of '%s' expected.\n",
            msg+2,narg,provided,expected);
      else
        luaL_error(L,"%s\n     argument #%d is '%s'; '%s' expected.\n",
            msg+2,narg,provided,expected);
    }
    else if (msg[1]=='v')
    {
      if (err->array)
        luaL_error(L,"%s\n     value is array of '%s'; array of '%s' expected.\n",
            msg+2,provided,expected);
      else
        luaL_error(L,"%s\n     value is '%s'; '%s' expected.\n",
            msg+2,provided,expected);
    }
  }
  else
    luaL_error(L,msg);
}

/* the equivalent of lua_is* for usertable */
static  int lua_isusertable (lua_State* L, int lo, const char* type)
{
  int r = 0;
  if (lo < 0) lo = lua_gettop(L)+lo+1;
  lua_pushvalue(L,lo);
  lua_rawget(L,LUA_REGISTRYINDEX);  /* get registry[t] */
  if (lua_isstring(L,-1))
  {
    r = strcmp(lua_tostring(L,-1),type)==0;
    if (!r)
    {
      /* try const */
      lua_pushstring(L,"const ");
      lua_insert(L,-2);
      lua_concat(L,2);
      r = lua_isstring(L,-1) && strcmp(lua_tostring(L,-1),type)==0;
    }
  }
  lua_pop(L, 1);
  return r;
}

/* the equivalent of lua_is* for usertype */
static int lua_isusertype (lua_State* L, int lo, const char* type)
{
  if (lua_isuserdata(L,lo))
  {
    /* check if it is of the same type */
    int r;
    const char *tn;
    if (lua_getmetatable(L,lo))        /* if metatable? */
    {
      lua_rawget(L,LUA_REGISTRYINDEX);  /* get registry[mt] */
      tn = lua_tostring(L,-1);
      r = tn && (strcmp(tn,type) == 0);
      lua_pop(L, 1);
      if (r)
        return 1;
      else
      {
        /* check if it is a specialized class */
        lua_pushstring(L,"tolua_super");
        lua_rawget(L,LUA_REGISTRYINDEX); /* get super */
        lua_getmetatable(L,lo);
        lua_rawget(L,-2);                /* get super[mt] */
        if (lua_istable(L,-1))
        {
          int b;
          lua_pushstring(L,type);
          lua_rawget(L,-2);                /* get super[mt][type] */
          b = lua_toboolean(L,-1);
          lua_pop(L,3);
          if (b)
            return 1;
        }
      }
    }
  }
  return 0;
}

TOLUA_API int tolua_isnoobj (lua_State* L, int lo, tolua_Error* err)
{
  if (lua_gettop(L)<abs(lo))
    return 1;
  err->index = lo;
  err->array = 0;
  err->type = NULL;
  return 0;
}
TOLUA_API int tolua_isvalue (lua_State* L, int lo, int def, tolua_Error* err)
{
  if (def || abs(lo)<=lua_gettop(L))  /* any valid index */
    return 1;
  err->index = lo;
  err->array = 0;
  err->type = "value";
  return 0;
}

TOLUA_API int tolua_isboolean (lua_State* L, int lo, int def, tolua_Error* err)
{
  if (def && lua_gettop(L)<abs(lo))
    return 1;
  if (lua_isnil(L,lo) || lua_isboolean(L,lo))
    return 1;
  err->index = lo;
  err->array = 0;
  err->type = "boolean";
  return 0;
}

TOLUA_API int tolua_isnumber (lua_State* L, int lo, int def, tolua_Error* err)
{
  if (def && lua_gettop(L)<abs(lo))
    return 1;
  if (lua_isnumber(L,lo))
    return 1;
  err->index = lo;
  err->array = 0;
  err->type = "number";
  return 0;
}

TOLUA_API int tolua_isstring (lua_State* L, int lo, int def, tolua_Error* err)
{
  if (def && lua_gettop(L)<abs(lo))
    return 1;
  if (lua_isnil(L,lo) || lua_isstring(L,lo))
    return 1;
  err->index = lo;
  err->array = 0;
  err->type = "string";
  return 0;
}

TOLUA_API int tolua_istable (lua_State* L, int lo, int def, tolua_Error* err)
{
  if (def && lua_gettop(L)<abs(lo))
    return 1;
  if (lua_istable(L,lo))
    return 1;
  err->index = lo;
  err->array = 0;
  err->type = "table";
  return 0;
}

TOLUA_API int tolua_isusertable (lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
  if (def && lua_gettop(L)<abs(lo))
    return 1;
  if (lua_isusertable(L,lo,type))
    return 1;
  err->index = lo;
  err->array = 0;
  err->type = type;
  return 0;
}

TOLUA_API int tolua_isfunction (lua_State* L, int lo, int def, tolua_Error* err)
{
  if (def && lua_gettop(L)<abs(lo))
    return 1;
  if (lua_isfunction(L,lo))
    return 1;
  err->index = lo;
  err->array = 0;
  err->type = "function";
  return 0;
}

TOLUA_API int tolua_isuserdata (lua_State* L, int lo, int def, tolua_Error* err)
{
  if (def && lua_gettop(L)<abs(lo))
    return 1;
  if (lua_isnil(L,lo) || lua_isuserdata(L,lo))
    return 1;
  err->index = lo;
  err->array = 0;
  err->type = "userdata";
  return 0;
}

TOLUA_API int tolua_isusertype (lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
  if (def && lua_gettop(L)<abs(lo))
    return 1;
  if (lua_isnil(L,lo) || lua_isusertype(L,lo,type))
    return 1;
  err->index = lo;
  err->array = 0;
  err->type = type;
  return 0;
}

TOLUA_API int tolua_isvaluearray
(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
  if (!tolua_istable(L,lo,def,err))
    return 0;
  else
    return 1;
}

TOLUA_API int tolua_isbooleanarray
(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
  if (!tolua_istable(L,lo,def,err))
    return 0;
  else
  {
    int i;
    for (i=1; i<=dim; ++i)
    {
      lua_pushnumber(L,i);
      lua_gettable(L,lo);
      if (!(lua_isnil(L,-1) || lua_isboolean(L,-1)) &&
          !(def && lua_isnil(L,-1))
      )
      {
        err->index = lo;
        err->array = 1;
        err->type = "boolean";
        return 0;
      }
      lua_pop(L,1);
    }
  }
  return 1;
}

TOLUA_API int tolua_isnumberarray
(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
  if (!tolua_istable(L,lo,def,err))
    return 0;
  else
  {
    int i;
    for (i=1; i<=dim; ++i)
    {
      lua_pushnumber(L,i);
      lua_gettable(L,lo);
      if (!lua_isnumber(L,-1) &&
          !(def && lua_isnil(L,-1))
      )
      {
        err->index = lo;
        err->array = 1;
        err->type = "number";
        return 0;
      }
      lua_pop(L,1);
    }
  }
  return 1;
}

TOLUA_API int tolua_isstringarray
(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
  if (!tolua_istable(L,lo,def,err))
    return 0;
  else
  {
    int i;
    for (i=1; i<=dim; ++i)
    {
      lua_pushnumber(L,i);
      lua_gettable(L,lo);
      if (!(lua_isnil(L,-1) || lua_isstring(L,-1)) &&
          !(def && lua_isnil(L,-1))
      )
      {
        err->index = lo;
        err->array = 1;
        err->type = "string";
        return 0;
      }
      lua_pop(L,1);
    }
  }
  return 1;
}

TOLUA_API int tolua_istablearray
(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
  if (!tolua_istable(L,lo,def,err))
    return 0;
  else
  {
    int i;
    for (i=1; i<=dim; ++i)
    {
      lua_pushnumber(L,i);
      lua_gettable(L,lo);
      if (! lua_istable(L,-1) &&
          !(def && lua_isnil(L,-1))
      )
      {
        err->index = lo;
        err->array = 1;
        err->type = "table";
        return 0;
      }
      lua_pop(L,1);
    }
  }
  return 1;
}

TOLUA_API int tolua_isuserdataarray
(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
  if (!tolua_istable(L,lo,def,err))
    return 0;
  else
  {
    int i;
    for (i=1; i<=dim; ++i)
    {
      lua_pushnumber(L,i);
      lua_gettable(L,lo);
      if (!(lua_isnil(L,-1) || lua_isuserdata(L,-1)) &&
          !(def && lua_isnil(L,-1))
      )
      {
        err->index = lo;
        err->array = 1;
        err->type = "userdata";
        return 0;
      }
      lua_pop(L,1);
    }
  }
  return 1;
}

TOLUA_API int tolua_isusertypearray
(lua_State* L, int lo, const char* type, int dim, int def, tolua_Error* err)
{
  if (!tolua_istable(L,lo,def,err))
    return 0;
  else
  {
    int i;
    for (i=1; i<=dim; ++i)
    {
      lua_pushnumber(L,i);
      lua_gettable(L,lo);
      if (!(lua_isnil(L,-1) || lua_isuserdata(L,-1)) &&
          !(def && lua_isnil(L,-1))
      )
      {
        err->index = lo;
        err->type = type;
        err->array = 1;
        return 0;
      }
      lua_pop(L,1);
    }
  }
  return 1;
}

#if 0
int tolua_isbooleanfield
(lua_State* L, int lo, int i, int def, tolua_Error* err)
{
  lua_pushnumber(L,i);
  lua_gettable(L,lo);
  if (!(lua_isnil(L,-1) || lua_isboolean(L,-1)) &&
      !(def && lua_isnil(L,-1))
  )
  {
    err->index = lo;
    err->array = 1;
    err->type = "boolean";
    return 0;
  }
  lua_pop(L,1);
  return 1;
}

int tolua_isnumberfield
(lua_State* L, int lo, int i, int def, tolua_Error* err)
{
  lua_pushnumber(L,i);
  lua_gettable(L,lo);
  if (!lua_isnumber(L,-1) &&
      !(def && lua_isnil(L,-1))
  )
  {
    err->index = lo;
    err->array = 1;
    err->type = "number";
    return 0;
  }
  lua_pop(L,1);
  return 1;
}

int tolua_isstringfield
(lua_State* L, int lo, int i, int def, tolua_Error* err)
{
  lua_pushnumber(L,i);
  lua_gettable(L,lo);
  if (!(lua_isnil(L,-1) || lua_isstring(L,-1)) &&
      !(def && lua_isnil(L,-1))
  )
  {
    err->index = lo;
    err->array = 1;
    err->type = "string";
    return 0;
  }
  lua_pop(L,1);
  return 1;
}

int tolua_istablefield
(lua_State* L, int lo, int i, int def, tolua_Error* err)
{
  lua_pushnumber(L,i+1);
  lua_gettable(L,lo);
  if (! lua_istable(L,-1) &&
      !(def && lua_isnil(L,-1))
  )
  {
    err->index = lo;
    err->array = 1;
    err->type = "table";
    return 0;
  }
  lua_pop(L,1);
}

int tolua_isusertablefield
(lua_State* L, int lo, const char* type, int i, int def, tolua_Error* err)
{
  lua_pushnumber(L,i);
  lua_gettable(L,lo);
  if (! lua_isusertable(L,-1,type) &&
      !(def && lua_isnil(L,-1))
  )
  {
    err->index = lo;
    err->array = 1;
    err->type = type;
    return 0;
  }
  lua_pop(L,1);
  return 1;
}

int tolua_isuserdatafield
(lua_State* L, int lo, int i, int def, tolua_Error* err)
{
  lua_pushnumber(L,i);
  lua_gettable(L,lo);
  if (!(lua_isnil(L,-1) || lua_isuserdata(L,-1)) &&
      !(def && lua_isnil(L,-1))
  )
  {
    err->index = lo;
    err->array = 1;
    err->type = "userdata";
    return 0;
  }
  lua_pop(L,1);
  return 1;
}

int tolua_isusertypefield
(lua_State* L, int lo, const char* type, int i, int def, tolua_Error* err)
{
  lua_pushnumber(L,i);
  lua_gettable(L,lo);
  if (!(lua_isnil(L,-1) || lua_isusertype(L,-1,type)) &&
      !(def && lua_isnil(L,-1))
  )
  {
    err->index = lo;
    err->type = type;
    err->array = 1;
    return 0;
  }
  lua_pop(L,1);
  return 1;
}

#endif
