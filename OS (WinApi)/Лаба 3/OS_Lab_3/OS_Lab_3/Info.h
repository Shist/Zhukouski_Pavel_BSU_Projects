// ��������� �������
struct Info
{
	int arr_size = 0;					// ������� ������� (�� ��������� 0)
	int* arr = nullptr;					// ��������� �� ������ ������� arr
	bool* marked_elements = nullptr;	// � ���� ������� �������� ��������, ���������� ����������� ������ marker
	int thread_num = 0;					// ���������� ����� ���������� ������ marker (�� ��������� 0)
};