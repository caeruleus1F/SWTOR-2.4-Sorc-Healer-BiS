#include <iostream>
#include <cmath>
#include <string>
#include "Player.h"

using namespace std;

Player::Player () {

	//Group buffs
	if (IN_GROUP == 1) {
		COORDINATION = .05;
		UNNATURAL_MIGHT = 1.05;
		MARK_OF_POWER_STAT = .05;
	}

	else {
		COORDINATION = 0.0;
		UNNATURAL_MIGHT = 1.0;
		MARK_OF_POWER_STAT = 0.0;
	}

	//Companion buffs
	if (COMP_CRIT_BUFF == 1)
		CritFromCompanion = .01;

	else
		CritFromCompanion = 0.0;

	if (COMP_SURGE_BUFF == 1)
		SurgeFromCompanion = .01;

	else
		SurgeFromCompanion = 0.0;

	if (COMP_ACCURACY_BUFF == 1)
		AccuracyFromCompanion = .01;

	else
		AccuracyFromCompanion = 0.0;
		
	//Accuracy
	AccuracyRating = 0.0;
	AccuracyFromRating = .3 * ( 1.0 - pow( 1.0 - (.01 / .3) , AccuracyRating / 55.0 / 1.2 ));
	AccuracyFromSkillsBuffs = .03 + AccuracyFromCompanion;
	AccuracyPercent = AccuracyFromRating + AccuracyFromSkillsBuffs;

	//Bonus Heal
	WillpowerRating = 400.0;
	TotalWillpower = WillpowerRating * (1 + MARK_OF_POWER_STAT + .06);
	BonusHealFromWillpower = TotalWillpower * .14;
	PowerRating = 0.0;
	BonusHealFromPower = PowerRating * .17;
	ForcePower = 2012.0;
	BonusHealFromForcePower = ForcePower * .17;
	BonusHeal = (BonusHealFromWillpower + BonusHealFromPower + BonusHealFromForcePower) * UNNATURAL_MIGHT;

	//Crit
	CritRating = 0.0;
	CritFromRating = .3 * ( 1.0 - pow( 1.0 - (.01 / .3) , CritRating / 55.0 / .9 ));
	CritFromWillpower = .2 * ( 1.0 - pow( 1.0 - (.01 / .2) , TotalWillpower / 55.0 / 5.5 ));
	CritFromSkillsBuffs = CritFromCompanion + .05 + COORDINATION;
	BaseCriticalChance = .05;
	ForceCriticalChance = CritFromRating + CritFromWillpower + CritFromSkillsBuffs + BaseCriticalChance;
	
	//Surge
	SurgeRating = 0.0;
	SurgeFromRating = .3 * ( 1.0 - pow( 1.0 - (.01 / .3) , SurgeRating / 55.0 / .22 ));
	SurgeFromSkillsBuffs = SurgeFromCompanion;
	BaseSurge = .5;
	SurgePercent = SurgeFromRating + SurgeFromSkillsBuffs + BaseSurge;

	//Alacrity
	AlacrityRating = 0.0;
	AlacrityFromRating = .3 * ( 1.0 - pow( 1.0 - (.01 / .3) , AlacrityRating / 55.0 / 1.25 ));
	AlacrityFromSkillsBuffs = .02;
	BaseAlacrity = 0.0;
	AlacrityPercent = BaseAlacrity + AlacrityFromSkillsBuffs + AlacrityFromRating;
}

