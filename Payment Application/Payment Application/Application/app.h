#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

ST_cardData_t cardData;
ST_terminalData_t termData;
ST_transaction_t transData;


uint8_t choice;

void appStart(void);


#endif