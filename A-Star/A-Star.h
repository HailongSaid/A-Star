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
	int s_x;    // 坐标(最终输出路径需要)  
	int s_y;
	int s_g;    // 起点到此点的距离( 由g和h可以得到f，此处f省略，f=g+h )  
	int s_h;    // 启发函数预测的此点到终点的距离  
	int s_style;// 结点类型：起始点，终点，障碍物  
	struct AStarNode * s_parent;    // 父节点  
	int s_is_in_closetable;     // 是否在close表中  
	int s_is_in_opentable;      // 是否在open表中  
}AStarNode, *pAStarNode;

class AStar
{
public:
	AStar(int maze[M][N], int m, int n);
	void swap(int idx1, int idx2);

	void adjust_heap(int nIndex);

	// 判断邻居点是否可以进入open表  
	void insert_to_opentable(int x, int y, pAStarNode curr_node, pAStarNode end_node, int w);

	// 查找邻居  
	// 对上下左右8个邻居进行查找  
	void get_neighbors(pAStarNode curr_node, pAStarNode end_node);


	void findRouteUseAstar();
private:
	AStarNode  map_maze[10][10];        // 结点数组  
	pAStarNode open_table[100];     // open表  
	pAStarNode close_table[100];        // close表  
	int   open_node_count;  // open表中节点数量  
	int    close_node_count;  // close表中结点数量  
	pAStarNode path_stack[100];     // 保存路径的栈  
	int        top = -1;            // 栈顶  

	AStarNode *start_node;          // 起始点  
	AStarNode *end_node;            // 结束点  
};






#endif