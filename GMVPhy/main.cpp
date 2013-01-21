#include "GarrysMod/Lua/Interface.h"

#include <vphysics_interface.h>

IPhysics *g_pPhysics = NULL;

int lPhysStats(lua_State *state) {
	// 3000 is just a big number, don't worry about it
	for (int i = 0; i < 3000; i++) {
		IPhysicsEnvironment *pEnv = g_pPhysics->GetActiveEnvironmentByIndex(i);
		if (!pEnv)
			break;

		Msg("Environment %d active\n", i);
		Msg("\t%d active objects\n", pEnv->GetActiveObjectCount());
	}

	return 0;
}

GMOD_MODULE_OPEN() {
	CreateInterfaceFn physFactory = Sys_GetFactory("vphysics");
	if (physFactory)
		g_pPhysics = (IPhysics *)physFactory(VPHYSICS_INTERFACE_VERSION, NULL);

	if (g_pPhysics)
		Msg("Found physics interface!\n");

	// Let's setup our table of functions
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		LUA->CreateTable();
			LUA->PushCFunction(lPhysStats); LUA->SetField(-2, "printstats");
		LUA->SetField(-2, "vphysics");
	LUA->Pop();

	return 0;
}

GMOD_MODULE_CLOSE() {
	return 0;
}