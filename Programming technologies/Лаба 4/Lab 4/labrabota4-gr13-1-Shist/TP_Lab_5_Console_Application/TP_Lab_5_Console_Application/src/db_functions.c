//
//  db_functions.c
//  TP_Lab_5_Console_Application
//
//  Created by Pavel Zhukouski on 21.03.2020.
//  Copyright © 2020 Pavel Zhukouski. All rights reserved.
//

#include <stdio.h>
#include "db_functions.h"




static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void ReadFile(InternationalCompany* temp)
{
    printf("\n\t\tEnter international company data \n");
    printf("Enter id ");
    scanf("%d", &temp->id);
    printf("Enter site ");
    scanf("%s", &temp->site);
    printf("Enter mail index ");
    scanf("%d",&temp->mail_ind);
    printf("Enter country ");
    scanf("%s", &temp->country);
    printf("Enter region ");
    scanf("%s", &temp->region);
    printf("Enter district ");
    scanf("%s", &temp->district);
    printf("Enter town ");
    scanf("%s", &temp->town);
    printf("Enter street ");
    scanf("%s", &temp->street);
    printf("Enter house ");
    scanf("%d", &temp->house);
    printf("Enter flat ");
    scanf("%d", &temp->flat);
    printf("Enter foundation year ");
    scanf("%s", &temp->found_year);
    printf("Enter length of staing in the global market ");
    scanf("%d",&temp->len_stay_in_glob_market);
    printf("Enter employees amount ");
    scanf("%d",&temp->emp_amount);
    printf("Enter Europe branches' amount ");
    scanf("%d",&temp->eu_branches_amount);
    printf("Enter category id ");
    scanf("%d",&temp->category_id);
}
	
int OpenDb(char * db_name, sqlite3** db)
{
    int status;
    status=sqlite3_open(db_name, db);
    if(status != SQLITE_OK){
        fprintf(stderr, "Can't open_database: %s\n",sqlite3_errmsg(*db));
        sqlite3_close(*db);
        exit(1);
    }
    return status;
}

int SelectQuery(sqlite3 *db_name,char* query)
{
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db_name, query, callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error in making \"SelectQuery:\" function %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 1;
    }
    return rc;
}

int InsertQuery(sqlite3 *db_name)
{
    char *zErrMsg = 0;
    //char *query="insert into region_lists (id, region_name, main_town_name, population, area_square, region_manager, country_id) values (%d, %s, %s, %s, %d, %d, %d)";
    char comand[1000];
    InternationalCompany* temp=malloc(sizeof(InternationalCompany));

    ReadFile(temp);
    int n=snprintf(&comand, 1000,"INSERT INTO International_Company (id, site, mail_ind, country, region, district, town, street, house, flat, found_year, len_saty_in_glob_market, emp_amount, eu_branches_amount, category_id) values (%d, \"%s\", %d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %d, %d, \"%s\", %d, %d, %d, %d)", temp->id, temp->site, temp->mail_ind, temp->country, temp->region, temp->district, temp->town, temp->street, temp->house, temp->flat, temp->found_year, temp->len_stay_in_glob_market, temp->emp_amount, temp->eu_branches_amount, temp->category_id);

    int rc = sqlite3_exec(db_name, comand, -1, 0, &zErrMsg);
    if( rc!=SQLITE_OK )
    {
      fprintf(stderr, "SQL error in making \"InsertQuery:\" function %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 1;
    }
   free(temp);
   return 0;
}

int GetDeletedId()
{
    printf("Enter id of the record that should be selected ");
    int ans;
    scanf("%d", &ans);
    return ans;
}

void GetParamSelect(char* param)
{
    printf("Enter parameter to select ");
    scanf("%s", &param);
}

int DeleteQuery(sqlite3 *db_name)
{
    char *zErrMsg = 0;
    char comand[256];

    int id_to_del=GetDeletedId();
    int n=snprintf(&comand, 255,"DELETE FROM International_Company WHERE id=%d", id_to_del);

    int rc = sqlite3_exec(db_name, comand, -1, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error in making \"DeleteQuery:\" function %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 1;
    }
    printf("Record was deleted! \n");
   return 0;
}

int ParameterizedQuery(sqlite3 *db_name){
    int status;
    printf("Make a choice, how to select?\n");
    printf("1: by id\n");
    printf("2: by like\n");
    printf("3: by category id\n");
    scanf("%d", &status);
	
    sqlite3_stmt* res;
    char *zErrMsg = 0;
    char comand[256];
    char* sql;

    switch(status){
        case 1:
            printf("\n");
            int id_to_query=GetDeletedId();
            sql="SELECT * FROM International_Company WHERE id=?";
            sqlite3_prepare_v2(db_name, sql, -1, &res, 0);
            sqlite3_bind_int(res, 1, id_to_query);
            break;
        case 2:
            printf("\n");
            int status_t;
            printf("Make a choice, What which field to use??\n");
            printf("1: by company name\n");
            printf("2: by company site\n");
            scanf("%d",&status_t);
            /*printf("Enter mask ");
            char mask[20];
            scanf("%s",&mask);*/
            if(status_t==1){
            sql="SELECT * FROM International_Company WHERE Name like=?";
            }else if(status==2){
            sql="SELECT * FROM International_Company WHERE Site like=?";
            } else{
                return -1;
            }
            sqlite3_prepare_v2(db_name, sql, -1, &res, 0);
            char* param;
            GetParamSelect(param);
            sqlite3_bind_text(res, 1, param,2,SQLITE_STATIC);
            break;
        case 3:
            printf("\n");
            sqlite3_exec(db_name, "SELECT * FROM Category", callback, 0, &zErrMsg);
            id_to_query=GetDeletedId();
            sql="SELECT * FROM International_Company WHERE Category_ID=?";
            sqlite3_prepare_v2(db_name, sql, -1, &res, 0);
            sqlite3_bind_int(res, 1, id_to_query);
            break;
    }


    int step = sqlite3_step(res);
    while(step == SQLITE_ROW) {
        for(int i=0; i<7;i++){
            printf("%s\n", sqlite3_column_text(res, i));
        }
        printf("\n");
           step=sqlite3_step(res);
    }

   return 0;
}


int InsertImage(sqlite3 *db_name){
    char image_name[256];
    printf("Enter image name ");
    scanf("%s", &image_name);
    char image_path[256];
    snprintf(&image_path, 255,"images/%s", image_name );
    printf("%s\n",image_path);
    //image_name="src/images/Almaz.jpg";
    FILE *fp = fopen(image_path, "rb");
    
    if (fp == NULL) {
        fprintf(stderr, "Cannot open image file\n");
        return 1;
    }
        
    fseek(fp, 0, SEEK_END);
    
    if (ferror(fp)) {
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        return 1;
    }
    
    int flen = ftell(fp);
    
    if (flen == -1) {
        perror("error occurred");
        int r = fclose(fp);

        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        return 1;
    }
    
    fseek(fp, 0, SEEK_SET);
    
    if (ferror(fp)) {
        
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);

        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        
        return 1;
    }

    //store image
    char data[flen+1];

    int size = fread(data, 1, flen, fp);

    if (ferror(fp)) {
        
        fprintf(stderr, "fread() failed\n");
        int r = fclose(fp);

        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        
        return 1;
    }
    
    int r = fclose(fp);

    if (r == EOF) {
        fprintf(stderr, "Cannot close file handler\n");
    }

    char *err_msg = 0;
    
    sqlite3_stmt *pStmt;

    char sql[256];
    int id_to_query=GetDeletedId();
    int n=snprintf(&sql, 256,"UPDATE International_Company SET Image=? WHERE ID=%d", id_to_query);
    
    int rc = sqlite3_prepare(db_name, sql, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db_name));
        return 1;
    }
    

    sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);

    
    rc = sqlite3_step(pStmt);
    
    if (rc != SQLITE_DONE) {
        printf("execution failed: %s", sqlite3_errmsg(db_name));
    }
        
    sqlite3_finalize(pStmt);
    printf("%s\n",sql);

    return 0;
}
	
