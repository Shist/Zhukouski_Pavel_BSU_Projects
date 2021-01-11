#include "functional.h"

void LoadPlugins()
{
	pluginsCount = 0;
	WIN32_FIND_DATA file;
	HANDLE hFile = FindFirstFile("Plugins\\*.dll", &file);
	if (hFile == INVALID_HANDLE_VALUE) {
		return;
	}
	do
	{
		if (pluginsCount == MAXPLUGINSALLOWED) {
			break;
		}
		char buf[256] = "Plugins\\";
		strcat_s(buf, 256, file.cFileName);
		Plugins[pluginsCount] = LoadLibrary(buf); // Явное подключение DLL
		++pluginsCount;
	} while (FindNextFile(hFile, &file));
	FindClose(hFile);
	printf("%d %s\n\n", pluginsCount, "plugin(s) was/were loaded.");
}

void UnloadPlugins() {
	if (pluginsCount == 0) {
		printf("%s\n\n", "There're no loaded plugins");
		return;
	}
	do {
		FreeLibrary(Plugins[pluginsCount - 1]); // Отключение DLL
		Plugins[pluginsCount - 1] = NULL;
		--pluginsCount;
	} while (pluginsCount != 0);
	printf("%s\n\n", "All plugins were unloaded.");
}

void ShowInfo() {
	if (pluginsCount == 0) {
		printf("%s\n\n", "There're no loaded plugins");
		return;
	}
	DWORD bufdword = 0;
	char buffer[512];
	PluginInfo PI;
	for (int i = 0; i < pluginsCount; ++i) {
		PI = (PluginInfo)GetProcAddress(Plugins[i], "GetDescription");
		PI(buffer, 512, &bufdword);
		printf("Plugin #%d description: %s\n", i + 1, buffer);
		PI = (PluginInfo)GetProcAddress(Plugins[i], "GetAuthor");
		PI(buffer, 512, &bufdword);
		printf("Author: %s\n\n", buffer);
	}
}

void RunPlugins() {
	if (pluginsCount == 0) {
		printf("%s\n\n", "There're no loaded plugins");
		return;
	}
	PluginExecute PE;
	for (int i = 0; i < pluginsCount; ++i) {
		PE = (PluginExecute)GetProcAddress(Plugins[i], "Execute");
		PE();
	}
}


void Exit() {
	if (pluginsCount != 0) {
		do {
			FreeLibrary(Plugins[pluginsCount - 1]); // Отключение DLL
			Plugins[pluginsCount - 1] = NULL;
			--pluginsCount;
		} while (pluginsCount != 0);
		printf("%s\n\n", "All plugins were unloaded.");
	}
	printf("%s", "Program finished...");
}