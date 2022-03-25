#include "vcmp.h"
#include "main.h"
#include "squirrel/SQImports.h"
#include "squirrel/SQFuncs.h"

extern PluginFuncs* functions;
HSQAPI sq;
HSQUIRRELVM v;

uint8_t OnPluginCommand(uint32_t commandIdentifier, const char* message)
{
	switch (commandIdentifier)
	{
	case 0x7D6E22D8:
		{
			int32_t pluginId = functions->FindPlugin(PLUGIN_TO_ATTACH_TO);
			if (pluginId > -1)
			{
				size_t size;
				const void** imports = functions->GetPluginExports(pluginId, &size);
				if (imports && size)
				{
					SquirrelImports* sqImports = *(SquirrelImports**)imports;
					if (sqImports)
					{
						sq = *sqImports->GetSquirrelAPI();
						v = *sqImports->GetSquirrelVM();
						RegisterFuncs(v);

						functions->LogMessage("Attached " PLUGIN_NAME " to " PLUGIN_TO_ATTACH_TO " by sfwidde ([R3V]Kelvin).");
						return 1;
					}
				}
			}

			functions->LogMessage("[" PLUGIN_NAME "] Failed to attach to " PLUGIN_TO_ATTACH_TO ".");
		}
		break;
	}

	return 1;
}
