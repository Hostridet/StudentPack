#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>

using namespace std;


class student
{
    string Name = "";
    string marks = "";

    //Проверка на инородные символы в строке с оценками
    bool Check(const string& s)
    {
        return !s.empty() && (s.find_first_not_of("0123456789") == s.npos);
    }

public:
    void SetName(string name)
    {
        this->Name = move(name);
    }

    void SetMarks(string Marks)
    {
        if (Check(Marks))
            this->marks = move(Marks);
    }
    string GetName()
    {
        return this->Name;
    }
    string GetMarks()
    {
        return this->marks;
    }
    bool IsGotTheBestMarks()
    {
        float result = 0;
        for (int i = 0; i < marks.length(); i++)
        {
            result = (result + marks[i] - 48);
        }
        result = (result / marks.length());
        if (result > 4.5)
            return true;
        else
            return false;
    }
    friend ostream &operator<<(std::ostream &out, student &s) {
        out << "Ученик " << s.Name << endl;
    }
};
class teacher {
    string Name;
    int mood; // 0 - злой, как черт,  1 - поставит троечку за коллок (отличное настроение)
    unsigned int CountOfMarks = 0;

    bool IsGoodMood()
    {
        if (mood == 0)
            return false;
        if (mood == 1)
            return true;
    }
public:
    void SetName(string name) {
        this->Name = name;
    }

    string GetName()
    {
        return Name;
    }

    void SetMood()
    {
        this->mood = rand() % 2; // настроение зависит от погоды :)
    }
    int GetMood()
    {
        return mood;
    }

    void SetCurrentMark(student stud, string mark)
    {
        stud.SetMarks(stud.GetMarks() + mark);
        CountOfMarks++;
        if (CountOfMarks % 5 == 0)
            SetMood();
    }
    void SetRandomMark(student stud)
    {
        if (IsGoodMood())
        {
            CountOfMarks++;
            if (stud.IsGotTheBestMarks())
                stud.SetMarks(stud.GetMarks() + "5");
            else
                stud.SetMarks(stud.GetMarks() + "4");
        }
        else
        {
            CountOfMarks++;
            if (stud.IsGotTheBestMarks()) {
                if ((rand() % 2) == 1)
                    stud.SetMarks(stud.GetMarks() + "5");
                else
                    stud.SetMarks(stud.GetMarks() + "4");
            }
            else{
                if ((rand() % 2) == 1)
                    stud.SetMarks(stud.GetMarks() + "3");
                else
                    stud.SetMarks(stud.GetMarks() + "2");
            }
        }
        if (CountOfMarks % 5 == 0)
            SetMood();
    }

    friend ostream &operator<<(std::ostream &out, teacher &t) {
        out << "Преподаватель " << t.Name << " Настроение: "<< t.mood << endl;
    }

};

class Parent
{
    string Name;
    unsigned int mood = 0;

    bool IsGoodMood()
    {
        if (mood == 0)
            return false;
        if (mood == 1)
            return true;
    }
    void Say(student& s)
    {
        switch(mood){
            case 0:
                if (s.IsGotTheBestMarks())
                    cout << "Мои ребенок лучший на свете, списывает всё на 5" << endl;
                else
                    cout << "Мой ребенок лучший на свете, но списывать не умеет" << endl;
                break;
            case 1:
                if (s.IsGotTheBestMarks())
                    cout << "Мой ребенок хороший, но лучше бы его заменить" << endl;
                else
                    cout << "Моего ребенка даже в дет дом не взяли" << endl;
                break;
        }
    }
    void SayAll(bool gang)
    {
        switch(mood)
        {
            case 0:
                if (gang)
                    cout << "Мои дети не плохие!" << endl;
                else
                    cout << "Мои дети худшие их худших" << endl;
                break;
            case 1:
                if (gang)
                    cout << "Мои дети лучшие на свете!" << endl;
                else
                    cout << "Мои дети хорошие!" << endl;
                break;
        }

    }
    int GetLength()
    {
        unsigned int count = 0;
        for (auto &i : child)
            count ++;
        return count;
    }

protected:
    int CountOfChild = 0;
public:
    student* child[20];


