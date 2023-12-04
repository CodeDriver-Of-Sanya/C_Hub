#include <regex> //正则表达式头文件
#include <fstream> //文件操作头文件
#include <iostream>
#include <string>
#include <queue>//队列容器
#include <map>//解决网址重复问题
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")//加载动态库   把源代码弄过来
#include <windows.h>

using namespace std;
//http://www.netbian.com/s/meinvmm/
 

//网址       数据
map<string, int> g_map;//解决网址重复问题
//存放主机名
char g_zhuji[256] = { 0 };
//存放主机后的路径
char g_path[256] = { 0 };
//服务器socket
SOCKET g_socket;
//存放图片地址的容器
vector<string> photoAddr;
//存放网页地址的容器
vector<string> htmlAddr;

//爬jpg图片
void snapJpg(const char* addr);

//解析网址
void jiexiAddr(char* buff);
//连接服务器
void connectAddr();
//得到源代码
void getHtml();
//下载图片
void saveImage(string str);
//从网页源代码中获取图片链接
void getImage(string& allHtml);
//从网页源代码中获取网址链接
void getAddr(string& allHtml);

int main() {

	string begAddr;
	cout << "请输入起始网址:";
	cin >> begAddr;

	//创建一个文件夹
	CreateDirectory(".\\images", NULL);

	snapJpg(begAddr.c_str());
	while (1);
	return 0;
}


//爬jpg图片
void snapJpg(const char* addr) {
	queue<string> q;//存网址
	q.push(addr);//把起始网址放进去

	while (!q.empty()) {
		//从q中拿出一个 
		string currentAddr = q.front();
		//删掉
		q.pop();
		//解决网址重复问题
		g_map[currentAddr]++;
		//解析网址 拿到域名
		char buff[256] = { 0 };
		strcpy(buff, currentAddr.c_str());
		//解析网址
		jiexiAddr(buff);
		//连接服务器
		connectAddr();
		//得到源代码
		getHtml();
#if 1
		//从源代码中解析出网址和图片地址 存入对应容器中
		//把网址存放到队列q中
		vector<string>::iterator it;
		for (it = htmlAddr.begin(); it != htmlAddr.end(); it++) {
			if (0 == g_map[*it]) {//没有连接过
				q.push(*it);//放到队列中
			}
		}
		htmlAddr.clear();//清空容器
		//下载图片
		for (it = photoAddr.begin(); it != photoAddr.end(); it++) {
			saveImage(*it);
		}
		photoAddr.clear();//清空容器
#else
		while (1);
#endif
	}
}

