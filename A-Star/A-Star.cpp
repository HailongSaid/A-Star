#include "A-Star.h"





// 交换两个元素  
//   
void AStar::swap(int idx1, int idx2)
{
	pAStarNode tmp = open_table[idx1];
	open_table[idx1] = open_table[idx2];
	open_table[idx2] = tmp;
}

// 堆调整  
//   
void AStar::adjust_heap(int /*i*/nIndex)
{
	int curr = nIndex;
	int child = curr * 2 + 1;   // 得到左孩子idx( 下标从0开始，所有做孩子是curr*2+1 )  
	int parent = (curr - 1) / 2;  // 得到双亲idx  

	if (nIndex < 0 || nIndex >= open_node_count)
	{
		return;
	}

	// 往下调整( 要比较左右孩子和cuur parent )  
	//   
	while (child < open_node_count)
	{
		// 小根堆是双亲值小于孩子值  
		//   
		if (child + 1 < open_node_count && open_table[child]->s_g + open_table[child]->s_h > open_table[child + 1]->s_g + open_table[child + 1]->s_h)
		{
			++child; // 判断左右孩子大小  
		}

		if (open_table[curr]->s_g + open_table[curr]->s_h <= open_table[child]->s_g + open_table[child]->s_h)
		{
			break;
		}
		else
		{
			swap(child, curr);            // 交换节点  
			curr = child;               // 再判断当前孩子节点  
			child = curr * 2 + 1;           // 再判断左孩子  
		}
	}

	if (curr != nIndex)
	{
		return;
	}

	// 往上调整( 只需要比较cuur child和parent )  
	//   
	while (curr != 0)
	{
		if (open_table[curr]->s_g + open_table[curr]->s_h >= open_table[parent]->s_g + open_table[parent]->s_h)
		{
			break;
		}
		else
		{
			swap(curr, parent);
			curr = parent;
			parent = (curr - 1) / 2;
		}
	}
}

// 判断邻居点是否可以进入open表  
//   
void AStar::insert_to_opentable(int x, int y, pAStarNode curr_node, pAStarNode end_node, int w)
{
	int i;

	if (map_maze[x][y].s_style != BARRIER)        // 不是障碍物  
	{
		if (!map_maze[x][y].s_is_in_closetable)   // 不在闭表中  
		{
			if (map_maze[x][y].s_is_in_opentable) // 在open表中  
			{
				// 需要判断是否是一条更优化的路径  
				//   
				if (map_maze[x][y].s_g > curr_node->s_g + w)    // 如果更优化  
				{
					map_maze[x][y].s_g = curr_node->s_g + w;
					map_maze[x][y].s_parent = curr_node;

					for (i = 0; i < open_node_count; ++i)
					{
						if (open_table[i]->s_x == map_maze[x][y].s_x && open_table[i]->s_y == map_maze[x][y].s_y)
						{
							break;
						}
					}

					adjust_heap(i);                   // 下面调整点  
				}
			}
			else                                    // 不在open中  
			{
				map_maze[x][y].s_g = curr_node->s_g + w;
				map_maze[x][y].s_h = abs(end_node->s_x - x) + abs(end_node->s_y - y);
				map_maze[x][y].s_parent = curr_node;
				map_maze[x][y].s_is_in_opentable = 1;
				open_table[open_node_count++] = &(map_maze[x][y]);
			}
		}
	}
}

