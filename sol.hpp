#ifndef SOLUTION
#define SOLUTION
#include <bits/stdc++.h>
using namespace std;


class Faculty
{
public:
	string name;
	set<pair<int,int>> slots;

	Faculty();
	~Faculty(){};	
};

Faculty::Faculty()
{
	name = "ANONYMOUS";
}


class Room
{
public:
	int size;
	set<pair<int,int>> slots;

	Room();
	~Room(){};
};

Room::Room()
{
	size = 0;
}

class Course
{
public:
	set<pair<int,int>> slots;
	Course();
	~Course(){};	
};

Course::Course()
{

}

class SubDay
{
public:
	set<int> days;
	SubDay();
	~SubDay(){};	
};

SubDay::SubDay()
{

}

class Subject
{
public:
    string c_id;
    string s_id;
    string f_id;
    string r_id;
    bool tut;
    vector<string> r_pref;
    int size;
    set<string> groups;
    int duration;
    int cont_slot_req;
    set<pair<int,int>> slot;

	Subject();
	~Subject(){};
	void printDetails();
	string printTableDetails();
};

Subject::Subject()
{

}

void Subject::printDetails()
{
	cout<<"\n c_id: "<<c_id;
	cout<<"\n s_id: "<<s_id;
	cout<<"\n f_id: "<<f_id;
	cout<<"\n tut: "<<tut;
	cout<<"\n groups: ";
	for(auto& grp:groups)
		cout<<grp<<" ";
	cout<<"\n slot: ";
	for(auto s:slot)
		cout<<s.first<<" "<<s.second<<" ";
	cout<<"\n-------------";
}

string Subject::printTableDetails()
{
	string s = s_id + " " + f_id + " " + c_id + " " + r_id;
	for(auto grp:groups)
	{
		s = s + " " + grp;
	}
	return s;
}

class Solution
{
public:
	int DAYS;
	int SLOTS;
	int SLOT_LENGHT;
	int RoomError = 10;
	int T_WIDTH = 20;
	int T_SMALL = 8;
	string DATABASE_DIR = "DATABASE/";
	unsigned int seed = time(NULL);
	vector<Subject*> subjects;
	map<string,Room*> Rooms;
	set<int> LunchSlots;
	set<string> OpenElectives;
	map<string,Faculty*> Faculties;
	map<string,Course*> Courses;
	map<string,SubDay*> SubsDay;
	vector<Subject*> garbage;

	Solution();
	~Solution(){};

	void setSlots();
	
	void setRooms();
	
	void setLunch();
	
	void setSubjects();
	
	bool runBestFit();
	
	bool dayAllowed(const Subject* sub, const int& day);
	
	bool facultyAllowed(const Subject* sub, const pair<int,int>& slot);
	
	bool courseAllowed(const Subject* sub, const pair<int,int>& slot);
	
	bool lunchAllowed(const Subject* sub, const pair<int,int>& slot);
	
	string AllotRoom(Subject* sub, const pair<int,int>& slot);

	void printTable(int iteration);

	void makeClassView(int iteration);
	void makeFacultyView(int iteration);
	void makeRoomView(int iteration);

	void resetData();

};

Solution::Solution()
{
	DAYS = SLOTS = 5;
	SLOT_LENGHT = 60;
}

void Solution::setSlots()
{
	cin>>DAYS;
	cin>>SLOTS;
	cin>>SLOT_LENGHT;
}

void Solution::setRooms()
{
	int num;
	cin>>num;
	while(num--){
		string id;
		cin>>id;
		if(Rooms.find(id)==Rooms.end())
			Rooms[id] = new Room();
		cin>>Rooms[id]->size;
	}
}

void Solution::setLunch()
{
	int num;
	cin>>num;
	int slot;
	while(num--){
		cin>>slot;
		LunchSlots.insert(slot-1);
	}
}

