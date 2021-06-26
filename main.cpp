#include <iostream>
#include "src/Method.h"

int main() {
    student stud;
    stud.SetMarks("223");
    stud.IsGotTheBestMarks();

    teacher teach;
    teach.SetMood();
    teach.SetName("Marinka");

    GrandMa bigma;
    bigma.SayGood();

    lesson less;
    less.SetName("Biology");

    Meeting meet;
    meet.StartMeeting();
    return 0;
}
