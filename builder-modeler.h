struct Wall
{
	int x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	float r, g, b;
	int pos; /* 0 = no corners placed 
			    1 = 1st corner placed
				2 = + 2nd corner placed
				3 = + 3rd corner placed
				4 = + 4th corner placed (wall complete) */
};

struct Marker
{
	int x, y, z;
};

void add_wall();
void undo_last_wall(int);

void create_background();
void create_grid();
void create_walls();
void create_cursor();
void create_markers();
void clear_markers();

void init();
void display_callback();
void keyboard_callback(unsigned char, int, int);
void special_keyboard_callback(int, int, int);

void display_cord(int, int, float, float, float, void*, char*, int);
