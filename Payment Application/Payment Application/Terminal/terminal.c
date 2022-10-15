#include "terminal.h"
#include<stdio.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	char trandate[100];
	int i = 0;
	trandate[10] = '\0';
	uint32_t D, M, Y;
	printf("\n Enter Transaction Date [DD/MM/YYYY]: ");
	gets(trandate);
	while (trandate[i]) 
	{
		if (isalpha(trandate[i]) != 0)
		{
			return WRONG_DATE;
		}
		i++;
	}

	if (trandate[9] == '\0' || trandate[10] != '\0') 
	{
		return WRONG_DATE;
	}
	D = (trandate[0] - '0') * 10 + (trandate[1] - '0');
	M = (trandate[3] - '0') * 10 + (trandate[4] - '0');
	Y = (trandate[6] - '0') * 10 + (trandate[9] - '0');
	if (D < 1 || D > 31 || trandate[2] != '/' || M < 1 || M > 12 || trandate[5] != '/' || Y < 1 || Y > 9999) 
	{
		return WRONG_DATE;
	}
	termData->transactionDate[0] = trandate[0];
	termData->transactionDate[1] = trandate[1];
	termData->transactionDate[2] = '/';
	termData->transactionDate[3] = trandate[3];
	termData->transactionDate[4] = trandate[4];
	termData->transactionDate[5] = '/';
	termData->transactionDate[6] = trandate[6];
	termData->transactionDate[7] = trandate[7];
	termData->transactionDate[8] = trandate[8];
	termData->transactionDate[9] = trandate[9];
	termData->transactionDate[10] = '\0';
	return TERMINAL_OK;


}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{

	int Exm = (cardData->cardExpirationDate[0] - '0') * 10 + cardData->cardExpirationDate[1] - '0';
	int Exy = (cardData->cardExpirationDate[3] - '0') * 10 + cardData->cardExpirationDate[4] - '0' + 2000;
	int Tranm = (termData->transactionDate[3] - '0') * 10 + termData->transactionDate[4] - '0';
	int Trany = (termData->transactionDate[6] - '0') * 1000 + (termData->transactionDate[7] - '0') * 100 + (termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0');
	if (Trany > Exy) 
	{
		return EXPIRED_CARD;
	}
	if (Trany == Exy && Tranm > Exm) 
	{
		return EXPIRED_CARD;
	}
	return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	float amount = 0.0;
	printf("\n Enter Transaction Amount: ");
	scanf_s("%f", &amount);
	if (amount <= 0) 
	{
		return INVALID_AMOUNT;
	}
	termData->transAmount = amount;
	return TERMINAL_OK;

}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount) 
	{
		return EXCEED_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	printf("\n Enter the maximum amount for the transaction: ");
	scanf_s("%f", &maxAmount);
	if (maxAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	termData->maxTransAmount = maxAmount;
	return TERMINAL_OK;
}


