#pragma once
#include<string>
#include<iostream>
using namespace std;
const int INF = 65505;
//����ṹ
struct ENode {
	string name;
	int power;
	ENode* ep;
};
typedef ENode* Edge;
struct VNode {
	string name;
	//ָ����һ����ָ��
	VNode* vp;
	Edge ep;
	//���
	bool visited;
	//��ʼ�����
	VNode() :visited(false) {};
};
typedef VNode* Vert;
//Ȩֵ�ṹ

//��Ȩ�رߵĽṹ
struct WeightEdge {
	string from;
	string to;
	int weight;

};

class Graph{
public:
	Vert head;	//�ڽӱ�
	int Vsum;
	int Esum;	
	//Ĭ�Ϲ��캯����ʼ����������ͼ
	Graph() :head(new VNode{}), Vsum(0), Esum(0) {
		head->name = "";
		head->ep = nullptr;
		head->vp = nullptr;
	}
	//���ƹ�����������ͼ,���Զ����������,���������ظ�ֵ�����ʵ�����
	Graph& operator = (const Graph& other)
	{ 
		//�������Ҹ�ֵ
		if (this == &other)
		{
			return *this;
		}
		//ɾ��������Դ
		deleteGraph(head->vp);

		//�������
		copyV(other.head->vp, head->vp);
		Vsum = other.Vsum;
		Esum = other.Esum;

		return *this;
	}

	//�������������ͷ��������Դ
	~Graph() {
		deleteGraph(head->vp);
		delete head;
	}

	//��������������ͼ
	void InitGraph(const Graph& other)
	{
		//���ݴ�����������������ͼ�������Լ�ȱ�ٵ���Ϣ
		Vert otherV = other.head->vp;
		//���䲻���ڵĶ�����Ϣ
		while (otherV != nullptr)
		{
			if (!FindV(otherV->name))
				AddV(otherV->name);
			//������һ������
			otherV = otherV->vp;
		}

		//�������Ϣ
		otherV = other.head->vp;
		//�������ж���
		while (otherV != nullptr)
		{
			Edge otherE = otherV->ep;
			//����other��������б�
			while (otherE != nullptr)
			{
				if (!FindE(otherV->name, otherE->name))
					AddEdge(otherV->name, otherE->name, otherE->power);
				//����������һ����
				otherE = otherE->ep;
			}
			//����������һ������
			otherV = otherV->vp;
		}
	}

	//�Ҷ���
	Vert FindV(string V)
	{
		Vert p = head;
		while (p->vp)
		{
			p = p->vp;
			if (p->name == V)
				return p;
		}
		return nullptr;
	}


	//���ڽӵ�
	Edge FindE(string from, string to)
	{
		Vert p = FindV(from);
		Edge Ep;
		Ep = p->ep;
		while (Ep)
		{
			if (Ep->name == to)
				return Ep;
			Ep = Ep->ep;
		}
		return nullptr;
	}

	//�ж�ĳ�����Ƿ����ڽӶ���
	bool IsEmptyE(string name)
	{
		Vert V = FindV(name);
		if (V->ep)
			return false;
		return true;
	}
	
	//��Ӷ���
	void AddV(string str)
	{

		Vert v = FindV(str);
		if (v)
			return;
		v = new VNode;	//β�巨
		v->name = str;
		v->ep = nullptr;
		v->vp = head->vp;
		head->vp = v;
		Vsum++;
	}
	
	//�޸�ͼȨֵ
	bool AddEdge(string From, string To, int power)
	{
		if (!_AddEdge(From, To, power))
			return false;
		_AddEdge(To, From, power);
		Esum++;
		return true;
	}
	
	//ɾ��ͼȨֵ
	void DeleteE(string from, string to)
	{
		_DeleteE(from, to);
		_DeleteE(to, from);
		Esum--;
	}
	//ɾ��ĳ��������ڽӶ���(Ҳ�������б�)
	void DeleteNE(string from)
	{
		Vert p = FindV(from);
		if (!p)
			return;
		if (!p->ep)
			return;
		Edge t = p->ep;
		_delete_ne(p, t);
		p->ep = nullptr;
	}

