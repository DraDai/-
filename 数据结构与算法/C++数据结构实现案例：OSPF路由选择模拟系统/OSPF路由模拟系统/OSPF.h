#pragma once
#include"RoutList.h"
#include<fstream>
struct Router {//·�����ṹ
	string name;	//·������ַ
	RoutList rlist;	//·�ɱ���
	Graph network;	//��������ͼ��
};

struct RTNode {
	Router R;	//·�����ڵ�
	RTNode* left;	//������
	RTNode* right;	//������
	bool visited;	//���
	int Height;	//����
};
typedef RTNode* RAVL;	//ƽ�������

struct Node {	//���������������
	Router R;	//·������ַ
	Node* next;
};
typedef Node* Position;

struct QNode {	//���е�ͷβָ��
	Position front, Rear;
};
typedef QNode* Queue;//���нṹ
class OSPF {
public:
	//��Ա
	Graph AllNetwork;	//����������ͼ
	RAVL head;	//·����ƽ�������

	//��ʼ��OSPF��
	OSPF() {
		//��ʼ������������ͼ
		InitOSPF();
	}

	//����AllNetwork���ļ�����
	void SaveAllNetwork() {
		ofstream outputFile("AllNetWork.txt");

		if (!outputFile.is_open()) {
			cerr << "�ļ���ʧ�ܣ�" << "AllNetWork.txt" << endl;
			return;
		}

		Vert p = AllNetwork.head;
		while (p->vp) {
			p = p->vp;

			Edge t = p->ep;
			while (t) {
				outputFile <<p->name<< " " << t->name << " " << t->power << endl;
				t = t->ep;
			}
		}
		outputFile.close();
		cout << "������Ϣ����ɹ�!" << endl;
	}

	//��ʾ����������ͼ
	void printAllNetwork()
	{
		cout << "����������ͼ��" << endl;
		AllNetwork.printG();
	}

	//�鿴ĳ·�����������ڽӵ�
	void printAllNetWork(const string& name) {
		if (!AllNetwork.FindV(name)) {
			cout << "��·����������\n";
			return;
		}
		AllNetwork.printNE(name);
	}

	//ͨ������·������ַ����ʾ���·���Լ�������·����
	void printMinPath(const string& from, const string& to) {
		//�ҵ�from·���������е�λ��
		RAVL F, T;
		F = FindRAVL(head, from);
		T = FindRAVL(head, to);
		if (!F || !T) {
			cout << "�޷���ʾ " << from << " �� " << to << " �����·��" << endl;
			return;
		}
		string nextjump = F->R.rlist.FindRoutlist(to);
		if (nextjump == "") {
			cout << from << " �� " << to << " ������" << endl;
			return;
		}
		int sum = 0;
		cout << from << " �� " << to << " �����·����������·�����У�" << endl;
		cout << from;
		while (nextjump != to) {
			cout << " -> " << nextjump;
			sum += F->R.network.Getpower(F->R.name, nextjump);
			F = FindRAVL(head, nextjump);
			nextjump = F->R.rlist.FindRoutlist(to);
		}
		cout << " -> " << nextjump << endl << endl;
		sum += F->R.network.Getpower(F->R.name, nextjump);
		cout << "���·������ȨֵΪ��" << sum << endl;
		//��·�ɱ��ȡ·��
	}

	//�ֵ�����ʾ·������ַ��Ϣ
	void printRAVL()
	{
		cout << "ƽ̨������·������" << endl;
		//���ú���
		_print_ravl(head);
		cout << endl;
	}

	//ͨ��·�ɵ�ַ��ʾ·�����ڲ�����������ͼ
	void printRouterNetwork(const string& name)
	{
		RAVL Rp = FindRAVL(head, name);
		if (Rp == nullptr)
			cout << "��·���������ڣ�" << endl;
		else
		{
			cout << name << " ����������ͼ:" << endl;
			Rp->R.network.printG();
		}
	}

	//ͨ��·������ַ��ʾ·�����ڲ���·�ɱ�
	void printRouterRoutlist(const string& name) {
		RAVL Rp = FindRAVL(head, name);
		if (Rp) {
			Rp->R.rlist.printRouters();
		}
		else
			cout << "·���������ڣ�" << endl;
	}

	//�������Ȩֵ
	void printPower() {
		AllNetwork.SortPrintEdge();
	}

	//���·����
	void AddRouter(const string& name)
	{
		//����ƽ�������
		InsertRAVL(head, name);
		//��������������ͼ
		AllNetwork.AddV(name);
	}

