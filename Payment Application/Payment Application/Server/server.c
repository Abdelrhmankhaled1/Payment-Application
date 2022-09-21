#include "server.h"
#include <stdio.h>
uint32_t tsn=0;

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
	{10000,BLOCKED,"1000000000000000"}
};

ST_transaction_t transactions_database[255] = {0};


EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	uint32_t i = 0, z = 0;

	for (i = 0; i < 255; i++) {
		z = strcmp(cardData->primaryAccountNumber, accounts_database[i].primaryAccountNumber);
		if (z == 0) {
			return  SERVER_OK;
			break;
		}
	}
	return  ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence->state == RUNNING)
		return RUNNING;
	else
		return BLOCKED;

}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (accounts_database->balance >= termData->transAmount) 
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
	for (int i = 0; i < 255; i++)
	{
		if (transactions_database[i].transactionSequenceNumber == 0)
		{
			strcpy_s(transactions_database[i].cardHolderData.cardHolderName,25, transData->cardHolderData.cardHolderName);
			strcpy_s(transactions_database[i].cardHolderData.cardExpirationDate,6, transData->cardHolderData.cardExpirationDate);
			strcpy_s(transactions_database[i].cardHolderData.primaryAccountNumber,20, transData->cardHolderData.primaryAccountNumber);
			strcpy_s(transactions_database[i].terminalData.transactionDate,11, transData->terminalData.transactionDate);
			transactions_database[i].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
			transactions_database[i].terminalData.transAmount = transData->terminalData.transAmount;
			transactions_database[i].transState = transData->transState;
			tsn = transactions_database[i].transactionSequenceNumber = i + 1;
			

			return SERVER_OK;
		}
	}
	return SAVING_FAILED;
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	int r=0;
	ST_accountsDB_t accref;

	r = isValidAccount(&transData->cardHolderData, &accref);
	if (r == ACCOUNT_NOT_FOUND) return FRAUD_CARD;

	r = isAmountAvailable(&transData->terminalData, &accref);
	if (r == LOW_BALANCE) return DECLINED_INSUFFECIENT_FUND;
	
	r = isBlockedAccount(&accref);
	if (r == BLOCKED) return DECLINED_STOLEN_CARD;




}









