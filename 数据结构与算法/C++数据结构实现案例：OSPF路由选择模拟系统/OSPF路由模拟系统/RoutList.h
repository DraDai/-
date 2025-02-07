#pragma once
#include"Network.h"
struct RNode {
	string name;
	string NextJump;
	RNode* next;
};
typedef RNode* RLink;//·�ɱ�ڵ�

struct PNode {
	string name;
	int dist;
	string parent;
	bool flag;
	PNode* next;
};
typedef PNode* Path;	//·���ṹ�����ڹ���·�ɱ�

class RoutList
{
public:
	RLink routerlist;	//·�ɱ�

	//�޲ι��캯������ʼ��·�ɱ�
	RoutList() : routerlist(new RNode{"", "", nullptr}) {}

	//����·�����ĵ�ַ�Լ�������������ͼ����·�ɱ�
	void Make_routerlist(Graph& G, const string& name)
	{
		routerlist->name = name;
		//ͨ����������ͼ��·������ַ��ʼ��·���ṹ��
		Path P = CreatePath(G, name);
		//�Ͻ�˹��������Path��
		Dijkstra(P, G);
		//ͨ��Path����·�ɱ�
		_make_routers(P);
	}

	//����·�ɱ�
	string FindRoutlist(const string& to) {
		RLink RL = routerlist->next;
		while (RL) {
			if (RL->name == to) {
				return RL->NextJump;
			}
			RL = RL->next;
		}
		return "";
	}

	//���·�ɱ�ֻ��ͷ�ڵ�
	void deleteRouterList()
	{
		//�����������
		_delete_routerlist(routerlist->next);
	}

	//���·�ɱ�
	void printRouters()
	{
		RLink t = routerlist->next;
		cout << routerlist->name << " ��·�ɱ�:" << endl;
		while (t)
		{
			cout << "To ---> " << t->name << "  NextJump: " << FindRouters(t->name) << endl;
			t = t->next;
		}
	}

private:
	//ͨ����������ͼ��ʼ��·���ṹ��
	Path CreatePath(Graph& G, const string& name)
	{
		//��ʼ��ͷ�ڵ�
		Path P = new PNode{};

		P->name = name;
		P->dist = 0;
		P->flag = true;
		P->parent = "";
		P->next = nullptr;

		Vert t = G.head->vp;
		while (t)
		{
			//���뱾��·������ͨ���Ҳ��Ǳ���·������·��������Path
			if (t != G.FindV(name) && G.IsConnectivity(name, t->name))
			{
				Path pp = new PNode{};

				//Ԫ�ظ�ֵ
				pp->name = t->name;
				pp->dist = G.Getpower(name, t->name);
				pp->flag = false;
				pp->parent = name;

				//ͷ�巨����P����
				pp->next = P->next;
				P->next = pp;
			}
			t = t->vp;
		}
		return P;
	}

	//�Ͻ�˹����Ѱ�ҵ�Դ���·��
	void Dijkstra(Path P, Graph& G)
	{
		//ͼ���뱾��·������ͨ��·����������ǣ����˳�
		if (IsFullFlag(P))
			return;

		//��δ����ǵ��뱾��·����dist��С��·��������������
		Path minp = FindMinPath(P);

		//����dist
		UpDist(P, minp, G);
		Dijkstra(P, G);
	}

	//�жϱ���Ƿ�����
	bool IsFullFlag(Path P)
	{
		Path pp = P->next;
		while (pp)
		{
			//��δ����ǵĽڵ㷵�ر��δ��
			if (!pp->flag)
			{
				return false;
			}
			
			//�����һ���ڵ�
			pp = pp->next;
		}
		return true;
	}

	//����Сdistδ��Ƕ���
	Path FindMinPath(Path P)
	{
		Path pp = P->next;
		int min = INF;
		Path minp = pp;

		//ѭ���ҵ���Сdistֵ
		while (pp)
		{
			//����ýڵ�δ�������dist��minС����dist����min,���ڵ�ָ�븳��minp
			if (!pp->flag && pp->dist < min)
			{
				min = pp->dist;
				minp = pp;
			}
			pp = pp->next;
		}

		//���ҵ�����Сdist�ڵ���ϱ��
		minp->flag = true;
		//��������dist�ڵ�
		return minp;
	}

	//����dist
	void UpDist(Path P, Path minp, Graph& G)
	{
		Path p = P->next;

		//ѭ������dist
		while (p)
			{
			//���p�ڵ�δ����ǣ���������Сdist�ڵ��Ȩֵ����Сdist���С���Լ���dist��������Լ���dist
			if (!p->flag && p->dist > G.Getpower(p->name, minp->name) + minp->dist)
			{
				p->dist = G.Getpower(p->name, minp->name) + minp->dist;
				//�����Լ���parentΪ��Сdist�ڵ��ַ
				p->parent = minp->name;

			}
			p = p->next;
		}
	}
	//ͨ��Path����·�ɱ�,������ɾ��Path��
	void _make_routers(Path P)
	{
		Path p = P->next;
		//ѭ������Path����·�ɱ�
		while (p)
		{
			RLink r = new RNode{};
			//��ֵ
			r->name = p->name;
			//�ҵ�����·������p�ڵ����һ��
			r->NextJump = NextJump(P, p);
			//ͷ�巨��r�ڵ����·�ɱ�
			r->next = routerlist->next;
			routerlist->next = r;
			//��һ��path�ڵ�
			p = p->next;
		}
		//ɾ��Path��
		deletePath(P);
	}

	//�ҵ�����·������to�ڵ����һ��
	string NextJump(Path P, Path to)
	{
		//��to�ڵ��parent���Ǳ���·������ַʱ����parent��ָ�븳��to
		while (to->parent != P->name)
		{
			//�ҵ�parent��P���е�λ��
			to = GetPath(P, to->parent);
		}
		//����to
		return to->name;
	}

	//�ҵ�str��P���е�λ��
	Path GetPath(Path P, string str)
	{
		Path p = P;
		while (p)
		{
			if (p->name == str)
			{
				return p;
			}
			p = p->next;
		}
		return nullptr;
	}
	
	//ɾ��Path��
	void deletePath(Path P)
	{
		if (P == nullptr)
			return;
		//�ݹ�ɾ������Ľڵ�
		deletePath(P->next);
		//ɾ���������
		delete P;
		//��p�ÿ�
		P = nullptr;
	}

	string FindRouters(string to)
	{
		RLink t = routerlist->next;
		while (t)
		{
			if (t->name == to)
				return t->NextJump;
			t = t->next;
		}
	}
	
	//�������·�ɱ���
	void _delete_routerlist(RLink& Rp)
	{
		if (Rp == nullptr)
			return;
		_delete_routerlist(Rp->next);
		delete Rp;
		Rp = nullptr;
	}
};

