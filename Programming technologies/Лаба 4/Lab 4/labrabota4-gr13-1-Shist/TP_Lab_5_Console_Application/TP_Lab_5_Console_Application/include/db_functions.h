//
//  db_functions.h
//  TP_Lab_5_Console_Application
//
//  Created by Pavel Zhukouski on 21.03.2020.
//  Copyright © 2020 Pavel Zhukouski. All rights reserved.
//

#ifndef db_functions_h
#define db_functions_h
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdbool.h>
#include <string.h>

#include "db_struct.h"

void ReadFile(InternationalCompany* temp);
int OpenDb(char * db_name, sqlite3** db);
int SelectQuery(sqlite3 *db_name,char* query);
int InsertQuery(sqlite3 *db_name);
int DeleteQuery(sqlite3 *db_name);
int ParameterizedQuery(sqlite3 *db_name);
int InsertImage(sqlite3 *db_name);
int ReadImage(sqlite3 *db_name, char* file_name);
int TransactionMode(sqlite3 *db_name);

#endif /* db_functions_h */
