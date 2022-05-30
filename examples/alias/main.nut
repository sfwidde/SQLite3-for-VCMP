// --------------------------------------------------

dofile("scripts/playeralias.nut", true);

// --------------------------------------------------

db <- null; // Database connection.

// --------------------------------------------------

function onScriptLoad() {
	// Open database.
	db = SQLite_Open("alias.db");
	// Create table in case it doesn't exist.
	SQLite_Prepare(db,
		"CREATE TABLE IF NOT EXISTS player_uids " +
		"(uid TEXT        NOT NULL,             " +
		"name TEXT UNIQUE NOT NULL);            ");
}

// --------------------------------------------------

function onScriptUnload() {
	// Close database.
	SQLite_Close(db);
	db = null;
}

// --------------------------------------------------

function onPlayerJoin(player) {
	SavePlayerUID(player);
}

// --------------------------------------------------

function onPlayerCommand(player, cmd, text) {
	cmd = cmd.tolower();
	if (cmd == "uidalias") {
		if (text) {
			local plr = FindPlayer(IsNum(text) ? text.tointeger() : text);
			if (plr) {
				local aliases = GetPlayerUIDAliases(plr);
				if (aliases) {
					local aliasList = "";
					foreach (name in aliases) {
						aliasList += aliasList != "" ? format(", %s", name) : name;
					}
					
					PrivMessage(player, format("%s UID aliases: %s", plr.Name, aliasList));
				} else {
					PrivMessage(player, format("%s has no UID aliases.", plr.Name));
				}
			} else {
				PrivMessage(player, "Unknown player.");
			}
		} else {
			PrivMessage(player, format("Syntax: /%s <player>", cmd));
		}
	}
}

// --------------------------------------------------