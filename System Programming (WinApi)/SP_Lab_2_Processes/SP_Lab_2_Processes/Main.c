#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <tchar.h>

// BOOL - аналог bool (NULL или 1)
// DWORD - 32-битное беззнаковое целое. Аналоги: unsigned long int, UINT.
BOOL GetProcessList();
BOOL ListProcessModules(DWORD dwPID);
BOOL ListProcessThreads(DWORD dwOwnerPID);

int main()
{
	GetProcessList(); // Просто вызываем основной метод (он потом, если надо, повызывает все остальные методы)
	return 0;
}

BOOL GetProcessList()
{ // Метод "получить список процессов"
	HANDLE hProcessSnap; // HANDLE - Дескриптор объекта
	HANDLE hProcess;
	PROCESSENTRY32 pe32; // Вход в список процессов
	// PROCESSENTRY32 - Описывает запись из списка процессов, находящихся в системном адресном пространстве, по снапшоту. (это целая структура)
	DWORD dwPriorityClass;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// Cоздает снапшот запущенных процессов, модулей и т.д.
	// Аргумент dwFlags определяет, снапшот чего именно мы хотим получить. (задаем 0x00000002)
	// Параметр dwProcessId задает идентификатор процесса, для которого создается снапшот. (задаем 0)
	// Возвращает хэндл снапшота

	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return(FALSE); // Если с дескриптором произошло что-то не так, то возвращаем 0 в методе

	pe32.dwSize = sizeof(PROCESSENTRY32); // sizeof возвращает количество памяти, которую занимает processentry32
	// dwSize - это одно из полей структуры типа PROCESSENTRY23

	if (!Process32First(hProcessSnap, &pe32))
	{ // Process32First - Получает информацию о первом процессе, обнаруженном в системном снимке.
		CloseHandle(hProcessSnap); // Если ничего не нашли, закрываем текущий декскриптом и...
		return(FALSE); // Возвращаем 0 в методе
	}
	// Process32First принимает хэндл, полученный от CreateToolhelp32Snapshot, 
	// Вызванной с dwFlags = TH32CS_SNAPPROCESS, а также указатель на структуру PROCESSENTRY32. 
	// Перед вызовом процедуры поле dwSize этой структуры должно быть установлено в sizeof(PROCESSENTRY32). 
	// В случае успеха возвращается TRUE, а в peProcessEntry записывается информация о первом процессе

	do
	{
		_tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile); // Печатаем имя объекта (имя берем из одного из полей структуры pe32)

		dwPriorityClass = 0;
		// OpenProcess(...) - Открывает существующий объект локального процесса.
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID); // Создаем процесс

		if (hProcess == INVALID_HANDLE_VALUE)
			return(FALSE); // Если что-то пошло не так, возвращаем 0

		dwPriorityClass = GetPriorityClass(hProcess);
		// GetPriorityClass извлекает значение класса приоритета для заданного процесса hProcess.
		// Это значение, вместе со значением приоритета каждого потока процесса, обуславливает основной уровень приоритета каждого потока.
		CloseHandle(hProcess);
		// Далее печатаем информацию о процессе
		_tprintf(TEXT("\n  Process ID        = %d"), pe32.th32ProcessID); // ID процесса
		_tprintf(TEXT("\n  Thread count      = %d"), pe32.cntThreads); // Кол-во тредов в нём
		_tprintf(TEXT("\n  Parent process ID = %d"), pe32.th32ParentProcessID); // ID процесса, который создал этот процесс (родительский процесс)
		_tprintf(TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase); // Базовый приоритет любых потоков, созданных этим процессом

		ListProcessModules(pe32.th32ProcessID); // Перечисляем все модули данного процесса (если есть)
		ListProcessThreads(pe32.th32ProcessID); // Перечисляем все треды данного процесса (если есть)

	} while (Process32Next(hProcessSnap, &pe32)); // То же самое, что и Process32First, только для следующих
	CloseHandle(hProcessSnap); // Закрываем
	return(TRUE);
}

BOOL ListProcessModules(DWORD dwPID) // Передаем ID текущего процесса
{ // Модули - exe-шники, dll-ки, и т.д. (скомпилированный код)
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32; // MODULEENTRY32 - Структура, служащая для перечисления модулей в заданном процессе

	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	// CreateToolhelp32Snapshot - Делает снимок указанных процессов, а также куч, модулей и потоков, используемых этими процессами.
	if (hModuleSnap == INVALID_HANDLE_VALUE)
		return(FALSE); // Если что-то пошло не так, возвращаем 0

	me32.dwSize = sizeof(MODULEENTRY32); // Задаем полю dwSuze размер структуры tagMODULEENTRY32W

	if (!Module32First(hModuleSnap, &me32))
	{ // Module32First - то же самое, что Process32First, только с модулями, а не процессами
		CloseHandle(hModuleSnap);
		return(FALSE);
	}
	do
	{ // Печатаем информацию о модуле...
		_tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule); // Имя модуля
		_tprintf(TEXT("\n     Path     = %s"), me32.szExePath); // Путь к модулю
		_tprintf(TEXT("\n     Process ID     = 0x%08X"), me32.th32ProcessID); // ID Процесса, в котором этот модуль располагается
		_tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize); // Размер модуля (в байтах)

	} while (Module32Next(hModuleSnap, &me32)); // То же самое, что и Module32First, только для следующих
	CloseHandle(hModuleSnap); // Закрываем
	return(TRUE);
}

BOOL ListProcessThreads(DWORD dwOwnerPID) // Передаем ID текущего процесса
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32; // THREADENTRY32 - Структура, служащая для перечисления тредов в заданном процессе

	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	// CreateToolhelp32Snapshot - Делает снимок указанных процессов, а также куч, модулей и потоков, используемых этими процессами.
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return(FALSE); // Если что-то пошло не так, возвращаем 0

	te32.dwSize = sizeof(THREADENTRY32); // Задаем полю dwSuze размер структуры tagTHREADENTRY32

	if (!Thread32First(hThreadSnap, &te32))
	{// Thread32First - то же самое, что Module32First, только с стредами
		CloseHandle(hThreadSnap);
		return(FALSE);
	}
	do
	{
		if (te32.th32OwnerProcessID == dwOwnerPID)
		{ // Если ID-шник треда совпадает с ID-шником хозяина, то печатаем информацию о нём
			_tprintf(TEXT("\n\n     THREAD ID      = 0x%08X"), te32.th32ThreadID); // ID-шник треда
			_tprintf(TEXT("\n     Base priority  = %d"), te32.tpBasePri); // Базовый уровень приоритета ядра, назначенный потоку.
			// Приоритет - это число от 0 до 31, где 0 представляет наименьший возможный приоритет потока.
			_tprintf(TEXT("\n     Delta priority = %d"), te32.tpDeltaPri); // Этот элемент больше не используется и всегда устанавливается в ноль.
			_tprintf(TEXT("\n"));
		}
	} while (Thread32Next(hThreadSnap, &te32)); // То же самое, что и Thread32First, только для следующих
	CloseHandle(hThreadSnap); // Закрываем
	return(TRUE);
}