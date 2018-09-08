#include"define.h"


void Encode(char *ins)
{
	int i = 0;
	while (ins[i] != 0)
	{
		if (ins[i] >= 'A'&&ins[i] <= 'Z')
		{
			ins[i] += 32;
		}
		i++;
	}
}

