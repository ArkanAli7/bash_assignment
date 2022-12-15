#include "linked-list.h"
#include "grades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FAIL 1
#define SUCCESS 0




typedef struct student
{  //a struct for every student with course list
    int id;
    char *student_name;
    struct list* list_course;
} Student;

typedef struct course
{  // a struct for every course 
    int course_grade;
    char *course_name;
} Course;

typedef struct grades
{   // a struct for all students
    struct list* students;
} Grade;

void coursedestroy(void *element);

void coursedestroy(void *element);

int clonecourse(void *element, void **output);

int clonestudent(void *element, void **output);

// let's begin

int clonecourse(void *element, void **output)
{ 
    Course* tmp_copy= malloc(sizeof(Course));
    Course* casted_from = element;
    int name_length=strlen(casted_from->course_name)+1;
    tmp_copy->course_grade = casted_from->course_grade;
    tmp_copy->course_name = malloc(name_length);
    strcpy(tmp_copy->course_name,casted_from->course_name);
    *output=tmp_copy; 
    return 0;
}




int  clonestudent(void *element, void **output)
{	

    Student* tmp_copy= malloc(sizeof(Student));
    Student* casted_from =element;
    tmp_copy->id = casted_from->id;
    
    int name_length=strlen(casted_from->student_name) + 1;
    tmp_copy->student_name = (char*)malloc(name_length);
    
    strcpy(tmp_copy->student_name,casted_from->student_name);
    tmp_copy->list_course= list_init(clonecourse,coursedestroy );	 
                                     
                                     
    struct iterator *from_iterator = list_begin(casted_from->list_course);
    
    struct iterator *to_iterator = list_begin(tmp_copy->list_course);
    
    Course *from_course=list_get(from_iterator);
    
    int size=(int)list_size(casted_from->list_course);
    
    if(size) 
    {
        list_push_front(tmp_copy->list_course, from_course);
        
        to_iterator = list_begin(tmp_copy->list_course);
    }
    for (int j = 0; j < size-1; ++j) 
    {
    
        from_iterator = list_next(from_iterator);
        
        from_course = list_get(from_iterator);
        
        list_insert(tmp_copy->list_course,to_iterator,from_course);
        
        to_iterator = list_next(to_iterator);
        
    }
    *output=tmp_copy;
    return 0;
    
}


void coursedestroy(void *element)
{ 
    Course *tmp =element;
    free(tmp->course_name);
    free(tmp);
}

void studentdestroy(void *element)
{ 
    Student *tmp = element;
    list_destroy(tmp->list_course);
    free(tmp->student_name);
    free(tmp);
}





struct grades* grades_init()
{
   // building the new grades struct
    Grade* grades= malloc(sizeof (Grade));
    
    element_clone_t studentclonefunc = clonestudent;
    element_destroy_t studentdestroyfunc = studentdestroy;
    
    grades->students= list_init(studentclonefunc, studentdestroyfunc);
    return grades;
}

void grades_destroy(struct grades *grades)
{
    list_destroy(grades->students);
    free(grades);
}


float grades_calc_avg(struct grades *grades, int id, char **out){
    if(!grades||id <=0) // checking for errors
    {
        *out = NULL;
        return -1;
    }
    
   
    struct iterator *Iterator_course;
    struct iterator *Iterator_student = list_begin(grades->students);
    Student *current_student;
    Course *current_course;
    int counter=0, sum=0;
    while (Iterator_student!=NULL) {
        current_student = list_get(Iterator_student);
        if(current_student->id == id) // if we found the student
        {
        
            *out = (char*)malloc((strlen(current_student->student_name)+1));
            
            strcpy(*out,current_student->student_name);
            
            Iterator_course = list_begin(current_student->list_course);
            //going over all student courses
            while(Iterator_course!=NULL)
            {
                current_course = list_get(Iterator_course);
                Iterator_course = list_next(Iterator_course);
                sum = sum + (current_course->course_grade) ;
                counter++;
            }
            
            if(counter == 0) 
            {
                return 0;
            }
            return ((float)sum/(float)counter);
        }
        else
           {
               Iterator_student = list_next(Iterator_student);
           }
    }
      *out = NULL;
      return -1;
   

}


