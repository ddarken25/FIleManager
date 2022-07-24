#pragma once
#include "Pursuer.h"
class Menu
{
	Pursuer manager;
	int key;

	void ControlTips()
	{
		cout << "\nManagment:\n - input \033[38;5;003mEnter\033[0m to open the directory";
		cout << "\n - input \033[38;5;003mBackspace\033[0m to open root of the directory";
		cout << "\n - input \033[38;5;003mn\033[0m to create a new directory";
		cout << "\n - input \033[38;5;003md\033[0m to delete a directory";
		cout << "\n - input \033[38;5;003mr\033[0m to rename a directory\n";
	}
public:
	void UserSelecotr()
	{
		do {
			system("cls");
			manager.Selector();
			ControlTips();
			key = _getch();
			key = (key == 224) ? _getch() : key;
			//cout << key;
			//_getch();
			string dirName;
			switch (key)
			{
			case 72:
				manager.SelectUp();
				break;
			case 80:
				manager.SelectDown();
				break;
			case 13:
				manager.SetFileway();
				break;
			case 8:
				manager.GoBack();
				break;
			case 110:
				cout << "Input name of new directory: ";
				cin >> dirName;
				manager.CreateDir(dirName);
				break;
			case 100:
				manager.DeleteDir();
				break;
			case 114:
				cout << "Input new name of directory: ";
				cin >> dirName;
				manager.Rename(dirName);
				break;
			case 3:
				manager.CopyDir(0);
				break;
			case 22:
				manager.InsertDir();
				break;
			case 24:
				manager.CopyDir(1);
				break;
			}
			
		} while (key != 27);
	}
};