    void SetMood()
    {
        this->mood = rand() % 2; // настроение зависит от погоды :)
    }
    void SetName (string name)
    {
        this->Name = name;
    }
    int GetCountOfChilds()
    {

    }
    string GetName()
    {
        return Name;
    }

    void addChild(student* stud)
    {
        child[CountOfChild] = stud;
        CountOfChild++;
    }
    void SayAboutOne(student* stud)
    {
        Say(*stud);
    }
    //Считае количество отлично и сравниваем с количеством всех детей
    void SayAboutAll()
    {
        float count = 0;
        for (auto &i : child)
            if (i->IsGotTheBestMarks())
                count++;
        count = (count / GetLength());
        bool gang;
        if (count >= 0.75)
        {
            gang = true;
            SayAll(gang);
        }
        else
        {
            gang = false;
            SayAll(gang);
        }


    }
    void SayAboutRand()
    {
        int childs = rand() % CountOfChild;
        Say(*child[childs]);
    }
    void SayAboutEveryone()
    {
        for (auto &i : child) {
            Say(*i);
        }
    }

    friend ostream &operator<<(std::ostream &out, Parent &p) {
        out << "Родитель: " << p.Name << endl;
    }
};

class lesson
{
    string LessonName;
    teacher *teach;
    int CountOfStudents = 0;

public:
    student* students[20];
    void SetName(string Name)
    {
        this->LessonName = Name;
    }
    string GetLessonName()
    {
        return LessonName;
    }
    teacher* GetTeacher()
    {
        return this->teach;
    }
    void addStudent(student* stud)
    {
        students[CountOfStudents] = stud;
        CountOfStudents++;
    }
    void addTeacher(teacher* teachs)
    {
        this->teach = teachs;
    }

    int GetStudentsOnLesson()
    {
        return CountOfStudents;
    }
    void StartLesson(teacher* t)
    {
        addTeacher(t);
        t->SetMood();

        for (int i = 0; i < CountOfStudents; i++)
        {
            unsigned int count = 0;
            if(!t->GetMood())
                t->SetRandomMark(*students[i]);
            count++;
            if (count % 5 == 0)  // меняем настроение учителя
            {
                t->SetMood();
            }
        }
    }
    friend ostream &operator<<(std::ostream &out, lesson l) {
        out << "Предмет: " << l.LessonName << ", " << l.teach << endl;
    }
};

class Meeting
{
    teacher* teach[10];
    Parent* parent[10];
    lesson* lessons[10];
    unsigned int CountOfTeachers = 0;
    unsigned int CountOfParents = 0;
    unsigned int CountOfLessons = 0;

public:
    void addTeacher(teacher* teachs)
    {
        teach[CountOfTeachers] = teachs;
        CountOfTeachers++;
    }
    void addParent(Parent* parents)
    {
        parent[CountOfParents] = parents;
        CountOfParents++;
    }
    void addLessons(lesson* lesson)
    {
        lessons[CountOfLessons] = lesson;
        CountOfLessons++;
    }

    void StartMeeting()
    {
        for (int i = 0; i < CountOfLessons; i++)
        {
            bool found = false;
            int k = 0;
            while (k < CountOfTeachers && !found)
            {
                if (teach[k] == lessons[i]->GetTeacher())
                    found = true;
            }
            k++;
            if (found)
            {
                for (int t = 0; t < lessons[i]->GetStudentsOnLesson(); t++)
                {
                    bool foundParents;
                    for (int k = 0; k < CountOfParents; k++)
                        for (int j = 0; j < parent[k]->GetCountOfChilds();j++)
                            if (lessons[i]->students[t] == parent[k]->child[j])
                            {
                                foundParents = true;
                                cout <<"Имя: " <<lessons[k]->students[t] <<"Урок: "<< lessons[i]->GetLessonName() << endl;
                                parent[k]->SayAboutOne(lessons[k]->students[t]);
                            }
                }
            }
        }
    }
};
class GrandMa: public Parent
{
public:
    void SayGood()
    {
        for (int i = 1; i < CountOfChild; i++)
            cout << "Ля какой у меня внук " << child[i]->GetName();
    }
};