#pragma once
#include "OSPF.h"
//�û��ṹ
struct UNode {
    string username;    //�û���
    string account;     //�˺�
    string password;    //����
    UNode* left;
    UNode* right;
}; 

//����Ա�ṹ
struct AdNode {
    string name;
    string account;
    string password;
};
typedef UNode* UsersBST;
class User :
    public OSPF
{
public:
    UsersBST head;  //�û�������

    //��ʼ���û�������
   User() {
        ifstream inputFile("./user.txt",ios::in | ios::binary);

        if (!inputFile.is_open()) {
            cerr << "�ļ���ʧ�ܣ�" << "user.txt" << endl;
            return;
        }

        string name, account, password;
        while (inputFile >> name >> account >> password) {
            InsertUser(name, account, password);
        }
        inputFile.close();
   }

   //�����û���Ϣ���ļ���
   void SaveUserBST() {
       ofstream outputFile("user.txt");

       if (!outputFile.is_open()) {
           cerr << "�ļ���ʧ�ܣ�" << "user.txt" << endl;
           return;
       }

       _save_userbst(head, outputFile);
       outputFile.close();
       cout << "�û���Ϣ����ɹ���" << endl;
    }
    //�����û�(�˺�)
    void InsertUser(const string& username, const string& account, const string& password)
    {
        _insert_user(head, username, account, password);
    }

    //�����û�(�˺�)
    UsersBST FindUser(const string& account) {
        return _find_user(head, account);
    }

    //����û�����������룩
    void printUsers() {
        cout << "�û���Ϣ��:" << endl;
        cout << "�û���\t\t�˺�" << endl;
        _print_users(head);
    }

    //ɾ���û�(�˺�)
    void DeleteUser(const string& account) {
         _delete_user(head, account);
    }
    
    //�޸��û�����
    bool ModifyPassword(const string& account, string& password, string& new_password) {
        UsersBST UBT = FindUser(account);
        if (UBT && UBT->password == password) {
            UBT->password = new_password;
            return true;
        }
        return false;
    }
private:

    //�ݹ�������������(�˺�)
    UsersBST _insert_user(UsersBST& Head, const string& username, const string& account, const string& password) {
        if (!Head) {
            //�����½ڵ�
            Head = new UNode{};
            Head->username = username;
            Head->account = account;
            Head->password = password;
            Head->left = Head->right = nullptr;
        }
        else if (account < Head->account) {
            //����������
            Head->left = _insert_user(Head->left, username, account, password);
        }
        else if (account > Head->account) {
            //����������
            Head->right = _insert_user(Head->right, username, account, password);
        }
        return Head;
    }

    //�ݹ�����û�
    UsersBST _find_user(const UsersBST& Head, const string& account) {
        if (!Head)
            return nullptr;
        if (Head->account == account)
            return Head;
        else if (Head->account > account) {
            //����������
            return _find_user(Head->left, account);
        }
        else if (Head->account < account) {
            //����������
           return  _find_user(Head->right, account);
        }
    }

    //�ݹ�ɾ���û�
    UsersBST _delete_user(UsersBST& Head,const string& account) {
        if (!Head)
            return nullptr;
        if (account < Head->account) {
            //ɾ��������
            Head->left = _delete_user(Head->left, account);
        }
        else if (account > Head->account) {
            //ɾ��������
            Head->right = _delete_user(Head->right, account);
        }
        else {
            //�ҵ���Ҫɾ���Ķ���
            //�������������
            if (Head->left && Head->right) {
                //����������С�Ľڵ��滻
                UsersBST MinNode = FindMinUBST(Head->right);
                Head->account = MinNode->account;
                Head->password = MinNode->password;
                Head->username = MinNode->username;
                //ɾ����С�ڵ�
                Head->right = _delete_user(Head->right, MinNode->account);
            }
            else {
                UsersBST temp = Head;
                if (Head->left)
                    Head = Head->left;
                else
                    Head = Head->right;
                delete temp;
            }
        }
        return Head;
    }

    //������������С����
    UsersBST FindMinUBST(const UsersBST& Head) {
        if (!Head)
            return nullptr;
        UsersBST current = Head;
        while (current->left)
            current = current->left;
        return current;
    }

    //�ݹ�����û���Ϣ
    void _print_users(const UsersBST& Head) {
        if (Head) {
            _print_users(Head->left);
            cout << Head->username << "\t\t" << Head->account << endl;
            _print_users(Head->right);
        }
    }

    //�ݹ鱣���ļ�
    void _save_userbst(const UsersBST& Head, ofstream& outputFile) {
        if (Head) {
            _save_userbst(Head->left, outputFile);
            outputFile << Head->username << " " << Head->account << " " << Head->password << endl;
            _save_userbst(Head->right, outputFile);
        }
    }
};

class Ad :
    public User
{
public:
    AdNode* Adarray = new AdNode[20];

    Ad() {
        ifstream inputFile("./administrator.txt");

        if (!inputFile.is_open()) {
            cerr << "�ļ���ʧ�ܣ�" << "administrator.txt" << endl;
            return;
        }

        string name, account, password;
        int i = 0;
        while (inputFile >> name >> account >> password) {
            AdNode ad;
            ad.name = name;
            ad.account = account;
            ad.password = password;
            Adarray[i] = ad;
            i++;
        }
        inputFile.close();
    }

    //���ҹ���Ա
    int FindAd(const string& account) {
        int i = 0;
        while (i < 20 && Adarray[i].account != account) {
            i++;
        }
        if (i == 20)
            return -1;
        return i;
    }
};

