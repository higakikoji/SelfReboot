#include <windows.h>
#include <tchar.h>
#include "app.h"

#if defined(_CONSOLE)
int _tmain(int argc, LPTSTR argv[], LPTSTR envp[]) {
#else
int _tWinMain(HINSTANCE inst, HINSTANCE prev_inst, LPTSTR cmd_line, int cmd_show) {
#endif
  // Allocate app object
  app_t *app = app_ctor();
  if (app == NULL) {
    return -1;
  }

  // 
  app_cmd_loop(app, argc, argv, TEXT("application"), 5000);

  // Release app object
  app_dtor(app);

  return 0;
}