float Player::modOffStats (string STAT1_NAME, float STAT1, string STAT2_NAME, float STAT2, string STAT3_NAME, float STAT3, string STAT4_NAME, float STAT4,
	string STAT5_NAME, float STAT5, string STAT6_NAME, float STAT6) {

	//STAT1 Accuracy, STAT2 Willpower, STAT3 Power, STAT4 Crit, STAT5 Surge, STAT6 Alacrity
	string stat_name[6] = {STAT1_NAME, STAT2_NAME, STAT3_NAME, STAT4_NAME, STAT5_NAME, STAT6_NAME};
	double rating[6] = {STAT1, STAT2, STAT3, STAT4, STAT5, STAT6};

	for (short i = 0; i < 6; i++) {

		if (stat_name[i] == "AC") {
			AccuracyRating += rating[i];
			AccuracyFromRating = .3 * ( 1.0 - pow( 1.0 - (.01 / .3) , AccuracyRating / 55.0 / 1.2 ));
			AccuracyPercent = AccuracyFromRating + AccuracyFromSkillsBuffs;
		}

		else if (stat_name[i] == "WP") {
			WillpowerRating += rating[i];
			TotalWillpower = WillpowerRating * (1 + MARK_OF_POWER_STAT + .06);
			CritFromWillpower = .2 * ( 1.0 - pow( 1.0 - (.01 / .2) , TotalWillpower / 55.0 / 5.5 ));
			ForceCriticalChance = CritFromRating + CritFromWillpower + CritFromSkillsBuffs + BaseCriticalChance;
			BonusHealFromWillpower = TotalWillpower * .14;
			BonusHeal = (BonusHealFromWillpower + BonusHealFromPower + BonusHealFromForcePower) * UNNATURAL_MIGHT;
		}

		else if (stat_name[i] == "PO") {
			PowerRating += rating[i];
			BonusHealFromPower = PowerRating * .17;
			BonusHeal = (BonusHealFromWillpower + BonusHealFromPower + BonusHealFromForcePower) * UNNATURAL_MIGHT;
		}

		else if (stat_name[i] == "CR") {
			CritRating += rating[i];
			CritFromRating = .3 * ( 1.0 - pow( 1.0 - (.01 / .3) , CritRating / 55.0 / .9 ));
			ForceCriticalChance = CritFromRating + CritFromWillpower + CritFromSkillsBuffs + BaseCriticalChance;
		}

		else if (stat_name[i] == "SU") {
			SurgeRating += rating[i];
			SurgeFromRating = .3 * ( 1.0 - pow( 1.0 - (.01 / .3) , SurgeRating / 55.0 / .22 ));
			SurgePercent = SurgeFromRating + SurgeFromSkillsBuffs + BaseSurge;
		}

		else if (stat_name[i] == "AL") {
			AlacrityRating += rating[i];
			AlacrityFromRating = .3 * ( 1.0 - pow( 1.0 - (.01 / .3) , AlacrityRating / 55.0 / 1.25 ));
			AlacrityPercent = BaseAlacrity + AlacrityFromSkillsBuffs + AlacrityFromRating;
		}

	}
	
	//return heal rotation
	return HealRotation();
}

void Player::showOffStats () {

	cout << "\n\nAccuracy Rating : " << AccuracyRating << "\n";
	cout << "Accuracy %: " << AccuracyPercent << "\n\n";

	cout << "Willpower: " << TotalWillpower << "\n";
	cout << "Power: " << PowerRating << "\n";
	cout << "ForcePower: " << ForcePower << "\n";
	cout << "Bonus Heal: " << BonusHeal << "\n\n";

	cout << "Crit Rating: " << CritRating << "\n";
	cout << "ForceCrit %: " << ForceCriticalChance << "\n\n";

	cout << "SurgeRating: " << SurgeRating << "\n";
	cout << "Surge %: " << SurgePercent << "\n\n";

	cout << "AlacrityRating: " << AlacrityRating << "\n";
	cout << "Alacrity %: " << AlacrityPercent << "\n\n";
}

