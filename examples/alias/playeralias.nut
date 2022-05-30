// --------------------------------------------------

function SavePlayerUID(player) {
    SQLite_Prepare(db, format("INSERT INTO player_uids (uid, name) VALUES ('%s', '%s');", player.UID, player.Name));
}

// --------------------------------------------------

function GetPlayerUIDAliases(player) {
    // Try to get names.
    local stmt = SQLite_Prepare(db, format("SELECT name FROM player_uids WHERE uid = '%s';", player.UID));
    // Success.
    if (stmt) {
        // Array holding string names.
        local result = [];
        local playerName = player.Name;
        do {
            // Get name from current row.
            local name = SQLite_GetColumnData(stmt, 0);
            // Append ONLY if 'name' != 'playerName'.
            if (name != playerName) {
                result.append(name);
            }
        } while (SQLite_GetNextRow(stmt)); // Loop until there are no more rows available.
        // 'SELECT' statements must always be freed!
        SQLite_Finalize(stmt);

        // Did we actually append anything
        // to the resulting array?
        if (result.len() > 0) {
            return result;
        }
    }

    // Return null in any case.
    return null;
}

// --------------------------------------------------