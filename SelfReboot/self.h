#pragma once

typedef struct self_t self_t;

/// <summary>
/// Constructor
/// </summary>
/// <param name="allocation_size">Allocation size for each pathes</param>
/// <returns>Pointer of the self_t structure</returns>
self_t *self_ctor(DWORD allocation_size);

LPTSTR self_get_path(self_t *this);
LPTSTR self_get_name(self_t *this);
LPTSTR self_get_name_without_extension(self_t *this);
LPTSTR self_get_directory_path(self_t *this);
LPTSTR self_get_directory_name(self_t *this);

BOOL self_restart(self_t *this, LPCTSTR id);
BOOL self_check_restart(self_t *this, LPCTSTR id, DWORD wait, LPCTSTR restarted_id, DWORD restarted_pid);

/// <summary>
/// Destructor
/// </summary>
/// <returns>Pointer of the self_t structure</returns>
void self_dtor(self_t *this);
