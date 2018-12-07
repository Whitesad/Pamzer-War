#ifndef _MAP_H_
#define _MAP_H_

#include "head.h"
#include "resources.h"

class map_class
{
  public:
    int bfs(Node from, Node to, Forward arr_path[MAXR][MAXC]);
	int flash_map_elements(void);
	int map_incident_judge(void);
	int print_map(void);
};

#endif