int ReadImage(sqlite3 *db_name, char* file_name){
    //printf("erye %s\n",file_name);
    FILE *fp = fopen(file_name, "wb");
    
    if (fp == NULL) {
        fprintf(stderr, "Cannot open image file\n");
        return 1;
    }
    
    char *err_msg = 0;
    
    char sql[256];
    int id_to_query=GetDeletedId();
    int n=snprintf(&sql, 256,"SELECT image FROM International_Company WHERE ID = %d", id_to_query);

        
    sqlite3_stmt *pStmt;
    int rc = sqlite3_prepare_v2(db_name, sql, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to prepare statement\n");
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_name));
        
        sqlite3_close(db_name);
        
        return 1;
    }
    
    rc = sqlite3_step(pStmt);
    	
    int bytes = 0;
    
    if (rc == SQLITE_ROW) {

        bytes = sqlite3_column_bytes(pStmt, 0);
    }
        
    fwrite(sqlite3_column_blob(pStmt, 0), bytes, 1, fp);

    if (ferror(fp)) {
        
        fprintf(stderr, "fwrite() failed\n");

        return 1;
    }
    
    int r = fclose(fp);

    if (r == EOF) {
        fprintf(stderr, "Cannot close file handler\n");
    }
    
    rc = sqlite3_finalize(pStmt);
    
    return 0;
}

void ReverseTransaction(sqlite3* db_name){
    char *zErrMsg = 0;
    char query[512];
    char* sql1="UPDATE International_Company SET Emp_Amount=12412 WHERE id=1";
    char* sql2="UPDATE International_Company SET Emp_Amount=32475 WHERE id=2";
    char* sql3="UPDATE International_Company SET Emp_Amount=8925 WHERE id=3";
    int n=snprintf(&query, 511,"%s;\n%s;\n%s;\n", sql1, sql2, sql3);
    
    int rc = sqlite3_exec(db_name, query, -1, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error in make \"make_insert_request:\" fanction %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }

    SelectQuery(db_name, "SELECT * FROM International_Company");

}

int TransactionMode(sqlite3 *db_name){
    char *zErrMsg = 0;
    printf("Do you want to enable transaction mode (y/n) ");
    char query[512];
    char is_enabled;		
    scanf("%s", &is_enabled);

    char* sql1="UPDATE International_Company SET Emp_Amount=34 WHERE id=1"
            "UPDATE International_Company SET Emp_Amount=65 WHERE id=2"
            "UPDATE International_Company SET Emp_Amount=98 WHERE id=3";




    if(is_enabled=='y'){
            char* sql0="BEGIN TRANSACTION";
            char* sql5="COMMIT";
            snprintf(&query, 511,"%s%s%s",sql0, sql1, sql5);
    }else{
        snprintf(&query, 511,"%s\n", sql1);
    }
    printf("Show query:\n%s\n",query);

    int rc = sqlite3_exec(db_name, query, -1, 0, &zErrMsg);
    /*if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error in making \"InsertQuery:\" function %s\n", zErrMsg);
      return 1;
    }*/

    SelectQuery(db_name, "SELECT * from International_Company");

        if(is_enabled=='n')
        ReverseTransaction(db_name);
    return 0;


}
