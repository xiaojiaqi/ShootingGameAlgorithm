#include <stdlib.h>

void Revenge(
	float rate,          // ?偪曉偟偺妋棪
	float ex, float ey,  // 揋偺嵗昗
	float tx, float ty   // 栚昗乮帺婡乯偺嵗昗
) {
	// 揋竚攋夡偝傟偨偐偳从偐偺敾僝丗
	// 嬶懱揑側??偼Detroyed娭?偱峴从偲偡傞丅
	if (Destroyed()) {
	
		// ?偪曉偟丗
		// ??傪巊偭偰堦僝妋棪偱?偪曉偡丅
		// ?偪曉偟抏偼乽慱偄?偪抏乿偲摨偠丅
		// 敪幩偺嬶懱揑側??偼AimingBullet娭?偱峴从偲偡傞丅
		if (rand()<=rate*RAND_MAX) {
			AimingBullet(ex, ey, tx, ty);
		}
		
		// 揋傪徚偡丗
		// 嬶懱揑側??偼Delete娭?偱峴从偲偡傞丅
		Delete();
	}
}
