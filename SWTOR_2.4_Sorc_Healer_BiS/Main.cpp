#include "Player.h"


int main () {

	cout << "... Initializing stats ...\n\n";

	Player AD;
	float StatCompare[6] = {0};

	AD.IN_GROUP = 1;
	AD.COMP_HEALTH_BUFF = 1;
	AD.COMP_CRIT_BUFF = 1;
	AD.COMP_SURGE_BUFF = 1;
	AD.COMP_ACCURACY_BUFF = 1;

	cout << "... Stats Initialized ...\n\n";

	AD.OffHiltArmorings(StatCompare);
	AD.OffMods(StatCompare);
	AD.OffEnhancements(StatCompare);
	AD.OffEarpieces(StatCompare);
	AD.OffImplants(StatCompare);
	AD.OffColorCrystals(StatCompare);
	AD.OffAugments(StatCompare);

	//2 Relics
	AD.modOffStats("AC", 0.0, "WP", 0.0, "PO", 64.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
	//show end result stats
	AD.showOffStats();

	AD.showHPS();

	cin.get();

	return 0;

}