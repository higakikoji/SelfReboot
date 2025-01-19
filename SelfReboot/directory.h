#pragma once

typedef struct directory_t directory_t;

/// <summary>
/// Constructor
/// </summary>
/// <param name="allocation_size">Allocation size for each pathes</param>
/// <returns>Pointer of the directory_t structure</returns>
directory_t *directory_ctor(DWORD allocation_size);

/// <summary>
/// Get current directory
/// </summary>
/// <param name="this">Pointer of the directory_t structure</param>
/// <returns>Current directory</returns>
LPTSTR directory_get_current(directory_t *this);

/// <summary>
/// Destructor
/// </summary>
/// <param name="this">Pointer of the directory_t structure</param>
void directory_dtor(directory_t *this);
