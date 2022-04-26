#include <iostream>
#include <vector>
#include <fstream>
#include<string>
#include <algorithm>

using namespace std;

#define size_project 4

#define size_news 4


struct new_project {
	string title;
	string start_date;
	string end_date;
	string brief;
};

struct new_news {
	string title;
	string publish_date;
	string brief;
	string project_id;
};

//Add New Project And News
void add_new_project_info();
void add_new_news_info();


//Add Data To External Files
void add_to_projects_file(string arr_project[4], string filePath);
void add_to_news_file(string arr_news[4], string project_title, string filePath);


//Clear All Data Of External Files
void clear_all_projects_data();
void clear_all_news_data();


//Handle Data Of External Files
vector<vector<string>> data_projects_handle();
vector<vector<string>> data_news_handle();


//Display All Data In External Files
void display_data_of_projects(vector<vector<string>> info);
void display_data_of_news(vector<vector<string>> info);


//Listing Data By Filter by User
vector<vector<string>> filter_projects_by_user();
vector<vector<string>> filter_news_by_user();


//Delete item From file
void delete_project();
void delete_news();


//Split String By Space
vector<string> split_string_by_space(string str);


//System Run Function
void system();


//Read Data From External Files
vector<string> read_data_from_File(string filePath);


int main() {
	cout << endl << "--------------Welcome To Enigma System--------------" << endl << endl;

	system();

	return 0;
}


//Add New Project And News
void add_new_project_info() {
	string arr_project[size_project];
	vector<string> data;
	new_project project;

	//Avoid Error
	getline(cin, project.title);

	cout << "Enter New Project Title : ";
	getline(cin, project.title);
	arr_project[0] = project.title;
	cout << "Enter Start Date : ";
	getline(cin, project.start_date);
	arr_project[1] = project.start_date;
	cout << "Enter End Date : ";
	getline(cin, project.end_date);
	arr_project[2] = project.end_date;
	cout << "Enter a Brief : ";
	getline(cin, project.brief);
	arr_project[3] = project.brief;
	add_to_projects_file(arr_project, "data/Projects.txt");
}
void add_new_news_info() {
	string arr_news[size_news];
	vector<vector<string>> info = data_projects_handle();
	vector<string> data;
	new_news news;
	bool id_exist = false;

	//Avoid Error
	getline(cin, news.title);

	cout << "Enter New News Title : ";
	getline(cin, news.title);
	arr_news[0] = news.title;
	cout << "Enter Publish Date : ";
	getline(cin, news.publish_date);
	arr_news[1] = news.publish_date;
	cout << "Enter Brief : ";
	getline(cin, news.brief);
	arr_news[2] = news.brief;
	cout << "\nProject IDs : \n";
	while (true) {
		display_data_of_projects(info);
		cout << "\nchoose Your Project Id : ";
		getline(cin, news.project_id);
		arr_news[3] = news.project_id;
		id_exist = false;
		for (int i = 0;i < info.size();i++) {
			if (news.project_id == info[i][4]) {
				id_exist = true;
				break;
			}
		}
		if (id_exist) {
			break;
		}
		string exit;
		cout << "\nAre You Want To Exit (no/yes)?";
		getline(cin, exit);
		if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
			continue;
		}
		else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
			return;
		}
		cout << "\nPlease Choose From Exist ID\n";
	}
	add_to_news_file(arr_news, info[stoi(news.project_id) - 1][0], "data/News.txt");
}



//Add Data To External Files
void add_to_projects_file(string arr_project[4], string filePath) {
	ofstream myfile;
	myfile.open(filePath, ios::out | ios::app);
	myfile << arr_project[0] << endl << arr_project[1] << endl << arr_project[2] << endl << arr_project[3] << "\n--finish--\n";
	myfile.close();
	cout << "\nAdded Successfully" << endl << endl;
}
void add_to_news_file(string arr_news[4], string project_title, string filePath) {
	ofstream myfile;
	myfile.open(filePath, ios::out | ios::app);
	myfile << arr_news[0] << endl << arr_news[1] << endl << arr_news[2] << endl << arr_news[3] << endl << project_title << "\n--finish--\n";
	myfile.close();
	cout << "\nAdded Successfully" << endl << endl;
}



