// On my system with 16GBs of RAM, I managed to allocate around 14GBs
// before the OS killed my process.
int main()
{
	while (true)
	{
		new char[1024];
	}
}
