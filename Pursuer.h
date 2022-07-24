#pragma once
#include "DiskSelector.h"

class Pursuer
{
	fs::path fileway;
	fs::path nextFileway;
	int selectEnd;
	int select;

	bool CheckRepeat(string name)
	{
		for (auto file : fs::directory_iterator(fileway))
		{
			fs::path temp = file;
			if (name == temp.filename())
			{
				return false;
			}
		}
		return true;
	}


	struct CutOrCopy
	{
		fs::path RememberDir;
		bool type;
	};

	CutOrCopy buffer;


public:
	Pursuer()
	{
		fileway = fs::current_path();
		selectEnd = 0;
		select = 0;
		nextFileway = fileway;
	}
	Pursuer(string way) :Pursuer()
	{
		fileway = way;
	}


	void Selector()
	{
		_setmode(_fileno(stdout), _O_U8TEXT);
		selectEnd = 0;
		int i = 0;
		wcout << "PATH: " << fileway << endl;
		for (auto file : fs::directory_iterator(fileway))
		{
			if (i == select)
			{
				wcout << "\033[48;5;002m";
				nextFileway = file;
			}
			fs::path temp = file;
			wstring fileName = temp.filename();
			wcout << fileName << "\033[0m" << endl;
			i++;
			selectEnd++;
		}
		_setmode(_fileno(stdout), _O_TEXT);
	}

	void SelectUp()
	{
		select = (select > 0) ? --select : select;
	}

	void SelectDown()
	{
		select = (select < selectEnd - 1) ? ++select : select;
	}

	void SetFileway()
	{
		if (fs::is_directory(nextFileway)) {
			fileway = nextFileway;
			select = 0;
		}
		else {
			cout << "\n\033[48;5;001mCan't open file!\033[0m";
			Sleep(1000);
		}
	}

	void GoBack()
	{
		if (fileway == fileway.parent_path())
		{
			DiskSelector Disk;
			fileway = Disk.DiskSelect();
		}
		else {
			fileway = fileway.parent_path();
		}
		select = 0;
	}

	void CreateDir(string dirName)
	{
		fs::path temp = fileway / dirName;
		fs::create_directories(temp);
	}

	void DeleteDir()
	{

		// Я намерено сделал возможным удаление только пустых файлов для учебного проекта. В реальном проекте заменить remove на remove_all и убрать первое условие. 
		if (!fs::is_empty(nextFileway))  
		{
			cout << "\033[48;5;001mFile is not empty! I can't delete this file!\033[0m";
			Sleep(1000);
		}
		else if (fileway != nextFileway) {
			fs::remove(nextFileway);
			select = 0;
		}
		else {
			cout << "\033[48;5;001mNothing to delete!\033[0m";
			Sleep(1000);
		}
	}

	void Rename(string name)
	{
		if (CheckRepeat(name)) {
			fs::path temp = fileway / name;
			fs::rename(nextFileway, temp);
		}
		else {
			cout << "\033[48;5;001mПапка с таким именем уже существует!\033[0m";
			Sleep(1500);
		}
	}


	void CopyDir(bool x)
	{
		buffer.RememberDir = nextFileway;
		buffer.type = x;
		cout << "\n\033[38;5;002m" << buffer.RememberDir.filename() << "\033[0m скопировано в буффер";
		_getch();
	}

	void InsertDir()
	{
		error_code err;
		fs::path newDir = fileway / buffer.RememberDir.filename();
		fs::create_directories(newDir);
		const auto opt = fs::copy_options::update_existing | fs::copy_options::recursive;
		fs::copy(buffer.RememberDir, newDir, opt, err);
		if (err)
		{
			cout << "\n\033[48;5;001mОшибка при копировании файла!\033[0m";
		}
		else 
		{
			cout << "\n\033[48;5;002mПапка успешно скопирована!\033[0m";
		}
		Sleep(2000);
		if (buffer.type)
		{
			fs::remove_all(buffer.RememberDir);
		}
	}

};