int grades_add_grade(struct grades *grades, 
                       const char *name, int id, int grade)
{                     
    if(grades == 0 || name == 0)
    {
    	return  FAIL;
    }
    
    // if the grade is invalid 
    if(grade > 100 || grade < 0)
    {
       	return FAIL;
    }

    int name_length = (int)strlen(name)+1;
    
    struct iterator *iterator = list_begin(grades->students);
    
    Student *current_student;
    Course *current_course; 
       
    while(iterator!=NULL)
    {
        current_student = list_get(iterator);
        
        if(current_student->id == id)
        {
            iterator = list_begin(current_student->list_course);
            
            while(iterator!=NULL)
            {
                current_course = list_get(iterator);
                
                if(!strcmp(current_course->course_name,name))
                { 
                    return FAIL;
                }
                
                else
                {
                    iterator = list_next(iterator);
                }
            }
            
            Course *added_course = (Course*)malloc(sizeof(Course));
            added_course->course_grade = grade;
            added_course->course_name = (char*)malloc(name_length);
            
            strcpy(added_course->course_name,name);
            list_push_back(current_student->list_course,added_course);
            //free memory
            free(added_course->course_name);
            free(added_course);
            
            return SUCCESS;
        }
        
        else
        {
            iterator = list_next(iterator);
        }
    }
    	return FAIL;
}



int grades_add_student(struct grades *grades, const char *name, int id)
{
    if(grades == 0 || name == 0 || id<=0) /// check needed errors
    {
    	return FAIL;
    }
        
    int name_length = (int)strlen(name) + 1;
    Student *current_student;    
    struct iterator *iterator = list_begin(grades->students);
    
    while(iterator!=NULL)
    {
        current_student = list_get(iterator);
        
        if(current_student->id == id) // check if the id is in use
        {
            return  FAIL;
        }
        
        iterator = list_next(iterator);
        
    }
    // adding new student
    Student* new_student = (Student*)malloc(sizeof(Student)); 
    new_student->student_name = (char*)malloc(name_length);
    
    if(new_student == NULL)        
    {
    	return FAIL;
    }
    
        
    new_student->id = id;
    
    strcpy(new_student->student_name,name);
    
    new_student ->list_course = list_init(clonestudent,studentdestroy);
    
    
    if(list_push_back(grades->students, new_student)==SUCCESS)
    {        
        free(new_student->student_name);
        list_destroy(new_student->list_course);       
        free(new_student);        
        return SUCCESS;
    }
     
    free(new_student->student_name);
    list_destroy(new_student->list_course);
    free(new_student);
    return FAIL;
	
}




int grades_print_all(struct grades *grades){
    if(!grades)  // check if there is grades
    {
    	return FAIL;
    }
    
    
    struct iterator *Iterator =list_begin(grades->students);
    Student *current_student;
    
    while (Iterator!=NULL) { // printing all students
        current_student = list_get(Iterator);
        grades_print_student(grades,current_student->id);
        Iterator = list_next(Iterator);
    }
    
    return SUCCESS;
    
}

int grades_print_student(struct grades *grades, int id)
{
    if(grades == NULL || id <=0) //check needed errors
    {
    	return FAIL;
    }
    
    struct iterator *iterator = list_begin(grades->students);
    Student *current_student;
    Course *current_course;
    
    
    while(iterator!=NULL) 
    {
        current_student = list_get(iterator);
        //checking if this is the student we want
        if(current_student->id == id) 
        {
         printf("%s %d:",current_student->student_name,current_student->id);
            
            iterator = list_begin(current_student->list_course);
            
          if(iterator)
          {
         current_course = list_get(iterator);
    printf(" %s %d",current_course->course_name,current_course->course_grade);
      	    	  
    	    iterator = list_next(iterator);
    	  }
 	     
            while(iterator!=NULL)
            {
         printf(",");
           current_course = list_get(iterator);
    printf(" %s %d",current_course->course_name,current_course->course_grade);

                iterator = list_next(iterator);
            }
            printf("\n");
            return SUCCESS;
        }
        else
        {
        // going to the next student
            iterator = list_next(iterator);
        }
    }
    
    return FAIL;
}



