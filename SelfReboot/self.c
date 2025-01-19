#include <windows.h>
#include <tchar.h>
#include "err.h"
#include "directory.h"
#include "shell.h"
#include "self.h"

struct self_t {
  /// <summary>
  /// err object
  /// </summary>
  err_t *err;

  /// <summary>
  /// shell object
  /// </summary>
  shell_t *shell;

  /// <summary>
  /// Allocation size for each pathes
  /// </summary>
  DWORD allocation_size;

  /// <summary>
  /// Pointer of the module file path
  /// </summary>
  LPTSTR path;

  /// <summary>
  /// Pointer of the module file name
  /// </summary>
  LPTSTR name;

  /// <summary>
  /// Internal pointer of the module file path
  /// </summary>
  LPTSTR _path;

  /// <summary>
  /// Internal pointer of the command line string
  /// </summary>
  LPTSTR _cmdline;
};

self_t *self_ctor(DWORD allocation_size) {
  // Allocate object
  self_t *_this = malloc(sizeof(self_t));
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

  // Allocate shell object
  _this->shell = shell_ctor();
  if (_this->shell == NULL) {
    _tprintf_s(TEXT("[%s] ERROR: shell_ctor is NULL\n"), TEXT(__FUNCTION__));
    err_dtor(_this->err);
    free(_this);
    _this = NULL;
    return _this;
  }

  // Initialize members
  _this->allocation_size = allocation_size;
  _this->path = NULL;
  _this->name = NULL;
  _this->_path = NULL;
  _this->_cmdline = NULL;

  // Return object
  return _this;
}

LPTSTR self_get_path(self_t *this) {
  // Allocate path
  if (this->path == NULL) {
    this->path = malloc(this->allocation_size);
    if (this->path == NULL) {
      _tprintf_s(TEXT("[%s] ERROR: malloc is NULL\n"), TEXT(__FUNCTION__));
      return this->path;
    }
  }

  // Get module file path
  if (GetModuleFileName(NULL, this->path, this->allocation_size / sizeof(TCHAR)) == 0) {
    _tprintf_s(TEXT("[%s] ERROR: GetModuleFileName=%lu (%s)\n"), TEXT(__FUNCTION__), err_get(this->err), err_get_string(this->err));
    return NULL;
  }
  if (err_get(this->err) == ERROR_INSUFFICIENT_BUFFER) {
    _tprintf_s(TEXT("[%s] ERROR: GetModuleFileName=%lu (%s)\n"), TEXT(__FUNCTION__), err_get(this->err), err_get_string(this->err));
    return NULL;
  }

  // Return path
  return this->path;
}

LPTSTR self_get_name(self_t *this) {
  // Allocate path
  if (this->name == NULL) {
    this->name = malloc(this->allocation_size);
    if (this->name == NULL) {
      _tprintf_s(TEXT("[%s] ERROR: malloc is NULL\n"), TEXT(__FUNCTION__));
      return this->name;
    }
  }

  // Get module file path
  if (GetModuleFileName(NULL, this->name, this->allocation_size / sizeof(TCHAR)) == 0) {
    _tprintf_s(TEXT("[%s] ERROR: GetModuleFileName=%lu (%s)\n"), TEXT(__FUNCTION__), err_get(this->err), err_get_string(this->err));
    return NULL;
  }
  if (err_get(this->err) == ERROR_INSUFFICIENT_BUFFER) {
    _tprintf_s(TEXT("[%s] ERROR: GetModuleFileName=%lu (%s)\n"), TEXT(__FUNCTION__), err_get(this->err), err_get_string(this->err));
    return NULL;
  }

  // Return name
  return this->name;
}

LPTSTR self_get_name_without_extension(self_t *this) {

}

LPTSTR self_get_directory_path(self_t *this) {

}

LPTSTR self_get_directory_name(self_t *this) {

}

BOOL self_restart(self_t *this, LPCTSTR id) {
  // Get module file path
  if (this->_path == NULL) {
    this->_path = malloc(this->allocation_size);
    if (this->_path == NULL) {
      _tprintf_s(TEXT("[%s] ERROR: malloc is NULL\n"), TEXT(__FUNCTION__));
      return FALSE;
    }
  }
  if (GetModuleFileName(NULL, this->_path, this->allocation_size / sizeof(TCHAR)) == 0) {
    _tprintf_s(TEXT("[%s] ERROR: GetModuleFileName=%lu (%s)\n"), TEXT(__FUNCTION__), err_get(this->err), err_get_string(this->err));
    return FALSE;
  }
  if (err_get(this->err) == ERROR_INSUFFICIENT_BUFFER) {
    _tprintf_s(TEXT("[%s] ERROR: GetModuleFileName=%lu (%s)\n"), TEXT(__FUNCTION__), err_get(this->err), err_get_string(this->err));
    return FALSE;
  }
  _tprintf_s(TEXT("[%s] DEBUG: path=%s\n"), TEXT(__FUNCTION__), this->_path);

  // Execute
  if (this->_cmdline == NULL) {
    this->_cmdline = malloc(this->allocation_size);
    if (this->_cmdline == NULL) {
      _tprintf_s(TEXT("[%s] ERROR: malloc is NULL\n"), TEXT(__FUNCTION__));
      return FALSE;
    }
  }
  if (_stprintf_s(this->_cmdline, this->allocation_size / sizeof(TCHAR), TEXT("%s %u"), id, GetCurrentProcessId()) == -1) {
    _tprintf_s(TEXT("[%s] ERROR: _stprintf_s=%lu (%s)\n"), TEXT(__FUNCTION__), err_get(this->err), err_get_string(this->err));
    return FALSE;
  }
  if (shell_execute(this->shell, NULL, this->_path, this->_cmdline, NULL) == FALSE) {
    return FALSE;
  }
  _tprintf_s(TEXT("[%s] DEBUG: %s %s\n"), TEXT(__FUNCTION__), this->_path, this->_cmdline);

  return TRUE;
}

BOOL self_check_restart(self_t *this, LPCTSTR id, DWORD wait, LPCTSTR restarted_id, DWORD restarted_pid) {
  BOOL ret = TRUE;

  // Check application id
  if (_tcscmp(id, restarted_id) != 0) {
    _tprintf_s(TEXT("[%s] DEBUG: id=%s, restarted_id=%s\n"), TEXT(__FUNCTION__), id, restarted_id);
    return ret;
  }

  // Wait foor exiting application
  HANDLE h = OpenProcess(SYNCHRONIZE, FALSE, restarted_pid);
  if (h == NULL) {
    _tprintf_s(TEXT("[%s] DEBUG: already exited\n"), TEXT(__FUNCTION__));
    return ret;
  }
  if (WaitForSingleObject(h, wait) == WAIT_TIMEOUT) {
    _tprintf_s(TEXT("[%s] ERROR: timeout\n"), TEXT(__FUNCTION__));
    ret = FALSE;
  }

  // Return result
  return ret;
}

void self_dtor(self_t *this) {
  if (this == NULL) {
    return;
  }

  // Release err object
  if (this->err != NULL) {
    err_dtor(this->err);
  }

  // Release shell object
  if (this->shell != NULL) {
    shell_dtor(this->shell);
  }

  // Release path
  if (this->path != NULL) {
    free(this->path);
  }

  // Release name
  if (this->name != NULL) {
    free(this->name);
  }

  // Release internal path
  if (this->_path != NULL) {
    free(this->_path);
  }

  // Release internal command line string
  if (this->_cmdline != NULL) {
    free(this->_cmdline);
  }

  // Release object
  free(this);

  return;
}
