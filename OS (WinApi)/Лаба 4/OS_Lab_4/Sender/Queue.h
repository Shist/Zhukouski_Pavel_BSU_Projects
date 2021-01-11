#pragma once

// Элемент очереди
struct QueueNode
{
	char* msg = new char[20];				// Сообщение
	QueueNode* next_node = nullptr;			// Указатель на следующий элемент
};

// Очередь
struct Queue
{
	QueueNode* first = new QueueNode;		// Указатель на первый элемент
	QueueNode* last = first;				// Указатель на последний элемент
	int size = 0;							// Размер очереди
};

// Добавить в очередь Q сообщение
void AddToQueue(Queue* Q, char* new_msg)
{
	Q->last->next_node = new QueueNode;		// Создаём новый элемент и даём на него ссылку в текущий последний элемент
	for (int i = 0; i < 20; i++)
		Q->last->msg[i] = new_msg[i];		// Вписываем значение этого элемента
	Q->last = Q->last->next_node;			// Говорим, что теперь самым последним элементом стал только что созданный элемент
	Q->size++;								// Увеличиваем размер очереди на единицу
}

// Удалить первый элемент очереди
void DeleteFromQueue(Queue* Q)
{
	QueueNode* link_to_next = Q->first->next_node;	// Запоминаем ссылку на следующий элемент очереди
	delete Q->first;								// Очищаем память от элемента очереди
	Q->first = link_to_next;						// Говорим, что теперь самым первым элементом стал следующий после первого
	Q->size--;										// Уменьшаем размер очереди на единицу
}

// Проверка очереди на пустоту
bool QueueIsEmpty(Queue* Q)
{
	return !(Q->size);						// Если size != 0, то очередь НЕ пуста
}