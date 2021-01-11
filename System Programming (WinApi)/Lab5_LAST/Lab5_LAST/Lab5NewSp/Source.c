#include <Windows.h>
#include <stdio.h>

typedef BOOLEAN (__stdcall *GetAuthor)(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
typedef BOOLEAN(__stdcall *GetDescription)(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
typedef VOID(__stdcall *Execute)();

int main()
{
	BOOLEAN exit = TRUE, load = FALSE;

	CHAR name[50], info[100];

	DWORD size = 50, sizeI = 100;
	DWORD end = 0, endI = 0;

	int choosenMove;

	HMODULE first = NULL;
	HMODULE second = NULL;

	GetAuthor getAuthorFirst = NULL, getAuthorSecond = NULL;

	GetDescription getDescritpionFirst = NULL, getDescritpionSecond = NULL;

	Execute showProcesses = NULL, show = NULL;

	puts("Hello, my Creator!\n");
	while (exit)
	{
		choosenMove = 0;
		puts("Choose Functions:\n 1. Load Plugins\n 2. Free Plugins\n 3. Show Plugin's function's names\n 4. See Info about each Plugin\n 5. Execute Functions\n 0. Exit\n");
		scanf_s("%i", &choosenMove);

		switch (choosenMove)
		{
		case 1:
			if (load)
			{
				puts("Creator, the libraries are connected!\n");
			}
			else
			{
				first = LoadLibrary("plugins\\SYSTEM.dll");
				second = LoadLibrary("plugins\\RAMMSTEIN.dll");
				getAuthorFirst = (GetAuthor)GetProcAddress(first, "_GetAuthor@12");
				getAuthorSecond = (GetAuthor)GetProcAddress(second, "_GetAuthor@12");
				getDescritpionFirst = (GetDescription)GetProcAddress(first, "_GetDescription@12");
				getDescritpionSecond = (GetDescription)GetProcAddress(second, "_GetDescription@12");
				showProcesses = (Execute)GetProcAddress(first, "_ShowProcesses@0");
				show = (Execute)GetProcAddress(second, "_Show@0");
				load = TRUE;
			}
			break;

		case 2:
			if (load)
			{
				FreeLibrary(first);
				FreeLibrary(second);
				load = FALSE;

			}
			else
			{
				puts("You should press 1 before pressing 2 ¯\_('-')_/¯\n");
			}
			break;
		case 3:
			if (load)
			{
				puts("1st Plugin is \"System\"\n2nd Plugin is \"Rammstein\"\n");
			}
			else
			{
				puts("Libraries have unloaded!\n");
			}
			break;
		case 4:
			if (load)
			{
				getAuthorFirst(name, size, &end);
				getDescritpionFirst(info, sizeI, &endI);
				printf("Info about first plugin:\nAuthor Name: %s\nPlugin Info: %s", name, info);
				getAuthorSecond(name, size, &end);
				getDescritpionSecond(info, sizeI, &endI);
				printf("Info about second plugin:\nAuthor Name: %s\nPlugin Info: %s", name, info);
			}
			else
			{
				puts("Libraries have unloaded!\n");
			}
			break;
		case 5:
			if (load)
			{
				system("chcp 1251");
				puts("First plugin Function:\n");
				showProcesses();
				puts("Second plugin Function:\n");
				show();
			}
			else
			{
				puts("Libraries have unloaded!\n");
			}
			break;

		case 0:
		{
			exit = FALSE;
		}
			break;
		default:
		{
			puts("Wrong answer!");
			rewind(stdin);
		}
			break;
		}
	}
	system("pause");
	return 0;
}

//Неявное связывание, или связывание во время загрузки(load - time linking) является простейшей из двух методик связывания.
//Порядок действий в случае использования Microsoft C++ следующий:

//1. После того как собраны все необходимые для новой DLL функции, осуществляется сборка DLL, а не, например, консольного приложения.

//2. В процессе сборки создается библиотечный.
//LIB - файл, играющий роль заглушки(stub) для фактического кода.Этот файл должен помещаться в каталог библиотек общего пользования, указанный в проекте.


//Явное связывание

//Явное связывание, или связывание во время выполнения(run - time linking), требует, чтобы в программе содержались конкретные указания относительно того, когда именно необходимо загрузить или освободить библиотеку DLL.Далее программа получает адрес запрошенной точки входа и использует этот адрес в качестве указателя при вызове функции.В вызывающей программе функция не объявляется; вместо этого в качестве указателя на функцию объявляется переменная.Поэтому во время компоновки программы присутствие библиотеки не является обязательным.Для выполнения необходимых операций требуются три функции : LoadLibrary(или LoadLibraryEx), GetProcAddress и FreeLibrary.На 16 - битовое происхождение определений функций указывает присутствие в них дальних(far) указателей и дескрипторов различных типов.

//Для загрузки библиотеки служат две функции : LoadLibrary и LoadLibraryEx.


//Подключаем явным связыванием dll через loadlibrary и потом получаем указатели на функцию через GetProcAddress.






//Статическая библиотека(или ещё «архив») состоит из подпрограмм, которые непосредственно компилируются и линкуются с вашей программой.
//При компиляции программы, которая использует статическую библиотеку, весь функционал статической библиотеки(тот, что использует ваша программа) 
//становится частью вашего исполняемого файла.В Windows статические библиотеки имеют расширение.lib(от «library»), 
//тогда как в Linux статически библиотеки имеют расширение.a(от «archive»).

//Одним из преимуществ статических библиотек является то, что вам нужно распространять всего лишь 1 файл(исполняемый файл), 
//дабы пользователи могли запустить и использовать вашу программу.Поскольку статические библиотеки становятся частью вашей программы, 
//то вы можете использовать их подобно функционалу своей собственной программы.С другой стороны, поскольку копия библиотеки становится 
//частью каждого вашего исполняемого файла, то это может привести к увеличению размера файла.
//Также, если вам нужно будет обновить статическую библиотеку, вам придётся перекомпилировать каждый исполняемый файл, который её использует.





//зачем нужны lib файлы у DLL
//Особенность некоторых линкеров(например, майкрософтовского).
//Они не умеют то ли оставлять имена функций в библиотеке, то ли извлекать их оттуда, поэтому вместе с библиотекой таскают еще и библиотеку импорта.


//__declspec (dllexport) сообщает компоновщику, что вы хотите, чтобы этот объект был доступен для импорта другими DLL.Он используется при создании DLL,
//на которую могут ссылаться другие.

//__declspec (dllimport) импортирует реализацию из DLL, чтобы ваше приложение могло ее использовать.