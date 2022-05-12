#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include<string>

using namespace std;

#define size_project 4

#define size_news 4

#define all_project_data 5

#define all_news_data 6

#define pro_file_path "data/Projects.txt"

#define news_file_path "data/News.txt"

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
vector<array<string, all_project_data>> data_projects_handle();
vector<array<string, all_news_data>> data_news_handle();


//Display All Data In External Files
void display_data_of_projects(vector<array<string, all_project_data>> info);
void display_data_of_news(vector<array<string, all_news_data>> info);


//Listing Data By Filter by User
vector<array<string, all_project_data>> filter_projects_by_user();
vector<array<string, all_news_data>> filter_news_by_user();


//Delete item From file
void delete_project();
void delete_news();


//Split String By Space
vector<string> split_string_by_space(string str);



//Check News of deleted Project
void check_news_of_deleted_project(vector<array<string, all_project_data>> data_pro);

//Check If Input Is Number Or Not
bool check_number(string str);


//Read Data From External Files
vector<string> read_data_from_File(string filePath);


//Update Data
void update_data_project();
void update_data_news();


//Recycle Project Data
void recycle_project_data(vector<array<string, all_project_data>> info);
void recycle_news_data(vector<array<string, all_news_data>> info);


//System Run Function
void system();


void main() {
	cout << endl << "--------------Welcome To Enigma System--------------" << endl << endl;

	system();
}


//Add New Project And News
void add_new_project_info() {
	string arr_project[size_project];
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

	add_to_projects_file(arr_project, pro_file_path);
}
void add_new_news_info() {
	string arr_news[size_news];
	vector<array<string, all_project_data>> info = data_projects_handle();
	new_news news;
	bool is_exist = false;

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
		is_exist = false;
		for (int i = 0;i < info.size();i++) {
			if (news.project_id == info[i][4]) {
				is_exist = true;
				string pro_title = info[stoi(news.project_id) - 1][0];
				add_to_news_file(arr_news, pro_title, news_file_path);
				break;
			}
		}
		if (is_exist) {
			break;
		}
		string exit;
		cout << "\nAre You Want To Exit (no/yes)?";
		getline(cin, exit);
		if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
			continue;
		}
		else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
			break;
		}
		cout << "\nPlease Choose From Exist ID\n";
	}
}



//Add Data To External Files
void add_to_projects_file(string arr_project[4], string filePath) {
	ofstream myfile;
	myfile.open(filePath, ios::out | ios::app);
	for (int i = 0;i < size_project;i++) {
		myfile << arr_project[i] << endl;
	}
	myfile << "--finish--\n";
	myfile.close();
}
void add_to_news_file(string arr_news[4], string project_title, string filePath) {
	ofstream myfile;
	myfile.open(filePath, ios::out | ios::app);
	for (int i = 0;i < size_news;i++) {
		myfile << arr_news[i] << endl;
	}
	myfile << project_title << "\n--finish--\n";
	myfile.close();
}



//Handle Data Of External Files
vector<array<string, all_project_data>> data_projects_handle() {
	vector<string> data = read_data_from_File("data/Projects.txt");
	vector<array<string, all_project_data>> info;
	array<string, all_project_data> project;
	int id = 0;
	int index = 0;
	for (int i = 0;i < data.size();i++) {
		if (data[i] == "--finish--") {
			id += 1;
			project[index] = to_string(id);
			info.push_back(project);
			index = 0;
			continue;
		}
		else {
			project[index] = data[i];
		}
		index += 1;
	}
	return info;
}
vector<array<string, all_news_data>> data_news_handle() {
	vector<string> data = read_data_from_File("data/News.txt");
	vector<array<string, all_news_data>> info;
	array<string, all_news_data> news;
	int id = 0;
	int index = 0;
	for (int i = 0;i < data.size();i++) {
		if (data[i] == "--finish--") {
			id += 1;
			news[index] = to_string(id);
			info.push_back(news);
			index = 0;
			continue;
		}
		else {
			news[index] = data[i];
		}
		index += 1;
	}
	return info;
}



