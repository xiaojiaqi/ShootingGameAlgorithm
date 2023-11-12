void MoveMyShip2(
	float& x, float& y,    // Ž©‹@‚ÌÀ•WiX•ûÅØCY•ûÅØj
	float speed,           // Ž©‹@‚Ì‘¬‚³
	float x0, float y0,    // Ž©‹@‚Ì¶ãÀ•W
	float x1, float y1,    // Ž©‹@‚Ì…¸‰ºÀ•W
	float sx0, float sy0,  // ˆÚ“®‰Â”\˜g‚Ì¶ãÀ•W
	float sx1, float sy1,  // ˆÚ“®‰Â”\˜g‚Ì…¸‰ºÀ•W
	bool up, bool down,    // ã‰º•ûÅØ‚Ö‚ÌƒXƒeƒBªóƒN“ü—Í
	bool left, bool right  // ¶…¸•ûÅØ‚Ö‚ÌƒXƒeƒBªóƒN“ü—Í
) {
	if (up    && sy0<=y0) y-=speed;
	if (down  && y1<=sy1) y+=speed;
	if (left  && sx0<=x0) x-=speed;
	if (right && x1<=sx1) x+=speed;
}
