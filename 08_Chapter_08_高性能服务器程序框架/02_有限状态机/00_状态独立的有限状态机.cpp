
STATE_MACHINE( Package _pack )
{
	Package _type = _pack.GetType();
	switch( _type )
	{
		case type_A:
				process_package_A( _pack );
				break;
		case type_B:
				process_package_B( _pack );
				break;
	}
}

//这就是一个简单有限状态机，只不过该状态机的每个状态都是相互的，即状态之间没有相互转移
