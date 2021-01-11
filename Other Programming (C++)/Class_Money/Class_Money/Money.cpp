#include "Money.h"

Money::Money() // ���������� ������������ ��� ����������, ��������� ������� �������� �����
{
	sum = 0;
}

Money::Money(int pd, int sh, double p) // ���������� ������������ � ����� �����������, ��������� 3 ���������� (������)
{
	if (pd > 1000000000 || (pd == 1000000000 && (sh > 0 || p > 0))) throw exception("Error! Too big value of sum!"); // �������� �� ������������ �����
	if (pd < 0) throw exception("Error! Entered value of pounds is negative!"); // �������� �� ��������������� ������
	if (sh > 19) throw exception("Error! Your value of shillings isn't smaller than 20!"); // �������� �� ������������ ���������
	if (sh < 0) throw exception("Error! Entered value of shillings is negative!"); // �������� �� ��������������� ���������
	if (p > 11.5) throw exception("Error! Your value of pences isn't smaller than 12!"); // �������� �� ������������ ������
	if (p < 0) throw exception("Error! Entered value of pences if negatice!"); // �������� �� ��������������� ������
	check = true; // ���� �� ���� � set-����� �� ������������, �� ������ ���� �� true
	set_sum(pd, sh, p, 0);
}

Money::~Money() // ����������� ����������
{
}

long long Money::get_sum() const // ���������� get-������ ��� �����
{
	return sum;
}

void Money::set_sum(int pd, int sh, double p, long long new_sum) // ���������� set-������ ��� �����
{
	if (check) // ���� �� ������ �� ������������, ��...
	{
		check = false;
		sum = (long long)(2 * p) + 24 * ((long long)sh + 20 * ((long long)pd)); // ����������� sum, � ������� ����� �������� �� ����� ��������
	}
	else // ���� �� �� ������ ���� �� ��������� ������ ��������������� ��������, ��...
	{
		sum = new_sum;
	}
	if (sum > 480000000000) throw exception("Error! Too big value of sum!"); // �������� �� ������������ �����
	if (sum < -480000000000) throw exception("Error! Too small value of sum!"); // �������� �� ����������� �����
}

Money Money::operator + (const Money& x) const
{
	Money X;
	X.set_sum(0, 0, 0, get_sum() + x.get_sum());
	return X; // ��������
}

Money Money::operator - (const Money& x) const
{
	Money X;
	X.set_sum(0, 0, 0, get_sum() - x.get_sum());
	return X; // ���������
}

Money Money::operator - () const
{
	Money X;
	X.set_sum(0, 0, 0, -get_sum());
	return Money(X); // ������� �����
}

Money Money::operator += (const Money& x) // �������� � �����������
{
	Money money(*this);
	sum += x.get_sum();
	set_sum(0, 0, 0, sum);
	return money;
}

Money Money::operator -= (const Money& x) // ��������� � �����������
{
	Money money(*this);
	sum -= x.get_sum();
	set_sum(0, 0, 0, sum);
	return money;
}

bool Money::operator == (const Money& x) const
{
	if (get_sum() == x.get_sum()) // ��������� (�����)
		return true;
	else
		return false;
}

