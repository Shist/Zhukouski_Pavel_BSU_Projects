//
//  main.c
//  TP_Lab_5_Console_Application
//
//  Created by Pavel Zhukouski on 20.03.2020.
//  Copyright © 2020 Pavel Zhukouski. All rights reserved.
//

#include "db_functions.h"
char* database_path="DB International Company.vlb";
char* database_select_1_table="SELECT * FROM International_Company";
char* database_select_2_table="SELECT * FROM Category";


int main()
{
    int status = 0;
    do{
    printf("Make a choice, what do you want to do?\n");
    printf("1: make a query with using select\n");
    printf("2: make an insert in a table\n");
    printf("3: delete line by id\n");
    printf("4: make parameterized request\n");
    printf("5: write image in database\n");
    printf("6: read image from database\n");
    printf("7: example of transaction mode\n");
    printf("8: exit\n");

    scanf("%d", &status);

    sqlite3* database;
    OpenDb(database_path, &database);
    printf("autocommit mode: %s\n",(sqlite3_get_autocommit(database)==0)?"disabled":"enabled");
    switch (status){
    case (1) :
        printf("1st case:\n");
        int t_stat = -1;
        char * query;
        printf("Make a choice\n1: to output International_Company table\n");
        printf("2: to output Category table\nYour Choice: ");
        scanf("%d", &t_stat);
        if(t_stat==1){
            query=database_select_1_table;
        }else if(t_stat==2){
            query=database_select_2_table;
        }else{
            fprintf(stderr, "programm will closed t_stat=%d\n", t_stat);
            return -1;
        }
        int err_msg=SelectQuery(database, query);
        if(err_msg!=0){
            fprintf(stderr, "programm will closed code -2 and reason%d\n",err_msg);
            return -2;
        }
        
        break;
    case 2:
        printf("2nd case:\n");
        
        err_msg=InsertQuery(database);
        if(err_msg!=0){
            fprintf(stderr, "programm will closed code -3 and reason%d\n",err_msg);
            return -3;
        }
        break;
    case 3:
        printf("3rd case:\n");
        err_msg=DeleteQuery(database);
        if(err_msg!=0){
            fprintf(stderr, "programm will closed code -4 and reason%d\n",err_msg);
            return -4;
        }
        break;
    case 4:
        printf("4th case:\n");
        err_msg=ParameterizedQuery(database);
        if(err_msg!=0){
            fprintf(stderr, "programm will closed code -5 and reason%d\n",err_msg);
            return -5;
        }
        break;
    case 5:
        printf("5th case:\n");
        err_msg=InsertImage(database);
        if(err_msg!=0){
            fprintf(stderr, "programm will closed code -6 and reason%d\n",err_msg);
            return -6;
        }
        break;
    case 6:
        printf("6th case:\n");
        printf("Enter name where to write image from db ");
        char files[20];
        scanf("%s", &files);

        err_msg=ReadImage(database, files);
        if(err_msg!=0){
            fprintf(stderr, "programm will closed code -6 and reason%d\n",err_msg);
            return -6;
        }
        break;
    case 7:
        printf("7th case:\n");
        err_msg=TransactionMode(database);
        if(err_msg!=0){
            fprintf(stderr, "programm will closed code -7 and reason%d\n",err_msg);
            return -6;
        }
        break;
    }
    
    sqlite3_close(database);

    }while(status!=8);
    return 0;
}
