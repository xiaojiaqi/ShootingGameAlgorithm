#include <math.h>

void MoveAtConstantSpeed(
	float& x, float& y,    // ���@�̍��W�iX���؁CY���؁j
	float speed,           // ���@�̑���
	bool up, bool down,    // �㉺���؂ւ̃X�e�B��N����
	bool left, bool right  // �������؂ւ̃X�e�B��N����
) {
	// �΂߂Ɉړ�����ƪ��̃X�s�[�h�F
	// �㉺�����̖�0.7�{�ɂ���
	float s=speed/sqrt(2);

	// �΂߈ړ�
	if (up   && left ) x-=s, y-=s; else
	if (up   && right) x+=s, y-=s; else
	if (down && left ) x-=s, y+=s; else
	if (down && right) x+=s, y+=s; else
	
	// �㉺�����ړ�
	if (up    && !down ) y-=speed; else
	if (down  && !up   ) y+=speed; else
	if (left  && !right) x-=speed; else
	if (right && !left ) x+=speed;
}

