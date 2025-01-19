#pragma once

typedef struct err_t err_t;

/// <summary>
/// Constructor
/// </summary>
/// <returns>Pointer of the err_t structure</returns>
err_t *err_ctor(void);

/// <summary>
/// Get error code
/// </summary>
/// <param name="this">Pointer of the err_t structure</param>
/// <returns>Error code</returns>
DWORD err_get(err_t *this);

/// <summary>
/// Get error code string
/// </summary>
/// <param name="this">Pointer of the err_t structure</param>
/// <returns>Error string</returns>
LPTSTR err_get_string(err_t *this);

/// <summary>
/// Destructor
/// </summary>
/// <param name="this">Pointer of the err_t structure</param>
void err_dtor(err_t *this);
