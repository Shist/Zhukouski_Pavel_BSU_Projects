/* 
 * SPLPv1.c
 * The file is part of practical task for System programming course. 
 * This file contains definitions of the data structures and forward
 * declaration of handle_message() function
 */



enum test_status 
{ 
    MESSAGE_INVALID, 
    MESSAGE_VALID 
};


enum Direction 
{ 
    A_TO_B, 
    B_TO_A 
};


struct Message /* message */
{
	enum Direction	direction;        
	char			*text_message;
};


extern enum test_status validate_message( struct Message* pMessage ); 