// 查找邻居  
// 对上下左右8个邻居进行查找  
//    
void AStar::get_neighbors(pAStarNode curr_node, pAStarNode end_node)
{
	int x = curr_node->s_x;
	int y = curr_node->s_y;

	// 下面对于8个邻居进行处理！  
	//   
	if ((x + 1) >= 0 && (x + 1) < 10 && y >= 0 && y < 10)
	{
		insert_to_opentable(x + 1, y, curr_node, end_node, 10);
	}

	if ((x - 1) >= 0 && (x - 1) < 10 && y >= 0 && y < 10)
	{
		insert_to_opentable(x - 1, y, curr_node, end_node, 10);
	}

	if (x >= 0 && x < 10 && (y + 1) >= 0 && (y + 1) < 10)
	{
		insert_to_opentable(x, y + 1, curr_node, end_node, 10);
	}

	if (x >= 0 && x < 10 && (y - 1) >= 0 && (y - 1) < 10)
	{
		insert_to_opentable(x, y - 1, curr_node, end_node, 10);
	}

	if ((x + 1) >= 0 && (x + 1) < 10 && (y + 1) >= 0 && (y + 1) < 10)
	{
		insert_to_opentable(x + 1, y + 1, curr_node, end_node, 14);
	}

	if ((x + 1) >= 0 && (x + 1) < 10 && (y - 1) >= 0 && (y - 1) < 10)
	{
		insert_to_opentable(x + 1, y - 1, curr_node, end_node, 14);
	}

	if ((x - 1) >= 0 && (x - 1) < 10 && (y + 1) >= 0 && (y + 1) < 10)
	{
		insert_to_opentable(x - 1, y + 1, curr_node, end_node, 14);
	}

	if ((x - 1) >= 0 && (x - 1) < 10 && (y - 1) >= 0 && (y - 1) < 10)
	{
		insert_to_opentable(x - 1, y - 1, curr_node, end_node, 14);
	}
}

AStar::AStar(int maze[M][N], int m, int n)
{
	
	int       i, j, x;

	// 下面准备点  
	//   
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			map_maze[i][j].s_g = 0;
			map_maze[i][j].s_h = 0;
			map_maze[i][j].s_is_in_closetable = 0;
			map_maze[i][j].s_is_in_opentable = 0;
			map_maze[i][j].s_style = maze[i][j];
			map_maze[i][j].s_x = i;
			map_maze[i][j].s_y = j;
			map_maze[i][j].s_parent = NULL;

			if (map_maze[i][j].s_style == STARTNODE)  // 起点  
			{
				start_node = &(map_maze[i][j]);
			}
			else if (map_maze[i][j].s_style == ENDNODE)    // 终点  
			{
				end_node = &(map_maze[i][j]);
			}

			printf("%d ", maze[i][j]);
		}

		printf("\n");
	}
}

void AStar::findRouteUseAstar()
{
	// 地图数组的定义  
	//   

	AStarNode *curr_node;           // 当前点  
	int       is_found;         // 是否找到路径  
	

	// 下面使用A*算法得到路径  
	//    
	open_table[open_node_count++] = start_node;         // 起始点加入open表  

	start_node->s_is_in_opentable = 1;               // 加入open表  
	start_node->s_g = 0;
	start_node->s_h = abs(end_node->s_x - start_node->s_x) + abs(end_node->s_y - start_node->s_y);
	start_node->s_parent = NULL;

	if (start_node->s_x == end_node->s_x && start_node->s_y == end_node->s_y)
	{
		printf("起点==终点！\n");
		return ;
	}

	is_found = 0;

	while (1)
	{
		// for test  
		//   
		/*      for ( x = 0; x < open_node_count; ++x )
		{
		printf("(%d,%d):%d   ", open_table[x]->s_x, open_table[x]->s_y, open_table[x]->s_g+open_table[x]->s_h);
		}
		printf("\n\n");
		*/
		curr_node = open_table[0];      // open表的第一个点一定是f值最小的点(通过堆排序得到的)  
		open_table[0] = open_table[--open_node_count];  // 最后一个点放到第一个点，然后进行堆调整  
		adjust_heap(0);               // 调整堆  

		close_table[close_node_count++] = curr_node;    // 当前点加入close表  
		curr_node->s_is_in_closetable = 1;       // 已经在close表中了  

		if (curr_node->s_x == end_node->s_x && curr_node->s_y == end_node->s_y)// 终点在close中，结束  
		{
			is_found = 1;
			break;
		}

		get_neighbors(curr_node, end_node);           // 对邻居的处理  

		if (open_node_count == 0)             // 没有路径到达  
		{
			is_found = 0;
			break;
		}
	}

	if (is_found)
	{
		curr_node = end_node;

		while (curr_node)
		{
			path_stack[++top] = curr_node;
			curr_node = curr_node->s_parent;
		}

		while (top >= 0)        // 下面是输出路径看看~  
		{
			if (top > 0)
			{
				printf("(%d,%d)-->", path_stack[top]->s_x, path_stack[top--]->s_y);
			}
			else
			{
				printf("(%d,%d)", path_stack[top]->s_x, path_stack[top]->s_y);
				top--;
			}
		}
	}
	else
	{
		printf("么有找到路径");
	}

	puts("");
}