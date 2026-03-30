#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name? ");
    int age = get_int("What is your age? ");
    float gpa = get_float("What is your GPA? ");
    printf("hello, %s. Your age is %i and your GPA is %f\n", name,age,gpa);
}