#include "Application.h"

void appStart(void) {

	while (1) {

		while (getCardHolderName(&clnt.cardHolderData) == WRONG_NAME)
			printf("Please Enter The Name In Correct Format\n");
		
		while (getCardExpiryDate(&clnt.cardHolderData) == WRONG_EXP_DATE)
			printf("Please Enter The Expiration Date In Correct Format\n");

		while (getCardPAN(&clnt.cardHolderData) == WRONG_PAN)
			printf("Please Enter The Card Pan In Correct Format\n");

		getTransactionDate(&clnt.terminalData);
		if (isCardExpired(clnt.cardHolderData, clnt.terminalData) == EXPIRED_CARD) {
			printf("Declined Expeired Card\n Press Any Button To Restart");
			getch();
			system("cls");
			continue;
		}
		
		while (getTransactionAmount(&clnt.terminalData) == INVALID_AMOUNT)
			printf("Please Enter The Valid Amount Of Transation\n");
		
		setMaxAmount(&clnt.terminalData); //5000
		
		if (isBelowMaxAmount(&clnt.terminalData) == EXCEED_MAX_AMOUNT) {
			printf("Eceeded Max Amount\n");
			printf("Press Any Button To Restart"); getch(); system("cls"); continue;
		}
		
		EN_transState_t err = recieveTransactionData(&clnt);
		if (err == DECLINED_INSUFFECIENT_FUND) {
			printf("Declined Insuffecient Funds\n Press Any Button To Restart"); getch(); system("cls"); continue;
		}
		if (err == DECLINED_STOLEN_CARD) {
			printf("Declined Invalid Account\n Press Any Button To Restart"); getch(); system("cls"); continue;
		}
		if (err == APPROVED) {
			printf("the Transaction is approved\n");
		}

		EN_transState_t Serr = saveTransaction(&clnt);

		if (Serr == SAVING_FAILED) {
			printf("save failed \n Press Any Button To Restart"); getch(); system("cls"); continue;
		}
		else {
			printf("the Transaction is saved\n");
			printf("Press Any Button To Restart"); getch(); system("cls");
		}


	}
}