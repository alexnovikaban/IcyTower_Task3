#pragma once

struct Tprofile
{
	char header[6];
	char handle[32];
	int checksum;
	int games_played;
	int custom_games_played;
	int games_quit;
	int seconds_spent_playing;
	int total_floors;
	int total_score;
	int total_combos;
	int total_combo_floors;
	int best_floor;
	int best_combo;
	int best_score;
	int no_combo_top_floor;
	int biggest_lost_combo;
	int cccNum[5];
	int cccTotal[5];
	int ccc[5];
	int jc[5];
	int rewards[10];
	int total_jumps;
	char best_replay_names[32][32];
	int flash;
	int jump_hold;
	char last_avatar[64];
	int start_floor;
	int msc_volume;
	int snd_volume;
	char creationDate[16];
	char saveDate[16];
};
