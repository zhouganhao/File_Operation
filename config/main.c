#include <stdio.h>
#include "config.h"

int main(void)
{
	config_ini("./config.ini");
	Write_Config_Value("./config.ini","name","abcd");
	return 0;
}
