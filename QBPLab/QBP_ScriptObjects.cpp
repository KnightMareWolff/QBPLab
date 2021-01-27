/*
** Lua binding: ObjetosExportados
*/


#include "QBP_GlobalDef.h"
#include "QBP_ScriptObjectsBind.h"

#include "LibToLua/tolua.h"

#ifndef __cplusplus
#include <stdlib.h>
#endif
#ifdef __cplusplus
 extern "C" int tolua_bnd_takeownership (lua_State* L); // from tolua_map.c
#else
 int tolua_bnd_takeownership (lua_State* L); /* from tolua_map.c */
#endif
#include <string.h>

 /* Exported function */
 TOLUA_API int tolua_ObjetosExportados_open (lua_State* tolua_S);
 LUALIB_API int luaopen_ObjetosExportados (lua_State* tolua_S);


 /* function to release collected object via destructor */
 #ifdef __cplusplus

 static int tolua_collect_QBPSearchEngine (lua_State* tolua_S)
 {
  QBPSearchEngine* self = (QBPSearchEngine*) tolua_tousertype(tolua_S,1,0);
  tolua_release(tolua_S,self);
  delete self;
  return 0;
 }
 #endif


 /* function to register type */
 static void tolua_reg_types (lua_State* tolua_S)
 {
  tolua_usertype(tolua_S,"QBPSearchEngine");
 }

 /* method: new of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_new00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertable(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,2,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
  {
   QBPSearchEngine* tolua_ret = (QBPSearchEngine*)  new QBPSearchEngine();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"QBPSearchEngine");
  }
  }
  return 1;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: delete of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_delete00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,2,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
 #endif
  tolua_release(tolua_S,self);
  delete self;
  }
  return 0;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: Search of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_Search00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isstring(tolua_S,2,0,&tolua_err) ||
  !tolua_isstring(tolua_S,3,0,&tolua_err) ||
  !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
  !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
  !tolua_isboolean(tolua_S,6,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,7,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   char* SearchName = ((char*)  tolua_tostring(tolua_S,2,0));
   char* SongAName = ((char*)  tolua_tostring(tolua_S,3,0));
   int DatasetType = ((int)  tolua_tonumber(tolua_S,4,0));
   int ComparatorType = ((int)  tolua_tonumber(tolua_S,5,0));
   bool UseAttitude = ((bool)  tolua_toboolean(tolua_S,6,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Search'",NULL);
 #endif
  {
   bool tolua_ret = (bool)  self->Search(SearchName,SongAName,DatasetType,ComparatorType,UseAttitude);
  tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
  }
  return 1;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'Search'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: Search of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_Search01(lua_State* tolua_S)
 {
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isstring(tolua_S,2,0,&tolua_err) ||
  !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
  !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
  !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
  !tolua_isboolean(tolua_S,6,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,7,&tolua_err)
  )
  goto tolua_lerror;
  else
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   char* SearchName = ((char*)  tolua_tostring(tolua_S,2,0));
   int SongAId = ((int)  tolua_tonumber(tolua_S,3,0));
   int DatasetType = ((int)  tolua_tonumber(tolua_S,4,0));
   int ComparatorType = ((int)  tolua_tonumber(tolua_S,5,0));
   bool UseAttitude = ((bool)  tolua_toboolean(tolua_S,6,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Search'",NULL);
 #endif
  {
   bool tolua_ret = (bool)  self->Search(SearchName,SongAId,DatasetType,ComparatorType,UseAttitude);
  tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
  }
  return 1;
 tolua_lerror:
  return tolua_ObjetosExportados_QBPSearchEngine_Search00(tolua_S);
 }

 /* method: SetPrecisionBalance of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_SetPrecisionBalance00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,3,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   int Precision = ((int)  tolua_tonumber(tolua_S,2,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPrecisionBalance'",NULL);
 #endif
  {
   self->SetPrecisionBalance(Precision);
  }
  }
  return 0;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'SetPrecisionBalance'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: SetResultSizeBalance of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_SetResultSizeBalance00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,3,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   int ResultSize = ((int)  tolua_tonumber(tolua_S,2,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetResultSizeBalance'",NULL);
 #endif
  {
   self->SetResultSizeBalance(ResultSize);
  }
  }
  return 0;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'SetResultSizeBalance'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: SetBufferSize of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_SetBufferSize00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,3,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   int BufferSize = ((int)  tolua_tonumber(tolua_S,2,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBufferSize'",NULL);
 #endif
  {
   self->SetBufferSize(BufferSize);
  }
  }
  return 0;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'SetBufferSize'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: SetPProcType of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_SetPProcType00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,3,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   int PProcType = ((int)  tolua_tonumber(tolua_S,2,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPProcType'",NULL);
 #endif
  {
   self->SetPProcType(PProcType);
  }
  }
  return 0;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'SetPProcType'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: CreateList of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_CreateList00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
  !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,4,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   int DatasetType = ((int)  tolua_tonumber(tolua_S,2,0));
   int CreationFormula = ((int)  tolua_tonumber(tolua_S,3,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateList'",NULL);
 #endif
  {
   self->CreateList(DatasetType,CreationFormula);
  }
  }
  return 0;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'CreateList'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: GetListSize of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_GetListSize00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,3,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   int DatasetType = ((int)  tolua_tonumber(tolua_S,2,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetListSize'",NULL);
 #endif
  {
   int tolua_ret = (int)  self->GetListSize(DatasetType);
  tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
  }
  return 1;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'GetListSize'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: GetListSongName of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_GetListSongName00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
  !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,4,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   int DatasetType = ((int)  tolua_tonumber(tolua_S,2,0));
   int pQBPMusicId = ((int)  tolua_tonumber(tolua_S,3,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetListSongName'",NULL);
 #endif
  {
   char* tolua_ret = (char*)  self->GetListSongName(DatasetType,pQBPMusicId);
  tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
  }
  return 1;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'GetListSongName'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: GetListSongNotes of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_GetListSongNotes00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
  !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,4,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   int DatasetType = ((int)  tolua_tonumber(tolua_S,2,0));
   int pQBPMusicId = ((int)  tolua_tonumber(tolua_S,3,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetListSongNotes'",NULL);
 #endif
  {
   int tolua_ret = (int)  self->GetListSongNotes(DatasetType,pQBPMusicId);
  tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
  }
  return 1;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'GetListSongNotes'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: GetListSongScore of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_GetListSongScore00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
  !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,4,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   int DatasetType = ((int)  tolua_tonumber(tolua_S,2,0));
   int pQBPMusicId = ((int)  tolua_tonumber(tolua_S,3,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetListSongScore'",NULL);
 #endif
  {
   int tolua_ret = (int)  self->GetListSongScore(DatasetType,pQBPMusicId);
  tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
  }
  return 1;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'GetListSongScore'.",&tolua_err);
  return 0;
 #endif
 }

 /* method: PushLog of class  QBPSearchEngine */
 static int tolua_ObjetosExportados_QBPSearchEngine_PushLog00(lua_State* tolua_S)
 {
 #ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
  !tolua_isusertype(tolua_S,1,"QBPSearchEngine",0,&tolua_err) ||
  !tolua_isstring(tolua_S,2,0,&tolua_err) ||
  !tolua_isnoobj(tolua_S,3,&tolua_err)
  )
  goto tolua_lerror;
  else
 #endif
  {
   QBPSearchEngine* self = (QBPSearchEngine*)  tolua_tousertype(tolua_S,1,0);
   char* pQBPLogString = ((char*)  tolua_tostring(tolua_S,2,0));
 #ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PushLog'",NULL);
 #endif
  {
   self->PushLog(pQBPLogString);
  }
  }
  return 0;
 #ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'PushLog'.",&tolua_err);
  return 0;
 #endif
 }

 /* Open lib function */
 LUALIB_API int luaopen_ObjetosExportados (lua_State* tolua_S)
 {
  tolua_open(tolua_S);
  tolua_reg_types(tolua_S);
  tolua_module(tolua_S,NULL,0);
  tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"QBP_ALG_SW",QBP_ALG_SW);
  tolua_constant(tolua_S,"QBP_ALG_MUSSUM",QBP_ALG_MUSSUM);
  tolua_constant(tolua_S,"QBP_ALG_MUSSIX",QBP_ALG_MUSSIX);
  tolua_constant(tolua_S,"QBP_ALG_MUSSAT",QBP_ALG_MUSSAT);
  tolua_constant(tolua_S,"QBP_LIST_FULLSET",QBP_LIST_FULLSET);
  tolua_constant(tolua_S,"QBP_LIST_TESTSET",QBP_LIST_TESTSET);
  tolua_constant(tolua_S,"QBP_LIST_VALISET",QBP_LIST_VALISET);
  tolua_constant(tolua_S,"QBP_LIST_RANDSET",QBP_LIST_RANDSET);
  tolua_constant(tolua_S,"QBP_FORM_LESS_GENRE",QBP_FORM_LESS_GENRE);
  tolua_constant(tolua_S,"QBP_FORM_PERC_10",QBP_FORM_PERC_10);
  tolua_constant(tolua_S,"QBP_FORM_PERC_15",QBP_FORM_PERC_15);
  tolua_constant(tolua_S,"QBP_FORM_LESS_1015F",QBP_FORM_LESS_1015F);
  tolua_constant(tolua_S,"QBP_PPROC_F1",QBP_PPROC_F1);
  tolua_constant(tolua_S,"QBP_PPROC_B1",QBP_PPROC_B1);
  tolua_constant(tolua_S,"QBP_PPROC_G1",QBP_PPROC_G1);
  tolua_constant(tolua_S,"QBP_PPROC_A1",QBP_PPROC_A1);
 #ifdef __cplusplus
  tolua_cclass(tolua_S,"QBPSearchEngine","QBPSearchEngine","",tolua_collect_QBPSearchEngine);
 #else
  tolua_cclass(tolua_S,"QBPSearchEngine","QBPSearchEngine","",NULL);
 #endif
  tolua_beginmodule(tolua_S,"QBPSearchEngine");
  tolua_function(tolua_S,"new",tolua_ObjetosExportados_QBPSearchEngine_new00);
  tolua_function(tolua_S,"delete",tolua_ObjetosExportados_QBPSearchEngine_delete00);
  tolua_function(tolua_S,"Search",tolua_ObjetosExportados_QBPSearchEngine_Search00);
  tolua_function(tolua_S,"Search",tolua_ObjetosExportados_QBPSearchEngine_Search01);
  tolua_function(tolua_S,"SetPrecisionBalance",tolua_ObjetosExportados_QBPSearchEngine_SetPrecisionBalance00);
  tolua_function(tolua_S,"SetResultSizeBalance",tolua_ObjetosExportados_QBPSearchEngine_SetResultSizeBalance00);
  tolua_function(tolua_S,"SetBufferSize",tolua_ObjetosExportados_QBPSearchEngine_SetBufferSize00);
  tolua_function(tolua_S,"SetPProcType",tolua_ObjetosExportados_QBPSearchEngine_SetPProcType00);
  tolua_function(tolua_S,"CreateList",tolua_ObjetosExportados_QBPSearchEngine_CreateList00);
  tolua_function(tolua_S,"GetListSize",tolua_ObjetosExportados_QBPSearchEngine_GetListSize00);
  tolua_function(tolua_S,"GetListSongName",tolua_ObjetosExportados_QBPSearchEngine_GetListSongName00);
  tolua_function(tolua_S,"GetListSongNotes",tolua_ObjetosExportados_QBPSearchEngine_GetListSongNotes00);
  tolua_function(tolua_S,"GetListSongScore",tolua_ObjetosExportados_QBPSearchEngine_GetListSongScore00);
  tolua_function(tolua_S,"PushLog",tolua_ObjetosExportados_QBPSearchEngine_PushLog00);
  tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  return 1;
 }
 /* Open tolua function */
 TOLUA_API int tolua_ObjetosExportados_open (lua_State* tolua_S)
 {
  lua_pushcfunction(tolua_S, luaopen_ObjetosExportados);
  lua_pushstring(tolua_S, "ObjetosExportados");
  lua_call(tolua_S, 1, 0);
  return 1;
 }