void Solution::setSubjects()
{
	int num_courses;
	cin>>num_courses;
	while(num_courses--){
		string c_id;
		cin>>c_id;
		int num_sub;
		cin>>num_sub;
		int num_grps;
		cin>>num_grps;
		int size;
		cin>>size;
		bool hasOpenElective;
		cin>>hasOpenElective;
		if(hasOpenElective)
			OpenElectives.insert(c_id);
		while(num_sub--){
			string s_id;
			cin>>s_id;
			string f_id;
			cin>>f_id;
			bool isLab;
			cin>>isLab;
			int lect;
			cin>>lect;
			int tut;
			cin>>tut;
			int duration;
			cin>>duration;
			int fixed;
			cin>>fixed;
			vector<string> r_pref;
			while(fixed--){
				string r_id;
				cin>>r_id;
				r_pref.push_back(r_id);
			}
			if(isLab)
			{
				for(int i=0;i<lect;i++)
				{
					for(int j=1;j<=num_grps;j++)
					{
						Subject* sub = new Subject();
						sub->s_id = s_id;
						sub->f_id = f_id;
						sub->c_id = c_id;
						sub->tut = false;
						sub->duration = duration;
						sub->size = size/num_grps;
						sub->cont_slot_req = (duration - 1)/SLOT_LENGHT + 1;
						sub->groups.insert("Grp_" + to_string(j));
						sub->r_pref = r_pref;
						subjects.push_back(sub);
					}
				}
				continue;
			} else {
				for(int i=0;i<lect;i++)
				{
					Subject* sub = new Subject();
					sub->s_id = s_id;
					sub->f_id = f_id;
					sub->c_id = c_id;
					sub->tut = false;
					sub->r_pref = r_pref;
					sub->duration = duration;
					sub->size = size;
					sub->cont_slot_req = (duration - 1)/SLOT_LENGHT + 1;
					for(int j=1;j<=num_grps;j++)
					{
						sub->groups.insert("Grp_" + to_string(j));
					}
					subjects.push_back(sub);
				}
			}

			for(int i=0;i<tut;i++)
			{
				for(int j=1;j<=num_grps;j++)
				{
					Subject* sub = new Subject();
					sub->s_id = s_id;
					sub->f_id = f_id;
					sub->c_id = c_id;
					sub->tut = true;
					sub->duration = duration;
					sub->size = size/num_grps;
					sub->cont_slot_req = (duration - 1)/SLOT_LENGHT + 1;
					sub->groups.insert("Grp_" + to_string(j));
					subjects.push_back(sub);
				}
			}
		}
	}
}

bool Solution::dayAllowed(const Subject* sub, const int& day)
{
	string sub_id = sub->c_id + sub->s_id + to_string(sub->tut);
	for(auto& grp: sub->groups)
	{
		if(SubsDay.find(sub_id + grp)==SubsDay.end())
			SubsDay[sub_id + grp] = new SubDay();
		if(SubsDay[sub_id + grp]->days.count(day))
			return false;
	}
	return true;
}

bool Solution::facultyAllowed(const Subject* sub, const pair<int,int>& slot)
{
	if(Faculties.find(sub->f_id) == Faculties.end())
		Faculties[sub->f_id] = new Faculty();
	if(Faculties[sub->f_id]->slots.count(slot))
		return false;
	return true;
}

bool Solution::courseAllowed(const Subject* sub, const pair<int,int>& slot)
{
	for(auto grp:sub->groups)
	{
		if(Courses.find(sub->c_id + grp) == Courses.end())
			Courses[sub->c_id + grp] = new Course;
		if(Courses[sub->c_id + grp]->slots.count(slot))
			return false;
	}
	return true;
}

bool Solution::lunchAllowed(const Subject* sub, const pair<int,int>& slot)
{	
	int count = 0;
	int occupied = 0;
	for(int i=slot.second;i<slot.second + sub->cont_slot_req;i++)
	{
		for(auto lunch:LunchSlots)
		{
			if(i == lunch && OpenElectives.count(sub->c_id))
				return false;
			if(i == lunch)
				count++;
		}
	}
	for(auto lunch:LunchSlots)
	{
		for(auto grp:sub->groups)
		{
			if(Courses.find(sub->c_id + grp)==Courses.end())
				Courses[sub->c_id + grp] = new Course;
			if(Courses[sub->c_id + grp]->slots.count(make_pair(slot.first,lunch)))
			{
				occupied++;
				break;
			}

		}
	}
	if(LunchSlots.size() <= count + occupied)
		return false;

	return true;
}

