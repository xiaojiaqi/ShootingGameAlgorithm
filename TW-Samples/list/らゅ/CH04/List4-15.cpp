void MoveReflectShot(
	float& x0, float& y0,      // V?ͺσgΜΆγΐW
	float& x1, float& y1,      // V?ͺσgΜΈΊΐW
	float& vx, float& vy,      // V?ͺσgΜ¬Γgi?½C?Όj
	float gx0[], float gy0[],  // n`ΜΆγΐW
	float gx1[], float gy1[],  // n`ΜΈΊΐW
	int num_ground,            // n`Μ?
	float ex0[], float ey0[],  // GΜΆγΐW
	float ex1[], float ey1[],  // GΜΈΊΐW
	int num_enemy              // GΜ?
) {
	// n`ΖΜ?½θ»]??F
	// V?ͺσgπ?ΌϋΕΨΙiί½ΐWΙΒ’ΔC
	// n`Ι?½ι©Η΄Σ©π»]·ιB
	// n`Ι?½Α½κ?ΙΝC?ΌϋΕΨΜ¬ΓgπΚδΙ΅ΔC
	// ?[v©η²―ιB
	for (int i=0; i<num_ground; i++) {
		if (gx0[i]<x1 && x0<gx1[i] && 
			gy0[i]<y1+vy && y0+vy<gy1[i]) {
			vy=-vy;
			break;
		}
	}
	
	// V?ͺσgπiίι
	x0+=vx; y0+=vy;
	x1+=vx; y1+=vy;

	// GΖΜ?½θ»]??F
	// GΙ?½Α½κ?ΙΝCGΙ_?[Wπ^·VΔC
	// ?[v©η²―ιB
	// _?[WΜοΜIΘ??ΝDamageEnemyΦ?Εs΄ΣΖ·ιB
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			break;
		}
	}
}
