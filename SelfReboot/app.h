#pragma once

typedef struct app_t app_t;

/// <summary>
/// Constructor
/// </summary>
/// <returns>Pointer of the app_t structure</returns>
app_t *app_ctor(void);

/// <summary>
/// Command loop
/// </summary>
/// <param name="this">Pointer of the app_t structure</param>
/// <param name="argc">Number of command line arguments</param>
/// <param name="argv">Command line arguments</param>
/// <param name="id"></param>
/// <param name="wait">Wait milliseconds</param>
void app_cmd_loop(app_t *this, int argc, LPTSTR argv[], LPCTSTR id, DWORD wait);

/// <summary>
/// Destructor
/// </summary>
/// <param name="this">Pointer of the app_t structure</param>
void app_dtor(app_t *this);