//Handle Data Of External Files
vector<vector<string>> data_projects_handle() {
	vector<string> data = read_data_from_File("data/Projects.txt");
	vector<vector<string>> info;
	vector<string> project;
	int id = 0;
	for (int i = 0;i < data.size();i++) {
		if (data[i] == "--finish--") {
			id += 1;
			project.push_back(to_string(id));
			info.push_back(project);
			project.clear();
		}
		else {
			project.push_back(data[i]);
		}
	}
	return info;
}
vector<vector<string>> data_news_handle() {
	vector<string> data = read_data_from_File("data/News.txt");
	vector<vector<string>> info;
	vector<string> news;
	int id = 0;
	for (int i = 0;i < data.size();i++) {
		if (data[i] == "--finish--") {
			id += 1;
			news.push_back(to_string(id));
			info.push_back(news);
			news.clear();
		}
		else {
			news.push_back(data[i]);
		}
	}
	return info;
}



//Display All Data In External Files
void display_data_of_projects(vector<vector<string>> info) {
	if (info.size() == 0) {
		cout << "--------------Sorry, No Found data!!!--------------" << endl;
		return;
	}
	for (int i = 0;i < info.size();i++) {
		cout << endl << i + 1 << "-Project : " << endl;

		cout << "--------Project Title => " << info[i][0] << endl;

		cout << "--------Start Date => " << info[i][1] << endl;

		cout << "--------End Date => " << info[i][2] << endl;

		cout << "--------Project Brief => " << info[i][3] << endl;

		cout << "--------Project ID => " << info[i][info[i].size() - 1] << endl;
	}
	cout << endl;
}
void display_data_of_news(vector<vector<string>> info) {
	if (info.size() == 0) {
		cout << "--------------Sorry, No Found data!!!--------------" << endl;
		return;
	}
	for (int i = 0;i < info.size();i++) {
		cout << endl << i + 1 << "-News : " << endl;

		cout << "--------News Title => " << info[i][0] << endl;

		cout << "--------News Publish Date => " << info[i][1] << endl;

		cout << "--------News Brief => " << info[i][2] << endl;

		cout << "--------Project ID => " << info[i][info[i].size() - 3] << endl;

		cout << "--------Project Title => " << info[i][info[i].size() - 2] << endl;

		cout << "--------News ID => " << info[i][info[i].size() - 1] << endl;

	}
	cout << endl;
}



//Clear All Data Of External Files
void clear_all_projects_data() {
	ofstream ofs;
	ofs.open("data/Projects.txt", ofstream::out | ofstream::trunc);
	ofs.close();
}
void clear_all_news_data() {
	ofstream ofs;
	ofs.open("data/News.txt", ofstream::out | ofstream::trunc);
	ofs.close();
}



//Delete item From file
void delete_project() {
	vector<string> data = read_data_from_File("data/Projects.txt");
	vector<vector<string>> info = data_projects_handle();
	display_data_of_projects(info);
	string Id;

	//Avoid Error
	getline(cin, Id);

	cout << "Enter Project ID That You Want To Delete : ";
	getline(cin, Id);
	int ID = stoi(Id);
	if (ID && info.size() >= ID && ID > 0) {
		info.erase(info.begin() + (ID - 1));
		clear_all_projects_data();
		for (int i = 0;i < info.size();i++) {
			ofstream myfile;
			myfile.open("data/Projects.txt", ios::out | ios::app);
			myfile << info[i][0] << endl << info[i][1] << endl << info[i][2] << endl << info[i][3] << "\n--finish--\n";
			myfile.close();
		}
		cout << "\nProject Deleted Successfully" << endl << endl;
		return;
	}
	else {
		cout << "Project ID is'nt exist, Please Choose From Above IDs\n";

		//Recursion
		delete_project();
	}
}
void delete_news() {
	vector<string> data = read_data_from_File("data/News.txt");
	vector<vector<string>> info = data_news_handle();
	display_data_of_news(info);
	string Id;

	//Avoid Error
	getline(cin, Id);

	cout << "Enter News ID That You Want To Delete : ";
	getline(cin, Id);
	int ID = stoi(Id);
	if (ID && info.size() >= ID && ID > 0) {
		info.erase(info.begin() + (ID - 1));
		clear_all_news_data();
		for (int i = 0;i < info.size();i++) {
			ofstream myfile;
			myfile.open("data/News.txt", ios::out | ios::app);
			myfile << info[i][0] << endl << info[i][1] << endl << info[i][2] << endl << info[i][3] << info[i][4] << "\n--finish--\n";
			myfile.close();
		}
		cout << "\News Deleted Successfully" << endl << endl;
		return;
	}
	else {
		cout << "News ID is'nt exist, Please Choose From Above IDs\n";

		//Recursion
		delete_news();
	}
}