//Display All Data In External Files
void display_data_of_projects(vector<array<string, all_project_data>> info) {
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
void display_data_of_news(vector<array<string, all_news_data>> info) {
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
	ofs.open(pro_file_path, ofstream::out | ofstream::trunc);
	ofs.close();
	clear_all_news_data();
}
void clear_all_news_data() {
	ofstream ofs;
	ofs.open(news_file_path, ofstream::out | ofstream::trunc);
	ofs.close();
}



//Delete item From file
void delete_project() {
	vector<string> data = read_data_from_File(pro_file_path);
	vector<array<string, all_project_data>> info = data_projects_handle();

	if (info.size() == 0) {
		cout << "\nSorry no data To Delete!!\n\n";
		return;
	}

	display_data_of_projects(info);
	string Id;

	//Avoid Error
	getline(cin, Id);

	while (true) {
		cout << "\nEnter Project ID That You Want To Delete : ";
		getline(cin, Id);
		int ID = 0;
		if (check_number(Id)) {
			ID = stoi(Id);
		}
		else {
			cout << "\n\Please Enter Correct Id\n";
			string exit;
			cout << "\nAre You Want To Exit (no/yes)?";
			getline(cin, exit);
			if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
				continue;
			}
			else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
				break;
			}
		}
		if (info.size() >= ID && ID > 0) {
			info.erase(info.begin() + (ID - 1));
			clear_all_projects_data();
			check_news_of_deleted_project(info);
			for (int i = 0;i < info.size();i++) {
				string arr_pro[size_project];
				for (int x = 0;x < size_project;x++) {
					arr_pro[x] = info[i][x];
				}
				add_to_projects_file(arr_pro, pro_file_path);
			}
			cout << "\nProject Deleted Successfully" << endl << endl;
			break;
		}
		else {
			cout << "\nProject ID is'nt exist, Please Choose From Above IDs\n";
			string exit;
			cout << "\nAre You Want To Exit (no/yes)?";
			getline(cin, exit);
			if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
				continue;
			}
			else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
				break;
			}
		}
	}
}
void delete_news() {
	vector<string> data = read_data_from_File("data/News.txt");
	vector<array<string, all_news_data>> info = data_news_handle();
	if (info.size() == 0) {
		cout << "\nSorry no data To Delete!!\n\n";
		return;
	}
	display_data_of_news(info);
	string Id;

	//Avoid Error
	getline(cin, Id);

	while (true) {
		cout << "\nEnter News ID That You Want To Delete : ";
		getline(cin, Id);
		int ID = 0;
		if (check_number(Id)) {
			ID = stoi(Id);
		}
		else {
			cout << "\n\Please Enter Correct Id\n";
			string exit;
			cout << "\nAre You Want To Exit (no/yes)?";
			getline(cin, exit);
			if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
				continue;
			}
			else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
				break;
			}
		}
		if (ID && info.size() >= ID && ID > 0) {
			info.erase(info.begin() + (ID - 1));
			clear_all_news_data();
			for (int i = 0;i < info.size();i++) {
				string arr_news[4];
				for (int x = 0;x < size_news;x++) {
					arr_news[x] = info[i][x];
				}
				add_to_news_file(arr_news, info[i][4], news_file_path);
			}
			cout << "\nNews Deleted Successfully" << endl << endl;
			return;
		}
		else {
			cout << "\nNews ID is'nt exist, Please Choose From Above IDs\n";
			string exit;
			cout << "\nAre You Want To Exit (no/yes)?";
			getline(cin, exit);
			if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
				continue;
			}
			else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
				break;
			}
		}
	}
}



