void ScrollForce(
	int& x, int& y,   // 自機の座標
	int vx, int vy,   // 自機の速ﾃg
	int svx, int svy  // スク?ー?の速ﾃg
) {
	x+=vx+svx/2;
	y+=vy+svy/2;
}