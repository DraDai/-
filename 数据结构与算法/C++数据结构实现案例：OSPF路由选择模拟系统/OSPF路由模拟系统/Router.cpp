#include"User.h"
using namespace std;

void adFunction();
void userFunction();
void _userFunction();
int main()
{
	//text:Container
		//text:G1 = G2;
		//text data:
		/*1 2 3 4 5
		1 2 3
		2 3 4
		3 4 5
		4 5 1
		5 1 2*/
		/*Graph G1;
		Graph G2;
		for (int i = 1; i <= 5; i++)
		{
			string s;
			cin >> s;
			G2.AddV(s);
		}
		for (int i = 1; i <= 5; i++)
		{
			string s1;
			string s2;
			int p;
			cin >> s1 >> s2 >> p;
			G2.AddEdge(s1, s2, p);
		}
		G1 = G2;
		G2.printG();
		G1.printG();*/


		//text:InitGraph()
		//text:data
		/*1 2 3 4
		1 2 3
		2 3 4
		3 4 1
		4 1 2
		2 3 4 5
		2 3 4
		3 4 5
		4 5 2
		5 2 3*/
		/*Graph G1, G2;
		for (int i = 1; i <= 4; i++)
		{
			string s;
			cin >> s;
			G1.AddV(s);
		}
		for (int i = 1; i <= 4; i++)
		{
			string s1;
			string s2;
			int p;
			cin >> s1;
			cin >> s2;
			cin >> p;
			G1.AddEdge(s1, s2, p);
		}
		for (int i = 1; i <= 4; i++)
		{
			string s;
			cin >> s;
			G2.AddV(s);
		}
		for (int i = 1; i <= 4; i++)
		{
			string s1;
			string s2;
			int p;
			cin >> s1;
			cin >> s2;
			cin >> p;
			G2.AddEdge(s1, s2, p);
		}
		G1.printG();
		cout << endl;
		G2.printG();
		cout << endl;
		G1.InitGraph(G2);
		G1.printG();
		cout << endl;
		G2.InitGraph(G1);
		G2.printG();*/


		//text:DeleteAllDisconnect()
		//text:data
		/*1 2 3 4 5
		1 2 3
		2 3 4
		3 4 1
		4 1 2*/
		/*Graph G;
		for (int i = 1; i <= 5; i++)
		{
			string s;
			cin >> s;
			G.AddV(s);
		}
		for (int i = 1; i <= 4; i++)
		{
			string s1;
			string s2;
			int p;
			cin >> s1;
			cin >> s2;
			cin >> p;
			G.AddEdge(s1, s2, p);
		}
		G.DeleteAllDisconnect("3");
		G.printG();*/


	//text:RoutList
		//text:Make_routerlist()
		//text:data
		/*1 2 3 4 5
		1 2 3
		2 3 4
		3 4 5
		4 5 1
		5 1 3*/
		/*Graph G;
		for (int i = 1; i <= 5; i++)
		{
			string name;
			cin >> name;
			G.AddV(name);
		}
		for (int i = 1; i <= 3; i++)
		{
			string s1, s2;
			int power;
			cin >> s1 >> s2 >> power;
			G.AddEdge(s1, s2, power);
		}
		RoutList R;
		R.Make_routerlist(G, "1");
		R.printRouters();*/
	//text:OSPF.h
		//text:InitAllNetWork()+SaveAllNetwork()
		/*OSPF O;
		O.AllNetwork.printG();
		for (int i = 1; i <= 2;i++) {
			string s;
			cin >> s;
			O.AllNetwork.AddV(s);
		}
		for (int i = 1; i <= 4; i++) {
			string s1;
			string s2;
			int power;
			cin >> s1 >> s2 >> power;
			O.AllNetwork.AddEdge(s1, s2, power);
		}
		O.AllNetwork.printG();
		O.SaveAllNetwork();*/
	
		//text:InsertRAVL()+DeleteRAVL()
		//text data:
		/*1 2 3 4 5 6 7 8 9 10
		2 4 6 10*/
		/*OSPF O;
		for (int i = 1; i <= 10; i++) {
			string name;
			cin >> name;
			O.InsertRAVL(O.head, name);
		}
		O.printRAVL();
		for (int i = 1; i <= 4; i++)
		{
			string name;
			cin >> name;
			O.DeleteRAVL(O.head, name);
		}
		O.printRAVL();*/

		//text:AddPower()+AddRouter()
		//text data:
		/*1 2 3 4 5
		1 2 3
		2 3 4
		4 5 6
		4 2 5*/
		//OSPF O;
		//for (int i = 1; i <= 5; i++)
		//{
		//	string name;
		//	cin >> name;
		//	O.AddRouter(name);
		//}
		//O.printRAVL();
		//for (int i = 1; i <= 4; i++)
		//{
		//	string s1, s2;
		//	int power;
		//	cin >> s1 >> s2 >> power;
		//	O.AddPower(s1, s2, power);
		//	O.printRouterNetwork(s1);
		//	cout << endl;
		//	O.printRouterNetwork(s2);
		//	cout << endl;
		//}

		//text:DeletePower()
		//text data:
		/*1 2 3 4
		1 2 3
		2 3 4
		3 4 1
		4 1 2
		1 4
		2 3
		1 2*/
		/*OSPF O;
		for (int i = 1; i <= 4; i++) {
			string s;
			cin >> s;
			O.AddRouter(s);
		}
		O.printRAVL();
		for (int i = 1; i <= 4; i++) {
			string s1, s2;
			int power;
			cin >> s1 >> s2 >> power;
			O.AddPower(s1, s2, power);
		}
		O.AllNetwork.printG();
		cout << endl;
		for (int i = 1; i <= 3; i++)
		{
			string s1, s2;
			cin >> s1 >> s2;
			O.DeletePower(s1, s2);
			O.printRouterNetwork(s1);
			cout << endl;
			O.printRouterRoutlist(s1);
			cout << endl;
			O.printRouterNetwork(s2);
			cout << endl;
			O.printRouterRoutlist(s2);
			cout << endl;
		}*/

		//text:DeleteNearPower()
		//text data
		/*1 2 3 4 5 6
		1 2 3
		1 3 4
		1 4 5
		1 5 6
		1 6 7*/
		/*OSPF O;
		for (int i = 1; i <= 6; i++) {
			string s;
			cin >> s;
			O.AddRouter(s);
		}
		O.printRAVL();
		for (int i = 1; i <= 5; i++)
		{
			string s1, s2;
			int p;
			cin >> s1 >> s2 >> p;
			O.AddPower(s1, s2, p);
		}
		O.AllNetwork.printG();
		O.DeleteNearPower("1");
		O.AllNetwork.printG();*/

		//text DeleteRouter()
		//text data:
		/*1 2 3 4 5 6
		1 2 3
		1 3 4
		1 4 5
		1 5 6
		1 6 1*/
		/*OSPF O;
		for (int i = 1; i <= 6; i++) {
			string s;
			cin >> s;
			O.AddRouter(s);
		}
		O.printRAVL();
		for (int i = 1; i <= 5; i++)
		{
			string s1, s2;
			int p;
			cin >> s1 >> s2 >> p;
			O.AddPower(s1, s2, p);
		}
		O.AllNetwork.printG();
		O.DeleteRouter("1");
		O.AllNetwork.printG();
		O.printRAVL();*/

		//text printMinPath()
		/*OSPF O;
		O.printMinPath("1", "9");
		O.printAllNetwork();*/

	//text��User.h
		//text:User()��InsertUser()��printUser()
		/*User U;

		U.printUsers();
		string s1;
		cin >> s1;		
		U.DeleteUser(s1);
		U.printUsers();
		U.SaveUserBST();*/
	cout << "��ӭ����OSPF·��ģ��ϵͳ��" << endl<<endl;
	cout << "�������Ҫ�Թ���Ա����ݵ�¼��������A��" << endl;
	cout << "��ͨ�û���¼������B" << endl;
	cout << "��ͨ�û�ע��������C" << endl;
	cout << "�˳�OSPF·��ģ��ϵͳ������D" << endl;
	cout << "�������룺";
	char ch;
	cin >> ch;
	while(ch != 'D')
	{

		switch (ch)
		{
		case 'A':
			adFunction();
			cout << endl;
			break;
		case'B':
			userFunction();
			cout << endl;
			break;
		case'C':
			_userFunction();
			cout << endl;
			break;
		default:
			break;
		}
		cout << "�������Ҫ�Թ���Ա����ݵ�¼��������A��" << endl;
		cout << "��ͨ�û���¼������B" << endl;
		cout << "��ͨ�û�ע��������C" << endl;
		cout << "�˳�OSPF·��ģ��ϵͳ������D" << endl<<endl;
		cout << "�������룺";
		cin >> ch;
	}
	return 0;
}//���񣺲�������ͼ�Ķ���ɾ�����ڽӶ���ɾ��

void adFunction() {
	cout << "�𾴵Ĺ���Ա�������������˺��Լ������¼��ƽ̨" << endl;
	cout << "�˺ţ�";
	string account;
	cin >> account;
	cout << "���룺";
	string password;
	cin >> password;
	Ad ad;
	int i = ad.FindAd(account);
	if (i == -1) {
		cout << "��¼ʧ�ܣ�" << endl<<endl;
		return;
	}
	if (ad.Adarray[i].password != password) {
		cout << "�������" << endl << endl;
		return;
	}

	cout << "��¼�ɹ���\n\n";
	cout << "�𾴵Ĺ���Ա���������¹��ܵ�ʹ��Ȩ�ޣ�\n\n";
	cout << "ͨ�ù��ܣ�\n";
	cout << "1���鿴����������ͼ\n";
	cout << "2���鿴��ĳ·�������ڵ�����·����\n";
	cout << "3���鿴��·����������·�����Լ�������·����\n";
	cout << "4���鿴ĳ·�����ڲ�����������ͼ\n";
	cout << "5���鿴ĳ·�����ڲ���·�ɱ�\n";
	cout << "6���˳���¼\n\n";
	cout << "����Աר�ù��ܣ�\n";
	cout << "7�����·����\n";
	cout << "8�����Ȩֵ\n";
	cout << "9���޸�Ȩֵ\n";
	cout << "10��ɾ��Ȩֵ\n";
	cout << "11��ɾ��ĳ·�����������ڽӱ�\n";
	cout << "12��ɾ��ĳ·����\n";
	cout << "13���鿴�û���Ϣ\n";
	cout << "14���鿴�������·ӵ�����\n";
	cout << "15��ע���û�\n\n";
	cout << "������Ӧ����ű�ʾ��Ҫʹ�õĹ��ܣ�";
	int a;
	cin >> a;
	while (a != 6) {
		string ip;
		string from, to;
		int power;
		string account;
		switch (a)
		{
		case 1:
			ad.printAllNetwork();
			cout << endl;
			break;
		case 2:
			cout << "����·������ַ���鿴�����ڽ�·������";
			cin >> ip;
			ad.printAllNetWork(ip);
			cout << endl;
			break;
		case 3:
			cout << "������ʼ·�������յ�·�������鿴���·��\n";
			cout << "��ʼ·������ַ��";
			cin >> from;
			cout << "�յ�·������ַ��";
			cin >> to;
			ad.printMinPath(from, to);
			cout << endl;
			break;
		case 4:
			cout << "����·������ַ���鿴���ڲ�����������ͼ��";
			cin >> ip;
			ad.printRouterNetwork(ip);
			cout << endl;
			break;
		case 5:
			cout << "����·������ַ���鿴���ڲ���·�ɱ�";
			cin >> ip;
			ad.printRouterRoutlist(ip);
			cout << endl;
			break;
		case 7:
			cout << "����·������ַ�����·������";
			cin >> ip;
			ad.AddRouter(ip);
			ad.SaveAllNetwork();
			cout << "��ӳɹ�\n";
			cout << endl;
			break;
		case 8:
			cout << "������ʼ·�������յ�·�����ĵ�ַ���Լ�����֮���Ȩֵ�����Ȩֵ\n";
			cout << "��ʼ·������ַ��";
			cin >> from;
			cout << "�յ�·������ַ��";
			cin >> to;
			cout << "Ȩֵ��";
			cin >> power;
			if (ad.AddPower(from, to, power))
			{
				cout << "��ӳɹ�\n";
				ad.SaveAllNetwork();
			}
			else
				cout << "���ʧ��\n";
			cout << endl;
			break;
		case 9:
			cout << "������ʼ·�������յ�·�����ĵ�ַ���Լ���Ȩֵ�����޸�����֮���Ȩֵ\n";
			cout << "��ʼ·������ַ��";
			cin >> from;
			cout << "�յ�·������ַ��";
			cin >> to;
			cout << "Ȩֵ��";
			cin >> power;
			if (ad.ModifyPower(from, to, power))
			{
				cout << "�޸ĳɹ�\n";
				ad.SaveAllNetwork();
			}
			else
				cout << "�޸�ʧ��\n";
			cout << endl;
			break;
		case 10:
			cout << "������ʼ·�������յ�·�����ĵ�ַ,��ɾ������֮���Ȩֵ\n";
			cout << "��ʼ·������ַ��";
			cin >> from;
			cout << "�յ�·������ַ��";
			cin >> to;
			if (ad.DeletePower(from, to)) {
				cout << "ɾ���ɹ�\n";
				ad.SaveAllNetwork();
			}
			else
				cout << "ɾ��ʧ��\n";
			cout << endl;
			break;
		case 11:
			cout << "����·������ַ��ɾ�����������ڽӱߣ�";
			cin >> ip;
			ad.DeleteNearPower(ip);
			ad.SaveAllNetwork();
			cout << endl;
			break;
		case 12:
			cout << "����·������ַ��ɾ��·������";
			cin >> ip;
			ad.DeleteRouter(ip);
			ad.SaveAllNetwork();
			cout << endl;
			break;
		case 13:
			ad.printUsers();
			cout << endl;
			break;
		case 14:
			cout << "��ʼ·���� -- �յ�·����    ӵ�����\n";
			ad.printPower();
			cout << endl;
			break;
		case 15:
			cout << "�����û��˺���ɾ���û���";
			cin >> account;
			ad.DeleteUser(account);
			ad.SaveUserBST();
			cout << endl;
			break;
		default:
			break;
		}
		cout << "������Ӧ����ű�ʾ��Ҫʹ�õĹ��ܣ�";
		cin >> a;
	}
}

