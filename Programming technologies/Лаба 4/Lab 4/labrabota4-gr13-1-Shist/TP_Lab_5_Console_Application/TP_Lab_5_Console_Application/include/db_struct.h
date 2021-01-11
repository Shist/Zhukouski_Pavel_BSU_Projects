//
//  db_struct.h
//  TP_Lab_5_Console_Application
//
//  Created by Pavel Zhukouski on 21.03.2020.
//  Copyright © 2020 Pavel Zhukouski. All rights reserved.
//

#ifndef db_struct_h
#define db_struct_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct International_Company
{
    int id;
    char name[256];
    char site[256];
    int mail_ind;
    char country[256];
    char region[256];
    char district[256];
    char town[256];
    char street[256];
    int house;
    int flat;
    char found_year[256];
    int len_stay_in_glob_market;
    int emp_amount;
    int eu_branches_amount;
    int category_id;
}InternationalCompany;

#endif /* db_struct_h */
