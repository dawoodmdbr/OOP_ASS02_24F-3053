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
};

struct Survey
{
    string title;
    Question *questions;
    int qCount;
    Survey()
    {
        title = "";
        questions = nullptr;
        qCount = 0;
    }
    ~Survey()
    {
        delete questions;
    }
};

class Admin
{
private:
    Survey *surveys;
    int sCount;
public:
    Admin()
    {
        surveys = nullptr;
        sCount = 0;
    }
    ~Admin()
    {
        delete surveys;
    }
    void createSurvey()
    {
        Survey *temp = new Survey[sCount + 1];
        for (int i = 0; i < sCount; i++)
            temp[i] = surveys[i];
        delete[] surveys;
        surveys = temp;

        cout << "Enter survey title: ";
        getline(cin, surveys[sCount++].title);
        surveys[sCount].qCount = 0;
        surveys[sCount].questions = nullptr;
        cout << "Survey created successfully!" << endl;
    }

    void addQuestion(int sIndex)
    {
        if (sCount <= sIndex)
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
        getline(cin, survey.questions[survey.qCount].text);
        cout << "Select question type:" << endl;
        cout << "0: Multiple choice" << endl;
        cout << "1: text input" << endl;
        cout << "2: Rating" << endl;
        cout << "Option: ";
        int qType;
        cin >> qType;
        survey.questions[survey.qCount].type = static_cast<QuestionType>(qType);

        if (qType == MULTIPLE_CHOICE)
        {
            cout << "Enter 4 options:";
            for (int i = 0; i < 4; i++)
                getline(cin, survey.questions->opt[i]);
        }
        survey.qCount++;
        cout << "Question added successfully!" << endl;
    }
    void removeQuestion(int sIndex){

    }
    void editQuestion(int sIndex){

    }
    void viewSurveys()
    {
        cout << "Surveys: " << endl;
        for (int i = 0; i < sCount; i++)
        {
            cout << "[" << i << "] " << surveys[i].title << " (" << surveys[i].qCount << " questions)\n";
        }
    }
};

class User{

public:
    void fillSurvey(Survey survey){
        cout<<"Survery title: "<< survey.title<< endl;
        for(int i =0;i<survey.qCount;i++){
            cout<<survey.questions[i].text;
            if(survey.questions[i].type == MULTIPLE_CHOICE){
                for(int j=0;j<4;j++){
                    cout<<i<<". "<<survey.questions->opt[j] << endl;
                }
                int ch;
                cout<<"Enter choice: ";
                cin>>ch;
            }
            else if(survey.questions[i].type = RATING){
                cout<<"Enter rating(1-5): ";
                int rating;
                cin>>rating;
            }
            else {
                string response;
                cout<<"Enter response: ";
                getline(cin, response);
            }
        }
        cout<<"Survey submitted!"<<endl;
    }


};
int main()
{
    cout << "hello world";

    return 0;
}