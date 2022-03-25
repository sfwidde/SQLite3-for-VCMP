function SavePlayerUID(player)
{
    SQLite_Query(db, format("INSERT INTO player_uids (uid, name) VALUES ('%s', '%s');", player.UID, player.Name));
}

function GetPlayerUIDAliases(player)
{
    // try to get names
    local stmt = SQLite_Query(db, format("SELECT name FROM player_uids WHERE uid = '%s';", player.UID));
    // success
    if (stmt)
    {
        // array holding string names
        local result = [];
        local playerName = player.Name;
        do
        {
            // get name from current row
            local name = SQLite_GetColumnData(stmt, 0);
            // append ONLY if 'name' != 'playerName'
            if (name != playerName)
                result.append(name);
        }
        // loop until there are no more rows available
        while (SQLite_GetNextRow(stmt));
        // SELECT statements must always be freed!
        SQLite_FreeQuery(stmt);

        // did we actually append anything
        // to the resulting array?
        if (result.len() > 0)
            return result;
    }

    // return null in any case
    return null;
}
