#include <windows.h>
#include <tchar.h>
#include "err.h"

struct err_t {
  /// <summary>
  /// Error string buffer
  /// </summary>
  LPTSTR buffer;
};

err_t *err_ctor(void) {
  // Allocate object
  err_t *_this = malloc(sizeof(err_t));
  if (_this == NULL) {
    _tprintf_s(TEXT("[%s] ERROR: malloc is NULL\n"), TEXT(__FUNCTION__));
    return _this;
  }

  // Initialize members
  _this->buffer = NULL;

  // Return object
  return _this;
}

DWORD err_get(err_t *this) {
  // Return error code
  return GetLastError();
}

LPTSTR err_get_string(err_t *this) {
  // Allocate buffer
  if (this->buffer == NULL) {
    this->buffer = malloc(MAX_PATH);
    if (this->buffer == NULL) {
      _tprintf_s(TEXT("[%s] ERROR: malloc is NULL\n"), TEXT(__FUNCTION__));
      return this->buffer;
    }
  }

  // Get error string
  DWORD ret = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), this->buffer, MAX_PATH / sizeof(TCHAR), NULL);
  if (ret == 0) {
    _tprintf_s(TEXT("[%s] ERROR: FormatMessage=%lu\n"), TEXT(__FUNCTION__), ret);
    return NULL;
  }

  // Return error string
  return this->buffer;
}

void err_dtor(err_t *this) {
  if (this == NULL) {
    return;
  }

  // Release buffer
  if (this->buffer != NULL) {
    free(this->buffer);
  }

  // Release object
  free(this);

  return;
}
