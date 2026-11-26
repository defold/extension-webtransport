#define LIB_NAME "Webtransport"
#define MODULE_NAME "webtransport"

#include <dmsdk/sdk.h>
#include <string.h>

namespace dmWebtransport
{

enum Event
{
    EVENT_CONNECTED = 1,
    EVENT_DISCONNECTED,
    EVENT_ERROR,
    EVENT_MESSAGE
};

static void CheckOptions(lua_State* L, int index)
{
    if (!lua_isnoneornil(L, index))
        luaL_checktype(L, index, LUA_TTABLE);
}

static void* CheckConnection(lua_State* L, int index)
{
    luaL_checktype(L, index, LUA_TLIGHTUSERDATA);
    void* connection = lua_touserdata(L, index);
    luaL_argcheck(L, connection != 0, index, "connection must not be null");
    return connection;
}

static int NotImplemented(lua_State* L)
{
    lua_pushnil(L);
    lua_pushliteral(L, "not_implemented");
    return 2;
}

// webtransport.connect(url, options, callback) -> connection, err
static int LuaConnect(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 2);

    luaL_checktype(L, 1, LUA_TSTRING);
    size_t url_length = 0;
    const char* url = luaL_checklstring(L, 1, &url_length);
    luaL_argcheck(L, url_length > 0, 1, "url must not be empty");
    luaL_argcheck(L, strlen(url) == url_length, 1, "url must not contain null bytes");

    // Connection options are reserved for the transport implementation.
    CheckOptions(L, 2);
    luaL_checktype(L, 3, LUA_TFUNCTION);

    // TODO: Create a connection and retain the callback with dmScript::CreateCallback.
    return NotImplemented(L);
}

// webtransport.send(connection, data, options) -> ok, err
static int LuaSend(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 2);

    void* connection = CheckConnection(L, 1);
    luaL_checktype(L, 2, LUA_TSTRING);
    size_t data_length = 0;
    const char* data = luaL_checklstring(L, 2, &data_length);

    CheckOptions(L, 3);
    bool reliable = true;
    if (!lua_isnoneornil(L, 3))
    {
        lua_getfield(L, 3, "reliable");
        if (!lua_isnil(L, -1) && !lua_isboolean(L, -1))
        {
            lua_pop(L, 1);
            return luaL_argerror(L, 3, "'reliable' must be a boolean");
        }
        if (!lua_isnil(L, -1))
            reliable = lua_toboolean(L, -1) != 0;
        lua_pop(L, 1);
    }

    // TODO: Validate connection ownership and send data_length bytes using reliable.
    (void)connection;
    (void)data;
    (void)data_length;
    (void)reliable;
    return NotImplemented(L);
}

// webtransport.disconnect(connection)
static int LuaDisconnect(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    void* connection = CheckConnection(L, 1);

    // TODO: Close the connection and release its callback. Repeated calls are harmless.
    (void)connection;
    return 0;
}

// Functions exposed to Lua.
static const luaL_reg Webtransport_module_methods[] =
{
    {"connect", LuaConnect},
    {"send", LuaSend},
    {"disconnect", LuaDisconnect},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    luaL_register(L, MODULE_NAME, Webtransport_module_methods);

    lua_pushinteger(L, EVENT_CONNECTED);
    lua_setfield(L, -2, "EVENT_CONNECTED");
    lua_pushinteger(L, EVENT_DISCONNECTED);
    lua_setfield(L, -2, "EVENT_DISCONNECTED");
    lua_pushinteger(L, EVENT_ERROR);
    lua_setfield(L, -2, "EVENT_ERROR");
    lua_pushinteger(L, EVENT_MESSAGE);
    lua_setfield(L, -2, "EVENT_MESSAGE");

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