string Solution::AllotRoom(Subject* sub, const pair<int,int>& slot)
{
	string room_id = "-1";
	for(auto room:sub->r_pref)
	{
		if(Rooms.find(room) == Rooms.end())
			Rooms[room] = new Room;
		if(Rooms[room]->slots.count(slot))
			continue;
		return room;
	}
	if(sub->r_pref.size()>0)
		return room_id;
	for(auto room: Rooms)
	{
		if(room.second->slots.count(slot))
			continue;
		if(room.second->size < sub->size + RoomError)
			continue;
		if(room_id == "-1")
		{
			room_id = room.first;
			continue;
		}
		if(Rooms[room_id]->size > room.second->size)
			room_id = room.first;
	}
	return room_id;
}

bool sortPriority(pair<string,int>& p1, pair<string,int>& p2)
{
	return p1.second < p2.second;
}

bool Solution::runBestFit()
{
	shuffle(subjects.begin(), subjects.end(), default_random_engine(seed));
	vector<pair<string,int>> priority;

	for(auto sub: subjects)
	{
		bool found = false;
		for(auto& p:priority)
		{
			if(p.first == sub->f_id)
			{
				found = true;
				p.second += sub->cont_slot_req;
				break;
			}
		}
		if(!found)
			priority.push_back(make_pair(sub->f_id,sub->cont_slot_req));
	}

	while(priority.size()>0)
	{
		sort(priority.begin(),priority.end(),&sortPriority);
		cout<<"\nid: "<<priority[priority.size()-1].first<<" "<<priority[priority.size()-1].second;
		string p_id = priority[priority.size()-1].first;

		pair<int,int> cur_slot;
		for(auto& sub:subjects)
		{
			if(sub->f_id != p_id || sub->slot.size()>0)
				continue;

			cout<<"\nCur Sub: "<<sub->printTableDetails();

			bool slot_found = false;
			
			for(int day=0;day<DAYS;day++)
			{
				if(!dayAllowed(sub,day))
				{
					cout<<" (Day: "<<day<<")";
					continue;
				}

				cur_slot.first = day;

				for(int start=0;start<SLOTS;start++)
				{
					if(sub->cont_slot_req + start > SLOTS)
					{
						cout<<" (Slot Overflow: "<<start<<")";
						continue;
					}

					bool allSlotsPossible = true;

					for(int slot = start;slot < start + sub->cont_slot_req;slot++)
					{
						cur_slot.second = slot;
						if(!facultyAllowed(sub,cur_slot))
						{
							cout<<" (F err: "<<day<<" "<<slot<<")";
							allSlotsPossible = false;
							break;
						}
						if(!courseAllowed(sub,cur_slot))
						{
							cout<<" (C err: "<<day<<" "<<slot<<")";
							allSlotsPossible = false;
							break;
						}
					}
					if(allSlotsPossible == false)
						continue;

					cur_slot.second = start;
					if(!lunchAllowed(sub,cur_slot))
					{
						cout<<" (L err: "<<day<<" "<<start<<")";
						continue;
					}
					string room_alloted = AllotRoom(sub,cur_slot);
					
					if(room_alloted == "-1")
					{
						cout<<" (R err: "<<day<<" "<<start<<")";
						continue;
					}
					slot_found = true;
					cout<<" Found";
					sub->r_id = room_alloted;
					for(int slot = start;slot < start + sub->cont_slot_req;slot++)
					{
						cur_slot.second = slot;
						sub->slot.insert(cur_slot);
						Faculties[sub->f_id]->slots.insert(cur_slot);
						Rooms[room_alloted]->slots.insert(cur_slot);
						for(auto& grp:sub->groups)
						{	
							if(Courses.find(sub->c_id + grp)==Courses.end())
								Courses[sub->c_id + grp] = new Course;
							Courses[sub->c_id + grp]->slots.insert(cur_slot);
						}
					}
					break;
				}
				if(slot_found)
				{
					string sub_id = sub->c_id + sub->s_id + to_string(sub->tut);
					for(auto grp: sub->groups)
					{
						if(SubsDay.find(sub_id + grp)==SubsDay.end())
							SubsDay[sub_id + grp] = new SubDay;	
						SubsDay[sub_id + grp]->days.insert(day);
					}
					break;
				}
			}
			priority[priority.size()-1].second -= sub->cont_slot_req;
			if(priority[priority.size()-1].second <= 0)
				priority.pop_back();
			break;
		}
	}
	for(auto& sub: subjects)
	{
		if(sub->slot.size()==0)
			garbage.push_back(sub);
	}
	if(garbage.size()>0)
	{
		return false;
	}
	return true;
}

