/*
Krish Khatri
11/21/2018

This program is an acting "gradebook".
It allows a user to add students normally or alphabetically if they choose,
add grades normally, or in a structed ordered if they choose,
count the number of students in the class,
print out specifed student details or the entire classes details,
remove grades from specifed students, and remove students from the "class"

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//Compares The Last Name Of Two Nodes
//  1. Returns Either 0, >0, <0
int comparePerson(Student *ptr1, Student *ptr2)
{
 return strcmp(ptr1 -> lastName, ptr2 -> lastName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//Compares The First Name of Two Nodes
//  1. Returns Either 0, >0, <0
int compareFirstName(Student *ptr1, Student *ptr2)
{
  return strcmp(ptr1 -> firstName, ptr2 -> firstName);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//Compares Grade Name of Two Nodes
// 1. Return 0, <0 or >0 Depending Upon Certain Conditions
int compareGradeName(Grade *ptr1, Grade *ptr2)
{

  char *name1 = ptr1 -> name;
  char *name2 = ptr2 -> name;


  if(*(name1) == *(name2))
  {
    int lenPtr1 = strlen(name1);
    int lenPtr2 = strlen(name2);

    if(lenPtr1 == lenPtr2)
    {
      return strcmp(name1,name2);
    }
    // Special Cases Where Strcmp Returns Wrong Value
    else if(lenPtr1 < lenPtr2 && *(name1 + 1) == '1')
    {
      return -1;
    }
    else if(lenPtr1 > lenPtr2 && *(name2 + 1) == '1')
    {
      return 1;
    }
    // Special Case To Handle Single Digit Assignment Number With Multi-Digit Assignment Number
    else
    {
      int val = strcmp(name1, name2);

      if(val < 0)
      {
        return 1;
      }
      else if ( val > 0)
      {
        return -1;
      }
      else
      {
        return 0;
      }
    }
  }
  else
  {
    return strcmp(name1,name2);
  }

  // Return "For Complier"
  // Never Reached If Code Above Works
  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// add a student to the list of students
//	   1. Make sure a student by that name does not exist (print an error message and do nothing if it exists)
//	   2. Add a new student with that name (add-at-front)

Student* addStudent(Student *headStudentList, char last[], char first[])
{

  // Creates A Node of Struct Student Properties
  Student *ptr = (Student*)malloc(sizeof(Student));
  ptr->headGradeList = NULL;

  ptr->lastName = malloc(sizeof(char) * (strlen(last) + 1));
  ptr->firstName = malloc(sizeof(char) *(strlen(first) + 1));
  strcpy(ptr->lastName, last);
  strcpy(ptr->firstName, first);

  // Checks if Head of Linked List is NULL, If so replaces the Head with Node "Ptr"
  if(headStudentList == NULL)
  {
    ptr -> next = NULL;
    headStudentList = ptr;
  }
  else
  {
  // Iterates Through Linked List to Check if A Student By The input names already Exists
  // If so, prints Error message
  // Else Places Node "Ptr" To The Front Of the Linked List
    for(Student *ptr1 = headStudentList; ptr1!=NULL; ptr1 = ptr1 -> next)
    {
      if(strcmp(ptr1->lastName, last) == 0 && strcmp(ptr1->firstName,first) == 0)
      {
        printf("Error: A Student By This Name Already Exists\n");
        return headStudentList;
      }
    }

    ptr -> next = headStudentList;
    headStudentList = ptr;
  }

	return ptr;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// add a grade to the specified student
//   1. Make sure a student by that name exists (so you can add grade to it)
//   2. If the specifed grade already exists, update the grade's value to the new value
//   3. Otherwise, add the grade to the end of the student's grade list (add-at-end)

void addGrade(Student *headStudentList, char last[], char first[], char gradeName[], double value)
{
  Student *student;
  int count = 0;
  int runCount = 0;

  // Iterates Through Linked List to Find Student specified.
  // If Found, Saves the Location into "student" pointer
  // Else, prints Error Message
  for(Student *ptr = headStudentList; ptr!=NULL; ptr = ptr -> next)
  {
    if(strcmp(ptr->lastName, last) == 0 && strcmp(ptr->firstName,first) == 0)
    {
      count++;
      student = ptr;
    }
  }

  /* Checks To See if Error Message if Printed.
     If not, Then Checks if head of the GradeList is NULL
     If so, creates a pointer with Properties of Struct Grade and Sets That as Head of Grade list
     If Not, then Checks if GradeName Already Exists In Linked List
     If so, Replaces Grade value for the Given Grade name
     Else, Finds the Last Element in the Linked List and Creates a Pointer with Properties of Struct Grade and Adds
     That to the end of the Linked List
  */

  if(count == 0)
  {
    printf("No Such Student Exists\n");
  }
  else
  {
    if(student -> headGradeList == NULL)
    {
      student -> headGradeList = (Grade*)malloc(sizeof(Grade));
      strcpy(student -> headGradeList -> name, gradeName);
      student -> headGradeList -> value = value;
    }

    for (Grade *ptr2 = student -> headGradeList; ptr2 != NULL; ptr2 = ptr2 -> next)
    {
      if(strcmp(ptr2->name, gradeName) == 0)
      {
        ptr2 -> value = value;
        runCount++;
      }
    }

    if (runCount == 0)
    {
      Grade *pLast;
      for (Grade *ptr = student -> headGradeList; ptr != NULL; ptr = ptr -> next)
      {
        pLast = ptr;
      }

      Grade *new = (Grade*)malloc(sizeof(Grade));
      strcpy(new -> name, gradeName);
      new -> value = value;
      pLast -> next = new;
    }
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////
// return the number of students in the list
// Iterate through the student list to count the number of students, return that count

int count(Student *headStudentList)
{
  int count  = 0;
  for(Student *ptr = headStudentList; ptr!=NULL; ptr = ptr -> next)
  {
    count++;
  }
	return count;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// print all the grades for a given student
//	1. Make sure a student with that name exists
//	2. Print the name of that student
//	3. Print all the "grade name: grade value" pairs for that student

void printStudent(Student *headStudentList, char last[], char first[])
{
  int count = 0;

  // Iterates over Linked List To Find Node with Matching Last Name and First name
  // If Found, Prints to Console
  // Else, Prints Error message

  for(Student *ptr = headStudentList; ptr!=NULL; ptr = ptr -> next)
  {
    if(strcmp(ptr->lastName, last) == 0 && strcmp(ptr->firstName,first) == 0)
    {
      count++;
      printf("Student Name: %s, %s\n", ptr->lastName, ptr->firstName );
      for (Grade *ptr1 = ptr->headGradeList; ptr1 != NULL; ptr1 = ptr1 -> next)
      {
        if(strlen(ptr1 -> name) == 2)
        {
          printf("        %s  : %g\n",ptr1->name, ptr1->value );
        }
        else
        {
          printf("        %s : %g\n",ptr1->name, ptr1->value );
        }
      }
    }
  }

  if(count == 0)
  {
    printf("Sorry, No Such Student Exists\n");
  }
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// print all the students
// For each student
//	   a. Print the name of that student
//	   b. Print all the "grade name: grade value" pairs for that student

void print(Student *headStudentList)
{
  // Iterates Over Linked List and Prints Every Node
  for(Student *ptr = headStudentList; ptr!=NULL; ptr = ptr -> next)
  {
      printf("Student Name: %s, %s\n", ptr->lastName, ptr->firstName );
      for (Grade *ptr1 = ptr->headGradeList; ptr1 != NULL; ptr1 = ptr1 -> next)
      {
        if(strlen(ptr1 -> name) == 2)
        {
          printf("        %s  : %g\n",ptr1->name, ptr1->value );
        }
        else
        {
          printf("        %s : %g\n",ptr1->name, ptr1->value );
        }
      }

      printf("\n");
  }
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// add a student (in alphabetical order)
//	1. Make sure a student by that name does not exist
//	2. Add a student with that name (add-in-order)

Student *addStudentOrdered(Student *headStudentList, char last[], char first[])
{
  Student *ptr = (Student*)malloc(sizeof(Student));
  Student *ptr2 = headStudentList;
  Student *ptr3 = headStudentList;
  int choice = 0;


  // Creates A Pointer With Properties of Struct Student
  ptr->headGradeList = NULL;
  ptr->lastName = malloc(sizeof(char) * (strlen(last) + 1));
  ptr->firstName = malloc(sizeof(char) *(strlen(first) + 1));
  strcpy(ptr->lastName, last);
  strcpy(ptr->firstName, first);

  // Checks To See if Linked List is Empty
  // If so, places first node into list
  if(headStudentList == NULL)
  {
    ptr -> next = headStudentList;
    return ptr;
  }

  // Assigns a Variable the Return Value from the function "comparePerson"
  // Has 3 return types:
  //      1. 0 , Indicating Same Last name , Need to Check First name
  //      2. < 0 , Indicating new node needs to be placed in the front of comparing node
  //      3. > 0, Indicating new node needs to be placed after comparing node

  // Comparing New Node With Head of The Linked List
  choice = comparePerson(ptr, headStudentList);

  // Places At Front
  if(choice < 0)
  {
    ptr -> next = headStudentList;
    return ptr;
  }

  // Same Last Name , Compare First Name
  if(choice == 0)
  {
    int headChoice  = 0;

    // Assigns a Variable the Return Value from the function "compareFirstName"
    // Has 3 return types:
    //      1. 0 , Indicating Same First Name
    //      2. < 0 , Indicating new node needs to be placed in the front of comparing node
    //      3. > 0, Indicating new node needs to be placed after comparing node


    // Comparing New Node First Name With Head of Linked List
    headChoice = compareFirstName(ptr, headStudentList);

    // If First Name is Also the Same, Prints Message To Console
    if(headChoice == 0)
    {
      printf("A Person By This Name Already Exists In The List\n");
      return headStudentList;
    }
    // Places At Front
    else if(headChoice < 0)
    {
      ptr -> next = headStudentList;
      return ptr;
    }
  }

  // Compares New Node Last Name With Every Other Node In Linked List Last Names
  for(ptr2 = headStudentList; ptr2 -> next != NULL; ptr2 = ptr2 -> next)
  {
    choice = comparePerson(ptr, ptr2 -> next);

    // Places At Front
    if(choice < 0)
    {
      ptr -> next = ptr2 -> next;
      ptr2 -> next = ptr;
      return headStudentList;
    }

    // If Last Name is The Same, Compares First Name
    else if (choice == 0)
    {
      int choice1 = 0;

      // Stores The Location of the First Instance of The Same Last Name To A Pointer of Type Student
      Student *pHolder;
      pHolder = ptr2 -> next;

      // Compares First Name of New Node With The First Names of Every Node After The First Node with Matching Last Name
      for(ptr3 = ptr2; ptr3 -> next != NULL; ptr3 = ptr3 -> next)
      {
       choice1 = compareFirstName(ptr, ptr3 -> next);

       // Place At Front
       if(choice1 < 0)
       {
         ptr -> next = ptr3 -> next;
         ptr3 -> next = ptr;
         return headStudentList;
       }

       // Prints Message to Console Because First Name and Last Name Match
       else if(choice1 == 0)
       {
          printf("A Person by This Name Already Exists In The List\n");
          return headStudentList;
       }
     }

     // default placement, place at end.
     Student *ptr4 = pHolder;

     // Finds the Last Node with the Same Last Name and Places New Node at the end
     while (ptr4 -> next != NULL && comparePerson(ptr, ptr4 -> next) == 0)
     {
       ptr4 = ptr4 -> next;
     }
     ptr -> next = ptr4 -> next;
     ptr4 -> next = ptr;
     return headStudentList;
   }
 }
 // default case: place at end.
  ptr2 -> next = ptr;
  return headStudentList;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a grade to the specified student in order
//	1. Make sure a student by that name exists (so you can add a grade to the student)
//	2. If the grade already exists, update the value
//	3. Otherwise, add the grade to the student (add-in-order)

void addGradeOrdered(Student *headStudentList, char last[], char first[], char gradeName[], double value)
{
  // Creates A Pointer With Properties of Struct Grade
  Grade *newGrade = (Grade*)malloc(sizeof(Grade));
  strcpy(newGrade -> name, gradeName);
  newGrade -> value  = value;

  Student *student;
  Grade *ptr;
  int count = 0, gradeIndex = 0;

  // Iterates Over Linked List
  // If Node With Same Last Name and First Name as Input Exists, Assigns ptr "student" with Location
  // Else prints Message to Console
  for (Student *ptr = headStudentList; ptr != NULL; ptr = ptr -> next)
  {
    if(strcmp(ptr->lastName,last) == 0 && strcmp(ptr->firstName,first) == 0)
    {
      student = ptr;
      count++;
    }
  }

  // Checks to see if Message if Printed
  // If so, does nothing
  // else checks if head of grade linked list is Empty
  // if so, Assigns head of grade linked list with pointer newGrade
  if(count == 0)
  {
    printf("No Such Student Exists In The List\n");
  }
  else if(student -> headGradeList == NULL)
  {
      student -> headGradeList = newGrade;
  }

  // Assigns a Variable the Return Value from the function "compareGradeName"
  // Has 3 return types:
  //      1. 0 , Indicating Same GradeName, Value needs to be updated
  //      2. < 0 , Indicating new node needs to be placed in the front of comparing node
  //      3. > 0, Indicating new node needs to be placed after comparing node

  else
  {
    // Compares new node with head of linked list
    gradeIndex = compareGradeName(newGrade, student -> headGradeList);

    // place at front
   if(gradeIndex < 0)
      {
        newGrade -> next = student -> headGradeList;
        student -> headGradeList = newGrade;
      }

    // replaces value of existing node with value of new node
    else if(gradeIndex == 0)
    {
      student -> headGradeList -> value = value;
    }

    // Iterates over the entire linked list except head, and Compares grade name
    else
    {
    for(ptr = student -> headGradeList; ptr -> next != NULL; ptr = ptr -> next)
     {
       gradeIndex = compareGradeName(newGrade, ptr -> next);

       // place at front
       if(gradeIndex < 0)
       {
         newGrade -> next = ptr -> next;
         ptr -> next = newGrade;
         break;
       }
       // replace value with new node value
       else if(gradeIndex == 0)
       {
         newGrade -> next = ptr -> next -> next;
         ptr -> next = newGrade;
         break;
       }
     }
     //default: place at end
     ptr -> next = newGrade;
    }
  }
  return;
}



/////////////////////////////////////////////////////////////////////////////////////////////
// remove a grade from a student
//	1. Make sure a student with that name exists
//	2. Make sure the grade exists in that student
//	3. Remove the grade from that student

void removeGrade(Student *headStudentList, char last[], char first[], char gradeName[])
{
  Student *student;
  int count = 0;
  int runCount = 0;

  for(Student *ptr = headStudentList; ptr != NULL; ptr = ptr -> next)
  {
    if(strcmp(ptr->lastName, last) == 0 && strcmp(ptr->firstName,first) == 0)
    {
      student = ptr;
      count++;
    }
  }

  if(count == 0)
  {
    printf("No Such Student Exists in The List\n");
  }
  else
  {
    for(Grade *ptr1 = student -> headGradeList; ptr1 != NULL; ptr1 = ptr1 -> next)
    {
      if(strcmp(ptr1 -> name,gradeName) == 0)
      {
        runCount++;
        break;
      }
    }

    if(runCount == 0)
    {
      printf("No Such Grade Exists For Student: %s , %s\n", student -> lastName, student -> firstName );
    }
    else if(strcmp(student -> headGradeList -> name, gradeName) == 0)
    {
      Grade *pDel = student -> headGradeList;
      student -> headGradeList = student -> headGradeList -> next;
      free(pDel);
    }
    else
    {
      for (Grade *ptr = student -> headGradeList; ptr != NULL; ptr = ptr -> next)
      {
        if(strcmp(ptr -> next -> name, gradeName) == 0)
        {
          Grade *pDel = ptr -> next;
          ptr -> next = ptr -> next -> next;
          free(pDel);
          break;
        }
      }
    }
  }
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// remove a student
//	1. Make sure a student with that name exists
//	2. Remove that student and all the grades of that student

Student *removeStudent(Student *headStudentList, char last[], char first[])
{
  int count = 0;

  for(Student *ptr =  headStudentList; ptr != NULL; ptr = ptr -> next)
  {
    if(strcmp(ptr -> lastName , last) == 0 && strcmp(ptr -> firstName , first) == 0)
    {
      count++;
    }
  }

  if(count == 0)
  {
    printf("No Such Student Currently Exists In The List\n");
  }
  else
  {
    if(strcmp(headStudentList -> lastName , last) == 0 && strcmp(headStudentList -> firstName , first) == 0)
    {
      Student *pDel;
      pDel = headStudentList;
      headStudentList =  headStudentList -> next;
      free(pDel);
      return headStudentList;
    }
    else
    {
      for (Student *ptr = headStudentList; ptr != NULL; ptr = ptr -> next)
      {
        if(strcmp(ptr -> next -> lastName, last) == 0 && strcmp(ptr -> next -> firstName, first) == 0)
        {
          Student *pDel = ptr -> next;
          ptr -> next = ptr -> next -> next;
          free(pDel);
          return headStudentList;
        }
      }
    }
  }

	return headStudentList;
}