//Listing Data By Filter by User
vector<array<string, all_project_data>> filter_projects_by_user() {
	string number;
	string chosen;

	vector<array<string, all_project_data>> info_project = data_projects_handle();
	vector<array<string, all_project_data>> info_project_filter;

	cout << "Enter 1 if you want to filter by Project Title\n";
	cout << "Enter 2 if you want to filter by Start Date\n";
	cout << "Enter 3 if you want to filter by End Date\n";
	cout << "Enter 4 if you want to filter by Project ID\n";
	cout << "Enter 0 if you want to back\n";

	//avoid error
	getline(cin, number);

	while (true) {
		cout << "\nEnter Chosen Number : ";
		getline(cin, number);

		if (number == "0") {
			break;
		}
		else if (number == "1") {
			cout << "\nEnter Title : ";
			getline(cin, chosen);
			break;
		}
		else if (number == "2") {
			cout << "\nEnter Start Date : ";
			getline(cin, chosen);
			break;
		}
		else if (number == "3") {
			cout << "\nEnter End Date : ";
			getline(cin, chosen);
			break;
		}
		else if (number == "4") {
			cout << "\nEnter ID : ";
			getline(cin, chosen);
			break;
		}
		else {
			cout << "\nPlease Choose Correct Number....\n\n";

			string exit;

			cout << "\nAre You Want To Exit (no/yes)?";
			getline(cin, exit);
			if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
				continue;
			}
			else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
				break;
			}
		}
	}


	for (int i = 0;i < info_project.size();i++) {
		if (number == "0") {
			break;
		}
		else if (number == "1") {
			if (info_project[i][0] == chosen) {
				info_project_filter.push_back(info_project[i]);
			}
		}
		else if (number == "2") {
			if (info_project[i][1] == chosen) {
				info_project_filter.push_back(info_project[i]);
			}
		}
		else if (number == "3") {
			if (info_project[i][2] == chosen) {
				info_project_filter.push_back(info_project[i]);
			}
		}
		else if (number == "4") {
			if (info_project[i][info_project[i].size() - 1] == chosen) {
				info_project_filter.push_back(info_project[i]);
			}
		}
	}
	cout << "\n-------Result Of Filter-------\n";
	return info_project_filter;
}
vector<array<string, all_news_data>> filter_news_by_user() {
	string number;

	string chosen;

	vector<array<string, all_news_data>> info_news = data_news_handle();
	vector<array<string, all_news_data>> info_news_filter;

	cout << "Enter 1 if you want to filter by Project Title or any word contained by project title\n";
	cout << "Enter 2 if you want to filter by Project ID\n";
	cout << "Enter 0 if you want to back\n";

	//avoid error
	getline(cin, number);

	while (true) {
		cout << "\nEnter Chosen Number : ";

		//avoid error
		getline(cin, number);

		if (number == "0") {
			break;
		}
		else if (number == "1") {
			cout << "\nEnter Title or Any word contained by title : ";
			getline(cin, chosen);
			break;
		}
		else if (number == "2") {
			//cout << "All Project Titles and IDs of news: \n";
			vector<array<string, all_news_data>> info = data_news_handle();
			bool id_exist = false;
			/*for (int i = 0;i < info.size();i++) {
				cout << endl << i + 1 << "-news :\n";
				cout << "--------Project Title => " << info[i][4] << endl;

				cout << "--------Project ID => " << info[i][3] << endl;
			}*/
			while (true) {
				cout << "\nChoose Project ID : ";
				getline(cin, chosen);
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

			string exit;

			cout << "\nAre You Want To Exit (no/yes)?";
			getline(cin, exit);
			if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
				continue;
			}
			else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
				break;
			}
		}
	}
	for (int i = 0;i < info_news.size();i++) {
		if (number == "0") {
			break;
		}
		else if (number == "1") {
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
		else if (number == "2") {
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



//Check If Input Is Number Or Not
bool check_number(string str) {
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
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



//Check News of deleted Project
void check_news_of_deleted_project(vector<array<string, all_project_data>> data_pro) {
	vector<array<string, all_news_data>> data_news = data_news_handle();
	for (int i = 0;i < data_news.size();i++) {
		string pro_id = data_news[i][data_news[i].size() - 3];
		bool exist = false;
		for (int x = 0;x < data_pro.size();x++) {
			if (data_pro[x][data_pro[x].size() - 1] == pro_id) {
				exist = true;
				break;
			}
		}
		if (!exist) {
			data_news.erase(data_news.begin()+ i);
			clear_all_news_data();
			for (int i = 0;i < data_news.size();i++) {
				string arr_news[4];
				for (int x = 0;x < size_news;x++) {
					arr_news[x] = data_news[i][x];
				}
				add_to_news_file(arr_news, data_news[i][4], news_file_path);
			}
		}
	}

}



//Update Data
void update_data_project() {
	vector<array<string, all_project_data>> info = data_projects_handle();
	display_data_of_projects(info);
	string Id;
	while (true) {
		cout << "\nEnter Id Of Update Project : ";
		cin >> Id;
		if (check_number(Id)) {
			if (stoi(Id) > info.size()) {
				cout << "\n\n Wrong Id , Please Enter Correct Id\n\n";

				string exit;

				//Void Error
				getline(cin, exit);

				cout << "\nAre You Want To Exit (no/yes)?";
				getline(cin, exit);
				if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
					continue;
				}
				else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
					return;
				}
			}
			else {
				break;
			}
		}
		else {
			cout << "\n\n Wrong Id , Please Enter Correct Id\n";

			string exit;

			//Void Error
			getline(cin, exit);

			cout << "\nAre You Want To Exit (no/yes)?";
			getline(cin, exit);
			if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
				continue;
			}
			else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
				return;
			}
		}
	}
	int id = stoi(Id);
	while (true) {
		cout << "Enter 1 If You Want Update Title\n";
		cout << "Enter 2 If You Want Update Start Date\n";
		cout << "Enter 3 If You Want Update End Date\n";
		cout << "Enter 4 If You Want Update Brief\n";
		cout << "Enter exit to Back\n";
		string number;
		cout << "The Chosen Number : ";
		cin >> number;

		

		if (number == "1") {
			string title;

			//avoid error
			getline(cin, title);

			cout << "\nOld Project Title : " << info[id - 1][0] << endl;
			cout << "Enter New Project Title : ";
			getline(cin, title);
			info[id - 1][0] = title;
			cout << "\n\nProject Updated Successfully\n";
			break;
		}
		else if (number == "2") {
			string start_date;

			//avoid error
			getline(cin, start_date);

			cout << "\nOld Start Date : " << info[id - 1][1] << endl;
			cout << "Enter New Start Date : ";
			getline(cin, start_date);
			info[id - 1][1] = start_date;
			cout << "\n\nProject Updated Successfully\n";
			break;
		}
		else if (number == "3") {
			string end_date;
			//avoid error
			getline(cin, end_date);

			cout << "\nOld End Date : " << info[id - 1][2] << endl;
			cout << "Enter New End Date : ";
			getline(cin , end_date);
			info[id - 1][2] = end_date;
			cout << "\n\nProject Updated Successfully\n";
			break;
		}
		else if (number == "4") {
			string Brief;
			//avoid error
			getline(cin, Brief);

			cout << "\nOld Brief : " << info[id - 1][3] << endl;
			cout << "Enter New Brief : ";
			getline(cin , Brief);
			info[id - 1][3] = Brief;
			cout << "\n\nProject Updated Successfully\n";
			break;
		}
		else if (number == "exit" || number == "Exit") {
			break;
		}
		else {
			cout << "\n\nWrong Number , Please Choose Correct Number\n";
			string exit;

			//Void Error
			getline(cin, exit);

			cout << "\nAre You Want To Exit (no/yes)?";
			getline(cin, exit);
			if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
				continue;
			}
			else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
				break;
			}
			continue;
		}
	}
	recycle_project_data(info);
}
void update_data_news() {
	vector<array<string, all_news_data>> info = data_news_handle();
	display_data_of_news(info);
	string Id;
	while (true) {
		cout << "\nEnter Id Of Update News : ";
		cin >> Id;
		if (check_number(Id)) {
			if (stoi(Id) > info.size()) {
				cout << "\n\n Wrong Id , Please Enter Correct Id\n\n";
				string exit;

				//Void Error
				getline(cin, exit);

				cout << "\nAre You Want To Exit (no/yes)?";
				getline(cin, exit);
				if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
					continue;
				}
				else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
					return;
				}
			}
			else {
				break;
			}
		}
		else {
			cout << "\n\n Wrong Id , Please Enter Correct Id\n\n";

			string exit;

			//Void Error
			getline(cin, exit);

			cout << "\nAre You Want To Exit (no/yes)?";
			getline(cin, exit);
			if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
				continue;
			}
			else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
				return;
			}
		}
	}
	int id = stoi(Id);
	while (true) {
		cout << "Enter 1 If You Want Update Title\n";
		cout << "Enter 2 If You Want Update Publish Date\n";
		cout << "Enter 3 If You Want Update Brief\n";
		cout << "Enter 4 If You Want Update Project Id\n";
		cout << "Enter exit to Back\n";
		string number;
		cout << "The Chosen Number : ";
		cin >> number;
		if (number == "1") {
			string title;
			cout << "\nOld News Title : " << info[id - 1][0] << endl;
			cout << "Enter New News Title : ";
			cin >> title;
			info[id - 1][0] = title;
			cout << "\n\nNews Updated Successfully\n";
			break;
		}
		else if (number == "2") {
			string publish_date;
			cout << "\nOld Publish Date : " << info[id - 1][1] << endl;
			cout << "Enter New Publish Date : ";
			cin >> publish_date;
			info[id - 1][1] = publish_date;
			cout << "\n\nNews Updated Successfully\n";
			break;
		}
		else if (number == "3") {
			string Brief;
			cout << "\nOld Brief : " << info[id - 1][3] << endl;
			cout << "Enter New Brief : ";
			cin >> Brief;
			info[id - 1][3] = Brief;
			cout << "\n\nNews Updated Successfully\n";
			break;
		}
		else if (number == "4") {
			string Pro_Id;
			cout << "\nOld Project Id : " << info[id - 1][4] << endl;
			cout << "Enter New Brief : ";
			cin >> Pro_Id;
			info[id - 1][3] = Pro_Id;
			cout << "\n\nNews Updated Successfully\n";
			break;
		}
		else if (number == "exit" || number == "Exit") {
			break;
		}
		else {
			cout << "\n\nWrong Number , Please Choose Correct Number\n";
			string exit;

			//Void Error
			getline(cin, exit);

			cout << "\nAre You Want To Exit (no/yes)?";
			getline(cin, exit);
			if (exit == "No" || exit == "no" || exit == "n" || exit == "N") {
				continue;
			}
			else if (exit == "Yes" || exit == "yes" || exit == "y" || exit == "Y") {
				break;
			}

			continue;
		}
	}
	recycle_news_data(info);
}



