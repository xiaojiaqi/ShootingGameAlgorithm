void WaveEffect();

void Underwater1(
	float& x, float& y,  // ���@�̍��W
	float vx, float vy,  // ���@�̑��g
	float h              // ?�ʂ�?��
) {
	// ��?�̏�?�F
	// �ʏ�̑��g�ňړ�����B
	if (y<h) {
		x+=vx; y+=vy;
	}

	// ??�̏�?�F
	// ���g����������B�����ł͋�?�̔����Ƃ����B
	else {
		x+=vx/2; y+=vy/2;
	}
}
