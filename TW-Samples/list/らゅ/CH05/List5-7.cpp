void MoveThrownShip(
	float& x0, float& y0,  // �@�̂̍�����W
	float& x1, float& y1,  // �@�̂̅������W
	float& vx, float& vy,  // �@�̂̑��g
	float sx0, float sy0,  // �ړ��\��ʤ�i��ʘg�j�̍�����W
	float sx1, float sy1   // �ړ��\��ʤ�i��ʘg�j�̅������W
) {
	// ���ˉ�铮���̂��߂�??�F
	// ��ʘg�̏㉺��������͂ݏo�����ӂɂȂ�����C
	// �ړ����g����ɂ���B
	if (x0+vx<sx0 || sx1<=x1+vx) vx=-vx;
	if (y0+vy<sy0 || sy1<=y1+vy) vy=-vy;
	
	// �@�̂��ړ�������
	x0+=vx; x1+=vx;
	y0+=vy; y1+=vy;
}

