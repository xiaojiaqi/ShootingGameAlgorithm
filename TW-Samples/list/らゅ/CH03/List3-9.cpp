void SpeedControlByItem(
	float& speed,          // Xs[h
	float max_speed,       // Ĺ?Ź
	float min_speed,       // ĹáŹ
	float x0, float y0,    // E˘ť]ĚśăŔW
	float x1, float y1,    // E˘ť]Ě¸şŔW
	float ix0, float iy0,  // ĽÂCe?Ě?˝čť]ĚśăŔW
	float ix1, float iy1,  // ĽÂCe?Ě?˝čť]Ě¸şŔW
	float accel            // Xs[hĽÂŞóvE_E?ĚĂg?˘
) {
	// ĽÂCe?đEÁ˝ĆŞ˝Ě??F
	// ?˝čť]??đs˘C?˝Á˝ĆŞ˝ÉÍC
	// Xs[hĽÂŞóvÜ˝ÍXs[h_E?đs´ÓB
	if (ix0<x1 && x0<ix1 && iy0<y1 && y0<iy1) {
		speed+=accel;
		
		// ČşĚć´ÓÉˇéĆC
		// Xs[h_E?đ1ÂEÁ˝žŻĹC
		// Xs[h¸mĹáÉČéć´ÓÉĹŞ˝éB
		// if (accel<0) speed=min_speed;
		
		// Xs[h¸mĹ?ŹâĹáŹđ´ˇV˝çâłˇé
		if (speed>max_speed) speed=max_speed;
		if (speed<min_speed) speed=min_speed;
	}
}
