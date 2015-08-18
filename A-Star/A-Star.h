#ifndef  A_Star_h
#define  A_Star_h

#include <stdio.h>  
#include <stdlib.h>  

#define M 10
#define N 10

#define STARTNODE   1  
#define ENDNODE     2  
#define BARRIER     3  

typedef struct AStarNode
{
	int s_x;    // ����(�������·����Ҫ)  
	int s_y;
	int s_g;    // ��㵽�˵�ľ���( ��g��h���Եõ�f���˴�fʡ�ԣ�f=g+h )  
	int s_h;    // ��������Ԥ��Ĵ˵㵽�յ�ľ���  
	int s_style;// ������ͣ���ʼ�㣬�յ㣬�ϰ���  
	struct AStarNode * s_parent;    // ���ڵ�  
	int s_is_in_closetable;     // �Ƿ���close����  
	int s_is_in_opentable;      // �Ƿ���open����  
}AStarNode, *pAStarNode;

class AStar
{
public:
	AStar(int maze[M][N], int m, int n);
	void swap(int idx1, int idx2);

	void adjust_heap(int nIndex);

	// �ж��ھӵ��Ƿ���Խ���open��  
	void insert_to_opentable(int x, int y, pAStarNode curr_node, pAStarNode end_node, int w);

	// �����ھ�  
	// ����������8���ھӽ��в���  
	void get_neighbors(pAStarNode curr_node, pAStarNode end_node);


	void findRouteUseAstar();
private:
	AStarNode  map_maze[10][10];        // �������  
	pAStarNode open_table[100];     // open��  
	pAStarNode close_table[100];        // close��  
	int   open_node_count;  // open���нڵ�����  
	int    close_node_count;  // close���н������  
	pAStarNode path_stack[100];     // ����·����ջ  
	int        top = -1;            // ջ��  

	AStarNode *start_node;          // ��ʼ��  
	AStarNode *end_node;            // ������  
};






#endif