void ScrollSpeed(
	int y,               // ���@��Y���W
	int& svy,            // �X�N?�[?�̑��g�iY���؁j
	int ymin, int ymax,  // ���@Y���W�̍ő�l�C�ŏ��l
	int smax, int smin   // �X�N?�[?�̍ő�C�ŏ��X�s�[�h
) {
	svy=smin+(y-ymin)*(smax-smin)/(ymax-ymin);
}