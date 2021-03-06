#include<iostream>
#include<string>
using namespace std;

class candidateNode {
public:
	candidateNode() { next = NULL; };
	candidateNode(int examNum, string name, string sex, int age, int examCourse);
	friend istream& operator>>(istream & in, candidateNode * one);//将考生信息输入该节点
	candidateNode * next;//指向下一个考生
	int examNum;//考号
	string name;//考生名字
	string sex;//考生性别
	int age;//考生年龄
	string examCourse;//报考类别
	
};
class mySystem {
private:
	candidateNode * first;//链表的头结点
	int totalNum;//系统中所有的考生人数
public:
	//初始化考试报名系统
	mySystem();
	mySystem(int totalNum) ;
	//在指定位置插入考生
	void insert(int position);
	//获得position位置的考生
	candidateNode * locate(int position);
	//统计系统中的所有考生，并显示
	void display();
	//删除考号为examNum的考生
	void cut(int examNum);
	//根据考号查找考生
	candidateNode * search(int examNum);
	//修改考生信息
	void modify(candidateNode * candidate);

};
candidateNode::candidateNode(int examNum, string name, string sex, int age, int examCourse)
{
	this->age = age;
	this->name = name;
	this->sex = sex;
	this->examNum = examNum;
	this->examCourse = examCourse;
}
istream& operator>>(istream & in, candidateNode * one)
{
	in >> one->examNum >> one->name >> one->sex >> one->age >> one->examCourse;
	return in;
}
candidateNode * mySystem::locate(int position)
{
	if (position < 0)
		return NULL;
	candidateNode * tempNode1 = first;
	candidateNode * tempNode2;
	for (int i = 1; i <= position; i++)
	{
		if (i == position)
			return tempNode1;
		if(tempNode1!=NULL)
			tempNode1 =tempNode1->next;
		else
		{
			cout << "location is out of range"<<endl;
			return NULL;
		}
	}
}
void mySystem::insert(int position)
{
	candidateNode * newCandidate = new candidateNode;
	cin >>newCandidate;//读入该考生的信息
	if (position == 1)
	{
		//插入第一位
		newCandidate->next = first;
		first = newCandidate;
	}
	else
	{
		//找到插入位置前一个位置考生的节点
		candidateNode * targetNode = locate(position - 1);
		//不存在前一个考生，则该插入位置有误
		if (targetNode == NULL)
			cout << "insert position is wrong"<<endl;
		else
		{
			//插入位置在最后
			if (targetNode->next == NULL)
				targetNode->next = newCandidate;
			else
			{
				//在中间位置插入
				candidateNode * tempNode = targetNode->next;
				targetNode->next = newCandidate;
				newCandidate->next = tempNode;
			}
		}
	}
}
mySystem::mySystem() {
	this->totalNum = 0;
	first = NULL;
}
mySystem::mySystem(int totalNum)
{
	this->totalNum = totalNum;
	for (int i = 0; i < totalNum; i++)
	{
		if (i == 0)
		{
			first = new candidateNode;
			cin >> first;
		}
		else
		{
			insert(i+1);
		}
	}
}
void mySystem::display()
{
	if (first == NULL)
		cout << "no candidate"<<endl;
	else
	{
		cout <<endl<< "考号	" << "姓名	" << "性别	"<<"年龄	" << "报考类别	" << endl;
		candidateNode * tempNode = first;
		while (tempNode != NULL)
		{
			cout << tempNode->examNum << "	" << tempNode->name << "	" <<tempNode->sex
				<< "	"<<tempNode->age << "	" << tempNode->examCourse << endl;
			tempNode = tempNode->next;
		}
	}
}
void mySystem::cut(int examNum)
{
	candidateNode * tempNode = first;
	candidateNode * aheadNode = first;
	candidateNode * targetNode;
	while (tempNode != NULL)
	{
		if (tempNode->examNum == examNum)
		{
			targetNode = tempNode;
			break;
		}
		else
		{
			aheadNode = tempNode;
			tempNode = tempNode->next;
		}
	}
	if (targetNode != NULL){
		if (targetNode == first){
			//删除第一个考生
			if (first->next == NULL){//无下一个考生
				cout << "你删除的考生信息是：" << targetNode->examNum << "	" << targetNode->name << "	" << targetNode->sex
					<< "	" << targetNode->age << "	" << targetNode->examCourse << endl;
				delete first;
				first = NULL;
			}
			else{//有下一个考生
				cout << "你删除的考生信息是：" << targetNode->examNum << "	" << targetNode->name << "	" << targetNode->sex
					<< "	" << targetNode->age << "	" << targetNode->examCourse << endl;
				candidateNode * temp = first->next;
				delete first;
				first = temp;
			}
		}
		else{
			//删除最后一个考生
			if (targetNode->next == NULL){
				aheadNode->next = NULL;
				cout << "你删除的考生信息是：" << targetNode->examNum << "	" << targetNode->name << "	" << targetNode->sex
					<< "	" << targetNode->age << "	" << targetNode->examCourse << endl;
				delete targetNode;
			}
			else{
				//删除中间位置的考生
				aheadNode->next = targetNode->next;
				cout <<"你删除的考生信息是："<< targetNode->examNum << "	" << targetNode->name << "	" << targetNode->sex
					<< "	" << targetNode->age << "	" << targetNode->examCourse << endl;
				delete targetNode;
			}
		}
	}
	else
		cout << "this examNum does exist in the system" << endl;
}
candidateNode * mySystem::search(int examNum)
{
	candidateNode * tempNode = first;
	if (tempNode == NULL)
		return NULL;
	while (tempNode != NULL)
	{
		if (tempNode->examNum == examNum)
			return tempNode;
		else
			tempNode = tempNode->next;
	}
	return NULL;
}
void mySystem::modify(candidateNode * candidate)
{
	cout << "请输入该为考生修改后的信息(依次输入考号、姓名、性别、年龄、报考类别)：";
	cin >> candidate;
}

