void ShotPower(
	float& x, float& y,  // �V?��g�̍��W
	float vx, float vy,  // �V?��g�̑��g
	float& power,        // �V?��g�̈З�
	float attenuation    // �З͸m��?�����g?��
) {
	// �V?��g���ړ�������
	x+=vx; y+=vy;
	
	// �ړ����邽�тɃV?��g�̈З͂���߂�
	power-=attenuation;
}
