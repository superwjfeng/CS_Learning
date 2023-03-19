int g_val = 2021; 
/* when we put static before int, the scope of variable will be limited
* so that variable can not be used in other c file */

int Add(int x, int y) // static can also be put before function
// static function changes the linkage of funciton 链接属性, which is external, internal or none
{
	int z = x + y;
	return z;
}
