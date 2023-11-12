void MoveAimingBulletDDA(
	int& x, int& y,  // 抏偺嵗昗
	int vx, int vy,  // 抏偺堏摦曽咆
	int dx, int dy,  // X曽咆偲Y曽咆偺他暘
	int& diff,       // 岆他
	int speed        // 抏偺懍偝
) {
	// 堏摦?棧偺X曽咆竚挿偄偲偺??
	if (dx>=dy) {
		for (int i=0; i<speed; i++) {

			// X曽咆偵偼?夞堏摦偝偣傞
			x+=vx;
			
			// Y曽咆偵偼岆他竚对愊偟偨偲偩偗堏摦偝偣傞
			diff+=dy;
			if (diff>=dx) {
				diff-=dx;
				y+=vy;
			}
		}
	} 

	// 堏摦?棧偺Y曽咆竚挿偄偲偺??
	else {
		for (int i=0; i<speed; i++) {

			// Y曽咆偵偼?夞堏摦偝偣傞
			y+=vy;

			// X曽咆偵偼岆他竚对愊偟偨偲偩偗堏摦偝偣傞
			diff+=dx;
			if (diff>=dy) {
				diff-=dy;
				x+=vx;
			}
		}
	}
}
