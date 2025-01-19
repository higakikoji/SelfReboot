#pragma once

typedef struct shell_t shell_t;

shell_t *shell_ctor(void);
BOOL shell_execute(shell_t *this, HWND h, LPCTSTR file, LPCTSTR parameters, LPCTSTR directory);
void shell_dtor(shell_t *this);
