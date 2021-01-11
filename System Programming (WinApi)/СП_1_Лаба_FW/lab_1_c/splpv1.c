/*
 * SPLPv1.c
 * The file is part of practical task for System programming course.
 * This file contains validation of SPLPv1 protocol.
 */


 /*
   Жуковский Павел Сергеевич
   Группа № 13
 */


/* ---------------------------------------------------------------------------------------------------------------------------
 # |      STATE      |         DESCRIPTION       |           ALLOWED MESSAGES            | NEW STATE | EXAMPLE
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 1 | INIT            | initial state             | A->B     CONNECT                      |     2     |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 2 | CONNECTING      | client is waiting for con-| A<-B     CONNECT_OK                   |     3     |
   |                 | nection approval from srv |                                       |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 3 | CONNECTED       | Connection is established | A->B     GET_VER                      |     4     |
   |                 |                           |        -------------------------------+-----------+----------------------
   |                 |                           |          One of the following:        |     5     |
   |                 |                           |          - GET_DATA                   |           |
   |                 |                           |          - GET_FILE                   |           |
   |                 |                           |          - GET_COMMAND                |           |
   |                 |                           |        -------------------------------+-----------+----------------------
   |                 |                           |          GET_B64                      |     6     |
   |                 |                           |        ------------------------------------------------------------------
   |                 |                           |          DISCONNECT                   |     7     |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 4 | WAITING_VER     | Client is waiting for     | A<-B     VERSION ver                  |     3     | VERSION 2
   |                 | server to provide version |          Where ver is an integer (>0) |           |
   |                 | information               |          value. Only a single space   |           |
   |                 |                           |          is allowed in the message    |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 5 | WAITING_DATA    | Client is waiting for a   | A<-B     CMD data CMD                 |     3     | GET_DATA a GET_DATA
   |                 | response from server      |                                       |           |
   |                 |                           |          CMD - command sent by the    |           |
   |                 |                           |           client in previous message  |           |
   |                 |                           |          data - string which contains |           |
   |                 |                           |           the following allowed cha-  |           |
   |                 |                           |           racters: small latin letter,|           |
   |                 |                           |           digits and '.'              |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 6 | WAITING_B64_DATA| Client is waiting for a   | A<-B     B64: data                    |     3     | B64: SGVsbG8=
   |                 | response from server.     |          where data is a base64 string|           |
   |                 |                           |          only 1 space is allowed      |           |
 --+-----------------+---------------------------+---------------------------------------+-----------+----------------------
 7 | DISCONNECTING   | Client is waiting for     | A<-B     DISCONNECT_OK                |     1     |
   |                 | server to close the       |                                       |           |
   |                 | connection                |                                       |           |
 ---------------------------------------------------------------------------------------------------------------------------

 IN CASE OF INVALID MESSAGE THE STATE SHOULD BE RESET TO 1 (INIT)
*/


#include "splpv1.h"
#include "string.h"
#include <stdlib.h>





 /* FUNCTION:  validate_message
  *
  * PURPOSE:
  *    This function is called for each SPLPv1 message between client
  *    and server
  *
  * PARAMETERS:
  *    msg - pointer to a structure which stores information about
  *    message
  *
  * RETURN VALUE:
  *    MESSAGE_VALID if the message is correct
  *    MESSAGE_INVALID if the message is incorrect or out of protocol
  *    state
  */

  /* FUNCTION:  validate_message
   *
   * PURPOSE:
   *    This function is called for each SPLPv1 message between client
   *    and server
   *
   * PARAMETERS:
   *    msg - pointer to a structure which stores information about
   *    message
   *
   * RETURN VALUE:
   *    MESSAGE_VALID if the message is correct
   *    MESSAGE_INVALID if the message is incorrect or out of protocol
   *    state
   */

const char base64[128] =
{ 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0, 1, // '+' и '/'
  1, 1, 1, 1, 1, 1, 1, 1, // цифры
  1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, // большие латинские буквы
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, // маленькие латинские буквы
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 0, 0, 0, 0, 0 };

const char data[128] = 
{ 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 1, 0, // точка
  1, 1, 1, 1, 1, 1, 1, 1, // цифры
  1, 1, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 1, 1, 1, 1, 1, 1, 1, // маленькие латинские буквы
  1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 0, 0, 0, 0, 0 };

int CurrentState = 1; // Глобальная переменная, хранящая в себе номер текущего состояния
int WhatCommand; // Глобальная переменная, храняющая в себе номер текущей команды

