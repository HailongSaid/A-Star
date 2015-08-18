#include "A-Star.h"





// ��������Ԫ��  
//   
void AStar::swap(int idx1, int idx2)
{
	pAStarNode tmp = open_table[idx1];
	open_table[idx1] = open_table[idx2];
	open_table[idx2] = tmp;
}

// �ѵ���  
//   
void AStar::adjust_heap(int /*i*/nIndex)
{
	int curr = nIndex;
	int child = curr * 2 + 1;   // �õ�����idx( �±��0��ʼ��������������curr*2+1 )  
	int parent = (curr - 1) / 2;  // �õ�˫��idx  

	if (nIndex < 0 || nIndex >= open_node_count)
	{
		return;
	}

	// ���µ���( Ҫ�Ƚ����Һ��Ӻ�cuur parent )  
	//   
	while (child < open_node_count)
	{
		// С������˫��ֵС�ں���ֵ  
		//   
		if (child + 1 < open_node_count && open_table[child]->s_g + open_table[child]->s_h > open_table[child + 1]->s_g + open_table[child + 1]->s_h)
		{
			++child; // �ж����Һ��Ӵ�С  
		}

		if (open_table[curr]->s_g + open_table[curr]->s_h <= open_table[child]->s_g + open_table[child]->s_h)
		{
			break;
		}
		else
		{
			swap(child, curr);            // �����ڵ�  
			curr = child;               // ���жϵ�ǰ���ӽڵ�  
			child = curr * 2 + 1;           // ���ж�����  
		}
	}

	if (curr != nIndex)
	{
		return;
	}

	// ���ϵ���( ֻ��Ҫ�Ƚ�cuur child��parent )  
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

// �ж��ھӵ��Ƿ���Խ���open��  
//   
void AStar::insert_to_opentable(int x, int y, pAStarNode curr_node, pAStarNode end_node, int w)
{
	int i;

	if (map_maze[x][y].s_style != BARRIER)        // �����ϰ���  
	{
		if (!map_maze[x][y].s_is_in_closetable)   // ���ڱձ���  
		{
			if (map_maze[x][y].s_is_in_opentable) // ��open����  
			{
				// ��Ҫ�ж��Ƿ���һ�����Ż���·��  
				//   
				if (map_maze[x][y].s_g > curr_node->s_g + w)    // ������Ż�  
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

					adjust_heap(i);                   // ���������  
				}
			}
			else                                    // ����open��  
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

// �����ھ�  
// ����������8���ھӽ��в���  
//    
void AStar::get_neighbors(pAStarNode curr_node, pAStarNode end_node)
{
	int x = curr_node->s_x;
	int y = curr_node->s_y;

	// �������8���ھӽ��д���  
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

	// ����׼����  
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

			if (map_maze[i][j].s_style == STARTNODE)  // ���  
			{
				start_node = &(map_maze[i][j]);
			}
			else if (map_maze[i][j].s_style == ENDNODE)    // �յ�  
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
	// ��ͼ����Ķ���  
	//   

	AStarNode *curr_node;           // ��ǰ��  
	int       is_found;         // �Ƿ��ҵ�·��  
	

	// ����ʹ��A*�㷨�õ�·��  
	//    
	open_table[open_node_count++] = start_node;         // ��ʼ�����open��  

	start_node->s_is_in_opentable = 1;               // ����open��  
	start_node->s_g = 0;
	start_node->s_h = abs(end_node->s_x - start_node->s_x) + abs(end_node->s_y - start_node->s_y);
	start_node->s_parent = NULL;

	if (start_node->s_x == end_node->s_x && start_node->s_y == end_node->s_y)
	{
		printf("���==�յ㣡\n");
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
		curr_node = open_table[0];      // open��ĵ�һ����һ����fֵ��С�ĵ�(ͨ��������õ���)  
		open_table[0] = open_table[--open_node_count];  // ���һ����ŵ���һ���㣬Ȼ����жѵ���  
		adjust_heap(0);               // ������  

		close_table[close_node_count++] = curr_node;    // ��ǰ�����close��  
		curr_node->s_is_in_closetable = 1;       // �Ѿ���close������  

		if (curr_node->s_x == end_node->s_x && curr_node->s_y == end_node->s_y)// �յ���close�У�����  
		{
			is_found = 1;
			break;
		}

		get_neighbors(curr_node, end_node);           // ���ھӵĴ���  

		if (open_node_count == 0)             // û��·������  
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

		while (top >= 0)        // ���������·������~  
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
		printf("ô���ҵ�·��");
	}

	puts("");
}