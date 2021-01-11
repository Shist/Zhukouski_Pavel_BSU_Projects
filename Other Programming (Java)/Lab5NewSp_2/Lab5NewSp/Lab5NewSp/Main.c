#include <Windows.h>
#include <stdio.h>

typedef BOOLEAN (__stdcall *GetAuthor)(LPSTR buffer,
	DWORD dwBufferSize, DWORD* pdwBytesWritten);
typedef BOOLEAN(__stdcall *GetDescription)(LPSTR buffer,
	DWORD dwBufferSize, DWORD* pdwBytesWritten);
typedef VOID(__stdcall *Execute)();

int main()
{
	BOOLEAN check = TRUE;
	BOOLEAN get = FALSE;
	CHAR name[50];
	CHAR info[100];
	DWORD size = 50;
	CHAR sizeI = 100;
	DWORD end = 0;
	DWORD endI = 0;
	HMODULE first = NULL;
	HMODULE second = NULL;
	GetAuthor getAuthorFirst = NULL;
	GetAuthor getAuthorSecond = NULL;
	GetDescription getDescritpionFirst = NULL;
	GetDescription getDescritpionSecond = NULL;
	Execute showProcesses = NULL;
	Execute showInfo = NULL;

	while (check)
	{
		int step = 0;
		puts("\nMenu:\n\
			Push 1 - upload plugins\n\
			Push 2 - clear plugins\n\
			Push 3 - list of plugins\n\
			Push 4 - show information about plugins\n\
			Push 5 - plugin action\n\
			Push 0 - exit\n");

		scanf_s("%i", &step);

		switch (step)
		{
		case 0:
			check = FALSE;
			break;
		case 1:
			if (get)
				puts("\nPlugins loaded!\n");
			else
			{
				first = LoadLibrary("plugins\\POBEDA.dll");
				second = LoadLibrary("plugins\\ZIMNYAYADOROGA.dll");
				getAuthorFirst = (GetAuthor)GetProcAddress(first, "GetAuthor");
				getAuthorSecond = (GetAuthor)GetProcAddress(second, "GetAuthor");
				getDescritpionFirst = (GetDescription)GetProcAddress(first, "GetDescription");
				getDescritpionSecond = (GetDescription)GetProcAddress(second, "GetDescription");
				showProcesses = (Execute)GetProcAddress(first, "ShowProcesses");
				showInfo = (Execute)GetProcAddress(second, "ShowInfo");
				get = TRUE;
			}
			break;
		case 2:
			if (get)
			{
				FreeLibrary(first);
				FreeLibrary(second);
				get = FALSE;

			}
			else
				puts("\nError! No plugins.\n");
			break;
		case 3:
			if (get)
				puts(" 1. Firstplugin\n 2. Secondplugin");
			else
				puts("\nError! No plugins.\n");
			break;
		case 4:
			if (get)
			{
				getAuthorFirst(name, size, &end);
				getDescritpionFirst(info, sizeI, &endI);
				puts("\nInfo about Firstplugin: ");
				printf("\n\tAuthor Name: %s\tPlugin Info: %s", name, info);
				getAuthorSecond(name, size, &end);
				getDescritpionSecond(info, sizeI, &endI);
				puts("\nInfo about Secondplugin: ");
				printf("\n\tAuthor Name: %s\tPlugin Info: %s", name, info);
			}
			else
				puts("\nError! No plugins.\n");
			break;
		case 5:
			if (get)
			{
				system("chcp 1251");
				puts("Firstplugin function:\n");
				showProcesses();
				puts("Secondplugin function:\n");
				showInfo();
			}
			else
			{
				puts("\nError! No plugins.\n");
			}
			break;
		default:
			puts("Wrong answer!");
			rewind(stdin);
			break;
		}
	}
	system("pause");
	return 0;
}