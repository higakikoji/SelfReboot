#include <windows.h>
#include <tchar.h>
#include "self.h"
#include "app.h"

/* http://www.sutosoft.com/room/archives/000012.html */

#define APP_VALID_ARG_NUM (3)

struct app_t {
  /// <summary>
  /// self object
  /// </summary>
  self_t *self;
};

app_t *app_ctor(void) {
  // Allocate object
  app_t *_this = malloc(sizeof(app_t));
  if (_this == NULL) {
    _tprintf_s(TEXT("[%s] ERROR: malloc is NULL\n"), TEXT(__FUNCTION__));
    return _this;
  }

  // Allocate self object
  _this->self = self_ctor(MAX_PATH);
  if (_this->self == NULL) {
    _tprintf_s(TEXT("[%s] ERROR: self_ctor is NULL\n"), TEXT(__FUNCTION__));
    free(_this);
    _this = NULL;
  }

  // Return object
  return _this;
}

void app_cmd_loop(app_t *this, int argc, LPTSTR argv[], LPCTSTR id, DWORD wait) {
  BOOL _loop = TRUE;

  // Check restart
  if (argc == APP_VALID_ARG_NUM) {
    _loop = self_check_restart(this->self, id, wait, argv[1], _tcstol(argv[2], NULL, 10));
  }

  // Command loop
  while (_loop) {
    // Display command
    _tprintf_s(
      TEXT("----------------------------------------\n")
      TEXT("[1] Restart\n")
      TEXT("[0] Exit\n")
      TEXT("----------------------------------------\n")
      TEXT("Command: "));

    // Input command
    int _cmd;
    _tscanf_s(TEXT("%d"), &_cmd);
    _tprintf_s(TEXT("\n"));

    // Parse command
    if (_cmd == 1) {
      // Restart
      if (self_restart(this->self, id) == TRUE) {
        // Exit
        _loop = FALSE;
      }
    } else if (_cmd == 0) {
      // Exit
      _loop = FALSE;
    }
  }

  return;
}

void app_dtor(app_t *this) {
  if (this == NULL) {
    return;
  }

  // Release self object
  self_dtor(this->self);

  // Release object
  free(this);

  return;
}