int main()
{
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：";
	int totalNum;
	cin >> totalNum;
	while (totalNum <= 0) {
		cout << "输入的考生人数不对" << endl;
		cout << "请重新输入考生人数：";
		cin >> totalNum;

	}
	cout << "请依次输入考生的考号、姓名、性别、年龄、报考类别"<<endl;
	mySystem * examSystem =new mySystem(totalNum);
	examSystem->display();
	cout << "选择你要进行的操作：（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl<<endl;
	cout << "选择你要进行的操作：";
	int command;
	cin >> command;
	int endMark = 0;
	candidateNode * result;
	while (command != 0)
	{
		switch (command) {
		case 1:
			cout << "请输入你要插入的考生位置：" << endl;
			int position;
			cin >> position;
			cout << "请依次输入要插入的考生的考号、姓名、性别、年龄、报考类别" << endl;
			examSystem->insert(position);
			examSystem->display();
			break;
		case 2:
			cout << "请输入要删除的考号";
			int examNum;
			cin >> examNum;
			result = examSystem->search(examNum);
			if (result == NULL)
				cout << "this examNum does exist in the system" << endl;
			else
			{
				examSystem->cut(examNum);
				examSystem->display();
			}
			break;
		case 3:
			cout << "请输入要查找的考生考号：";
			cin >> examNum;
			result= examSystem->search(examNum);
			if (result == NULL)
				cout << "this examNum does exist in the system"<<endl;
			else
			{
				cout << "考号	" << "姓名	" << "性别	" << "年龄	" << "报考类别	" << endl;
				cout<< result->examNum << "	" << result->name << "	" << result->sex
					<< "	" << result->age << "	" << result->examCourse << endl;
			}
			break;
		case 4:
			cout << "请输入要修改的考生考号：";
			cin >> examNum;
			result = examSystem->search(examNum);
			if(result==NULL)
				cout << "this examNum does exist in the system" << endl;
			else
			{
				examSystem->modify(result);
				examSystem->display();
			}
			break;
		case 5:
			examSystem->display();
			break;
		case 0:
			endMark = 1;
			break;
		default:
			cout << "your command is wrong!" << endl;
		}
		cout << "选择你要进行的操作：";
		cin >> command;
	}
	system("pause");


}