#ifndef CONTACT_H_
#define CONTACT_H_
#include <qstring.h>
#include<qrandom.h>

class Contact
{
public:
	enum accountType
	{
		NONE,
		VIP,
		SVIP
	};

	Contact(const QString& userName, const QString& noteName)
		:userName(userName)
		,noteName(noteName)
		,profilePath(":/Resource/images/defaultProfile.png")
		,signature("无信息")
		, type((QRandomGenerator::global()->bounded(3)))
	{

	}
	
	QString profilePath;//头像路径
	QString userName;//用户昵称
	QString noteName;//备注名称
	QString signature;//签名
	int type;//账户类型
};

#endif // !CONTACT_H_
