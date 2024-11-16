#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 获取需要查找的单词数
int get_word_count() {
    int word_count;
    scanf("%d", &word_count);
    return word_count;
}

// 为word_count个单词分配空间,并检查内存分配是否成功
char **allocate_words(int count) {
    char **words = (char **)malloc(sizeof(char *) * count);
    if (words == NULL) {
        printf("Memory allocation failed!\n");
        exit(1); // 内存分配失败则退出程序
    }
    return words;
}

// 读取word_count个单词到words中,并检查每个单词的内存分配是否成功
void get_words(char **words, int count) {
    for (int i = 0; i < count; ++i) {
        char *word = (char *)malloc(sizeof(char) * 50);
        if (word == NULL) {
            printf("Memory allocation failed!\n");
            exit(1); // 内存分配失败则退出程序
        }
        scanf("%s", word);
        words[i] = word;
    }
}

// 动态读取文本内容到*text中,记录每行开始位置到*line_numbers
// 使用扩容机制,每次内存不足时多分配一倍的空间,直到文件末尾
void read_text(FILE *fp, char **text, int **line_numbers, int *char_count, int *line_count) {
    int size = 100;
    *text = (char *)malloc(size * sizeof(char));
    *line_numbers = (int *)malloc(size * sizeof(int));
    if (*text == NULL || *line_numbers == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // 读取文本内容
    while (!feof(fp)) {
        // 扩容
        if (*char_count + 1 >= size) {
            size *= 2;
            char *tmp = (char *)malloc(size * sizeof(char));
            int *line_numbers_tmp = (int *)malloc(size * sizeof(int));
            if (tmp == NULL || line_numbers_tmp == NULL) {
                printf("Memory allocation failed!\n");
                exit(1);
            }
            strcpy(tmp, *text);
            free(*text);
            *text = tmp;
            memcpy(line_numbers_tmp, *line_numbers, (*char_count) * sizeof(int));
            free(*line_numbers);
            *line_numbers = line_numbers_tmp;
        }

        char next_char = fgetc(fp);
        if (next_char == '\n')
            (*line_count)++; // 记录行数
        else {
            (*line_numbers)[*char_count] = *line_count; // 记录当前行号
            (*text)[*char_count] = next_char;           // 添加字符
            (*char_count)++;                            // 统计字符数
        }
    }
}

// KMP算法在text中查找pattern,打印所在行号
void kmp(char *text, char *pattern, int *line_numbers, int char_count, int line_count) {
    int text_len = strlen(text);
    int pat_len = strlen(pattern);
    if (text_len < pat_len) {
        return;
    }
    int last_line = -1;
    int *next = (int *)malloc(pat_len * sizeof(int));
    next[0] = 0;
    // 构建next数组
    for (int i = 1, j = 0; i < pat_len;) {
        if (pattern[i] == pattern[j]) { // 如果当前字符匹配前缀
            j++;
            next[i] = j;
            i++; // 继续匹配下一个字符
        } else if (j > 0) {
            j = next[j - 1];
        } else {
            next[i] = 0;
            i++; // 继续匹配下一个字符
        }
    }

    // KMP匹配算法
    for (int i = 0, j = 0; i < text_len;) {
        if (text[i] == pattern[j]) { // 如果当前字符匹配
            i++;                     // 文本下标右移
            j++;                     // 模式下标右移
        } else if (j != 0) {
            j = next[j - 1]; // 模式下标回退到next[j-1]
        } else {
            i++; // 文本下标右移
        }
        if (j == pat_len) { // 如果找到匹配
            if (line_numbers[i - j] != last_line) {
                last_line = line_numbers[i - j];
                printf("%d ", last_line); // 打印行号
            }
        }
    }
    printf("\n");
    free(next); // 释放next数组空间
}

int main() {
    // 获取需要查找的单词数
    printf("Please enter the number of words you want to query: ");
    int word_count = get_word_count();

    // 为word_count个单词分配空间,并检查内存分配是否成功
    char **words = allocate_words(word_count);

    // 读取word_count个单词到words中,并检查每个单词的内存分配是否成功
    printf("Please enter the words you want to query in order: \n");
    get_words(words, word_count);

    // 打开文本文件,检查文件打开是否成功
    FILE *fp = fopen("./novel.txt", "r");
    if (fp == NULL) {
        printf("File open failed!\n");
        exit(1); // 文件打开失败则退出程序
    }

    // 定义变量,记录文本内容、文本长度、行号数组、字符数、行数
    char *text;
    int *line_numbers;
    int char_count = 0;
    int line_count = 1;

    // 读取文本
    read_text(fp, &text, &line_numbers, &char_count, &line_count);

    // 查找每个单词并精准打印行号
    for (int i = 0; i < word_count; ++i) {
        printf("%s exist in lines: ", words[i]);
        kmp(text, words[i], line_numbers, char_count, line_count);
    }

    // 释放所有内存空间,避免内存泄露
    for (int i = 0; i < word_count; ++i)
        free(words[i]);
    free(words);
    free(text);
    free(line_numbers);
}