	//����Ȩֵ
	int FindPower(const string& from, const string& to)
	{
		return AllNetwork.Getpower(from, to);
	}

	//���Ȩֵ
	bool AddPower(const string& from, const string& to, int power)
	{
		if (!FindRAVL(head, from) || !FindRAVL(head, to))
			return false;
		//��������������ͼ
		AllNetwork.AddEdge(from, to, power);
		//�ڸ��Ե���������ͼ������ӶԷ���·�ɵ�ַ�������Ȩֵ
		RAVL F = FindRAVL(head, from);
		F->R.network.AddV(to);
		F->R.network.AddV(from);
		F->R.network.AddEdge(from, to, power);

		RAVL T = FindRAVL(head, to);
		T->R.network.AddV(to);
		T->R.network.AddV(from);
		T->R.network.AddEdge(to, from, power);

		//���߽�����ͼ��ӱ���û�е���Ϣ
		F->R.network.InitGraph(T->R.network);
		T->R.network.InitGraph(F->R.network);

		//������·�ɱ�
		F->R.rlist.deleteRouterList();
		F->R.rlist.Make_routerlist(F->R.network, from);

		T->R.rlist.deleteRouterList();
		T->R.rlist.Make_routerlist(T->R.network, to);

		//��ѡ��һ���з���
		Flood_Fill(from);
		return true;
	}

	//ɾ��Ȩֵ
	bool DeletePower(const string& from, string to)
	{
		if (!FindRAVL(head, from) || !FindRAVL(head, to))
			return true;
		if (AllNetwork.Getpower(from, to) == INF)
			return true;
		//ɾ������������ͼȨֵ
		AllNetwork.DeleteE(from, to);
		//�ڸ��Ե���������ͼ��ɾ��Ȩֵ
		RAVL F = FindRAVL(head, from);
		RAVL T = FindRAVL(head, to);

		F->R.network.DeleteE(from, to);
		T->R.network.DeleteE(to, from);

		//�Ѳ����Լ���ͨ������·������Ϣȫ��ɾ��
		F->R.network.DeleteAllDisconnect(from);
		T->R.network.DeleteAllDisconnect(to);

		//����·�ɱ�
		F->R.rlist.deleteRouterList();
		F->R.rlist.Make_routerlist(F->R.network, from);

		T->R.rlist.deleteRouterList();
		T->R.rlist.Make_routerlist(T->R.network, to);

		//���߶����з��飨��Ϊ��·�������ܲ���ͨ��
		Flood_Fill(from);
		Flood_Fill(to);
		return true;
	}

	//�޸�Ȩֵ
	bool ModifyPower(const string& from, const string& to, int power) {
		if (!FindRAVL(head, from) || !FindRAVL(head, to))
			return false;
		if (AllNetwork.Getpower(from, to) == INF) {
			AddPower(from, to, power);
			return true;
		}
		//�޸�����������ͼȨֵ
		AllNetwork.AddEdge(from, to, power);

		//�޸ĸ��Ե���������ͼ��Ȩֵ
		RAVL F = FindRAVL(head, from);
		RAVL T = FindRAVL(head, to);

		F->R.network.AddEdge(from, to, power);
		T->R.network.AddEdge(from, to, power);

		//������·�ɱ�
		F->R.rlist.deleteRouterList();
		F->R.rlist.Make_routerlist(F->R.network, from);

		T->R.rlist.deleteRouterList();
		T->R.rlist.Make_routerlist(T->R.network, to);
		//��ѡ��һ���з���

		Flood_Fill(from);
		return true;
	}
	
	//ɾ��ĳ·���������ڽӱ�
	bool DeleteNearPower(const string& from) {
		Vert p = AllNetwork.FindV(from);
		if (!p)
			return true;
		if (!p->ep)
			return true;
		Edge t = p->ep;
		_delete_power(p, t);
		p->ep = nullptr;
	}

	//ɾ��·����
	bool DeleteRouter(const string& from) {
		if (!FindRAVL(head, from))
			return true;
		DeleteNearPower(from);
		AllNetwork.DeleteV(from);
		DeleteRAVL(head, from);
		return true;
	}


private:

	//���ļ�����������������ͼ
	void InitOSPF()
	{
		ifstream inputFile("./AllNetWork.txt");

		if (!inputFile.is_open()) {
			cerr << "�ļ���ʧ�ܣ�" << "AllNetWork.txt" << endl;
			return;
		}

		string from, to;
		int power;

		//��ȡ�ļ��е�ÿһ�У�ÿ�а���һ���ߵ���Ϣ
		while (inputFile >> from >> to >> power) {
			AddRouter(from);
			AddRouter(to);
			AddPower(from, to, power);
		}
		//�ر��ļ���
		inputFile.close();
	}

	//��������
	int GetHeight(RAVL& Head)
	{
		int HL, HR, MaxH;
		if (Head)
		{
			HL = GetHeight(Head->left);
			HR = GetHeight(Head->right);
			MaxH = max(HL, HR) + 1;
			return MaxH;
		}
		else
			return 0;
	}

	//Ѱ��ƽ��������С�ڵ�
	RAVL FindMinRAVL(const RAVL& Head)
	{
		if (!Head)
			return nullptr;
		RAVL current = Head;

		while (current->left)
			current = current->left;
		return current;
	}

	//��������
	RAVL LL_Rotion(RAVL& Head)
	{
		RAVL temp = Head->left;
		Head->left = temp->right;
		temp->right = Head;
		Head->Height = max(GetHeight(Head->right), GetHeight(Head->left)) + 1;
		temp->Height = max(GetHeight(temp->left), Head->Height) + 1;
		return temp;
	}

	//��������
	RAVL RR_Rotion(RAVL& Head)
	{
		RAVL temp = Head->right;
		Head->right = temp->left;
		temp->left = Head;
		Head->Height = max(GetHeight(Head->right), GetHeight(Head->left)) + 1;
		temp->Height = max(GetHeight(temp->right), Head->Height) + 1;
		return temp;
	}

	//����������
	RAVL LR_Rotion(RAVL& Head)
	{
		Head->right = LL_Rotion(Head->right);
		return RR_Rotion(Head);
	}

	// ����������
	RAVL RL_Rotion(RAVL& Head)
	{
		Head->left = RR_Rotion(Head->left);
		return LL_Rotion(Head);
	}

	// ����·����ƽ����
	RAVL InsertRAVL(RAVL& Head, const string& name)
	{
		if (!Head)
		{
			//�����½ڵ�
			Head = new RTNode{};
			Head->R.name = name;
			Head->left = Head->right = nullptr;
			Head->visited = false;
			Head->Height = 1;
		}
		else if (name < Head->R.name)
		{
			//����������
			Head->left = InsertRAVL(Head->left, name);
			//����Ƿ���Ҫ��ת
			if (GetHeight(Head->right) - GetHeight(Head->left) == -2)
				if (name < Head->left->R.name)
					Head = LL_Rotion(Head);
				else
					Head = RL_Rotion(Head);
		}
		else if (name > Head->R.name)
		{
			//����������
			Head->right = InsertRAVL(Head->right, name);
			//�ж��Ƿ���Ҫ��ת
			if (GetHeight(Head->right) - GetHeight(Head->left) == 2)
				if (name > Head->right->R.name)
					Head = RR_Rotion(Head);
				else
					Head = LR_Rotion(Head);
		}
		//��������
		Head->Height = max(GetHeight(Head->left), GetHeight(Head->right)) + 1;
		return Head;
	}

