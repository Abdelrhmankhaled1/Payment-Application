#include "card.h"


 EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	char name[100];
	name[25] = '\0';
	int length = 0;
	int i = 0;
	printf("\n Please enter card Holder name [20 to 24 characters] :");
	gets(name);
	length = strlen(name);
	while (name[i]) {
		if (isalpha(name[i]) == 0)
		{
			return WRONG_NAME;
		}
		i++;
	}
	if (length == 0 || length < 18 || length>24)
	{
		return WRONG_NAME;
	}
	else
	{
		for (i = 0; i < 25; i++) {
			cardData->cardHolderName[i] = name[i];
		}
		return CARD_OK;

	}
} 
	EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
		char expdate[100];
		int i=0;
		expdate[5] = '\0';
		uint32_t M, Y;
		printf("\n Enter Card Expiry Date In This Format [MM/YY] :");
		gets(expdate);
		while (expdate[i]) {
			if (isalpha(expdate[i]) != 0)
			{
				return WRONG_EXP_DATE;
			}
			i++;
		}
		if (expdate[4] == '\0' || expdate[5] != '\0') 
		{
			return WRONG_EXP_DATE;
		}
		M = (expdate[0] - '0') * 10 + (expdate[1] - '0');
		Y = (expdate[3] - '0') * 10 + (expdate[4] - '0');
		if (M < 1 || M > 12 || expdate[2] != '/' || Y < 1 || Y > 99) 
		{
			return WRONG_EXP_DATE;
		}
		for (i = 0; i < 6; i++) {
			cardData->cardExpirationDate[i] = expdate[i];
		}
		return CARD_OK;


	}
	EN_cardError_t getCardPAN(ST_cardData_t* cardData) 
	{
		char cardpan[100];
		int i = 0;
		for (i = 0; i < 100; i++)
		{
			cardpan[i] = '\0';
		}
			printf("\n Enter PAN [16 to 19 characters]: ");
		gets(cardpan);
		if (!cardpan || cardpan[19] != '\0' || cardpan[15] == '\0')
		{
			return WRONG_PAN;

		}
		for (int i = 0; i < 20; i++) {
			cardData->primaryAccountNumber[i] = cardpan[i];
		}
		return CARD_OK;
	}

	





