// --------------------------------------------------

#include "main.h"
#include "vcmp.h"
#include <string.h>

// --------------------------------------------------

PluginFuncs* vcmpFunction = NULL;

// --------------------------------------------------

uint8_t OnPluginCommand(uint32_t, const char*);

// --------------------------------------------------

#ifdef _WIN32
__declspec(dllexport)
#endif
unsigned int VcmpPluginInit(PluginFuncs* pluginFuncs, PluginCallbacks* pluginCalls, PluginInfo* pluginInfo) {
	strcpy(pluginInfo->name, PLUGIN_NAME);
	pluginInfo->apiMajorVersion = PLUGIN_API_MAJOR;
	pluginInfo->apiMinorVersion = PLUGIN_API_MINOR;

	vcmpFunction = pluginFuncs;

	pluginCalls->OnPluginCommand = OnPluginCommand;

	return 1;
}

// --------------------------------------------------