	//ƽ����ɾ��
	RAVL DeleteRAVL(RAVL& Head, const string& name)
	{
		if (!Head)
			return nullptr;
		if (name < Head->R.name)
		{
			//ɾ��������
			Head->left = DeleteRAVL(Head->left, name);
			//�ж��Ƿ���ת
			if (GetHeight(Head->right) - GetHeight(Head->left) == -2)
				if (name < Head->left->R.name)
					Head = LL_Rotion(Head);
				else
					Head = RL_Rotion(Head);
		}
		else if (name > Head->R.name)
		{
			//ɾ��������
			Head->right = DeleteRAVL(Head->right, name);
			//�ж��Ƿ���ת
			if (GetHeight(Head->right) - GetHeight(Head->left) == 2)
				if (name > Head->right->R.name)
					Head = RR_Rotion(Head);
				else
					Head = LR_Rotion(Head);
		}
		else
		{
			//�ҵ���Ҫɾ������
			if (Head->left && Head->right)
			{
				RAVL MinNode = FindMinRAVL(Head->right);
				Head->R.name = MinNode->R.name;
				Head->R.network = MinNode->R.network;
				Head->R.rlist = MinNode->R.rlist;
				Head->right = DeleteRAVL(Head->right, MinNode->R.name);
				//ɾ�����ж����������Ƿ�ƽ��
				if (GetHeight(Head->right) - GetHeight(Head->left) == -2)
					if (Head->R.name < Head->left->R.name)
						Head = LL_Rotion(Head);
					else
						Head = RL_Rotion(Head);
			}
			else
			{
				RAVL temp = Head;
				if (Head->left)
					Head = Head->left;
				else
					Head = Head->right;
				delete temp;
			}
		}
		//��������
		if (Head)
		{
			Head->Height = GetHeight(Head);
		}
		return Head;
	}
	//ƽ�����������
	RAVL FindRAVL(const RAVL& Head, const string& name)
	{
		if (!Head)
		{
			return nullptr;
		}
		if (name < Head->R.name)
		{
			return FindRAVL(Head->left, name);
		}
		else if (name > Head->R.name)
		{
			return FindRAVL(Head->right, name);
		}
		else
			return Head;
	}
	//�����ն���
	Queue CreateQueue()
	{
		Queue Q = new QNode;
		Q->front = Q->Rear = NULL;
		return Q;
	}
	//�ж϶����Ƿ�Ϊ��
	bool IsEmptyQ(Queue Q)
	{
		return (Q->front == nullptr);
	}
	//ѹ�����
	void PushQ(Queue Q, Router& R)
	{
		Position RearCell = new Node;
		RearCell->R = R;
		RearCell->next = nullptr;
		if (IsEmptyQ(Q))
			Q->front = Q->Rear = RearCell;
		else
		{
			Q->Rear->next = RearCell;
			Q->Rear = RearCell;
		}
	}
	//��������
	Router PopQ(Queue Q)
	{
		Position FrontCell;
		Router FrontR;

		FrontCell = Q->front;
		if (Q->front == Q->Rear)
			Q->front = Q->Rear = nullptr;
		else
			Q->front = Q->front->next;
		FrontR = FrontCell->R;
		delete FrontCell;
		return FrontR;
	}
	//���ñ��
	void ReserVisited(RAVL Head)
	{
		if (Head)
		{
			ReserVisited(Head->left);
			Head->visited = false;
			ReserVisited(Head->right);
		}
	}

	//�ֵ����·������ַ���ú���
	void _print_ravl(RAVL& Head)
	{
		if(Head){
			_print_ravl(Head->left);
			cout << Head->R.name << " ";
			_print_ravl(Head->right);
		}
	}


	//��bpsģ���·�������ķ��鴫������
	bool Flood_Fill(const string& name)
	{
		//����һ������
		Queue q = CreateQueue();
		//������nameֱ�ӷ���false
		if (!FindRAVL(head, name))
			return false;
		//�ҵ�·���������е�λ��
		RAVL Rp = FindRAVL(head, name);
		//��·�������
		PushQ(q, Rp->R);

		//ѭ��������Ӹ�����ͼ
		while (!IsEmptyQ(q))
		{
			//����
			Router R = PopQ(q);
			//�ҵ�·�������Լ�����ͼ�е�λ��
			Edge E = R.network.FindV(R.name)->ep;

			//Ѱ���ڽӶ���
			while (E)
			{
				//���ڽӵ��·����Ѱ���ڽ�·�������е�λ��
				Rp = FindRAVL(head, E->name);
				//������ڽ�·��δ�����
				if (!Rp->visited)
				{
					//���
					Rp->visited = true;
					//��·�ɵ���ͼ�����ڽӶ������ͼ
					Rp->R.network = R.network;
					//�ڽӽڵ����·�ɱ�
					Rp->R.rlist.deleteRouterList();
					Rp->R.rlist.Make_routerlist(Rp->R.network, Rp->R.name);
					//���
					PushQ(q, Rp->R);
				}
				E = E->ep;
			}
		}
		//���ñ��
		ReserVisited(head);
		return true;
	}

	//�ݹ�ɾ�����е��ڽӶ���
	void _delete_power(Vert& v, Edge& e) {
		if (e == nullptr)
			return;
		_delete_power(v, e->ep);
		DeletePower(v->name, e->name);
		e = nullptr;
	}
};
//��ͨ�û���
//class user :private OSPF {
//public:
//	//�鿴ĳ·������·�ɱ�
//	using OSPF::printRouterlist;
//	//�鿴��A��B����СȨֵ·��
//	using OSPF::printMinPath;
//	//�鿴��������ͼ
//	using OSPF::printNetwork;
//};
//
////����Ա��
//class Administrator :public OSPF {
//
//};