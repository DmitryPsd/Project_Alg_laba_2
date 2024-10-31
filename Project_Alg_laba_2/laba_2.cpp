#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

void mainFunk(char str[]) {
    bool hasDigit = false;
    int length = std::strlen(str);

    for (int i = 0; i < length; ++i) {
        if (isdigit(str[i])) {
            hasDigit = true;
            break;
        }
    }

    char replacement = hasDigit ? '_' : '-';

    for (int i = 0; i < length; ++i) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
    str[length] = '\0';
}
void replace_spaces(char* str) {
    if (str == NULL) {
        return; 
    }

    int has_digit = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            has_digit = 1;
            break;
        }
    }
    char replace_char = has_digit ? '_' : '-';
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replace_char;
        }
    }
}

int funk1() {
    const int initialSize = 1;
    char* inputString = (char*)malloc(initialSize * sizeof(char));
    if (!inputString) {
        std::cerr << "Memory allocation failed" << std::endl;
        return 1;
    }

    std::cout << "Enter a string: ";
    char ch;
    int length = 0;

    while ((ch = std::cin.get()) != '\n') {
        char* newInputString = (char*)malloc((length + 1) * sizeof(char));
        if (!newInputString) {
            std::cerr << "Memory allocation failed" << std::endl;
            free(inputString);
            return 1;
        }
        if (length > 0) {
            std::memcpy(newInputString, inputString, length * sizeof(char));
        }
        newInputString[length] = ch;
        free(inputString);
        inputString = newInputString;
        ++length;
    }

    inputString[length] = '\0';
    mainFunk(inputString);

    std::cout << "Processed string: " << inputString << std::endl;
    free(inputString);

    return 0;
}

int funk2() {
    const int initialSize = 5;
    char* inputString = (char*)calloc(initialSize, sizeof(char));
    if (!inputString) {
        std::cerr << "Memory allocation failed" << std::endl;
        return 1;
    }

    std::cout << "Enter a string: ";
    char ch;
    int length = 0;
    int allocatedSize = initialSize;

    while ((ch = std::cin.get()) != '\n') {
        if (length >= allocatedSize) {
            allocatedSize += initialSize;
            char* newInputString = (char*)realloc(inputString, allocatedSize * sizeof(char));
            if (!newInputString) {
                std::cerr << "Memory allocation failed" << std::endl;
                free(inputString);
                return 1;
            }
            inputString = newInputString;
        }
        inputString[length++] = ch;
    }

    inputString[length] = '\0';
    mainFunk(inputString);

    std::cout << "Processed string: " << inputString << std::endl;
    free(inputString);

    return 0;
}

int funk3() {
    char* str = NULL;
    size_t length = 0;
    char ch;
    FILE* input_file, * output_file;

    output_file = fopen("text1.txt", "w");
    if (output_file == NULL) {
        perror("Failed to open output file");
        return 1;
    }

    printf("INPUT:\n");
    while (1) {
        ch = getchar();
        if (ch == '\n') {
            break; 
        }

        char* temp = (char*)malloc(length + 2); 
        if (length > 0) {
            strcpy(temp, str); 
            free(str); 
        }
        temp[length] = ch;
        temp[length + 1] = '\0'; 
        str = temp; 
        length++;
    }

    fprintf(output_file, "%s\n", str);
    fclose(output_file);


    input_file = fopen("text1.txt", "r");
    if (input_file == NULL) {
        perror("Failed to open input file");
        free(str);
        return 1;
    }

    str = NULL;
    length = 0;
    while ((ch = fgetc(input_file)) != EOF) {
        char* temp = (char*)malloc(length + 2);
        if (length > 0) {
            strcpy(temp, str);
            free(str);
        }
        temp[length] = ch;
        temp[length + 1] = '\0';
        str = temp;
        length++;
    }
    fclose(input_file);

    replace_spaces(str);

    output_file = fopen("text2.txt", "w");
    if (output_file == NULL) {
        perror("Failed to open final output file");
        free(str);
        return 1;
    }
    fprintf(output_file, "%s\n", str);
    fclose(output_file);

    free(str);
    return 0;
}


int main() {
    funk3();
    return 0;
}
