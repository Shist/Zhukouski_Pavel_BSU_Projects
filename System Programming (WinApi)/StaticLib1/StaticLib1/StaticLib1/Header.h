#pragma once
#include <Windows.h>

BOOLEAN  GetAuthor(LPSTR buffer,
	DWORD dwBufferSize, DWORD* pdwBytesWritten);

BOOLEAN  GetDescription(LPSTR buffer,
	DWORD dwBufferSize, DWORD* pdwBytesWritten);

VOID Show();