	//ɾ��ͼ����
	void DeleteV(string str)
	{
		if (!FindV(str))
			return;
		DeleteNE(str);
		Vert p = head;
		while (p->vp)
		{
			if (p->vp->name == str)
			{
				Vert t = p->vp;
				p->vp = t->vp;
				delete t;
				Vsum--;
				return;
			}
			p = p->vp;
		}
	}
	
	//ɾ����ĳ·��������ͨ�����ж���
	void DeleteAllDisconnect(string name)
	{
		if (!FindV(name))
			return;
		Vert V = FindV(name);
		Vert P = head->vp;
		while (P != nullptr)
		{
			if (IsConnectivity(name, P->name))
				P = P->vp;
			else
			{
				Vert temp = P;
				P = P->vp;
				DeleteV(temp->name);
			}
		}
	}

	//����Ȩֵ
	int Getpower(string from, string to)
	{
		Edge t = FindE(from, to);
		if (t)
			return t->power;
		return INF;
	}

	//�ж���ͨ��
	bool IsConnectivity(const string& from, const string& to)
	{
		if (!FindV(from) || !FindV(to))
			return false;
		//�ҵ�from��λ��
		Vert V = FindV(from);
		if (V->name == to)
			return true;
		//���ñ��
		resetVisited();
		//������������ж���ͨ��
		return dfs(from, to);
	}

	//�ж�ͼ�Ƿ�Ϊ��
	bool IsEmptyGraph()
	{
		if (head->vp == nullptr)
			return true;
		return false;
	}
	//�������
	void printV()
	{
		Vert p = head;
		if (!head->vp)
			cout << "ͼΪ��" << endl;
		while (p->vp)
		{
			p = p->vp;
			cout << p->name << " ";
		}
		cout << endl;
	}
	//���ͼ��
	void printG()
	{
		if (IsEmptyGraph())
			cout << "ͼΪ��" << endl;
		Vert p = head;
		while (p->vp)
		{
			p = p->vp;
			cout << p->name;
			Edge t = p->ep;
			while (t)
			{
				cout <<"---->" << t->name;
				t = t->ep;
			}
			cout << endl;
		}
	}
	//���Ȩֵ
	void printP(string from, string to)
	{
		int n = Getpower(from, to);
		if (n == INF)
		{
			cout << "���������Ȩֵ" << endl;
			return;
		}
		cout << n << endl;
	}
	//����ڽӶ���
	void printNE(string from)
	{
		Vert p = FindV(from);
		if (!p)
			return;
			Edge t = p->ep;
		while (t)
		{
			cout << t->name << " ";
			t = t->ep;
		}
		cout << endl;
	}

	//��Ȩֵ�������򲢴�ӡ
	void SortPrintEdge() {
		const int MAX_EDGE = 1000;	//����ߵ������
		WeightEdge edges[MAX_EDGE];
		int size = 0;
		//��ȡ���б�
		GetAllEdges(edges, size);

		//ʹ�ÿ�������
		QuickSortEdges(edges, 0, size - 1);

		cout << "������·״����\n";
		if (size > 0) {
			cout << edges[0].from << " -- " << edges[0].to << "    " << edges[0].weight << endl;
		}
		
		for (int i = 1; i < size; i++) {
			if (edges[i].from != edges[i - 1].from || edges[i].to != edges[i - 1].to || edges[i].weight != edges[i - 1].weight)
				cout << edges[i].from << " -- " << edges[i].to << "    " << edges[i].weight << std::endl;
		}
	}
private:
	//�ݹ��������
	void copyV(Vert otherV, Vert& V)
	{
		if (otherV == nullptr)
		{
			V = nullptr;
			return;
		}
		//���Ƶ�ǰ����
		V = new VNode;
		V->name = otherV->name;
		V->ep = nullptr;
			
		//�ݹ鸴���ڽӱ�
		copyE(otherV->ep, V->ep);

		//�ݹ鸴����һ����
		copyV(otherV->vp, V->vp);
	}

