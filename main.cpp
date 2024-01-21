#include <iostream>
#include "Tprofile.h"

Tprofile* load_profile(const char* filename) {
	FILE* file_ptr = nullptr;
	errno_t err = fopen_s(&file_ptr, filename, "rb");

	if (err) {
		std::cout << "[!] " << filename << " doesn't exist." << std::endl;
		return nullptr;
	}

	Tprofile* profile = new Tprofile;
	fread(profile, sizeof(Tprofile), 1, file_ptr);
	fclose(file_ptr);

	return profile;
}

void save_profile(const char* filename, Tprofile *profile) {
	FILE* file_ptr = nullptr;
	errno_t err = fopen_s(&file_ptr, filename, "wb");

	if (err) {
		std::cout << "[!] Saving failed! " << filename << " doesn't exist." << std::endl;
		return;
	}

	fwrite(profile, sizeof(Tprofile), 1, file_ptr);
	fclose(file_ptr);
}

int generate_checksum(Tprofile *profile) {
	unsigned int old_checksum = profile->checksum;	// esi
	profile->checksum = 0;
	unsigned int tmp_result  = 0;		// edx
	unsigned int profile_token = 0;		// ecx

	for (int i = 0; i < 340; i++) {		// i=eax
		profile_token = ((unsigned int*)profile)[i];// mov ecx, [ebx+ecx*4]
		tmp_result += (i + 1) * profile_token;		// imul ecx, eax  &  add edx, ecx
	}
	
	profile->checksum = old_checksum;

	unsigned int eax = tmp_result;
	eax = eax ^ 0x3D;
	tmp_result = tmp_result >> 0x10;
	eax = eax ^ tmp_result;
	tmp_result = eax+eax*8;
	eax = tmp_result;
	eax = eax >> 0x4;
	eax = eax ^ tmp_result;

	tmp_result = eax + eax * 4;
	tmp_result = tmp_result + tmp_result * 4;
	tmp_result = tmp_result + tmp_result * 4;
	tmp_result = eax + tmp_result * 2;
	tmp_result = tmp_result + tmp_result * 4;
	tmp_result = tmp_result << 0x8;
	tmp_result = tmp_result + eax;
	tmp_result = eax + tmp_result * 4;
	tmp_result = eax + tmp_result * 2;

	tmp_result = tmp_result + (tmp_result << 0x6);	// mov ecx,edx;  add edx,ecx;
	tmp_result = eax + tmp_result * 4;
	eax = tmp_result;
	eax = eax >> 0xF;
	eax = eax ^ tmp_result;

	return eax;
}

int main() {
	// Load profile data
	char filename[256];
	std::cout << "[*] Enter the name of the profile file: ";
	std::cin.getline(filename, 256);
	Tprofile *profile = load_profile(filename);
	if (!profile) return 0;

	// Modify best score
	unsigned int score = 0;
	std::cout << "[*] Desired score: ";
	std::cin >> score;
	profile->best_score = score;

	// Calculate checksum
	profile->checksum = generate_checksum(profile);

	// Save profile data
	save_profile(filename, profile);
	std::cout << "[*] Profile saved. Have fun!" << std::endl;
}