ostream& operator << (ostream& s, const Money& x)
{
	if (x.sum % 2 == 1 || x.sum % 2 == -1) // ������, ����� � ��� ������� ���������� ������
	{
		if (((x.sum / 2) % 12) == 0) // ���� ���������� ������ ������ ����� ����, ��...
		{
			if ((x.sum / 24) % 20 == 0) // ���� ���������� ��������� ����� ����, ��...
			{
				if (x.sum / 480 == 0) // ���� ��� ���� ��� � ���������� ������ ����� ����, ��...
				{
					if (x.sum < 0) // ��������� ����
					{
						s << "-0,5p."; // ������� 0,5 ����� (1)
					}
					else
					{
						s << "0,5p."; // ������� 0,5 ����� (2)
					}
				}
				else // ���� �� ��� ���� ���������� ������ ���� �� �����, ��...
				{
					if (x.sum < 0) // ��������� ����
					{
						s << "-" << x.sum / 480 * (-1) << "pd.0,5p."; // ������� ����� � 0,5 ����� (3)
					}
					else
					{
						s << x.sum / 480 << "pd.0,5p."; // ������� ����� � 0,5 ����� (4)
					}
				}
			}
			else if (x.sum / 480 == 0) // ���� �� ���������� ������ ����� ����, ��...
			{
				if (x.sum < 0) // ��������� ����
				{
					s << "-" << (x.sum / 24) % 20 * (-1) << "sh.0,5p."; // ������� �������� � 0,5 ����� (5)
				}
				else
				{
					s << (x.sum / 24) % 20 << "sh.0,5p."; // ������� �������� � 0,5 ����� (6)
				}
			}
			else // ����� ��...
			{
				if (x.sum < 0) // ��������� ����
				{
					s << "-" << x.sum / 480 * (-1) << "pd." << (x.sum / 24) % 20 * (-1) << "sh.0,5p."; // ������� �����, �������� � 0,5 ����� (7)
				}
				else
				{
					s << x.sum / 480 << "pd." << (x.sum / 24) % 20 << "sh.0,5p."; // ������� �����, �������� � 0,5 ����� (8)
				}
			}
		}
		else if ((x.sum / 24) % 20 == 0) // ���� �� ���������� ��������� ����� ����, ��...
		{
			if (x.sum / 480 == 0) // ���� ���������� ������ ����� ����, ��...
			{
				if (x.sum < 0) // ��������� ����
				{
					s << "-" << ((x.sum / 2) % 12) * (-1) << ",5p."; // ������� ��� ������ ����� � 0,5 ����� (9)
				}
				else
				{
					s << ((x.sum / 2) % 12) << ",5p."; // ������� ��� ������ ����� � 0,5 ����� (10)
				}
			}
			else // ���� �� ���������� ������ ���� �� �����, ��...
			{
				if (x.sum < 0) // ��������� ����
				{
					s << "-" << x.sum / 480 * (-1) << "pd." << ((x.sum / 2) % 12) * (-1) << ",5p."; // ������� �����, ��� ������ ����� � 0,5 ����� (11)
				}
				else
				{
					s << x.sum / 480 << "pd." << ((x.sum / 2) % 12) << ",5p."; // ������� �����, ��� ������ ����� � 0,5 ����� (12)
				}		
			}
		}
		else if (x.sum / 480 == 0) // ���� �� ���������� ������ ����� ����, ��...
		{
			if (x.sum < 0) // ��������� ����
			{
				s << "-" << (x.sum / 24) % 20 * (-1) << "sh." << ((x.sum / 2) % 12) * (-1) << ",5p."; // ������� ��������, ��� ������ ����� � 0,5 ����� (13)
			}
			else
			{
				s << (x.sum / 24) % 20 << "sh." << ((x.sum / 2) % 12) << ",5p."; // ������� ��������, ��� ������ ����� � 0,5 ����� (14)
			}
		}
		else
		{
			if (x.sum < 0) // ��������� ����
			{
				s << "-" << x.sum / 480 * (-1) << "pd." << (x.sum / 24) % 20 * (-1) << "sh." << ((x.sum / 2) % 12) * (-1) << ",5p."; // ������� ��� (15)
			}
			else
			{
				s << x.sum / 480 << "pd." << (x.sum / 24) % 20 << "sh." << ((x.sum / 2) % 12) << ",5p."; // ������� ��� (16)
			}
		}
	}
	else // ������, ����� � ��� ����� (�� �������) ���������� ������
	{
		if (((x.sum / 2) % 12) == 0) // ���� ���������� ������ ����� ����, ��...
		{
			if ((x.sum / 24) % 20 == 0) // ���� ���������� ��������� ����� ����, ��...
			{
				if (x.sum / 480 == 0) // ���� ��� ���� � ���������� ������ ����� ����, ��...
				{
					s << "0p."; // ������� 0 ������ (17) �������, ��� ����� �������� �� ���� ������ �� �����
				}
				else // ���� �� ��� ���� ���������� ������ ���� �� �����, ��...
				{
					if (x.sum < 0) // ��������� ����
					{
						s << "-" << x.sum / 480 * (-1) << "pd."; // ������� ����� (18)
					}
					else
					{
						s << x.sum / 480 << "pd."; // ������� ����� (19)
					}
				}
			}
			else if (x.sum / 480 == 0) // ���� �� ���������� ������ ����� ����, ��...
			{
				if (x.sum < 0) // ��������� ����
				{
					s << "-" << (x.sum / 24) % 20 * (-1) << "sh."; // ������� �������� (20)
				}
				else
				{
					s << (x.sum / 24) % 20 << "sh."; // ������� �������� (21)
				}
			}
			else // ����� ��...
			{
				if (x.sum < 0) // ��������� ����
				{
					s << "-" << x.sum / 480 * (-1) << "pd." << (x.sum / 24) % 20 * (-1) << "sh."; // ������� � ����� � �������� (22)
				}
				else
				{
					s << x.sum / 480 << "pd." << (x.sum / 24) % 20 << "sh."; // ������� � ����� � �������� (23)
				}
			}
		}
		else if ((x.sum / 24) % 20 == 0) // ���� �� ���������� ��������� ����� ����, ��...
		{
			if (x.sum / 480 == 0) // ���� ���������� ������ ����� ����, ��...
			{
				if (x.sum < 0) // ��������� ����
				{
					s << "-" << ((x.sum / 2) % 12) * (-1) << "p."; // ������� ����� (24)
				}
				else
				{
					s << ((x.sum / 2) % 12) << "p."; // ������� ����� (25)
				}
			}
			else // ���� �� ���������� ������ ���� �� �����, ��...
			{
				if (x.sum < 0) // ��������� ����
				{
					s << "-" << x.sum / 480 * (-1) << "pd." << ((x.sum / 2) % 12) * (-1) << "p."; // ������� ����� � ����� (26)
				}
				else
				{
					s << x.sum / 480 << "pd." << ((x.sum / 2) % 12) << "p."; // ������� ����� � ����� (27)
				}
			}
		}
		else if (x.sum / 480 == 0) // ���� �� ���������� ������ ����� ����, ��...
		{
			if (x.sum < 0) // ��������� ����
			{
				s << "-" << (x.sum / 24) % 20 * (-1) << "sh." << ((x.sum / 2) % 12) * (-1) << "p."; // ������� �������� � ����� (28)
			}
			else
			{
				s << (x.sum / 24) % 20 << "sh." << ((x.sum / 2) % 12) << "p."; // ������� �������� � ����� (29)
			}
		}
		else
		{
			if (x.sum < 0) // ��������� ����
			{
				s << "-" << x.sum / 480 * (-1) << "pd." << (x.sum / 24) % 20 * (-1) << "sh." << ((x.sum / 2) % 12) * (-1) << "p."; // ������� ��� (30)
			}
			else
			{
				s << x.sum / 480 << "pd." << (x.sum / 24) % 20 << "sh." << ((x.sum / 2) % 12) << "p."; // ������� ��� (31)
			}
		}
	}
	return s;
}