const char* commands[3] = { "GET_DATA", "GET_FILE", "GET_COMMAND" }; // Перечисление команд для состояния 5 WAITING_DATA

enum test_status validate_message(struct Message *msg)
{
	char* message = msg->text_message; // В этой строке храним сообщение
	if (msg->direction == A_TO_B)
	{ // Разбираем все случаи для перехода из A в B...
		if (CurrentState == 1 && !strcmp(message, "CONNECT"))
		{
			CurrentState = 2;
			return MESSAGE_VALID;
		}
		if (CurrentState == 3)
		{
			if (!strcmp(message, "GET_VER"))
			{ // Версия сервера
				CurrentState = 4;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_DATA"))
			{ // Данные от сервера
				WhatCommand = 0;
				CurrentState = 5;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_FILE"))
			{ // Данные от сервера
				WhatCommand = 1;
				CurrentState = 5;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_COMMAND"))
			{ // Данные от сервера
				WhatCommand = 2;
				CurrentState = 5;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "GET_B64"))
			{ // Данные от сервера в Base64
				CurrentState = 6;
				return MESSAGE_VALID;
			}
			else if (!strcmp(message, "DISCONNECT"))
			{ // Закрытие соединения
				CurrentState = 7;
				return MESSAGE_VALID;
			}
		}
	}
	else
	{ // Из B в A
		if (CurrentState == 2 && !strcmp(message, "CONNECT_OK"))
		{ // Подтверждение соединения
			CurrentState = 3;
			return MESSAGE_VALID;
		}
		else if (CurrentState == 7 && !strcmp(message, "DISCONNECT_OK"))
		{ // Закрытие соединения
			CurrentState = 1;
			return MESSAGE_VALID;
		} // strncmp(str1, str2, N) - сравнивает первые N символов обеих строк, 0 - если равны, < 0 - если str1 < str2, > 0 - если str1 > str2
		else if (CurrentState == 4 && !strncmp(message, "VERSION ", 8)) 
		{ // Клиент ждёт версию сервера...
			message += 8; // Делаем так, чтобы сдвинуть указатель на начало нужной нам подстроки
			if (*message > 48 && *message < 58) // Тут могут быть все цифры, кроме нуля (т.к. версия с нуля начинаться не может)
			{ // Дальше должны быть уже все цифры (включая 0), поэтому смотрим диапазон [48, 57]
				for (++message; *message != '\0'; message++) // Сдвигаем указатель по строке, проверяя каждый символ
					if (*message < 48 || *message > 57)
					{ // Проверяем на валидность
						CurrentState = 1;
						return MESSAGE_INVALID;
					}
				CurrentState = 3;
				return MESSAGE_VALID;
			}
		}
		else if (CurrentState == 5)
		{ // Данные от сервера
			int l = strlen(commands[WhatCommand]); // Берем длину нужной нам команды
			if (!strncmp(message, commands[WhatCommand], l))
			{ // Проверяем название команды и идём дальше...
				message += l; // Делаем так, чтобы сдвинуть указатель на начало нужной нам подстроки
				if (*message == ' ')
				{ // Должно начаться с пробела...
					message++;
					char* s; // Указательно, который мы будем двигать по строке
					for (; data[*message]; ++message); // Проходимся по данным и проверяем их по нашей матрице
					s = (*message == ' ') ? message + 1 : NULL; // Избавляемся от пробела (если он конечно есть)
					if (s && !strcmp(s, commands[WhatCommand])) // Проверяем, все ли нормально и правильно ли написана команда с правой стороны
					{
						CurrentState = 3;
						return MESSAGE_VALID;
					}
				}
			}
		}
		else if (CurrentState == 6 && !strncmp(message, "B64: ", 5))
		{ // Клиент ждет данные от сервера в Base64
			message += 5; // Делаем так, чтобы сдвинуть указатель на начало нужно нам подстроки
			char* begin = message;
			for (; base64[*message]; ++message); // Проходимся по данным и проверяем их по нашей матрице, пока не наткнемся либо на конец строки, либо на '='
			int check = 0;
			for (; (check < 2) && (message[check] == '='); ++check); // В нашей матрице нету символа '=', поэтому проверяем его тут
			if ((message - begin + check) % 4 == 0 && !message[check])
			{ // Проверяем кратность 4-ём и то, что у нас верное количество символов '='
				CurrentState = 3;
				return MESSAGE_VALID;
			}
		}
	}
	CurrentState = 1; // Раз мы дошли сюда, то что-то не так
	return MESSAGE_INVALID;
}