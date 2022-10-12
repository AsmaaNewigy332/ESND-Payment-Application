#include "Server.h"
/*Implement server-side accounts' database*/
extern ST_accountsDB_t AccDB[255] = { {5000,"1234567899876543211"},{60000,"12345678912345678"},{55000,"98765432112345670"} };
/*Implement server-side transactions' database*/
extern ST_transaction_t TransDB[255] = { 0 };
uint16_t transactionNumbers = 0;
uint16_t accountNumber = 3;

/*This function will take all transaction data and validate its data.
It checks the account details and amount availability.
If the account does not exist return DECLINED_STOLEN_CARD, if the amount is not available will return DECLINED_INSUFFECIENT_FUND, if a transaction can't be saved will return INTERNAL_SERVER_ERROR and will not save the transaction, else returns APPROVED.
It will update the database with the new balance.*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	if (isValidAccount(&transData->cardHolderData) != OK) return DECLINED_STOLEN_CARD;
	if (isAmountAvailable(&transData->cardHolderData, &transData->terminalData) != tOK)
		return DECLINED_INSUFFECIENT_FUND;
	else {
		for (int i = 0; i < accountNumber; i++)
			if (strcmp(transData->cardHolderData.primaryAccountNumber, AccDB[i].primaryAccountNumber) == 0)
				AccDB[i].balance = AccDB[i].balance - transData->terminalData.transAmount;
	}
	return APPROVED;
}

/*This function will take card data and validate these data.
It checks if the PAN exists or not in the server's database.
If the PAN doesn't exist will return DECLINED_STOLEN_CARD, else will return OK*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	for (int i = 0; i < accountNumber; i++)
		if (strcmp(cardData->primaryAccountNumber, AccDB[i].primaryAccountNumber) == 0)
			return tOK;
	return DECLINED_STOLEN_CARD;
}

/*This function will take terminal data and validate these data.
It checks if the transaction's amount is available or not.
If the transaction amount is greater than the balance in the database will return LOW_BALANCE, else will return OK*/
EN_serverError_t isAmountAvailable(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	for (int i = 0; i < accountNumber; i++)
		if (strcmp(cardData->primaryAccountNumber, AccDB[i].primaryAccountNumber) == 0)
			if (AccDB[i].balance < termData->transAmount)
				return LOW_BALANCE;
	return tOK;


}

/*This function will take all transaction data into the transactions database.
It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server.
If saves any type of transaction, APPROVED or DECLINED, with the specific reason for declining/transaction state.
If transaction can't be saved will return SAVING_FAILED, else will return OK*/
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	if (transactionNumbers == 255)return SAVING_FAILED;
	else {
		TransDB[transactionNumbers].cardHolderData = transData->cardHolderData;
		TransDB[transactionNumbers].terminalData = transData->terminalData;
		TransDB[transactionNumbers].transactionSequenceNumber = transactionNumbers + 59534;
		TransDB[transactionNumbers].transState = recieveTransactionData(transData) == 0 ? APPROVED : recieveTransactionData(transData);
		transactionNumbers++;
		return tOK;
	}
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
	for (int i = 0; i < transactionNumbers; i++)
	{
		if (TransDB[i].transactionSequenceNumber == transactionSequenceNumber) {
			transData = &TransDB[i];
			return tOK;
		}
	}
	return TRANSACTION_NOT_FOUND;
}