//解析网址
void jiexiAddr(char* buff) {
	char temp[256] = { 0 };
	strcpy(temp, buff);

	//略过前面七个 http://
	char* p = strstr(buff, "http://");//buff中找子串 "http://" 找到返回子串首地址
	if (NULL == p) return;
	else
		p += 7;//往后挪七个

	sscanf(p, "%[^/]%s", g_zhuji, g_path);
	printf("主机：%s\n", g_zhuji);
	printf("路径：%s\n", g_path);
}
//连接服务器
void connectAddr() {
	//1 获取协议版本号
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		printf("请求版本号失败！\n");
		return;
	}
	printf("请求版本号成功！\n");
	//2 创建socket
	g_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == g_socket) {
		printf("创建socket失败!\n");
		return;
	}
	printf("创建socket成功!\n");
	//3 创建协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET; //必须和socket函数第一个参数一致
	//4 绑定
	int r = bind(g_socket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		printf("绑定失败!\n");
		return;
	}
	printf("绑定成功！\n");
	//5 拿到主机ip地址
	struct hostent* p = gethostbyname(g_zhuji);//192.168.0.44    ipv4
	if (NULL == p) {
		printf("获取主机地址失败!\n");
		return;
	}
	printf("获取主机地址成功!\n");

	memcpy(&addr.sin_addr, p->h_addr, 4);	//把主机地址放入协议地址族中
	addr.sin_port = htons(80);				//设置主机端口号   浏览器端口号一般为80

	//6 连接服务器
	r = connect(g_socket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		printf("连接服务器失败!\n");
		return;
	}
	printf("连接服务器成功！\n");
	//7 通信：发送获取源代码请求

	//请求信息
	string reqInfo = "GET " + (string)g_path + " HTTP/1.1\r\nHost:" +
		(string)g_zhuji + "\r\nConnection:Close\r\n\r\n";
	//发送请求信息到服务器
	r = send(g_socket, reqInfo.c_str(), reqInfo.size(), NULL);
	if (r > 0) {
		printf("发送请求信息成功!\n");
	}
	else {
		printf("发送请求信息失败，失败原因：%d\n", WSAGetLastError());
	}

}
//得到源代码
void getHtml() {
	string allHtml;

	char buff[1024];
	int r;
	while (1) {
		r = recv(g_socket, buff, 1023, NULL);
		if (r > 0) {
			buff[r] = 0;
			allHtml += buff;
		}
		else {
			break;
		}
	}

	cout << allHtml << endl;

	//从网页源代码中获取图片链接
	getImage(allHtml);
	//从网页源代码中获取网址链接
	getAddr(allHtml);
}
//下载图片
void saveImage(string str) {
	//1 解析图片地址
	char buff[256];
	memset(buff, 0, 256);
	strcpy(buff, str.c_str());

	jiexiAddr(buff);
	//2 连接服务器
	//3 发送下载图片请求
	connectAddr();
	//4 本地创建图片文件
	//4.1 得到图片文件名
	string photoName;
	photoName.resize(str.size());

	char ch;
	int j = 0;
	for (int i = 0; i < str.length(); i++) {
		ch = str[i];
		// '\0'  '\n' '\t' '\r' '\\' '\"'
		if (ch != '\\' && ch != '/' && ch != ':' && ch != '*' && ch != '?' &&
			ch != '"' && ch != '<' && ch != '>' && ch != '|') {
			photoName[j++] = ch;
		}
	}

	photoName = "./images/" + photoName.substr(0, j);

	//4.2 创建图片文件
	fstream file;
	file.open(photoName, ios::out | ios::binary);//二进制写

	//5 接收发送过来的图片信息并写入图片文件中
	int r;
	char tempBuff[1024] = { 0 };

	//排除掉文件头的"\r\n\r\n"
	r = recv(g_socket, tempBuff, 1023, NULL);
	char* p = strstr(tempBuff, "\r\n\r\n");
	file.write(p + strlen("\r\n\r\n"), r - (p - tempBuff) - strlen("\r\n\r\n"));

	while (1) {
		r = recv(g_socket, tempBuff, 1023, NULL);
		if (r > 0) {
			file.write(tempBuff, r);
		}
		else {
			break;
		}

	}
	//6 保存关闭
	file.close();

}

//从网页源代码中获取图片链接
void getImage(string& allHtml) {
	smatch mat;//用作匹配的对象
	regex pattren("src=\"(.*?\\.jpg)\"");
	string::const_iterator start = allHtml.begin();//起始位置
	string::const_iterator end = allHtml.end();//结束位置

	while (regex_search(start, end, mat, pattren)) {
		string msg(mat[1].first, mat[1].second);
		photoAddr.push_back(msg);
		cout << "找到图片：" << msg << endl;
		start = mat[0].second;//改变起始位置
	}
}
//从网页源代码中获取网址链接
void getAddr(string& allHtml) {
	smatch mat;//用作匹配的对象
	regex pattren("href=\"(http://[^\\s,\"]+)\"");
	string::const_iterator start = allHtml.begin();//起始位置
	string::const_iterator end = allHtml.end();//结束位置

	while (regex_search(start, end, mat, pattren)) {
		string msg(mat[1].first, mat[1].second);
		htmlAddr.push_back(msg);
		cout << "找到网址：" << msg << endl;
		start = mat[0].second;//改变起始位置
	}
}