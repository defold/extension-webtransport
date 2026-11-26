#define LIB_NAME "Webtransport"
#define MODULE_NAME "webtransport"

#include <dmsdk/sdk.h>

namespace dmWebtransport
{

// Functions exposed to Lua will be added here.
static const luaL_reg Webtransport_module_methods[] =
{
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    luaL_register(L, MODULE_NAME, Webtransport_module_methods);
    lua_pop(L, 1);
}

static dmExtension::Result AppInitialize(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalize(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result Initialize(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result Finalize(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result OnUpdate(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

} // namespace dmWebtransport

DM_DECLARE_EXTENSION(Webtransport, LIB_NAME, dmWebtransport::AppInitialize, dmWebtransport::AppFinalize, dmWebtransport::Initialize, dmWebtransport::OnUpdate, 0, dmWebtransport::Finalize)
