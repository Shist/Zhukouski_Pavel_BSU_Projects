#include "Person.h"
using namespace std;

int main()
{
	Person* child;
	const char* n1 = "Mike";
	const char* n2 = "Anna";
	try
	{
		child = Person::Eve.giveBirth(&Person::Adam, n1, n2);
		cout << "The name of the child:" << endl;
		cout << child->getName() << endl;
		cout << "The ID of the child:" << endl;
		cout << child->getID() << endl;
		cout << "The gender of the child:" << endl;
		child->output_gender(cout);
		cout << "The gender of the father of the child:" << endl;
		child->getFather()->output_gender(cout);
		cout << "The gender of the mother of the child:" << endl;
		child->getMother()->output_gender(cout);
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	return 0;
}