#pragma once
#include "Headers.h"
class DiskSelector
{
	struct DiskInfo
	{
		string diskName;
		string diskType;
	};
	vector<DiskInfo> Disks;
	void GetDiskInfo()
	{
		char m[1024];
		HANDLE find = FindFirstVolumeA(m, 1024);
		if (find != INVALID_HANDLE_VALUE) {
			do {
				char sm[1024];
				DWORD ln;
				GetVolumePathNamesForVolumeNameA(m, sm, 1024, &ln);
				DiskInfo hr;
				hr.diskName = sm;
				int type;
				LPSTR disk = sm;

				std::error_code er;
				if (hr.diskName != "" && fs::exists(hr.diskName, er)) {
					type = GetDriveTypeA(disk);
					switch (type)
					{
					case 0:
						hr.diskType = "Unknow";
						break;
					case 1:
						hr.diskType = "DRIVE_NO_ROOT_DIR";
						break;
					case 2:
						hr.diskType = "DRIVE_REMOVABLE";
						break;
					case 3:
						hr.diskType = "DRIVE_FIXED";
						break;
					case 4:
						hr.diskType = "DRIVE_REMOTE";
						break;
					case 5:
						hr.diskType = "DRIVE_CDROM";
						break;
					case 6:
						hr.diskType = "DRIVE_RAMDISK";
						break;
					}
					Disks.push_back(hr);
				}
			} while (FindNextVolumeA(find, m, 1024));
			FindVolumeClose(find);
		}
	}
public:
	DiskSelector()
	{
		GetDiskInfo();
	}

	fs::path DiskSelect()
	{
		fs::path currentDisk;
		int active = 0;
		int key = 0;
		do {
			system("cls");
			for (int i = 0; i < Disks.size(); i++)
			{
				if (i == active) {
					cout << "\033[48;5;002m";
					currentDisk = Disks[i].diskName;
				}
				cout << endl << Disks[i].diskName << " Type: " << Disks[i].diskType << "\033[0m";
			}
			key = _getch();
			key = (key == 224) ? _getch() : key;
			switch (key)
			{
			case 72:
				if (active == 0)
				{
					continue;
				}
				active--;
				break;
			case 80:
				if (active == Disks.size() - 1)
				{
					continue;
				}
				active++;
				break;
			case 13:
				return currentDisk;
				break;
			}
		} while (key != 27);
	}
};