void InitDirectedBullet(
	float ex, float ey,    // �G�̍��W
	float& x, float& y,    // �e�̍��W
	float& vx, float& vy,  // �e�̑��g
	float speed,           // �e�̑���
	float theta            // ���ˊp�g
) {
	// �e�̍��W��݃]����
	x=ex; y=ey;

	// ����speed�Ŋp�gtheta�̕��؂ɔ�Ԓe�̑��g(vx,vy)��?�߂�F
	// M_PI�͉~�����B
	vx=cos(M_PI/180*theta)*speed;
	vy=sin(M_PI/180*theta)*speed;
}