void Solution::printTable(int iteration)
{
	ofstream out(DATABASE_DIR + to_string(iteration) + "_" + "allView.txt");
	out<<"GARBAGE: "<<garbage.size()<<"\n\n";
	vector<Subject> subjects;
	for(auto sub: this->subjects)
	{
		subjects.push_back(*sub);
	}
	out<<"\n";
	out<<setw(T_SMALL)<<setfill(' ')<<left<<"X";
	for(int day=0;day<DAYS;day++)
	{
		out<<setw(T_WIDTH)<<setfill(' ')<<left<<day;
	}
	out<<"\n";
	pair<int,int> slot;

	bool status = false;

	for(int hour = 0;hour<SLOTS;hour++)
	{
		slot.second = hour;
		if(status)
			out<<setw(T_SMALL)<<setfill(' ')<<left<<" ";
		else
			out<<setw(T_SMALL)<<setfill(' ')<<left<<hour;
		status = false;
		for(int day=0;day<DAYS;day++)
		{
			bool day_status = false;
			slot.first = day;
			for(auto& sub:subjects)
			{
				if(sub.slot.count(slot))
				{
					out<<setw(T_WIDTH)<<setfill(' ')<<left<<"| " + sub.printTableDetails();
					sub.slot.erase(sub.slot.find(slot));
					status = true;
					day_status = true;
					break;
				}
			}
			if(!day_status)
			{
				out<<setw(T_WIDTH)<<setfill(' ')<<left<<"| ";
			}

		}
		out<<"\n";	
		if(status)
		{
			hour--;
		}
		else
		{
			out<<setw(T_SMALL)<<setfill('-')<<left<<"";
			for(int day=0;day<DAYS;day++)
			{
				out<<setw(T_WIDTH)<<setfill('-')<<left<<"";
			}
			out<<"\n";	
		}
	}
	out.close();
}

void Solution::makeFacultyView(int iteration)
{
	ofstream out(DATABASE_DIR + to_string(iteration) + "_" +"facultyView.txt");
	out<<"GARBAGE: "<<garbage.size()<<"\n\n";
	map<string,vector<Subject>> f_map;
	for(auto sub:subjects)
	{
		f_map[sub->f_id].push_back(*sub);
	}

	for(auto f:f_map)
	{
		out<<"\n"<<f.first<<"\n";
		out<<setw(T_SMALL)<<setfill(' ')<<left<<"X";
		for(int day=0;day<DAYS;day++)
		{
			out<<setw(T_WIDTH)<<setfill(' ')<<left<<day;
		}
		out<<"\n";
		pair<int,int> slot;

		bool status = false;

		for(int hour = 0;hour<SLOTS;hour++)
		{
			slot.second = hour;
			if(status)
				out<<setw(T_SMALL)<<setfill(' ')<<left<<" ";
			else
				out<<setw(T_SMALL)<<setfill(' ')<<left<<hour;
			status = false;
			
			for(int day=0;day<DAYS;day++)
			{
				bool day_status = false;
				slot.first = day;
				for(auto& sub:f.second)
				{
					if(sub.slot.count(slot))
					{
						out<<setw(T_WIDTH)<<setfill(' ')<<left<<"| " + sub.printTableDetails();
						sub.slot.erase(sub.slot.find(slot));
						status = true;
						day_status = true;
						break;
					}
				}
				if(!day_status)
				{
					out<<setw(T_WIDTH)<<setfill(' ')<<left<<"| ";
				}

			}
			out<<"\n";
			if(status)
			{
				hour--;
			}
			else
			{
				out<<setw(T_SMALL)<<setfill('-')<<left<<"";
				for(int day=0;day<DAYS;day++)
				{
					out<<setw(T_WIDTH)<<setfill('-')<<left<<"";
				}
				out<<"\n";
			}
		}
		out<<"\n";
	}
	out.close();
}

