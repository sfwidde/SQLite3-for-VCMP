# SQLite3 plugin for VC:MP 0.4

**Available functions:**
- `SQLite_Open`
  - **Parameter:** _string_ file path.
  - **Return type:** _sqlite3*_.
  - Throws error.
- `SQLite_Close`
  - **Parameter:** _sqlite3*_.
  - Returns nothing.
  - Throws error.
- `SQLite_Prepare`
  - **Parameters:** _sqlite3*_, _string_ query.
  - **Return type:** _sqlite3_stmt*_/_null_.
  - Throws error.
- `SQLite_GetNextRow`
  - **Parameter:** _sqlite3_stmt*_.
  - **Return type:** _bool_.
  - Throws no errors.
- `SQLite_GetColumnCount`
  - **Parameter:** _sqlite3_stmt*_.
  - **Return type:** _int_.
  - Throws no errors.
- `SQLite_GetColumnData`
  - **Parameters:** _sqlite3_stmt*_, _int_ column index.
  - **Return type:** _int_/_float_/_string_/_null_.
- `SQLite_Finalize`
  - **Parameter:** _sqlite3_stmt*_.
  - Returns nothing.
  - Throws no errors.
- `SQLite_EscapeString`
  - **Parameter:** _string_.
  - **Return type:** _string_.
  - Throws error.

Head to ***examples*** folder to find examples on how to use this plugin.