void userFunction() {
	cout << "�𾴵��û��������������˺��Լ������¼��ƽ̨" << endl;
	cout << "�˺ţ�";
	string account;
	cin >> account;
	cout << "���룺";
	string password;
	cin >> password;
	User U;
	UsersBST Up = U.FindUser(account);
	if (Up == nullptr) {
		cout << "��¼ʧ�ܣ�" << endl << endl;
		return;
	}
	if (Up->password != password) {
		cout << "�������" << endl << endl;
		return;
	}

	cout << "��¼�ɹ���\n\n";
	cout << "�𾴵��û����������¹��ܵ�ʹ��Ȩ�ޣ�\n\n";
	cout << "1���鿴����������ͼ\n";
	cout << "2���鿴��ĳ·�������ڵ�����·����\n";
	cout << "3���鿴��·����������·�����Լ�������·����\n";
	cout << "4���鿴ĳ·�����ڲ�����������ͼ\n";
	cout << "5���鿴ĳ·�����ڲ���·�ɱ�\n";
	cout << "6���鿴�����ӵ�����\n";
	cout << "7��ע���˻�\n";
	cout << "8���˳���¼\n\n";
	cout << "������Ӧ����ű�ʾ��Ҫʹ�õĹ��ܣ�";
	int a;
	cin >> a;
	while (a != 8) {
		string ip;
		string from, to;
		int power;
		switch (a)
		{
		case 1:
			U.printAllNetwork();
			cout << endl;
			break;
		case 2:
			cout << "����·������ַ���鿴�����ڽ�·������";
			cin >> ip;
			U.printAllNetWork(ip);
			cout << endl;
			break;
		case 3:
			cout << "������ʼ·�������յ�·�������鿴���·��\n";
			cout << "��ʼ·������ַ��";
			cin >> from;
			cout << "�յ�·������ַ��";
			cin >> to;
			U.printMinPath(from, to);
			cout << endl;
			break;
		case 4:
			cout << "����·������ַ���鿴���ڲ�����������ͼ��";
			cin >> ip;
			U.printRouterNetwork(ip);
			cout << endl;
			break;
		case 5:
			cout << "����·������ַ���鿴���ڲ���·�ɱ�";
			cin >> ip;
			U.printRouterRoutlist(ip);
			cout << endl;
			break;
		case 6:
			cout << "��ʼ·���� -- �յ�·����    ӵ�����\n";
			U.printPower();
			cout << endl;
			break;
		case 7:
			cout << "���������˻���������ע���˺�\n";
			cout << "�˺ţ�";
			cin >> account;
			cout << "���룺";
			cin >> password;
			Up = U.FindUser(account);
			if (Up->password != password) {
				cout << "�������" << endl << endl;
				break;
			}
			U.DeleteUser(account);
			U.SaveUserBST();
			cout << "ע���ɹ�\n";
			cout << endl;
			return;
		default:
			break;
		}
		cout << "������Ӧ����ű�ʾ��Ҫʹ�õĹ��ܣ�";
		cin >> a;
	}
}

void _userFunction() {
	cout << "���������û������˺ź�������ע���˻�\n";
	string s1, s2, s3;
	cout << "�û�����";
	cin >> s1;
	cout << "�˺ţ�";
	cin >> s2;
	cout << "���룺";
	cin >> s3;
	User U;
	U.InsertUser(s1, s2, s3);
	U.SaveUserBST();
	userFunction();
}