void Solution::makeClassView(int iteration)
{
	ofstream out(DATABASE_DIR + to_string(iteration) + "_" +"classView.txt");
	out<<"GARBAGE: "<<garbage.size()<<"\n\n";
	map<string,vector<Subject>> c_map;
	for(auto sub:subjects)
	{
		c_map[sub->c_id].push_back(*sub);
	}

	for(auto c:c_map)
	{
		out<<"\n"<<c.first<<"\n";
		out<<setw(T_SMALL)<<setfill(' ')<<left<<"X";
		for(int day=0;day<DAYS;day++)
		{
			out<<setw(T_WIDTH)<<setfill(' ')<<left<<day;
		}
		out<<"\n";
		pair<int,int> slot;

		bool status = false;

		for(int hour = 0;hour<SLOTS;hour++)
		{
			slot.second = hour;
			if(status)
				out<<setw(T_SMALL)<<setfill(' ')<<left<<" ";
			else
				out<<setw(T_SMALL)<<setfill(' ')<<left<<hour;
			status = false;
			
			for(int day=0;day<DAYS;day++)
			{
				bool day_status = false;
				slot.first = day;
				for(auto& sub:c.second)
				{
					if(sub.slot.count(slot))
					{
						out<<setw(T_WIDTH)<<setfill(' ')<<left<<"| " + sub.printTableDetails();
						sub.slot.erase(sub.slot.find(slot));
						status = true;
						day_status = true;
						break;
					}
				}
				if(!day_status)
				{
					out<<setw(T_WIDTH)<<setfill(' ')<<left<<"| ";
				}

			}
			out<<"\n";
			if(status)
			{
				hour--;
			}
			else
			{
				out<<setw(T_SMALL)<<setfill('-')<<left<<"";
				for(int day=0;day<DAYS;day++)
				{
					out<<setw(T_WIDTH)<<setfill('-')<<left<<"";
				}
				out<<"\n";
			}
		}
		out<<"\n";
	}
	out.close();
}

void Solution::makeRoomView(int iteration)
{
	ofstream out(DATABASE_DIR + to_string(iteration) + "_" + "roomView.txt");
	out<<"GARBAGE: "<<garbage.size()<<"\n\n";
	map<string,vector<Subject>> r_map;
	for(auto sub:subjects)
	{
		r_map[sub->r_id].push_back(*sub);
	}

	for(auto r:r_map)
	{
		out<<"\n"<<r.first<<"\n";
		out<<setw(T_SMALL)<<setfill(' ')<<left<<"X";
		for(int day=0;day<DAYS;day++)
		{
			out<<setw(T_WIDTH)<<setfill(' ')<<left<<day;
		}
		out<<"\n";
		pair<int,int> slot;

		bool status = false;

		for(int hour = 0;hour<SLOTS;hour++)
		{
			slot.second = hour;
			if(status)
				out<<setw(T_SMALL)<<setfill(' ')<<left<<" ";
			else
				out<<setw(T_SMALL)<<setfill(' ')<<left<<hour;
			status = false;
			
			for(int day=0;day<DAYS;day++)
			{
				bool day_status = false;
				slot.first = day;
				for(auto& sub:r.second)
				{
					if(sub.slot.count(slot))
					{
						out<<setw(T_WIDTH)<<setfill(' ')<<left<<"| " + sub.printTableDetails();
						sub.slot.erase(sub.slot.find(slot));
						status = true;
						day_status = true;
						break;
					}
				}
				if(!day_status)
				{
					out<<setw(T_WIDTH)<<setfill(' ')<<left<<"| ";
				}

			}
			out<<"\n";
			if(status)
			{
				hour--;
			}
			else
			{
				out<<setw(T_SMALL)<<setfill('-')<<left<<"";
				for(int day=0;day<DAYS;day++)
				{
					out<<setw(T_WIDTH)<<setfill('-')<<left<<"";
				}
				out<<"\n";
			}
		}
		out<<"\n";
	}
	out.close();
}

void Solution::resetData()
{
	for(auto& sub: subjects)
	{
		sub->slot.clear();
		sub->r_id = "";
	}

	for(auto& room:Rooms)
	{
		room.second->slots.clear();
	}

	for(auto& f:Faculties)
	{
		f.second->slots.clear();
	}

	for(auto& c:Courses)
	{
		c.second->slots.clear();
	}

	for(auto& s:SubsDay)
	{
		s.second->days.clear();
	}

	garbage.clear();
}

#endif