dofile("scripts/playeralias.nut", true);

// database connection
db <- null;

function onScriptLoad()
{
	// open database
	db = SQLite_Connect("alias.db");
	// create table in case it doesn't exist
	SQLite_Query(db,
				 "CREATE TABLE IF NOT EXISTS player_uids " +
				 "(uid TEXT        NOT NULL,             " +
				 "name TEXT UNIQUE NOT NULL);            ");
}

function onScriptUnload()
{
	// close database
	SQLite_Disconnect(db);
	db = null;
}

function onPlayerJoin(player)
{
	SavePlayerUID(player);
}

function onPlayerCommand(player, cmd, text)
{
	cmd = cmd.tolower();
	if (cmd == "uidalias")
	{
		if (text)
		{
			local plr = FindPlayer(IsNum(text) ? text.tointeger() : text);
			if (plr)
			{
				local aliases = GetPlayerUIDAliases(plr);
				if (aliases)
				{
					local aliasList = "";
					foreach (name in aliases)
						aliasList += aliasList != "" ? format(", %s", name) : name;
					
					PrivMessage(player, format("%s UID aliases: %s", plr.Name, aliasList));
				}
				else PrivMessage(player, format("%s has no UID aliases.", plr.Name));
			}
			else PrivMessage(player, "Unknown player.");
		}
		else PrivMessage(player, format("Syntax: /%s <player>", cmd));
	}
}
