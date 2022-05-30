// --------------------------------------------------

#include "vcmp.h"
#include "main.h"
#include "squirrel/SQImports.h"
#include "squirrel/SQFuncs.h"

// --------------------------------------------------

extern PluginFuncs* vcmpFunction;
HSQAPI sq;
HSQUIRRELVM v;

// --------------------------------------------------

uint8_t OnPluginCommand(uint32_t commandIdentifier, const char* message) {
	switch (commandIdentifier) {
	case 0x7D6E22D8: {
		int32_t pluginId = vcmpFunction->FindPlugin(PLUGIN_TO_ATTACH_TO);
		if (pluginId > -1) {
			size_t size;
			const void** imports = vcmpFunction->GetPluginExports(pluginId, &size);
			if (imports && *imports && size) {
				SquirrelImports* sqImports = *(SquirrelImports**)imports;
				if (sqImports) {
					sq = *sqImports->GetSquirrelAPI();
					v = *sqImports->GetSquirrelVM();
					RegisterFuncs(v);

					vcmpFunction->LogMessage("Attached " PLUGIN_NAME_WITH_CREDITS " to " PLUGIN_TO_ATTACH_TO ".");
					return 1;
				}
			}
		}

		vcmpFunction->LogMessage(PLUGIN_NAME_WITH_CREDITS " failed to attach to " PLUGIN_TO_ATTACH_TO ".");
		break;
	}
	}

	return 1;
}

// --------------------------------------------------