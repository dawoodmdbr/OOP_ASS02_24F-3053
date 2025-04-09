#include <iostream>
#include <string>
using namespace std;

enum QuestionType
{
    MULTIPLE_CHOICE,
    TEXT,
    RATING
};

struct Question
{
    string text;
    QuestionType type;
    string opt[4];

    Question() : text(""), type(TEXT) {}
};



struct Survey
{
    string title;
    Question *questions;
    int qCount;

    Survey() : title(""), questions(nullptr), qCount(0) {}

    ~Survey()
    {
        delete[] questions;
    }
};

class Admin
{
private:
    Survey *surveys;
    int sCount;

public:
    Admin() : surveys(nullptr), sCount(0) {}

    ~Admin()
    {
        delete[] surveys;
    }

    void createSurvey()
    {
        Survey *temp = new Survey[sCount + 1];
        for (int i = 0; i < sCount; i++)
            temp[i] = surveys[i];
        delete[] surveys;
        surveys = temp;

        cout << "Enter survey title: ";
        cin.ignore(); // Clear input buffer
        getline(cin, surveys[sCount].title);
        surveys[sCount].qCount = 0;
        surveys[sCount].questions = nullptr;
        sCount++;
        cout << "Survey created successfully!" << endl;
    }

    void addQuestion(int sIndex)
    {
        if(sIndex < 0 || sIndex >= sCount)
        {
            cout << "Invalid survey index" << endl;
            return;
        }

        Survey &survey = surveys[sIndex];
        Question *temp = new Question[survey.qCount + 1];

        for (int i = 0; i < survey.qCount; i++)
            temp[i] = survey.questions[i];

        delete[] survey.questions;
        survey.questions = temp;

        cout << "Enter a question: ";
        cin.ignore();
        getline(cin, survey.questions[survey.qCount].text);

        cout << "\nSelect question type:" << endl;
        cout << "1: Multiple choice" << endl;
        cout << "2: Text input" << endl;
        cout << "3: Rating" << endl;
        cout << "Option: ";
        int qType;
        cin >> qType;

        survey.questions[survey.qCount].type = static_cast<QuestionType>(qType);

        if (qType-1 == MULTIPLE_CHOICE)
        {
            cout << "Enter 4 options:" << endl;
            cin.ignore();
            for (int i = 0; i < 4; i++)
            {
                cout << "Option " << i + 1 << ": ";
                getline(cin, survey.questions[survey.qCount].opt[i]);
            }
        }

        survey.qCount++;
        cout << "Question added successfully!" << endl;
    }

    void viewSurveys()
    {
        cout << "Available Surveys: " << endl;
        for (int i = 0; i < sCount; i++)
        {
            cout << "Survey ID: " << i+1 << ", Title: " << surveys[i].title << " (" << surveys[i].qCount << " questions)" << endl;
            for (int j = 0; j < surveys[i].qCount; j++)
            {
                cout << "Q" << j + 1 << ": " << surveys[i].questions[j].text << endl;
            }
            cout<< endl;
        }

    }

    Survey *getSurvey(int index)
    {
        if (index < 0 || index >= sCount)
        {
            cout << "Invalid survey index" << endl;
            return nullptr;
        }
        return &surveys[index];
    }
};

class User
{
public:
    void fillSurvey(Survey *survey)
    {
        if (!survey)
        {
            cout << "Survey not found!" << endl;
            return;
        }

        cout << "\nSurvey Title: " << survey->title << endl;

        for (int i = 0; i < survey->qCount; i++)
        {
            cout << survey->questions[i].text << endl;

            if (survey->questions[i].type == MULTIPLE_CHOICE)
            {
                for (int j = 0; j < 4; j++)
                {
                    cout << j + 1 << ". " << survey->questions[i].opt[j] << endl;
                }
                int ch;
                cout << "Enter ch (1-4): ";
                cin >> ch;
            }
            else if (survey->questions[i].type == RATING)
            {
                int rating;
                cout << "Enter rating (1-5): ";
                cin >> rating;
            }
            else
            {
                cin.ignore();
                string response;
                cout << "Enter response: ";
                getline(cin, response);
            }
        }
        cout << "Survey submitted!" << endl;
    }
};

int main()
{
    Admin admin;
    User user;
    int ch;
    int sIndex;
    while(1){
        cout<<"1. Admin"<<endl
        <<"2. User"<<endl
        <<"3. Exit"<<endl
        <<"Enter choice: ";
        cin>>ch;
        switch(ch){
            case 1:
                while (1)
                {
                    cout<<"\n1. Create survey"<<endl
                        <<"2. Add question"<<endl
                        <<"3. View survey"<<endl
                        <<"4. Exit"<<endl
                        <<"Enter choice: ";
                    cin >> ch;
                    if(ch==1) admin.createSurvey();
                    else if(ch==2){
                        cout << "Enter survey ID: ";
                        cin >> sIndex;
                        admin.addQuestion(sIndex-1);
                    } 
                    else if(ch==3) admin.viewSurveys();
                    else if(ch == 4) break;
                    else cout<<"Invalid choice. Try again."<<endl;
                }
                break;
            case 2:
                while(1){
                    cout<<"1. Fill a survey"<<endl
                        <<"2. Exit"<<endl  
                        <<"Enter choice: ";
                    cin>>ch;
                    if(ch==1){
                        admin.viewSurveys();
                        cout << "Enter survey ID to fill: ";
                        cin >> sIndex;
                        user.fillSurvey(admin.getSurvey(sIndex-1));
                    } else if(ch==2) break;
                    else cout<<"Invalid choice. Try again."<<endl;
                }
                break;
            case 3:
                return 0;


        }
    }
    
    
}