//Recycle Project Data
void recycle_project_data(vector<array<string, all_project_data>> info) {
	clear_all_projects_data();
	for (int i = 0;i < info.size();i++) {
		string arr_lines[4];
		for (int x = 0; x < info[i].size() - 1;x++) {
			arr_lines[x] = info[i][x];
		}
		add_to_projects_file(arr_lines, "data/Projects.txt");
	}
}
void recycle_news_data(vector<array<string, all_news_data>> info) {
	clear_all_news_data();
	for (int i = 0;i < info.size();i++) {
		string arr_lines[4];
		for (int x = 0; x < info[i].size() - 2;x++) {
			arr_lines[x] = info[i][x];
		}
		add_to_news_file(arr_lines, info[i][5], "data/News.txt");
	}
}



//System Run Function
void system() {
	string number;
	vector<array<string, all_project_data>> info_project = data_projects_handle();
	vector<array<string, all_news_data>> info_news = data_news_handle();
	while (true) {
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
		cout << "Enter 9 if you want to delete project." << endl;
		cout << "Enter 10 if you want to delete news." << endl;
		cout << "Enter 11 if you want to update projects." << endl;
		cout << "Enter 12 if you want to update news." << endl;
		cout << "Enter exist if you want to exit." << endl;
		cout << "\nChosen Number : ";
		cin >> number;

		if (number == "1") {
			add_new_project_info();
			cout << "\nAdded Successfully" << endl << endl;
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "2") {
			add_new_news_info();
			cout << "\nAdded Successfully" << endl << endl;
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
		else if (number == "11") {
			update_data_project();
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "12") {
			update_data_news();
			cout << "-------------------------------------------" << endl << endl;
		}
		else if (number == "exit" || number == "Exit") {
			break;
		}
		else {
			cout << "\nPlease Choose Correct Number!!\n\n";

			//Recursion
			system();
		}
	}
}