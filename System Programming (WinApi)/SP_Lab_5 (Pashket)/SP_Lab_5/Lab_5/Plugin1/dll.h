#include <windows.h>
#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllexport) BOOLEAN GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
	__declspec(dllexport) BOOLEAN GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
	__declspec(dllexport) VOID Execute();
	
#ifdef __cplusplus
};
#endif