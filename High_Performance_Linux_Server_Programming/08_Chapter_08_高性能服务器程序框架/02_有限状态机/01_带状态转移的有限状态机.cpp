
STATE_MACHINE()
{
	State cur_State = type_A;
	while( cur_State != type_C )
	{
		Package _pack = getNewPackage();
		switch( cur_State )
		{
			case type_A:
					process_package_state_A( _pack );
					cur_State = type_B;
					break;
			case type_B:
					process_package_state_B( _pack );
					cur_State = type_C;
					break;
		}
	}
}

//状态机的当前状态记录在cur_State变量中。
//状态机先通过getNewPackage()获得一个新的数据包，然后根据cur_State变量的值判断如何处理该数据包
//数据包处理完成之后，状态机通过给cur_Status变量传递目标状态值来实现状态转移
