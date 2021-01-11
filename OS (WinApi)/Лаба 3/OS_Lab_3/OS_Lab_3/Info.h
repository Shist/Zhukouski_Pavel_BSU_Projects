// Параметры потоков
struct Info
{
	int arr_size = 0;					// Размера массива (по умолчанию 0)
	int* arr = nullptr;					// Указатель на начало массива arr
	bool* marked_elements = nullptr;	// В этом массиве хранятся элементы, помеченные экземпляром потока marker
	int thread_num = 0;					// Порядковый номер экземпляра потока marker (по умолчанию 0)
};