#pragma warning(disable: 4996)
#include "pch.h"
#include <Windows.h>
#include "Header.h"

LPCSTR authorName = "/// Zhukovskiy Pavel | 13 group | 2 course ///";
int authorSize = 46;
int infoSize = 39;
LPCSTR pluginfo = "/// Plugin Info ///\nThis is static library ^-^ \n\n";
LPCSTR info = " \n\
 ______   ______   _________   _________   ______  _______  ______ _____  ______  \n\
| |  | \ | |  | | | | | | | \ | | | | | \ / |        | |   | |      | |  | |  \ \ \n\
| |__| | | |__| | | | | | | | | | | | | | '------.   | |   | |----  | |  | |  | | \n\
|_|  \_\ |_|  |_| |_| |_| |_| |_| |_| |_|  ____|_/   |_|   |_|____ _|_|_ |_|  |_| \n\ ";

BOOLEAN  GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)
{
	if (dwBufferSize < authorSize || pdwBytesWritten == NULL)
	{
		return FALSE;
	}
	strncpy(buffer, authorName, dwBufferSize);
	*pdwBytesWritten = authorSize;
	return TRUE;
}

BOOLEAN  GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)
{
	if (dwBufferSize < infoSize || pdwBytesWritten == NULL)
	{
		return FALSE;
	}
	strncpy(buffer, pluginfo, dwBufferSize);
	*pdwBytesWritten = infoSize;
	return TRUE;
}

VOID  Show()
{
	puts(info);
}