#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main() {
FILE *intermediate, *optab, *symtab, *output, *prgmlength,*objectcode;
char opcode[20], operand[20], label[20], mneumonic[20], code[20], value[20], textRecord[70];
int locctr, start, programLength, length = 0, textStartAddr;
optab = fopen("optab.txt", "r");
intermediate = fopen("intermediate.txt", "r");
symtab = fopen("symtab.txt", "r");
output = fopen("output.txt", "w");
objectcode=fopen("objectcode.txt","w");
prgmlength = fopen("prgmlength.txt", "r");
if (!optab || !intermediate || !symtab || !output || !prgmlength) {//to check whether there is any error in opening the file
printf("Error opening files\n");
return;
}
fscanf(intermediate, "%s %s %s", label, opcode, operand);//to read 1st input line
printf("first input line read: %s %s %s\n", label, opcode, operand);
fprintf(output, "     %-7s%-7s%-7s\n", label, opcode, operand);//write the listing line to an output file
if (strcmp(opcode, "START") == 0) {
fscanf(prgmlength, "%d", &programLength);
start = atoi(operand);//atoi()is used to convert string to an integer
fprintf(objectcode, "H^%s^%06d^%06d\n", label, start, programLength); // header format
}
fscanf(intermediate, "%d %s %s %s", &locctr, label, opcode, operand);
textStartAddr = locctr;//textStartAddr contains the starting address of a text record
strcpy(textRecord, "");//initialising a text record with a null terminator so that it can be used for other operations
while (strcmp(opcode, "END") != 0) {
char objectCode[10] = "";//initialising objectCode with a null terminator \0
printf("Processing line: %d %s %s %s\n", locctr, label, opcode, operand);
fprintf(output, "%d %-7s%-7s%-7s", locctr, label, opcode, operand);
if (strcmp(opcode, "BYTE") == 0) {
if (operand[0] == 'C' && operand[1] == '\'') {//Checks if the first character of the operand string is C and second character is a single quote '.
if (strcmp(operand, "C'EOF'") == 0) {
strcpy(objectCode, "454F46");
} else {   
for (int i = 2; i < strlen(operand) - 1; i++) {
//sprintf() function in C is used to write formatted data to a string or buffer(here to the location pointed by objectCode + strlen(objectCode) which is null \0)
sprintf(objectCode + strlen(objectCode), "%02X", operand[i]);
}
}
}
/*while (strlen(objectCode) < 6) {//insert 0's to the left if the no of digits in objectcode is less than 6
char temp[10];
sprintf(temp, "0%s", objectCode);
strcpy(objectCode, temp);
}*/
} else if (strcmp(opcode, "WORD") == 0) {
sprintf(objectCode, "%06d", atoi(operand));
} else if (strcmp(opcode, "RESB") == 0) {
// No object code for RESB
} else if (strcmp(opcode, "RESW") == 0) {
// No object code for RESW
} else {
rewind(optab);//reset the file pointer of the file optab to the beginning of the file
while (fscanf(optab, "%s %s", mneumonic, code) != EOF) {
if (strcmp(opcode, mneumonic) == 0) {//read pairs of strings from the file optab.txt until the end of the file(EOF) is reached.
strcpy(objectCode, code);//If a match is found,the next line copies the code to objectCode, and the loop breaks
break;
}
}
rewind(symtab);
while (fscanf(symtab, "%s %s", label, value) != EOF) {
if (strcmp(operand, label) == 0) {
sprintf(objectCode + strlen(objectCode), "%04d", atoi(value));
break;
}
}
}
printf("Object Code: %s\n", objectCode); 
fprintf(output, "%s\n",objectCode);
if (length + strlen(objectCode) > 60) {//to check whether the text record is full
fprintf(objectcode, "T^%06d^%02X^%s\n", textStartAddr, length / 2, textRecord);
strcpy(textRecord, "");//initialising new text record
textStartAddr = locctr;
length = 0;
}
if (strlen(objectCode) > 0) {//adding object code to text record
strcat(textRecord, objectCode);
strcat(textRecord, "^");
length += strlen(objectCode);
}
fscanf(intermediate, "%d %s %s %s", &locctr, label, opcode, operand);//reading next input line
}
if (length > 0) {
textRecord[strlen(textRecord) - 1] = '\0'; // Remove the last '^'
fprintf(objectcode, "T^%06d^%02X^%s\n", textStartAddr, length / 2, textRecord); // Ensure the last text record is written
}
fprintf(output, "%d %-7s%-7s%-7s", locctr, label, opcode, operand);
fprintf(objectcode, "E^%06d\n", start);
fclose(intermediate);
fclose(symtab);
fclose(optab);
fclose(output);
fclose(prgmlength);
printf("FINISHED EXECUTION!!!\n");
}
