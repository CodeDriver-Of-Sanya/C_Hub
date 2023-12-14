#define _CRT_SECURE_NO_WARNINGS 1
	/*int tmp;
	float tmpf = 12.5;
	tmp = tmpf;
	printf("%d",tmp);*/////////////浮点型位置切割
	
	//int start_t = clock();//记录毫秒的时间戳
	int i = 0;
	char highBark[25]; 
	for (i = 0 ; i < 25 ; i++)
	{
		highBark[i] = '|';//初始化图形表格
	}
	for (i = 0 ; i < 25 ; i++)
	{
		printf("%c\n",highBark[i]);//打印图形表格
	}
	//在下标为0的元素处放置一小球，使其自由落体运动
	//设定G = g = a为10m/s^2, 高度为25m , 位移 浮点型x = 1/2 at^2    
	//x的位移大小为粗劣值，先求具体位移，再确定为第几元素下标时，取用范围估值带入
	//时间为控制游戏的主要因素（获取真实时间） clock_t clock(void)[获取当前时间戳]
	
	
	//位置估算一个下标元素的区间假定为1m,1m为一个游戏单位
	//位置估算方式
	int postion;
	int x;
	postion = x;//将现有的位置元素放到位置变量上
	float tmp = x - postion;//查看多余数值
	if (tmp > 0)//有多余数值
	{
		//进行数组转换
	}
	

	
	
