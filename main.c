/*
	fetch balance and parse result
	(for MCU)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>




int main(int argc, char **argv)
{
	char *resp = "\r\nБаланс 457.78 р. Podkluchay uslugu zvoni i smotri nomer 756 678.89 р./мес\r\n\r\nOK\r\n";
	printf("ATD*105#;");
	printf("%s", resp);
	printf("\n");
	printf("parsed balance:\n");
	char token[256] = {0};
	char pos;
	char state = 0;
	char done;
	char resp_rcv = 0;
	char i = 0;
	char c; 
	char balance_found = 0;
	double balance = -1.0; 
	while (!resp_rcv && /*!balance_found*/balance < 0.0) {
		done = 0;
		pos = 0;		
		while (!done) {
			c = resp[i++];
			//printf("[%c]", c);
			switch (state) {
			case 0:
				if ('\r' == c) continue;
				else if ('\n' == c) state = 1; continue;
				break;
			case 1:
				if ('\r' == c) continue;
				else if ('\n' == c) {
					state = 0;  
					token[pos] = '\0';
					printf("tok: [%s]\n", token);
					// check on balance algorirhm
					if (isdigit(token[0])) {
						balance = atof(token);
														
						//char j;
						//for (j = 1; j < strlen(token); j++) {
						//	if (!isdigit(token[j]) && '.' != token[j]) {
						//	  balance_found = 0;
						//	}
							//printf("[c]");
						//}
						//printf("\n");						
					}
					 
					if (balance > 0) printf("balance: %.2f\n", balance);

					//if (balance_found) {
					//	printf("balance: %s\n", token);
					//}
		
					done = 1;
					if (NULL != strstr(token, "OK")) resp_rcv = 1;
			  }
				else if (' ' == c) {
					token[pos] = '\0';
					printf("tok: [%s]\n", token);
					// check on balance algorirhm
					if (isdigit(token[0])) {
						balance = atof(token);								
						//printf("[%c]", token[0]);
            //char j;
						//for (j = 1; j < strlen(token); j++) {
						//	if (!isdigit(token[j]) || '.' != token[j]) {
						//	  balance_found = 0;
						//	}
						//	printf("[%c]", token[j]);
						//}
						//printf("\n");			
					}
					 
					//if (balance_found) {
					//	printf("balance: %s\n", token);
					//}

					if (balance > 0) printf("balance: %.2f\n", balance);

					done = 1;
					if (NULL != strstr(token, "OK")) resp_rcv = 1;			
				}
				break;
			}
			token[pos++] = c;
		}
  }

	return 0;
}
