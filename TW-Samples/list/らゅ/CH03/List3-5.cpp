#include <math.h>

void MoveAtConstantSpeed(
	float& x, float& y,    // Ž©‹@‚ÌÀ•WiX•ûÅØCY•ûÅØj
	float speed,           // Ž©‹@‚Ì‘¬‚³
	bool up, bool down,    // ã‰º•ûÅØ‚Ö‚ÌƒXƒeƒBªóƒN“ü—Í
	bool left, bool right  // ¶…¸•ûÅØ‚Ö‚ÌƒXƒeƒBªóƒN“ü—Í
) {
	// ŽÎ‚ß‚ÉˆÚ“®‚·‚é‚Æª½‚ÌƒXƒs[ƒhF
	// ã‰º¶…¸‚Ì–ñ0.7”{‚É‚·‚é
	float s=speed/sqrt(2);

	// ŽÎ‚ßˆÚ“®
	if (up   && left ) x-=s, y-=s; else
	if (up   && right) x+=s, y-=s; else
	if (down && left ) x-=s, y+=s; else
	if (down && right) x+=s, y+=s; else
	
	// ã‰º¶…¸ˆÚ“®
	if (up    && !down ) y-=speed; else
	if (down  && !up   ) y+=speed; else
	if (left  && !right) x-=speed; else
	if (right && !left ) x+=speed;
}