	//�ݹ������
	void copyE(Edge otherE, Edge& E)
	{
		if (otherE == nullptr)
		{
			E = nullptr;
			return;
		}

		//���Ƶ�ǰ��
		E = new ENode;
		E->name = otherE->name;
		E->power = otherE->power;
		E->ep = nullptr;

		//�ݹ鸴����һ��
		copyE(otherE->ep, E->ep);
	}

	//�ͷŶ���ͱߵ���Դ
	void deleteGraph(Vert& V)
	{
		if (V == nullptr)
			return;

		//�ݹ��ͷ��ڽӱ�
		deleteE(V->ep);

		//�ݹ��ͷ���һ����
		deleteGraph(V->vp);
	
		//�ͷŵ�ǰ����
		delete V;
		V = nullptr;
	}

	//�ݹ��ͷűߵ���Դ
	void deleteE(Edge& E)
	{
		if (E == nullptr)
			return;

		//�ݹ��ͷ���һ��
		if(E->ep != nullptr)
			deleteE(E->ep);
		//�ͷŵ�ǰ��
		delete E;
		E = nullptr;
	}



	//�޸�ͼȨֵ���ú���
	bool _AddEdge(string From, string To, int power)
	{
		Vert p = FindV(From);
		if (!p)
			return false;
		Edge t = FindE(From, To);
		if (!p)
			return false;
		if (t)
		{
			t->power = power;
			return true;
		}
		t = new ENode;		//β�巨
		t->name = To;
		t->power = power;
		t->ep = p->ep;
		p->ep = t;
		return true;
	}

	//ɾ��ͼȨֵ���ú���
	void _DeleteE(const string& from, string to)
	{
		Vert p = FindV(from);
		if (!p)
			return;
		Edge t = p->ep;
		if (!t)
		{
			return;
		}
		if (t->name == to)
		{
			p->ep = t->ep;
			delete t;
			return;
		}
		while (t->ep)
		{
			if (t->ep->name == to)
			{
				Edge T = t->ep;
				t->ep = T->ep;
				delete T;
				Esum--;
				return;
			}
			t = t->ep;
		}
	}

	//�����ж���ͨ��
	bool dfs(const string& from, const string& to)
	{
		//���ҵ�ǰ����
		Vert V = FindV(from);
		
		if (V && V->visited)
			return false;

		if (V)
			V->visited = true;

		if (from == to)
			return true;

		Edge E = V ? V->ep : nullptr;

		while (E) {
			if (dfs(E->name, to))
				return true;
			E = E->ep;
		}

		return false;
	}

	//���ñ��
	void resetVisited() {
		Vert V = head->vp;
		while (V) {
			V->visited = false;
			V = V->vp;
		}
	}

	//�ݹ�ɾ�������ڽӱ�
	void _delete_ne(const Vert& v, Edge& e) {
		if (e == nullptr)
			return;
		_delete_ne(v, e->ep);
		DeleteE(v->name, e->name);
		e = nullptr;
	}

	//��ȡͼ�����б�
	void GetAllEdges(WeightEdge* edges, int& size) {
		size = 0;
		Vert p = head;
		while (p->vp) {
			p = p->vp;
			Edge t = p->ep;
			while (t) {
				edges[size].from = p->name;
				edges[size].to = t->name;
				edges[size].weight = t->power;
				size++;
				t = t->ep;
			}
		}
	}

	//��������
	void QuickSortEdges(WeightEdge* edges, int low, int high) {
		if (low < high) {
			int pivot = low;
			int i = low + 1;
			int j = high;

			while (i <= j) {
				if (edges[i].weight < edges[pivot].weight)
					i++;
				else if (edges[j].weight > edges[pivot].weight)
					j--;
				else
				{
					swap(edges[i], edges[j]);
					i++;
					j--;
				}
			}

			swap(edges[pivot], edges[j]);

			QuickSortEdges(edges, low, j - 1);
			QuickSortEdges(edges, j + 1, high);
		}
	}
};