//Listing Data By Filter by User
vector<vector<string>> filter_projects_by_user() {
	int number = 0;

	string chosen;

	vector<vector<string>> info_project = data_projects_handle();
	vector<vector<string>> info_project_filter;

	cout << "Enter 1 if you want to filter by Project Title\n";
	cout << "Enter 2 if you want to filter by Start Date\n";
	cout << "Enter 3 if you want to filter by End Date\n";
	cout << "Enter 4 if you want to filter by Project ID\n";
	cout << "Enter 0 if you want to back\n";


	cout << "\nEnter Chosen Number : ";
	cin >> number;

	while (true) {
		if (number == 0) {
			break;
		}
		else if (number == 1) {
			getline(cin, chosen);
			cout << "\nEnter Title : ";
			getline(cin, chosen);
			break;
		}
		else if (number == 2) {
			getline(cin, chosen);
			cout << "\nEnter Start Date : ";
			getline(cin, chosen);
			break;
		}
		else if (number == 3) {
			getline(cin, chosen);
			cout << "\nEnter End Date : ";
			getline(cin, chosen);
			break;
		}
		else if (number == 4) {
			getline(cin, chosen);
			cout << "\nEnter ID : ";
			getline(cin, chosen);
			break;
		}
		else {
			cout << "\nPlease Choose Correct Number....\n\n";

			//Recursion
			filter_projects_by_user();
		}
	}


	for (int i = 0;i < info_project.size();i++) {
		if (number == 0) {
			break;
		}
		else if (number == 1) {
			if (info_project[i][0] == chosen) {
				info_project_filter.push_back(info_project[i]);
			}
		}
		else if (number == 2) {
			if (info_project[i][1] == chosen) {
				info_project_filter.push_back(info_project[i]);
			}
		}
		else if (number == 3) {
			if (info_project[i][2] == chosen) {
				info_project_filter.push_back(info_project[i]);
			}
		}
		else if (number == 4) {
			if (info_project[i][info_project[i].size() - 1] == chosen) {
				info_project_filter.push_back(info_project[i]);
			}
		}
	}
	cout << "\n-------Result Of Filter-------\n";
	return info_project_filter;
}
vector<vector<string>> filter_news_by_user() {
	int number = 0;

	string chosen;

	vector<vector<string>> info_news = data_news_handle();
	vector<vector<string>> info_news_filter;

	cout << "Enter 1 if you want to filter by Project Title or any word contained by project title\n";
	cout << "Enter 2 if you want to filter by Project ID\n";
	cout << "Enter 0 if you want to back\n";

	cout << "\nEnter Chosen Number : ";
	cin >> number;

	while (true) {
		if (number == 0) {
			break;
		}
		else if (number == 1) {
			cout << "\nEnter Title or Any word contained by title : ";
			cin >> chosen;
			break;
		}
		else if (number == 2) {
			cout << "All Project Titles and IDs of news: \n";
			vector<vector<string>> info = data_news_handle();
			bool id_exist = false;
			for (int i = 0;i < info.size();i++) {
				cout << endl << i + 1 << "-news :\n";
				cout << "--------Project Title => " << info[i][4] << endl;

				cout << "--------Project ID => " << info[i][3] << endl;
			}
			while (true) {
				cout << "\nChoose Project ID : ";
				cin >> chosen;
				for (int i = 0;i < info.size();i++) {
					if (info[i][3] == chosen) {
						id_exist = true;
						break;
					}
				}
				if (id_exist) {
					break;
				}
				cout << "\nPlease Choose From Exist IDs\n";
			}

			break;
		}
		else {
			cout << "\nPlease Choose Correct Number....\n\n";

			//Recursion
			filter_news_by_user();
		}
	}
	for (int i = 0;i < info_news.size();i++) {
		if (number == 0) {
			break;
		}
		else if (number == 1) {
			if (info_news[i][4] == chosen) {
				info_news_filter.push_back(info_news[i]);
			}
			else {
				vector<string> splited = split_string_by_space(info_news[i][4]);
				for (int x = 0;x < splited.size();x++) {
					if (splited[x] == chosen) {
						info_news_filter.push_back(info_news[i]);
						break;
					}
				}
			}
		}
		else if (number == 2) {
			if (info_news[i][3] == chosen) {
				info_news_filter.push_back(info_news[i]);
			}
		}
	}
	cout << "\n-------Result Of Filter-------\n";
	return info_news_filter;
}



