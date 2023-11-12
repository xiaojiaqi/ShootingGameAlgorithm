void MoveAcceleratedBullet(
	float speed,          // ’e‚Ì‘¬‚³
	float accel,          // ‰Á‘¬Ãg
	float& vx, float& vy  // ‘¬Ãg‚ÌX¬•ª‚ÆY¬•ª
) {
	// ‘¬Ãg‚ğŒÃ‚¢‘¬‚³‚Å?‚é
	if (speed!=0) {
		vx/=speed; vy/=speed;
	}

	// ‘¬‚³‚ğXöè‚·‚é
	speed+=accel;

	// ‘¬Ãg‚Éöè‚µ‚¢‘¬‚³‚ğŠ|‚¯‚é
	vx*=speed; vy*=speed;
}