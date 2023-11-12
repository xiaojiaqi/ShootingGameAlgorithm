void SightedBomb(
	float x, float y,        // ���@�̍��W
	float sx, float sy,      // ��?�̍��W
	float bvx, float bvy,    // ?�e�̑��g
	bool button              // �{�^?�̏��ԁi?���ꂽ�ƪ�true�j
) {
	// ?�e�̏���
	static bool bombing=false;  // ???���Ǵӂ�
	static float bx, by;        // ?�e�̍��W
	static float tx, ty;        // ?�e���̍��W

	// ???�ł͂Ȃ��ƪ��F
	// �{�^?�m?���ꂽ��??����B
	// ?�e��?�����W��?�e���̍��W��݃]����B
	if (!bombing) {
		if (button) {
			bombing=true;
			bx=x; by=y;
			tx=sx; ty=sy;
		}
	}
	
	// ???�̂ƪ��F
	// ?�e���ړ�������B
	// ?�e�m?�e����?�B������?��������B
	// ?���̋�̓I��??��Explode��?�ōs�ӂƂ���B
	else {
		bx+=bvx; by+=bvy;
		if (bx==tx && by==ty) {
			Explode();
			bombing=false;
		}
	}
	
	// ���@�Ə�?��`���F
	// ��̓I��??��DrawMyShip��?��DrawScope��?�ōs�ӂƂ���B
	// ��?�ƒn�㕨�Ƃ�?���蔻�]??���s�V�΁C
	// ��?�̒[�𼨖ł��������Ƃ��Ū���B
	DrawMyShip(x, y);
	DrawScope(sx, sy);

	// ???�̏�?�ɂ�?�e����?�e��`���F
	// ��̓I��??��DrawTarget��?��DrawBomb��?�ōs�ӂƂ���B
	if (bombing) {
		DrawTarget(tx, ty);
		DrawBomb(bx, by);
	}
}

