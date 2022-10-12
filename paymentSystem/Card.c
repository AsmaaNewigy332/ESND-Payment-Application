#include"card.h"

/*
 *This function will ask for the cardholder's name and store it into card data.
 *Card holder name is 24 characters string max and 20 min.
 *If the cardholder name is NULL, less than 20 characters or more than 24 will return WRONG_NAME error, else return OK.
 */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Enter The Card Holder Name: ");
	gets( cardData->cardHolderName);
	/*If the cardholder name is NULL, less than 20 characters or more than 24 will return WRONG_NAME error, else return OK.*/
	if (cardData->cardHolderName != NULL || strlen(cardData->cardHolderName) >= 20 || strlen(cardData->cardHolderName) <= 24) {
		for (uint8_t i = 0; i < strlen(cardData->cardHolderName); i++) {
			if (cardData->cardHolderName[i] >= '0' && cardData->cardHolderName[i] <= '9')
				return WRONG_NAME;
		}
		return OK;
	}
	return WRONG_NAME;
}

/*
 *This function will ask for the card expiry date and store it in card data.
 *Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
 *If the card expiry date is NULL, less or more than 5 characters, or has the wrong format will return WRONG_EXP_DATE error, else return OK.
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Enter The Card Expiry Date: ");
	gets(cardData->cardExpirationDate);
	/*check expDate format is correct
	*If the card expiry date is NULL, less or more than 5 characters, or has the wrong format will return WRONG_EXP_DATE error, else return OK.
	*/
	if (cardData->cardExpirationDate == NULL || strlen(cardData->cardExpirationDate) != 5)
		return WRONG_EXP_DATE;

	if (cardData->cardExpirationDate[2] != '/')
		return WRONG_EXP_DATE;

	for (int i = 0; i < 5; i++) {
		if (i == 2)
			continue;
		else
			if (cardData->cardExpirationDate[i] < '0' || cardData->cardExpirationDate[i]>'9')
				return WRONG_EXP_DATE;
	}

	return OK;
}

/*
 *This function will ask for the card's Primary Account Number and store it in card data.
 *PAN is 20 characters alphanumeric only string 19 character max, and 16 character min.
 *If the PAN is NULL, less than 16 or more than 19 characters, will return WRONG_PAN error, else return OK.
 */
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Enter The Card Card Pan: ");
	gets(cardData->primaryAccountNumber);

	/*If the PAN is NULL, less than 16 or more than 19 characters,
	will return WRONG_PAN error, else return OK.
	*/
	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19|| strlen(cardData->primaryAccountNumber)==NULL)
		return WRONG_PAN;

	for (uint8_t i = 0; i < strlen(cardData->primaryAccountNumber); i++) {
		if (cardData->primaryAccountNumber[i] < '0' || cardData->primaryAccountNumber[i]>'9')
			return WRONG_PAN;
	}
	return OK;
}
