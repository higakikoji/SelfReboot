#include <windows.h>
#include <shellapi.h>
#include "shell.h"

struct shell_t {
  PVOID dummy;
};

shell_t *shell_ctor(void) {
  // Return object
  return malloc(sizeof(shell_t));
}

BOOL shell_execute(shell_t *this, HWND h, LPCTSTR file, LPCTSTR parameters, LPCTSTR directory) {
  ShellExecute(h, NULL, file, parameters, directory, SW_SHOWNORMAL);
  return TRUE;
}

void shell_dtor(shell_t *this) {
  if (this == NULL) {
    return;
  }

  // Release object
  free(this);
}
