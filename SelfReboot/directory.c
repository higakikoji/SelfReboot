#include <windows.h>
#include <tchar.h>
#include "err.h"
#include "directory.h"

struct directory_t {
  /// <summary>
  /// err object
  /// </summary>
  err_t *err;

  /// <summary>
  /// Allocation size for each pathes
  /// </summary>
  DWORD allocation_size;

  /// <summary>
  /// Current directory path
  /// </summary>
  LPTSTR current_path;
};

directory_t *directory_ctor(DWORD allocation_size) {
  // Allocate object
  directory_t *_this = malloc(sizeof(directory_t));
  if (_this == NULL) {
    _tprintf_s(TEXT("[%s] ERROR: malloc is NULL\n"), TEXT(__FUNCTION__));
    return _this;
  }

  // Allocate err object
  _this->err = err_ctor();
  if (_this->err == NULL) {
    _tprintf_s(TEXT("[%s] ERROR: err_ctor is NULL\n"), TEXT(__FUNCTION__));
    free(_this);
    _this = NULL;
    return _this;
  }

  // Initialize members
  _this->allocation_size = allocation_size;
  _this->current_path = NULL;

  // Return object
  return _this;
}

LPTSTR directory_get_current(directory_t *this) {
  // Allocate current path
  if (this->current_path == NULL) {
    this->current_path = malloc(this->allocation_size);
    if (this->current_path == NULL) {
      _tprintf_s(TEXT("[%s] ERROR: malloc is NULL\n"), TEXT(__FUNCTION__));
      return this->current_path;
    }
  }

  // Get current directory
  if (GetCurrentDirectory(this->allocation_size / sizeof(TCHAR), this->current_path) == 0) {
    _tprintf_s(TEXT("[%s] ERROR: GetCurrentDirectory=%lu (%s)\n"), TEXT(__FUNCTION__), err_get(this->err), err_get_string(this->err));
    return NULL;
  }

  // Return current directory
  return this->current_path;
}

void directory_dtor(directory_t *this) {
  if (this == NULL) {
    return;
  }

  // Release err object
  if (this->err != NULL) {
    err_dtor(this->err);
  }

  // Release current path
  if (this->current_path != NULL) {
    free(this->current_path);
  }

  // Release object
  free(this);

  return;
}