//Split String By Space
vector<string> split_string_by_space(string str) {
	vector<string> splited;
	string word;
	for (int i = 0;i < str.size();i++) {
		if (str[i] == ' ') {
			splited.push_back(word);
			word = "";
		}
		else {
			word.push_back(str[i]);
		}
	}
	splited.push_back(word);
	return splited;
}



//Read Data From External Files
vector<string> read_data_from_File(string filePath) {
	vector<string> fileLines;
	string line;
	ifstream myfile(filePath);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			fileLines.push_back(line);
		}
	}
	else {
		cout << "--------------Sorry, No Found data!!!--------------" << endl;
	}
	return fileLines;
}



//System Run Function
void system() {
	string number;
	vector<vector<string>> info_project = data_projects_handle();
	vector<vector<string>> info_news = data_news_handle();
	while (number != "exist" || number != "Exist") {
		info_project = data_projects_handle();
		info_news = data_news_handle();
		cout << "Enter 1 if you want to add new project." << endl;
		cout << "Enter 2 if you want to add new news." << endl;
		cout << "Enter 3 if you want to display all projects on screen." << endl;
		cout << "Enter 4 if you want to display all news on screen." << endl;
		cout << "Enter 5 if you want to filter projects." << endl;
		cout << "Enter 6 if you want to filter news." << endl;
		cout << "Enter 7 if you want to clear all data of projects." << endl;
		cout << "Enter 8 if you want to clear all data of news." << endl;
		cout << "Enter 9 if you want to Delete Project." << endl;
		cout << "Enter 10 if you want to Delete news." << endl;
		cout << "Enter exist if you want to exit." << endl;
		cout << "\nYou Chosen Number : ";
		cin >> number;

		if (number == "1") {
			add_new_project_info();
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "2") {
			add_new_news_info();
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "3") {
			display_data_of_projects(info_project);
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "4") {
			display_data_of_news(info_news);
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "5") {
			info_project = filter_projects_by_user();
			display_data_of_projects(info_project);
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "6") {
			info_news = filter_news_by_user();
			display_data_of_news(info_news);
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "7") {
			clear_all_projects_data();
			cout << "\n-----Deleted All Project Data Success-----\n";
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "8") {
			clear_all_news_data();
			cout << "\n-----Deleted All News Data Success-----\n";
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "9") {
			delete_project();
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "10") {
			delete_news();
			cout << "-------------------------------------------" << endl << endl;
		}
		else {
			cout << "\nPlease Choose Correct Number!!\n\n";

			//Recursion
			system();
		}
	}
}