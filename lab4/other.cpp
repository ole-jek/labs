#include "other.h"
void inc_by_value(int value)
{
	value++;
}

void inc_by_pointer(int* ptr)
{
	*ptr++;
}

void inc_by_reference(int& ref)
{
	ref++;
}
