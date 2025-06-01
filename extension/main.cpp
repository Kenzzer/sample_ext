#include "main.hpp"
#include "rconserver.hpp"
#include <CDetour/detours.h>

SampleExt gExt;
SMEXT_LINK(&gExt);

CDetour* gDetour = nullptr;
/*DETOUR_DECL_MEMBER0(Example, void) {
}*/

bool SampleExt::SDK_OnLoad(char* error, size_t maxlength, bool late) {
	IGameConfig* conf;
	if (!gameconfs->LoadGameConfigFile("sample", &conf, error, maxlength)) {
		return false;
	}

	CDetourManager::Init(g_pSM->GetScriptingEngine(), conf);
	g_pSM->LogMessage(myself, "Ext loaded");

	// Setup detour
	/*gDetour = DETOUR_CREATE_MEMBER(CSocketCreator_CreateListenSocket, "CSocketCreator::CreateListenSocket");
	if (gDetour) {
		gDetour->EnableDetour();
	}*/

	// Release the config file, we don't need it anymore
	gameconfs->CloseGameConfigFile(conf);
	return true;
}

void SampleExt::SDK_OnUnload() {
	if (gDetour) {
		gDetour->DisableDetour();
	}
}