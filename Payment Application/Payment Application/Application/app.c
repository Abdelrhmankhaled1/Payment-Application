#include <stdio.h>
#include <ctype.h>
#include "app.h"



int main()
{
	appStart();
	return 0;


}

void appStart(void)
{
	printf("\n*****Welcome To*****\n*****Payment Application Project*****\n**********By: Abelrhman Hamada **********");
	if (getCardHolderName(&cardData) == CARD_OK)
	{
		if (getCardExpiryDate(&cardData) == CARD_OK)
		{
			if (getCardPAN(&cardData) == CARD_OK)
			{
				if (getTransactionDate(&termData) == TERMINAL_OK)
				{
					if (isCardExpired(&cardData, &termData) == TERMINAL_OK)
					{
						if (setMaxAmount(&termData, maxAmount) == TERMINAL_OK)
						{
							if (getTransactionAmount(&termData) == TERMINAL_OK)
							{

								if (isBelowMaxAmount(&termData) == TERMINAL_OK)
								{
									if (isValidAccount(&cardData) == ACCOUNT_NOT_FOUND)
									{
										printf("\n FRAUD_CARD"); appStart();
									}
									if (isAmountAvailable(&termData) == LOW_BALANCE)
									{
										printf("\n DECLINED_INSUFFECIENT_FUND"); appStart();
									}
									transData.cardHolderData = cardData;
									transData.terminalData = termData;
									if (isBlockedAccount(&termData) == BLOCKED_ACCOUNT)
									{
										printf("\n DECLINED_STOLEN_CARD"); appStart();
									}
									
									if (recieveTransactionData(&transData) == INTERNAL_SERVER_ERROR)
									{
										printf("\n INTERNAL_SERVER_ERROR"); appStart();
									}
									if (saveTransaction(&transData) == SAVING_FAILED)
									{
										printf("\n INTERNAL_SERVER_ERROR"); appStart();
									}
									else
									{
										printf("\n APPROVED\n");
										listSavedTransactions();
										printf("\n Program ended see you soon !");
										appStart();
									}
								}
								else printf("\nEXCEED_MAX_AMOUNT"); appStart();
							}
							else printf("\nINVALID_AMOUNT"); appStart();
						}
						else printf("\nINVALID_MAX_AMOUNT"); appStart();
					}
					else printf("\nEXPIRED_CARD"); appStart();
				}
				else printf("\nWRONG_DATE"); appStart();
			}
			else printf("\nWRONG_PAN"); appStart();
		}
		else printf("\nWRONG_EXP_DATE"); appStart();
	}
	else printf("\nWRONG_NAME"); appStart();


}






