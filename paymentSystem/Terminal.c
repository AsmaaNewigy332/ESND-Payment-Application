#include "Terminal.h"

/*
*The function will read the current date from your computer and store it into terminal data with the mentioned size and format.
*Transaction date is 10 characters string in the format DD/MM/YYYY, e.g 25/06/2022.
*If the transaction date is NULL, less than 10 characters or wrong format will return WRONG_DATE error, else return OK.
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	/*return time and date from PC*/
	time_t raw;
	time(&raw);
	strftime(termData->transactionDate, sizeof(termData->transactionDate), "%d/%m/%Y", localtime(&raw));
	return Ok;
}

/*This function compares the card expiry date with the transaction date.
 *If the card expiration date is before the transaction date will return EXPIRED_CARD, else return OK.
 */
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	char cardM[3] = { cardData.cardExpirationDate[0] , cardData.cardExpirationDate[1] },
		cardY[3] = { cardData.cardExpirationDate[3] , cardData.cardExpirationDate[4] },
		terminalM[3] = { termData.transactionDate[3] , termData.transactionDate[4] },
		terminalY[3] = { termData.transactionDate[8] , termData.transactionDate[9] };
	if ((strcmp(terminalY, cardY) > 0) || ((strcmp(terminalY, cardY) == 0) && (strcmp(terminalM, cardM) > 0)))
		return EXPIRED_CARD;
	return Ok;
}

/*This function checks if the PAN is a Luhn number or not.
 *If PAN is not a Luhn number will return INVALID_CARD, else return OK.
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	uint32_t val = 0, temp = 0;
	for (uint32_t i = 0; i < strlen(cardData->primaryAccountNumber); i++) {
		if (i & 1)
			val += (cardData->primaryAccountNumber[i] - '0');
		else {
			temp = (cardData->primaryAccountNumber[i] - '0') * 2;
			while (temp >= 10)
				temp -= 9;
			val += temp;
		}
	}
	if (val % 10 != 0)
		return INVALID_CARD;
	return Ok;
}

/*
 *This function asks for the transaction amountand saves it into terminal data.
 *If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return OK.
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Enter The Transaction Amount: ");
	float temp = 0.0;
	scanf_s("%f", &temp);
	if (temp <= 0)
		return INVALID_AMOUNT;
	else {
		termData->transAmount = temp;
		return Ok;
	}
}

/*This function compares the transaction amount with the terminal max amount.
 *If the transaction amount is larger than the terminal max amount will return EXCEED_MAX_AMOUNT, else return OK.
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	else
		return Ok;
}

/*This function sets the maximum allowed amount into terminal data.
 *Transaction max amount is a float number.
 *If transaction max amount less than or equal to 0 will return INVALID_MAX_AMOUNT error, else return OK.
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	//printf("Enter the max amount: ");
	float temp = 5000.0;
	//scanf("%f", &temp);
	if (temp <= 0)
		return INVALID_MAX_AMOUNT;
	else {
		termData->maxTransAmount = temp;
		return Ok;
	}
}