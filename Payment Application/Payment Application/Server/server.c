#include "server.h"
#include "../Application/app.h"
#include <stdio.h>

uint32_t tsn = 0;
uint32_t n = 0;


ST_accountsDB_t accounts_database[255] = {
	{1000,RUNNING,"1111111111111111"},
	{2000,BLOCKED,"2222222222222222"},
	{3000,BLOCKED,"3333333333333333"},
	{4000,RUNNING,"4444444444444444"},
	{5000,RUNNING,"5555555555555555"},
	{6000,RUNNING,"6666666666666666"},
	{7000,RUNNING,"7777777777777777"},
	{8000,RUNNING,"8888888888888888"},
	{9000,RUNNING,"9999999999999999"},
	{10000,RUNNING,"1000000000000000"}
};

ST_transaction_t transactions_database[255] = {0};


EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	uint32_t z = 0;

	for (n = 0; n < 255; n++) {
		z = strcmp(cardData->primaryAccountNumber, accounts_database[n].primaryAccountNumber);
		if (z == 0) {
			return  SERVER_OK;
			break;
		}
	}
	return  ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* termData)
{
	if (accounts_database[n].state == RUNNING)
		return SERVER_OK;
	else
		return BLOCKED_ACCOUNT;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (accounts_database[n].balance >= termData->transAmount)
	{

		return SERVER_OK;
	}
	else 
	{
		return LOW_BALANCE;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	transData->transactionSequenceNumber = tsn;
		if (transData->transactionSequenceNumber <= 255)
		{
			transactions_database[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
			transactions_database[transData->transactionSequenceNumber].terminalData = transData->terminalData;
			transactions_database[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;
			tsn++;

			return SERVER_OK;
		}
	return SAVING_FAILED;
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (transData == NULL) {

		return INTERNAL_SERVER_ERROR;

	}
	else {
		accounts_database[n].balance = (accounts_database[n].balance) - (transData->terminalData.transAmount);
		return APPROVED;
	}
}

void listSavedTransactions(void) {

	uint32_t i = 0;
	for (i = 0; i < tsn; i++) {
		if (tsn != 0) {
			printf("\n*************************\n");
			printf("\nTransaction Sequence Number: %d\n", tsn);
			printf("Transaction Date: %s\n", transactions_database[i].terminalData.transactionDate);
			printf("Transaction Amount: %.02f\n", transactions_database[i].terminalData.transAmount);
			printf("\nTransaction State: %d\n", accounts_database[n].state);
			printf("Terminal Max Amount: %.02f\n", transactions_database[i].terminalData.maxTransAmount);
			printf("Cardholder Name: %s\n", transactions_database[i].cardHolderData.cardHolderName);
			printf("PAN: %s\n", transactions_database[i].cardHolderData.primaryAccountNumber);
			printf("Card Expiration Date: %s\n", transactions_database[i].cardHolderData.cardExpirationDate);
			printf("New balance: %.02f\n", accounts_database[n].balance);
			printf("\n*************************\n");
		}
		else {
			printf("No Transactions");
			break;
		}
	}
}