void Player::OffHiltArmorings(float StatCompare[]){

	for (short i = 0; i < 9; i++) {
		//Advanced Resolve Armoring/Hilt 31
		StatCompare[0] = modOffStats("AC", 0.0, "WP", 88.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", -88.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);

		//Advanced Force Wielder Armoring/Hilt 31
		StatCompare[1] = modOffStats("AC", 0.0, "WP", 79.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", -79.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);

		if (StatCompare[0] > StatCompare[1]) {
			modOffStats("AC", 0.0, "WP", 88.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv Resolve 31 is greater.";
		}

		else if (StatCompare[1] > StatCompare[0]) {
			modOffStats("AC", 0.0, "WP", 79.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv. Force Wielder 31 is greater.";
		}
	}

}

void Player::OffMods(float StatCompare[]) {

	for (short i = 0; i < 9; i++) {
		//Advanced Aptitude Mod 31
		StatCompare[0] = modOffStats("AC", 0.0, "WP", 69.0, "PO", 57.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", -69.0, "PO", -57.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);

		//Advanced Aptitude Mod 31A
		StatCompare[1] = modOffStats("AC", 0.0, "WP", 84.0, "PO", 32.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", -84.0, "PO", -32.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);

		//Advanced Aptitude Mod 31B
		StatCompare[2] = modOffStats("AC", 0.0, "WP", 57.0, "PO", 46.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", -57.0, "PO", -46.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);

		//Advanced Mettle Mod 31
		StatCompare[3] = modOffStats("AC", 0.0, "WP", 69.0, "PO", 0.0, "CR", 57.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", -69.0, "PO", 0.0, "CR", -57.0, "SU", 0.0, "AL", 0.0);

		//Advanced Mettle Mod 31A
		StatCompare[4] = modOffStats("AC", 0.0, "WP", 84.0, "PO", 0.0, "CR", 32.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", -84.0, "PO", 0.0, "CR", -32.0, "SU", 0.0, "AL", 0.0);

		//Advanced Mettle Mod 31B
		StatCompare[5] = modOffStats("AC", 0.0, "WP", 57.0, "PO", 0.0, "CR", 46.0, "SU", 0.0, "AL", 0.0);
					   	 modOffStats("AC", 0.0, "WP", -57.0, "PO", 0.0, "CR", -46.0, "SU", 0.0, "AL", 0.0);

		if (StatCompare[0] > StatCompare[1] && 
			StatCompare[0] > StatCompare[2] && 
			StatCompare[0] > StatCompare[3] &&
			StatCompare[0] > StatCompare[4] && 
			StatCompare[0] > StatCompare[5]) {
			modOffStats("AC", 0.0, "WP", 69.0, "PO", 57.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv Aptitude Mod 31 is greater.";
		}

		else if (StatCompare[1] > StatCompare[0] && 
			     StatCompare[1] > StatCompare[2] && 
				 StatCompare[1] > StatCompare[3] && 
				 StatCompare[1] > StatCompare[4] && 
				 StatCompare[1] > StatCompare[5]) {
			modOffStats("AC", 0.0, "WP", 84.0, "PO", 32.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv Aptitude Mod 31A is greater.";
		}

		else if (StatCompare[2] > StatCompare[0] && 
				 StatCompare[2] > StatCompare[1] && 
				 StatCompare[2] > StatCompare[3] && 
				 StatCompare[2] > StatCompare[4] && 
				 StatCompare[2] > StatCompare[5]) {
			modOffStats("AC", 0.0, "WP", 57.0, "PO", 46.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv Aptitude Mod 31B is greater.";
		}

		else if (StatCompare[3] > StatCompare[0] && 
				 StatCompare[3] > StatCompare[1] && 
				 StatCompare[3] > StatCompare[2] && 
				 StatCompare[3] > StatCompare[4] && 
				 StatCompare[3] > StatCompare[5]) {
			modOffStats("AC", 0.0, "WP", 69.0, "PO", 0.0, "CR", 57.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv Mettle Mod 31 is greater.";
		}

		else if (StatCompare[4] > StatCompare[0] && 
				 StatCompare[4] > StatCompare[1] && 
				 StatCompare[4] > StatCompare[2] && 
				 StatCompare[4] > StatCompare[3] && 
				 StatCompare[4] > StatCompare[5]) {
			modOffStats("AC", 0.0, "WP", 84.0, "PO", 0.0, "CR", 32.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv Mettle Mod 31A is greater.";
		}

		else if (StatCompare[5] > StatCompare[0] && 
				 StatCompare[5] > StatCompare[1] && 
				 StatCompare[5] > StatCompare[2] && 
				 StatCompare[5] > StatCompare[3] && 
				 StatCompare[5] > StatCompare[4]) {
			modOffStats("AC", 0.0, "WP", 57.0, "PO", 0.0, "CR", 46.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv Mettle Mod 31B is greater.";
		}
	}

}

void Player::OffEnhancements(float StatCompare[]) {

	for (short i = 0; i < 7; i++) {
		//Adv Adept 31
		StatCompare[0] = modOffStats("AC", 0.0, "WP", 0.0, "PO", 52.0, "CR", 0.0, "SU", 79.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", 0.0, "PO", -52.0, "CR", 0.0, "SU", -79.0, "AL", 0.0);

		//Adv Quick Savant 31
		StatCompare[1] = modOffStats("AC", 0.0, "WP", 0.0, "PO", 52.0, "CR", 0.0, "SU", 0.0, "AL", 79.0);
						 modOffStats("AC", 0.0, "WP", 0.0, "PO", -52.0, "CR", 0.0, "SU", 0.0, "AL", -79.0);

		//Adv Battle 31
		StatCompare[2] = modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 52.0, "SU", 79.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", -52.0, "SU", -79.0, "AL", 0.0);

		//Adv Insight 31
		StatCompare[3] = modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 52.0, "SU", 0.0, "AL", 79.0);
						 modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", -52.0, "SU", 0.0, "AL", -79.0);

		if (StatCompare[0] > StatCompare[1] && 
			StatCompare[0] > StatCompare[2] && 
			StatCompare[0] > StatCompare[3]) {
			modOffStats("AC", 0.0, "WP", 0.0, "PO", 52.0, "CR", 0.0, "SU", 79.0, "AL", 0.0);
			cout << "\nAdv Adept 31 is greater.";
		}

		else if (StatCompare[1] > StatCompare[0] && 
				 StatCompare[1] > StatCompare[2] && 
				 StatCompare[1] > StatCompare[3]) {
			modOffStats("AC", 0.0, "WP", 0.0, "PO", 52.0, "CR", 0.0, "SU", 0.0, "AL", 79.0);
			cout << "\nAdv Quick Savant 31 is greater.";
		}

		else if (StatCompare[2] > StatCompare[0] && 
				 StatCompare[2] > StatCompare[1] && 
				 StatCompare[2] > StatCompare[3]) {
			modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 52.0, "SU", 79.0, "AL", 0.0);
			cout << "\nAdv Battle 31 is greater.";
		}

		else if (StatCompare[3] > StatCompare[0] && 
				 StatCompare[3] > StatCompare[1] && 
				 StatCompare[3] > StatCompare[2]) {
			modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 52.0, "SU", 0.0, "AL", 79.0);
			cout << "\nAdv Insight 31 is greater.";
		}

	}
	
}

void Player::OffEarpieces(float StatCompare[]) {

	//Verpine Force-Lord's MK-1 Relay
	StatCompare[0] = modOffStats("AC", 0.0, "WP", 159.0, "PO", 0.0, "CR", 88.0, "SU", 79.0, "AL", 0.0);
					 modOffStats("AC", 0.0, "WP", -159.0, "PO", 0.0, "CR", -88.0, "SU", -79.0, "AL", 0.0);

	//Verpine Force-Healer's MK-1 Chip
	StatCompare[1] = modOffStats("AC", 0.0, "WP", 159.0, "PO", 88.0, "CR", 0.0, "SU", 0.0, "AL", 79.0);
					 modOffStats("AC", 0.0, "WP", -159.0, "PO", -88.0, "CR", 0.0, "SU", 0.0, "AL", -79.0);

	//Underworld Stalker's Device
	StatCompare[2] = modOffStats("AC", 0.0, "WP", 159.0, "PO", 0.0, "CR", 110.0, "SU", 79.0, "AL", 0.0);
					 modOffStats("AC", 0.0, "WP", -159.0, "PO", 0.0, "CR", -110.0, "SU", -79.0, "AL", 0.0);

	//Underworld Force Master's Device
	StatCompare[3] = modOffStats("AC", 0.0, "WP", 159.0, "PO", 0.0, "CR", 110.0, "SU", 0.0, "AL", 79.0);
					 modOffStats("AC", 0.0, "WP", -159.0, "PO", 0.0, "CR", -110.0, "SU", 0.0, "AL", -79.0);

	//Underworld Force Mystic's Device
	StatCompare[4] = modOffStats("AC", 0.0, "WP", 159.0, "PO", 110.0, "CR", 0.0, "SU", 79.0, "AL", 0.0);
					 modOffStats("AC", 0.0, "WP", -159.0, "PO", -110.0, "CR", 0.0, "SU", -79.0, "AL", 0.0);

	//Verpine Force-Healer's MK-2 Chip
	StatCompare[5] = modOffStats("AC", 0.0, "WP", 172.0, "PO", 0.0, "CR", 84.0, "SU", 79.0, "AL", 0.0);
					 modOffStats("AC", 0.0, "WP", -172.0, "PO", 0.0, "CR", -84.0, "SU", -79.0, "AL", 0.0);

	if (StatCompare[0] > StatCompare[1] && 
		StatCompare[0] > StatCompare[2] && 
		StatCompare[0] > StatCompare[3] &&
		StatCompare[0] > StatCompare[4] &&
		StatCompare[0] > StatCompare[5]) {
		modOffStats("AC", 0.0, "WP", 159.0, "PO", 0.0, "CR", 88.0, "SU", 79.0, "AL", 0.0);
		cout << "\nVerpine Force-Lord's MK-1 Relay is greater.";
		}

	else if (StatCompare[1] > StatCompare[0] && 
		     StatCompare[1] > StatCompare[2] && 
		     StatCompare[1] > StatCompare[3] &&
			 StatCompare[1] > StatCompare[4] &&
			 StatCompare[1] > StatCompare[5]) {
		modOffStats("AC", 0.0, "WP", 159.0, "PO", 88.0, "CR", 0.0, "SU", 0.0, "AL", 79.0);
		cout << "\nVerpine Force-Healer's MK-1 Chip is greater.";
		}

	else if (StatCompare[2] > StatCompare[0] && 
		     StatCompare[2] > StatCompare[1] && 
		     StatCompare[2] > StatCompare[3] &&
			 StatCompare[2] > StatCompare[4] &&
			 StatCompare[2] > StatCompare[5]) {
		modOffStats("AC", 0.0, "WP", 159.0, "PO", 0.0, "CR", 110.0, "SU", 79.0, "AL", 0.0);
		cout << "\nUnderworld Stalker's Device is greater.";
		}

	else if (StatCompare[3] > StatCompare[0] && 
		     StatCompare[3] > StatCompare[1] && 
		     StatCompare[3] > StatCompare[2] &&
			 StatCompare[3] > StatCompare[4] &&
			 StatCompare[3] > StatCompare[5]) {
		modOffStats("AC", 0.0, "WP", 159.0, "PO", 0.0, "CR", 110.0, "SU", 0.0, "AL", 79.0);
		cout << "\nUnderworld Force Master's Device is greater.";
		}

	else if (StatCompare[4] > StatCompare[0] && 
		     StatCompare[4] > StatCompare[1] && 
		     StatCompare[4] > StatCompare[2] &&
			 StatCompare[4] > StatCompare[3] &&
			 StatCompare[4] > StatCompare[5]) {
		modOffStats("AC", 0.0, "WP", 159.0, "PO", 110.0, "CR", 0.0, "SU", 79.0, "AL", 0.0);
		cout << "\nUnderworld Force Mystic's Device is greater.";
		}

	else if (StatCompare[5] > StatCompare[0] && 
		     StatCompare[5] > StatCompare[1] && 
		     StatCompare[5] > StatCompare[2] &&
			 StatCompare[5] > StatCompare[3] &&
			 StatCompare[5] > StatCompare[4]) {
		modOffStats("AC", 0.0, "WP", 172.0, "PO", 0.0, "CR", 84.0, "SU", 79.0, "AL", 0.0);
		cout << "\nVerpine Force-Healer's MK-2 Chip is greater.";
		}
}

void Player::OffImplants(float StatCompare[]) {

	for (short i = 0; i < 2; i++) {
	//Underworld Force-Master/Mystic's MK-X Package
	StatCompare[0] = modOffStats("AC", 0.0, "WP", 159.0, "PO", 0.0, "CR", 110.0, "SU", 79.0, "AL", 0.0);
					 modOffStats("AC", 0.0, "WP", -159.0, "PO", 0.0, "CR", -110.0, "SU", -79.0, "AL", 0.0);

	//Underworld Mystic's MK-V Package
	StatCompare[1] = modOffStats("AC", 0.0, "WP", 159.0, "PO", 110.0, "CR", 0.0, "SU", 0.0, "AL", 79.0);
					 modOffStats("AC", 0.0, "WP", -159.0, "PO", -110.0, "CR", 0.0, "SU", 0.0, "AL", -79.0);

	//Underworld Stalker's MK-X Package
	StatCompare[2] = modOffStats("AC", 0.0, "WP", 159.0, "PO", 110.0, "CR", 0.0, "SU", 79.0, "AL", 0.0);
					 modOffStats("AC", 0.0, "WP", -159.0, "PO", -110.0, "CR", 0.0, "SU", -79.0, "AL", 0.0);

	//Verpine Force-Lord's MK-2 System
	StatCompare[3] = modOffStats("AC", 0.0, "WP", 172.0, "PO", 0.0, "CR", 84.0, "SU", 79.0, "AL", 0.0);
					 modOffStats("AC", 0.0, "WP", -172.0, "PO", 0.0, "CR", -84.0, "SU", -79.0, "AL", 0.0);

	//Verpine Force-Healer's MK-1 Motivator
	StatCompare[4] = modOffStats("AC", 0.0, "WP", 159.0, "PO", 88.0, "CR", 0.0, "SU", 79.0, "AL", 0.0);
					 modOffStats("AC", 0.0, "WP", -159.0, "PO", -88.0, "CR", 0.0, "SU", -79.0, "AL", 0.0);

	//Verpine Force-Healer's MK-2 Motivator
	StatCompare[5] = modOffStats("AC", 0.0, "WP", 172.0, "PO", 84.0, "CR", 0.0, "SU", 79.0, "AL", 0.0);
					 modOffStats("AC", 0.0, "WP", -172.0, "PO", -84.0, "CR", 0.0, "SU", -79.0, "AL", 0.0);

	if (StatCompare[0] > StatCompare[1] && 
		StatCompare[0] > StatCompare[2] && 
		StatCompare[0] > StatCompare[3] &&
		StatCompare[0] > StatCompare[4] &&
		StatCompare[0] > StatCompare[5]) {
		modOffStats("AC", 0.0, "WP", 159.0, "PO", 0.0, "CR", 110.0, "SU", 79.0, "AL", 0.0);
		cout << "\nUnderworld Force-Master/Mystic's MK-X Package is greater.";
		}

	else if (StatCompare[1] > StatCompare[0] && 
		     StatCompare[1] > StatCompare[2] && 
			 StatCompare[1] > StatCompare[3] &&
			 StatCompare[1] > StatCompare[4] &&
			 StatCompare[1] > StatCompare[5]) {
		modOffStats("AC", 0.0, "WP", 159.0, "PO", 110.0, "CR", 0.0, "SU", 0.0, "AL", 79.0);
		cout << "\nUnderworld Mystic's MK-V Package is greater.";
		}

	else if (StatCompare[2] > StatCompare[0] && 
		     StatCompare[2] > StatCompare[1] && 
			 StatCompare[2] > StatCompare[3] &&
			 StatCompare[2] > StatCompare[4] &&
			 StatCompare[2] > StatCompare[5]) {
		modOffStats("AC", 0.0, "WP", 159.0, "PO", 110.0, "CR", 0.0, "SU", 79.0, "AL", 0.0);
		cout << "\nUnderworld Stalker's MK-X Package is greater.";
		}

	else if (StatCompare[3] > StatCompare[0] && 
		     StatCompare[3] > StatCompare[1] && 
			 StatCompare[3] > StatCompare[2] &&
			 StatCompare[3] > StatCompare[4] &&
			 StatCompare[3] > StatCompare[5]) {
		modOffStats("AC", 0.0, "WP", 172.0, "PO", 0.0, "CR", 84.0, "SU", 79.0, "AL", 0.0);
		cout << "\nVerpine Force-Lord's MK-2 System is greater.";
		}

	else if (StatCompare[4] > StatCompare[0] && 
		     StatCompare[4] > StatCompare[1] && 
			 StatCompare[4] > StatCompare[2] &&
			 StatCompare[4] > StatCompare[3] &&
			 StatCompare[4] > StatCompare[5]) {
		modOffStats("AC", 0.0, "WP", 159.0, "PO", 88.0, "CR", 0.0, "SU", 79.0, "AL", 0.0);
		cout << "\nVerpine Force-Healer's MK-1 Motivator is greater.";
		}

	else if (StatCompare[5] > StatCompare[0] && 
		     StatCompare[5] > StatCompare[1] && 
			 StatCompare[5] > StatCompare[2] &&
			 StatCompare[5] > StatCompare[3] &&
			 StatCompare[5] > StatCompare[4]) {
		modOffStats("AC", 0.0, "WP", 172.0, "PO", 84.0, "CR", 0.0, "SU", 79.0, "AL", 0.0);
		cout << "\nVerpine Force-Healer's MK-2 Motivator is greater.";
		}

	}

}

void Player::OffColorCrystals (float StatCompare[]) {

		for (short i = 0; i < 2; i++) {
		//Advanced Hawkeye
		StatCompare[0] = modOffStats("AC", 0.0, "WP", 0.0, "PO", 41.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", 0.0, "PO", -41.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);

		//Advanced Eviscerating
		StatCompare[1] = modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 41.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", -41.0, "SU", 0.0, "AL", 0.0);

		if (StatCompare[0] > StatCompare[1]) {
			modOffStats("AC", 0.0, "WP", 0.0, "PO", 41.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv. Hawkeye Color Crystal is greater.";
		}

		else if (StatCompare[1] > StatCompare[0]) {
			modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 41.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv. Eviscerating Color Crystal is greater.";
		}
	}

}

void Player::OffAugments (float StatCompare[]) { 

	for (short i = 0; i < 14; i++) {
		//Advanced Critical Augment 28
		StatCompare[0] = modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 32.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", -32.0, "SU", 0.0, "AL", 0.0);

		//Advanced Overkill Augment 28
		StatCompare[1] = modOffStats("AC", 0.0, "WP", 0.0, "PO", 32.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", 0.0, "PO", -32.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);

		//Advanced Surge Augment 28
		StatCompare[2] = modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 0.0, "SU", 32.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 0.0, "SU", -32.0, "AL", 0.0);

		//Advanced Alacrity Augment 28
		StatCompare[3] = modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 32.0);
						 modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", -32.0);

		//Advanced Resolve Augment 28
		StatCompare[4] = modOffStats("AC", 0.0, "WP", 32.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
						 modOffStats("AC", 0.0, "WP", -32.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);

		if (StatCompare[0] > StatCompare[1] && 
			StatCompare[0] > StatCompare[2] && 
			StatCompare[0] > StatCompare[3] &&
			StatCompare[0] > StatCompare[4]) {
			modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 32.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv Critical Augment 28 is greater.";
		}

		else if (StatCompare[1] > StatCompare[0] && 
			     StatCompare[1] > StatCompare[2] && 
				 StatCompare[1] > StatCompare[3] && 
				 StatCompare[1] > StatCompare[4]) {
			modOffStats("AC", 0.0, "WP", 0.0, "PO", 32.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv Overkill Augment 28 is greater.";
		}

		else if (StatCompare[2] > StatCompare[0] && 
				 StatCompare[2] > StatCompare[1] && 
				 StatCompare[2] > StatCompare[3] && 
				 StatCompare[2] > StatCompare[4]) {
			modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 0.0, "SU", 32.0, "AL", 0.0);
			cout << "\nAdv Surge Augment 28 is greater.";
		}

		else if (StatCompare[3] > StatCompare[0] && 
				 StatCompare[3] > StatCompare[1] && 
				 StatCompare[3] > StatCompare[2] && 
				 StatCompare[3] > StatCompare[4]) {
			modOffStats("AC", 0.0, "WP", 0.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 32.0);
			cout << "\nAdv Alacrity Augment 28 is greater.";
		}

		else if (StatCompare[4] > StatCompare[0] && 
				 StatCompare[4] > StatCompare[1] && 
				 StatCompare[4] > StatCompare[2] && 
				 StatCompare[4] > StatCompare[3]) {
			modOffStats("AC", 0.0, "WP", 32.0, "PO", 0.0, "CR", 0.0, "SU", 0.0, "AL", 0.0);
			cout << "\nAdv Resolve Augment 28 is greater.";
		}

	}

}