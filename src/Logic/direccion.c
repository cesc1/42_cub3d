void	dirn(double dir[2], double plane[2])
{
	dir[0] = 0.0;
	dir[1] = -1.0;
	plane[0] = 0.66;
	plane[1] = 0.0;
}

void	dirs(double dir[2], double plane[2])
{
	dir[0] = 0.0;
	dir[1] = 1.0;
	plane[0] = -0.66;
	plane[1] = 0.0;
}

void	dirw(double dir[2], double plane[2])
{
	dir[0] = -1.0;
	dir[1] = 0.0;
	plane[0] = 0.0;
	plane[1] = -0.66;
}

void	dire(double dir[2], double plane[2])
{
	dir[0] = 1.0;
	dir[1] = 0.0;
	plane[0] = 0.0;
	plane[1] = 0.66;
}

void	initialdir(char direccion, double dir[2], double plane[2])
{
	if (direccion == 'N')
		dirn(dir, plane);
	else if (direccion == 'S')
		dirs(dir, plane);
	else if (direccion == 'W')
		dirw(dir, plane);
	else if (direccion == 'E')
		dire(dir, plane);
}
