#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Event
{
private:
    string eventName;
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    int importance;
    
    string addNotes;
public:
    Event(const string& name,int importance, int y, int m, int d, int hour, int minutes, string notes) : eventName(name), importance(importance ), year(y), month(m), day(d), hours(hour), minutes(minutes), addNotes(notes) {}

    void setEventName(const string& name) {
        eventName = name;
    }
    void setImportance(int i)
    {
        importance = i;
    }
    void setDate(int y, int m, int d) {
        day = d;
        month = m;
        year = y;
    }
    void setTime(int hours, int minutes) {
        this->hours = hours;
        this->minutes = minutes;
    }
    
    void setNotes(string addNotes) {
        this->addNotes = addNotes;
    }
    string getEventName() const {
        return eventName;
    }
    int getImportance() const
    {
        return importance;
    }
    string getDate() const {
        return to_string(day) + "." + to_string(month) + "." + to_string(year);
    }
    string getTime() const {
        return to_string(hours) + ":" + to_string(minutes);
    }
    
    string getNotes() const {
        return addNotes;
    }

    friend ostream& operator<<(ostream& out, const Event& event) {
        out << "Event Name: " << event.eventName << endl;

        out << "Importance(1/2/3): " << event.importance << endl; 

        out << "Date: " << event.getDate() << endl;
        out << "Time: " << event.getTime() << endl;
        out << "Notes: " << event.addNotes << endl;
        return out;
    }

    bool operator<(const Event& other) const {
        return getDate() < other.getDate() || (getDate() == other.getDate() && getTime() < other.getTime()) || (getDate() == other.getDate() && getTime() == other.getTime() && eventName < other.eventName);
    }
};
class EventCalendar
{
private:
    vector<Event>events;
public:
    void addEvent(const Event& event) {
        events.push_back(event);
    }
    void removeEvent(const string& eventName) {
        for (auto it = events.begin(); it != events.end(); ++it) {
            if (it->getEventName() == eventName) {
                events.erase(it);
                break;
            }
        }
    }
    vector<Event> findEventsByDate(const string& date) const {
        vector<Event> eventsOnDate;
        for (const auto& event : events) {
            if (event.getDate() == date) {
                eventsOnDate.push_back(event);
            }
        }
        return eventsOnDate;
    }

    void sortByDate() {
        sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
            return a.getDate() < b.getDate();
            });
    }
    void sortByTime() {
        sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
            return a.getTime() < b.getTime();
            });
    }
    void sortByImportance()
    {
        sort(events.begin(), events.end(), [](const Event& a, const Event& b)
            {
                return a.getImportance() < b.getImportance();
            });
    }
    ///добавить сортировку по важности!!!!!!!!

    void showAll() {
        for (const auto& event : events) {
            cout << event << endl;
        }
    }

};


void showMenu(EventCalendar& calendar) {
    int choice;
    int sortBy;
    do {
        cout << "\n===== Event Calendar Menu =====" << endl;
        cout << "0. Show Events list" << endl;
        cout << "1. Add Event" << endl;
        cout << "2. Remove Event" << endl;
        cout << "3. Sort Events" << endl;
        cout << "4. Search Event by date" << endl;
        cout << "5. Update Event Details" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 0: {
            cout << endl;
            calendar.showAll();
            break;
        }
              ///добавление
        case 1: {
            string name, notes;
            int importance, year, month, day, hour, minute;
            cout << "Enter event name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter importance(1,2 or 3): ";
            cin >> importance; 
            cout << "Enter year: ";
            cin >> year;
            cout << "Enter month: ";
            cin >> month;
            cout << "Enter day: ";
            cin >> day;
            cout << "Enter hour(From 0 to 24): ";
            cin >> hour;
            cout << "Enter minute(From 0 to 59): ";
            cin >> minute;
            
            cout << "Enter notes: ";
            cin.ignore();
            getline(cin, notes);
            calendar.addEvent(Event(name, importance, year, month, day, hour, minute, notes));
            cout << "Event added successfully." << endl;
            break;
        } ///
              ///удаление
        case 2: {
            string eventNameToDelete;
            cout << "Enter the name of the event you want to delete: ";
            cin.ignore();
            getline(cin, eventNameToDelete);

            calendar.removeEvent(eventNameToDelete);
            cout << "Event \"" << eventNameToDelete << "\" has been deleted successfully." << endl;
            break;
        }
              ///Сортировка
        case 3: {

            cout << "1 - Sort by Date\n2 - Sort by Time\n3 - Sort by Importance\n4-Go back" << endl;
            cout << "Do: ";
            cin >> sortBy;
            switch (sortBy)
            {
            case 1:
            {
                calendar.sortByDate();
                cout << "Sorted successfully!" << endl;
                break;
            }
            case 2:
            {
                calendar.sortByTime();
                cout << "Sorted successfully!" << endl;
                break;
            }
            case 3:
            {
                calendar.sortByImportance();
                cout << "Sorted successfully!" << endl;
                break;
            }
            case 4:
            {
                break;
            }
            default:
                break;
            }

            break;
        }
              ///поиск по дате  
        case 4: {
            string dateToSearch;
            cout << "Enter the date (in format DD.MM.YYYY) to search events: ";
            cin.ignore();
            getline(cin, dateToSearch);

            vector<Event> eventsOnDate = calendar.findEventsByDate(dateToSearch);
            if (eventsOnDate.empty()) {
                cout << "No events found on date " << dateToSearch << "." << endl;
            }
            else {
                cout << "Events on date " << dateToSearch << ":" << endl;
                for (const auto& event : eventsOnDate) {
                    cout << event << endl;
                }
            }
            break;
        }
        case 5: {
            ///место для реализации работы с файлом
            break;
        }
        case 6: {
            cout << "Exiting..." << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
    } while (choice != 6);
}

int main() {
    setlocale(LC_ALL, "ru");
    EventCalendar calendar;


    showMenu(calendar);

    return 0;
}