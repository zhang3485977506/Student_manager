#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
//-------------------------------------------------------------------------------------------------------------
#define FG_BLACK          "\033[30m"    //��ɫ
#define FG_1  "\033[38;2;246;129;10m"   // ���ɫ
#define FG_2  "\033[38;2;243;100;13m"   // ����ɫ
#define FG_3  "\033[38;2;219;88;31m"    // �Ȼ�ɫ
#define FG_4  "\033[38;2;195;76;49m"    // ǳ��ɫ
#define FG_5  "\033[38;2;171;63;67m"    // �Ⱥ�ɫ
#define FG_6  "\033[38;2;0;90;0m"       // �������ɫ
#define FG_7  "\033[38;2;0;80;0m"       // �������ɫ
#define FG_8  "\033[38;2;0;64;0m"       // ʮ�����̵���ɫ
#define FG_9  "\033[38;2;0;51;0m"       // �������ɫ
#define YELLOW "\033[38;2;255;255;0m"
#define BG_WHITE   "\033[48;2;255;255;255m"
#define RESET      "\033[0m"
#define WHITE   "\033[47m"
#define BLINK_1 "\033[38;2;255;69;0m\033[5m"      // �Ⱥ�ɫ��˸
#define BLINK_2 "\033[38;2;255;0;0m\033[5m"       // ��ɫ��˸
#define BLINK_3 "\033[38;2;0;0;255m\033[48;2;255;255;0m\033[5m\033[48;2;255;255;255m"
#define RED "\033[38;2;255;0;0m"
//--------------------------------------------------------------------------------------------------------------
int m = 0, n = 0;
int userpower = 0;
int caozuoshu = 0;
int caozuo = 0;
typedef struct student {
    char name[30];
    char gender[10];
    char className[30];
    char num[30];
    int grade[100];
    int sum;
} Stu;

//-------------------------------------------------------

void Inilial_Write(FILE *p);

int Read_m(FILE *fp);//ѧ��������ʼ��
int Read_n(FILE *fp); //�γ�������ʼ��
void Append(FILE *p);

void Looking(FILE *fp);

void Delete(FILE *fp);

void Modify(FILE *fp);

void Mearch(FILE *fp);

void Mearch_class(Stu *p);

void Mearch_name(Stu *p);

void Mearch_grade(Stu *p);

void Mearch_num(Stu *p);

void Sort_Max_Min(FILE *fp);

void Sort_Min_Max(FILE *fp);

void SortNum_Min_Max(FILE *fp);

void SortNum_Max_Min(FILE *fp);

void Write_char(FILE *fp);

void Looking_all(FILE *fp);

void Sortbygender(FILE *fp);

void Randomsort(FILE *fp);

void PRINTF(Stu *p);

void PRINT_ALL(Stu *p);

void moshi1(Stu *p);

void moshi2(Stu *p);

void moshi3(Stu *p);

void CHOICE(int ch);

//-------------------------------------------------------
int main() {
    for (int k = 1; k <= 10; k++) {
        char USERNAME[100];
        char USERNUM[100];
        printf("----------------------\n");
        printf("�������û���:");
        scanf("%s", USERNAME);
        getchar();
        printf("----------------------\n");
        printf("����������:");
        scanf("%s", USERNUM);
        getchar();
        if (strcmp(USERNAME, "��Ӧʤ") == 0 && strcmp(USERNUM, "zhangyingsheng") == 0) {
            FILE *user;
            user = fopen("User.txt", "a");
            system("CLS");
            printf("--------------------------------\n");
            printf("���,������\n���������ӵ��û���������:\n");
            char aaa[100];
            char bbb[100];
            scanf("%s %s", aaa, bbb);
            getchar();
            fprintf(user, "%s %s\n", aaa, bbb);
            userpower = 1;
            k = 11;
            system("CLS");
            printf("������ȷ\n~~~~~~~~~~��ӭ~~~~~~~~~~\n");
            sleep(1);
        } else {
            {
                FILE *user;
                user = fopen("User.txt", "r");
                int mid = 1;
                char line[200];
                while (fgets(line, sizeof(line), user)) {
                    char aaa[100];
                    char bbb[100];
                    sscanf(line, "%s %s", aaa, bbb);
                    if (strcmp(USERNAME, aaa) == 0 && strcmp(USERNUM, bbb) == 0) {
                        mid = 0;
                    }
                }
                fclose(user);
                if (mid) {
                    system("CLS");
                    printf("~~~~~~~~~~~~~~~~\n�û������������󣡣���\n");
                } else {
                    userpower = 1;
                    k = 11;
                    printf("������ȷ\n~~~~~~~~~~��ӭ~~~~~~~~~~\n");
                    sleep(1);
                }
            }


        }
        if (k == 3) {
            system("CLS");
            printf("\n�����û������������3��,���˳�,��ò鿴Ȩ�޻��������,������10��!!!\n");
            printf("1.�˳�\n");
            printf("2.��������,������10��!!!\n");
            printf("3.��ò鿴Ȩ��(Ĭ��)\n");
            printf("~~~~~~~~~~~~~~~~\n");
            printf("��ѡ��:\n");
            int choice = 0;
            scanf("%d", &choice);
            getchar();
            switch (choice) {
                case 1: {
                    printf("�˳�\n");
                    return 0;
                    break;
                }
                case 2: {
                    printf("��������,������10��!!!\n");
                    k = 4;
                    break;
                }
                case 3: {
                    printf("######################\n�Ѿ���ò鿴Ȩ��(Ĭ��)\n");
                    getchar();
                    k = 11;
                    userpower = 0;
                    break;
                }
                default: {
                    printf("######################\n�Ѿ���ò鿴Ȩ��(Ĭ��)\n");
                    getchar();
                    k = 11;
                    userpower = 0;
                    break;
                }
            }
        }


        if (k == 10) return 0;
        if (k == 11) break;
    }

    system("CLS");
    //��ʼ��ģ��1------------------------------------------------------------------------------------------------------
    FILE *fp;
    fp = fopen("Students' scores.txt", "a");
    fseek(fp, 0L, SEEK_END);// �ƶ�ָ�뵽ĩβ
    if (ftell(fp) == 0)//���Ϊ0����ʼ��
    {
        Inilial_Write(fp);
        fclose(fp);
        printf(BG_WHITE BLINK_1"��ӭ����Management for Students' scoresϵͳ\n"RESET);
    } else
        //��ʼ��ģ��2-------------------------------------------------------------------------------------------
    {
        FILE *fp1;
        fp1 = fopen("Students' scores.txt", "r");
        m = Read_m(fp1);//ѧ��������ʼ��
        rewind(fp1);
        n = Read_n(fp1);//�γ�������ʼ��
        fclose(fp1);
    }
//-------------------------------------------------------------
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            system("CLS");
            printf("����ϵͳ��");
        }
        for (int j = 0; j < 3; j++) {
            printf(".");
            usleep(43000);
        }
    }
    system("CLS");
    printf("����ϵͳ�ɹ�������");
    sleep(1);
    //----------------------------------------------------------------------------------------------
    int choice = 0;
    int menuSize = 12; // �˵��Ĵ�С
    char menu[12][100] = {
            "1. Append record             (��Ӽ�¼)                               ",
            "2. List record               (�鿴��¼)                               ",
            "3. Delete record             (ɾ����¼)                               ",
            "4. Modify record             (�޸ļ�¼)                               ",
            "5. Search record             (������¼)                               ",
            "6. Sort by sum               (���ܺ�����)                             ",
            "7. Sort by course            (���γ�����)                             ",
            "8. Sort by male and female students (��ѧ����Ů����)                  ",
            "9. Random sort               (�������)                               ",
            "W. Write to a File            (�ɰ��º�����ַ���Ŀ��ѧ���У��������)",
            "R. Read from a File                           (�ļ����в鿴�����ȫ��)",
            "0. Exit                      (�˳�)                                   ",
    }; // �˵�ѡ��

    while (1) {
        if (caozuo) {
            system("CLS");
            caozuo = 0;
        }
        if (m == 0) return 0;
        printf("\033[0;0H");
        printf(WHITE FG_BLACK"��ʾ:�Ѿ�����"RESET);
        printf(WHITE RED"%5d"RESET, caozuoshu);
        printf(WHITE FG_BLACK"��                                                    \n"RESET);
        {
            FILE *fp1;
            fp1 = fopen("Students' scores.txt", "r");
            m = Read_m(fp1);//ѧ��������ʼ��
            rewind(fp1);
            n = Read_n(fp1);//�γ�������ʼ��
            fclose(fp1);
            printf(WHITE FG_BLACK"��ʾ:���ļ����Ѿ���ȡѧ��"RESET);
            printf(WHITE RED"%5d"RESET, m);
            printf(WHITE FG_BLACK"�ˣ��γ�"RESET);
            printf(WHITE RED"%5d"RESET, n);
            printf(WHITE FG_BLACK"��                           \n"RESET);
        }

        int mid = 0;
        printf(BG_WHITE YELLOW"########################################################################\n"RESET);
        printf(BG_WHITE BLINK_1);
        printf("��ӭ����Management for Students' scoresϵͳ                             \n                                                            �汾�� V3.0 \n"RESET);
        printf(BG_WHITE   FG_BLACK "Management for Students' scores                           (ѧ���ɼ�����)\n"RESET);
        for (int i = 0; i < menuSize; i++) {
            if (choice == i) {
                printf(BG_WHITE BLINK_3 ">>");
                printf(BG_WHITE   BLINK_3"%s\n"RESET, menu[i]);
                mid = i;
            } else {
                printf(BG_WHITE"  ");
                if (i == 1) printf(FG_2);
                else if (i == 2)printf(FG_3);
                else if (i == 3)printf(FG_4);
                else if (i == 4)printf(FG_5);
                else if (i == 5)printf(FG_6);
                else if (i == 6)printf(FG_7);
                else if (i == 7)printf(FG_8);
                else if (i == 8)printf(FG_9);
                else if (i == 9)printf(FG_BLACK);
                else if (i == 10)printf(BLINK_1);
                else if (i == 11)printf(BLINK_2);
                else if (i == 0)printf(FG_1);
                printf("%s\n"RESET, menu[i]);
            }

        }
        printf(BG_WHITE YELLOW"########################################################################\n"RESET);
        printf(WHITE FG_BLACK"��ʾ:ѡ����                                                             \n"RESET);
        printf(WHITE RED"%s  "RESET, menu[mid]);
        char key = getch();
        switch (key) {
            case 13: // �س���
                system("cls");
                CHOICE(choice);
                caozuoshu++;
                getchar();
                getchar();
                break;
            case 72: // �ϼ�ͷ��
                choice = (choice - 1 + menuSize) % menuSize;
                break;
            case 80: // �¼�ͷ��
                choice = (choice + 1) % menuSize;
                break;
            default:
                // ������
                break;
        }
    }
}

//------------------------------------------------------------------------------------------------
void CHOICE(int ch) {
    switch (ch) {
        case 11: {
            for (int i = 0; i < 10; i++) {
                if (i % 2 == 0) {
                    system("CLS");
                    printf("�˳�������");
                }
                for (int j = 0; j < 3; j++) {
                    printf(".");
                    usleep(40000);
                }
            }
            system("CLS");
            printf("��ȫ�˳�����ɹ�������");
            sleep(1);
            exit(0);
            break;
        }
        case 0: {
            system("cls");
            printf(BG_WHITE   FG_1  "1.Append record                                             (��Ӽ�¼)\n"RESET);
            //---------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\nû��Ȩ��ʹ�ã�����\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "a");
                Append(fp);
                fclose(fp);
            }
            //---------------------------------------------
            printf("\n�س����κ�ˢ��");
            getchar();
            getchar();
            break;
        }
        case 1: {
            system("cls");
            printf(BG_WHITE   FG_2  "2.List record                                               (�鿴��¼)\n"RESET);
            FILE *fp;
            fp = fopen("Students' scores.txt", "r");
            //--------------------------
            Looking(fp);
            //------------------------------
            fclose(fp);
            int c;
            printf("\n�س����κ�ˢ��");
            while ((c = getchar()) != '\n' && c != EOF);
            break;
        }
        case 2: {
            system("cls");
            printf(BG_WHITE   FG_3  "3.Delete record                                             (ɾ����¼)\n"RESET);
            //-------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\nû��Ȩ��ʹ�ã�����\n"RESET);
            }
            if (userpower) {
                printf("0.ɾ�����м�¼\n�����������ͨģʽ\n");
                char aaa;
                scanf("%c", &aaa);
                getchar();
                switch (aaa) {
                    case '0': {
                        printf("ȷ����?Y/N\n");
                        char ch = getchar();
                        if (ch == 'Y') {
                            printf("�Ѿ�������м�¼������");
                            FILE *fp;
                            fp = fopen("Students' scores.txt", "w");
                            exit(0);
                            fclose(fp);
                        }
                        break;
                    }
                    default: {
                        FILE *fp;
                        fp = fopen("Students' scores.txt", "r");
                        Delete(fp);
                        fclose(fp);
                        break;
                    }
                }
            }
            //-------------------------------------------------

            int c;
            printf("\n�س����κ�ˢ��");
            while ((c = getchar()) != '\n' && c != EOF);
            break;
        }
        case 3: {
            system("cls");
            printf(BG_WHITE   FG_4  "4.Modify record                                             (�޸ļ�¼)\n"RESET);
            //-------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\nû��Ȩ��ʹ�ã�����\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                Modify(fp);
                fclose(fp);
            }
            //---------------------------------------------------------------------
            printf("\n�س����κ�ˢ��");
            getchar();
            getchar();
            break;
        }
        case 4: {
            system("cls");
            printf(BG_WHITE   FG_5  "5.Search record                                             (������¼)\n"RESET);
            FILE *fp;
            fp = fopen("Students' scores.txt", "r");
            Mearch(fp);
            fclose(fp);
            printf("\n�س����κ�ˢ��");
            getchar();
            getchar();
            break;
        }
        case 5: {
            system("cls");
            printf(BG_WHITE   FG_6  "6.Sort by sum                                             (���ܺ�����)\n"RESET);

            //-----------------------------------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\nû��Ȩ��ʹ�ã�����\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                printf("0.����\n1.����\n");
                char c = getchar();

                getchar();
                switch (c) {
                    case '0': {
                        printf(BG_WHITE   FG_6  "Sort in descending order by sum                       (���ܺͽ�������)\n"RESET);
                        Sort_Max_Min(fp);
                        break;
                    }
                    case '1': {
                        printf(BG_WHITE   FG_7  "Sort in ascending order by sum                        (���ܺ���������)\n"RESET);
                        Sort_Min_Max(fp);
                        break;
                    }
                    default: {
                        printf("��Ч�ַ�������\n");
                        break;
                    }
                }
                fclose(fp);
            }
            //-------------------------------------------------------------------------------
            printf("\n�س����κ�ˢ��");
            getchar();
            getchar();
            break;
        }
        case 6: {
            system("cls");

            printf(BG_WHITE   FG_7  "7.Sort by course                                          (���γ�����)\n"RESET);
            //------------------------------------------------------------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\nû��Ȩ��ʹ�ã�����\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                printf("0.�γ̽���\n1.�γ�����\n");

                char c = getchar();

                getchar();
                switch (c) {
                    case '0': {
                        printf(BG_WHITE   FG_8  "Sort in descending order by course                   (���γ̽�������)\n"RESET);
                        SortNum_Max_Min(fp);
                        break;
                    }
                    case '1': {
                        printf(BG_WHITE   FG_9  "Sort in ascending order by course                     (���γ���������)\n"RESET);
                        SortNum_Min_Max(fp);
                        break;
                    }
                    default: {
                        printf("��Ч�ַ�������\n");
                        break;
                    }
                }
                fclose(fp);
            }
            //-----------
            printf("\n�س����κ�ˢ��");
            getchar();
            getchar();
            break;
        }
        case 7: {
            system("cls");
            printf(BG_WHITE   FG_8  "8.Sort by male and female students                    (��ѧ����Ů����)\n"RESET);
            //--------------------------------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\nû��Ȩ��ʹ�ã�����\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                Sortbygender(fp);
                fclose(fp);
            }
            //-------------------------------------------
            printf("\n�س����κ�ˢ��");
            getchar();
            getchar();
            break;
        }
        case 8: {
            system("cls");
            printf(BG_WHITE   FG_9  "9.Random sort                                               (�������)\n"RESET);
            //--------------------------------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\nû��Ȩ��ʹ�ã�����\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                Randomsort(fp);
                fclose(fp);
            }
            //---------------------------------------
            printf("\n�س����κ�ˢ��");
            getchar();
            getchar();
            break;
        }
        case 9: {
            system("cls");
            printf(BG_WHITE BLINK_1 "W. Write to a File             (�ɰ��º�����ַ���Ŀ��ѧ���У��������)\n"RESET);

            //--------------------------------------------------------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\nû��Ȩ��ʹ�ã�����\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                Write_char(fp);
                fclose(fp);
            }
            //------------------------------------------------------------------------------------
            printf("\n�س����κ�ˢ��");
            getchar();
            getchar();
            break;
        }
        case 10: {
            printf(BG_WHITE BLINK_2 "R. Read from a File                           (�ļ����в鿴�����ȫ��)\n"RESET);
            //-------------------------------------------------------------------------------------------------------------
            FILE *fp;
            fp = fopen("Students' scores.txt", "r");
            Looking_all(fp);
            fclose(fp);
            //--------------------------------------------------------------------------------
            printf("\n�س����κ�ˢ��");
            getchar();
            getchar();
            break;
        }
        default: {
            printf("\n�س����κ�ˢ��");
            break;
        }
    }
    caozuo = 1;
}


void Inilial_Write(FILE *p) {
    {
        printf("���ȳ�ʼ������ѧ����Ϣ:\n");
        printf("������ѧ��������:\n");
        scanf("%d", &m);
        printf("�γ���Ŀ:\n");
        scanf("%d", &n);
        getchar();
    }
    for (int i = 1; i <= m; i++) {

        char name[30];
        char gender[10];
        char className[30];
        char num[30];

        printf("��%d��ѧ��\n\n", i);
        {

            printf("����:");
            scanf("%s", name);
            fprintf(p, "%s", name);
            fputc(' ', p);
        }
        {

            printf("�Ա�:");
            scanf("%s", gender);
            fprintf(p, "%s", gender);
            fputc(' ', p);
        }

        {
            printf("�༶:");
            scanf("%s", className);
            fprintf(p, "%s", className);
            fputc(' ', p);
        }

        {
            printf("ѧ��:");
            scanf("%s", num);
            fprintf(p, "%s", num);
            fputc('\n', p);
        }

        {
            for (int j = 1; j <= n; j++) {
                printf("�γ�%d:", j);
                scanf("%s", num);
                fprintf(p, "%s", num);
                if (j == n)
                    fputc('\n', p);
                else
                    putc(' ', p);
            }
        }
    }


}


void Append(FILE *p)//nΪ�γ�����
{
    int a = 0;
    printf("������Ҫ���뼸������:\n");
    scanf("%d", &a);
    int mid = m;
    m = m + a;
    for (int i = 1; i <= a; i++) {

        char name[30];
        char gender[10];
        char className[30];
        char num[30];
        printf("��%d��ѧ��\n\n", mid + i);
        {
            printf("����:");
            scanf("%s", name);
            fprintf(p, "%s", name);
            fputc(' ', p);
        }
        {

            printf("�Ա�:");
            scanf("%s", gender);
            fprintf(p, "%s", gender);
            fputc(' ', p);
        }

        {
            printf("�༶:");
            scanf("%s", className);
            fprintf(p, "%s", className);
            fputc(' ', p);
        }

        {
            printf("ѧ��:");
            scanf("%s", num);
            fprintf(p, "%s", num);
            fputc('\n', p);
        }

        {
            for (int j = 1; j <= n; j++) {
                printf("�γ�%d:", j);
                scanf("%s", num);
                fprintf(p, "%s", num);
                if (j == n)
                    fputc('\n', p);
                else
                    putc(' ', p);
            }
        }
    }


}

void Looking(FILE *fp) {
    char line[100];
    int i = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (i % 2 == 0) {
            printf("--------------------------------------------\n");
            printf("��%d��ѧ��:  ", i / 2 + 1);
        }

        printf("%s", line);
        i++;
    }
}

int Read_m(FILE *fp)//ѧ��������ʼ��
{
    int count = 0;
    char ch[100];
    while (fgets(ch, 100, fp) != NULL) {
        count++;
    }

    return count / 2;
}

int Read_n(FILE *fp) {
    char ch[100];
    int count = 0;
    fgets(ch, 100, fp);
    memset(ch, -1, sizeof(ch));
    fgets(ch, 100, fp);
    for (int i = 0; i < 100; i++) {
        if (ch[i] == ' ') {
            count++;
        }
    }
    return count + 1;
}


void Delete(FILE *fp) {
    //-------------------------------
    Stu *p_old;
    p_old = (Stu *) malloc(sizeof(Stu) * m);
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%s %s %s %s", p_old[i].name, p_old[i].gender, p_old[i].className, p_old[i].num);
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &p_old[i].grade[j]);
        }
    }
    printf("ѧ�������ܱ�:\n");
    for (int i = 0; i < m; i++) {
        printf("��%4d��ѧ��:%s\n", i + 1, p_old[i].name);
    }


    //-------------------------------
    printf("��������Ҫɾ��ѧ������:");
    int a = 0;
    scanf("%d", &a);
    char **p_delete = (char **) malloc(sizeof(char *) * 30 * a);
    for (int i = 0; i < a; i++) {
        p_delete[i] = (char *) malloc(sizeof(char) * 30);
        printf("������ɾ����%d��ѧ������:\n", i + 1);
        scanf("%s", p_delete[i]);
    }
    system("cls");
    for (int i = 0; i < a; i++) {
        printf("%10s----- ׼��ɾ����...\n", p_delete[i]);
    }

    Stu *p_new;
    p_new = (Stu *) malloc(sizeof(Stu) * (m));
    int k = 0;
//---------------------------------------------------------------------------------
    for (int i = 0; i < m; i++) {

        int mid = 1;
        for (int j = 0; j < a; j++) {
            if (strcmp(p_old[i].name, p_delete[j]) == 0) {
                mid = 0;
                break;
            }
        }

        if (mid == 1) {
            strcpy(p_new[k].name, p_old[i].name);
            strcpy(p_new[k].gender, p_old[i].gender);
            strcpy(p_new[k].className, p_old[i].className);
            strcpy(p_new[k].num, p_old[i].num);
            for (int s = 0; s < n; s++) {
                p_new[k].grade[s] = p_old[i].grade[s];
            }
            k++;
        }

    }

//---------------------------------------------------------------------------------
    printf("��ǰѧ���ܱ���Ϣ:\n");
    for (int i = 0; i < k; i++) {
        printf("%s\t%s\t%s\t%s\n", p_new[i].name, p_new[i].gender, p_new[i].className, p_new[i].num);
        for (int j = 0; j < n; j++) {
            printf("%d ", p_new[i].grade[j]);
        }
        printf("\n");
    }
//------------------------------------�ļ�д��------------------------------------------------
    FILE *fp1;
    fp1 = fopen("Students' scores.txt", "w");
    for (int i = 0; i < k; i++) {
        fprintf(fp1, "%s %s %s %s\n", p_new[i].name, p_new[i].gender, p_new[i].className, p_new[i].num);
        for (int j = 0; j < n; j++) {
            if (j != n - 1)
                fprintf(fp1, "%d ", p_new[i].grade[j]);
            else
                fprintf(fp1, "%d\n", p_new[i].grade[j]);
        }
    }
    fclose(fp1);
    free(p_delete);
    free(p_old);
    free(p_new);
    printf("\nɾ���ɹ�!");
//------------------------------------------------------------------------------------------
}


void Modify(FILE *fp) {
    //-------------------------------
    Stu *p_old;
    Stu *p_new;
    p_old = (Stu *) malloc(sizeof(Stu) * m);
    p_new = (Stu *) malloc(sizeof(Stu) * m);
    rewind(fp);
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%s %s %s %s", p_old[i].name, p_old[i].gender, p_old[i].className, p_old[i].num);
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &p_old[i].grade[j]);
        }
    }
    rewind(fp);
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%s %s %s %s", p_new[i].name, p_new[i].gender, p_new[i].className, p_new[i].num);
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &p_new[i].grade[j]);
        }
    }
    printf("��ǰѧ���ܱ���Ϣ:\n");
    for (int i = 0; i < m; i++) {
        printf("%s\t%s\t%s\t%s\n", p_new[i].name, p_new[i].gender, p_new[i].className, p_new[i].num);
        for (int j = 0; j < n; j++) {
            printf("%d ", p_new[i].grade[j]);
        }
        printf("\n");
    }
    //--------------------------------------------------------------------------------------------------
    printf("��������Ҫ�޸�ѧ������:\n");
    int a;
    scanf("%d", &a);

    for (int i = 0; i < a; i++) {
        char temp_name[30];
        int mid = 1;
        printf("�����%d��ѧ������:\n", i + 1);
        scanf("%s", temp_name);
        for (int j = 0; j < m; j++) {
            if (strcmp(temp_name, p_old[j].name) == 0) {
                mid = 0;
                strcpy(p_new[j].name, temp_name);
                printf("�ҵ���ѧ��������\n�������ѧ�����ĺ���Ϣ:\n");
                printf("ѧ��");
                printf("%s", p_new[j].name);
                printf("�޸���Ϣ\n");

                printf("�༶:\n");
                scanf("%s", p_new[j].className);
                printf("�Ա�:\n");
                scanf("%s", p_new[j].gender);
                printf("ѧ��:\n");
                scanf("%s", p_new[j].num);
                for (int u = 0; u < n; u++) {
                    printf("�γ�%d:\n", u + 1);
                    scanf("%d", &p_new[j].grade[u]);
                }
            }
        }
        if (mid) {
            printf("��Ч��ѧ����Ϣ����������:\n");
            getchar();
            i--;
        }
    }
    system("cls");
    printf("\033[5;31;1m��ǰѧ���ܱ���Ϣ��\n\033[0m");
    for (int i = 0; i < m; i++) {
        printf("��%d��ѧ��:", i + 1);
        printf("%s\t%s\t%s\t%s\t", p_new[i].name, p_new[i].gender, p_new[i].className, p_new[i].num);
        for (int j = 0; j < n; j++) {
            printf("%d\t", p_new[i].grade[j]);
        }
        printf("\n");
    }



//------------------------------------�ļ�д��------------------------------------------------

    FILE *fp1;
    fp1 = fopen("Students' scores.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(fp1, "%s %s %s %s\n", p_new[i].name, p_new[i].gender, p_new[i].className, p_new[i].num);
        for (int j = 0; j < n; j++) {
            if (j != n - 1)
                fprintf(fp1, "%d ", p_new[i].grade[j]);
            else
                fprintf(fp1, "%d\n", p_new[i].grade[j]);
        }
    }


    fclose(fp1);
    free(p_old);
    free(p_new);
    printf("\n�޸ĳɹ�!");
//------------------------------------------------------------------------------------------
}


void Mearch(FILE *fp) {
    //--------------------------------------------------------------------------------------------------
    Stu *p;
    p = (Stu *) malloc(sizeof(Stu) * m);
    rewind(fp);
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &p[i].grade[j]);
        }
    }
    //--------------------------------------------------------------------------------------------------
    printf("0.�˳�\n");
    printf("1.���༶����\n");
    printf("2.���ɼ�����\n");
    printf("3.��ѧ�Ų���\n");
    printf("~�������������~\n");
    char ch;
    scanf("%c", &ch);

    //-------------------------------------------------------------
    switch (ch) {
        case '0': {
            system("cls");
            printf("�˳��ɹ�������");
            break;
        }
        case '1': {
            system("cls");
            Mearch_class(p);
            break;
        }

        case '2': {
            system("cls");
            Mearch_grade(p);
            break;
        }
        case '3': {
            system("cls");
            Mearch_num(p);
            break;
        }
        default: {
            system("cls");
            Mearch_name(p);
            break;
        }
    }
    free(p);
}

void Mearch_num(Stu *p) {
    printf("��������Ҫ���ҵ�ѧ��ѧ��:\n");
    char Num[30];
    scanf("%s", Num);
    int mid = 1;
    for (int i = 0; i < m; i++) {
        if (strcmp(Num, p[i].num) == 0) {
            printf("-------------------------------------------------------\n");
            printf("----------����:%s----------- \n�༶:%s �Ա�%s ѧ��%s \n�ɼ�:\n", p[i].name, p[i].className,
                   p[i].gender, p[i].num);
            int sum = 0;
            int max = p[i].grade[0];
            int min = p[i].grade[0];
            for (int j = 0; j < n; j++) {
                printf("�γ�%d:%d\n", j + 1, p[i].grade[j]);
                if (max < p[i].grade[j]) {
                    max = p[i].grade[j];
                }
                if (min > p[i].grade[j]) {
                    min = p[i].grade[j];
                }
                sum += p[i].grade[j];
            }
            double average = sum / n;
            printf("��߷�:%d\n", max);
            printf("��ͷ�:%d\n", min);
            printf("ƽ��ֵ:%f\n", average);
            printf("�ܳɼ�:%d\n", sum);
            mid = 0;
        }
    }
    if (mid) {
        printf("δ�ҵ�ѧ��ѧ����Ϣ!!!\n");
    }

}

void Mearch_grade(Stu *p) {

    printf("��������Ҫ���ҵĿγ�:\n");
    printf("���пγ�:");

    for (int i = 0; i < n; i++) {
        printf("�γ�%d ", i + 1);
    }
    printf("\n��ѡ��γ�:");
    int x;
    int up = 0, low = 0;
    scanf("%d", &x);
    x = x - 1;
    printf("\n��ѡ��γ̲�������:\n");
    printf("���ֵ:\n");
    scanf("%d", &up);
    printf("��Сֵ:\n");
    scanf("%d", &low);
    if (up < low) {
        int temp = low;
        low = up;
        up = temp;
        printf("���ֵ�������ֵ���Ѿ�����\n");
    }
    int mid = 1;
    for (int i = 0; i < m; i++) {
        if (p[i].grade[x] > low && p[i].grade[x] < up) {
            printf("�γ�%d  �ɼ�:%d\t", x + 1, p[i].grade[x]);
            printf("      ����:%s\t�Ա�%s\t�༶:%s\tѧ��%s\n", p[i].name, p[i].gender, p[i].className, p[i].num);
            mid = 0;
        }
    }
    if (mid) {
        printf("δ�ҵ��γ���Ϣ!!!\n");
    }
}

void Mearch_name(Stu *p) {
    printf("��������Ҫ���ҵ�ѧ������:\n");
    char Stu_name[30];
    scanf("%s", Stu_name);
    int mid = 1;
    for (int i = 0; i < m; i++) {
        if (strcmp(Stu_name, p[i].name) == 0) {
            printf("-----------------------------------------\n");
            printf("----------����:%s----------- \n�༶:%s �Ա�%s ѧ��%s \n�ɼ�:\n", p[i].name, p[i].className,
                   p[i].gender, p[i].num);
            int sum = 0;
            int max = p[i].grade[0];
            int min = p[i].grade[0];
            for (int j = 0; j < n; j++) {
                printf("�γ�%d:%d\n", j + 1, p[i].grade[j]);
                if (max < p[i].grade[j]) {
                    max = p[i].grade[j];
                }
                if (min > p[i].grade[j]) {
                    min = p[i].grade[j];
                }
                sum += p[i].grade[j];
            }
            double average = sum / n;
            printf("��߷�:%d\n", max);
            printf("��ͷ�:%d\n", min);
            printf("ƽ��ֵ:%f\n", average);
            printf("�ܳɼ�:%d\n", sum);
            mid = 0;
        }
    }
    if (mid) {
        printf("δ�ҵ�ѧ����Ϣ!!!\n");
    }
}


void Mearch_class(Stu *p) {
    printf("��������Ҫ���ҵİ༶:\n");
    char classname[30];
    scanf("%s", classname);
    int mid = 1;
    for (int i = 0; i < m; i++) {
        if (strcmp(classname, p[i].className) == 0) {
            printf("-----------------------------------------\n");
            printf("----------����:%s----------- \n�༶:%s �Ա�:%s ѧ��%s \n�ɼ�:\n", p[i].name, p[i].className,
                   p[i].gender, p[i].num);
            int sum = 0;
            int max = p[i].grade[0];
            int min = p[i].grade[0];
            for (int j = 0; j < n; j++) {
                printf("�γ�%d:%d\n", j + 1, p[i].grade[j]);
                if (max < p[i].grade[j]) {
                    max = p[i].grade[j];
                }
                if (min > p[i].grade[j]) {
                    min = p[i].grade[j];
                }
                sum += p[i].grade[j];
            }
            double average = sum / n;
            printf("��߷�:%d\n", max);
            printf("��ͷ�:%d\n", min);
            printf("ƽ��ֵ:%f\n", average);
            printf("�ܳɼ�:%d\n", sum);
            mid = 0;
        }
    }
    if (mid) {
        printf("δ�ҵ��༶��Ϣ!!!\n");
    }
}


void Sort_Max_Min(FILE *fp) {
    printf("�Ƿ�����Y/N\n");
    char ch;
    if (ch = getchar() == 'Y') {

        Stu *p;
        p = (Stu *) malloc(sizeof(Stu) * m);
        rewind(fp);
        for (int i = 0; i < m; i++) {
            fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
            p[i].sum = 0;
            for (int j = 0; j < n; j++) {
                fscanf(fp, "%d", &p[i].grade[j]);
                p[i].sum += p[i].grade[j];
            }
        }


        for (int i = 0; i < m; i++) {
            int max = i;
            for (int j = i + 1; j < m; j++) {
                if (p[max].sum < p[j].sum) {
                    max = j;
                }
            }
            {
                Stu temp = p[i];
                p[i] = p[max];
                p[max] = temp;
            }
        }

        PRINTF(p);

//------------------------------------�ļ�д��------------------------------------------------
        FILE *fp1;
        fp1 = fopen("Students' scores.txt", "w");
        for (int i = 0; i < m; i++) {
            fprintf(fp1, "%s %s %s %s\n", p[i].name, p[i].gender, p[i].className, p[i].num);
            for (int j = 0; j < n; j++) {
                if (j != n - 1)
                    fprintf(fp1, "%d ", p[i].grade[j]);
                else
                    fprintf(fp1, "%d\n", p[i].grade[j]);
            }
        }
        fclose(fp1);
        free(p);
    }
//------------------------------------�ļ�д��------------------------------------------------

}

void Sort_Min_Max(FILE *fp) {
    printf("�Ƿ�����Y/N\n");
    char ch;
    if (ch = getchar() == 'Y') {

        Stu *p;
        p = (Stu *) malloc(sizeof(Stu) * m);
        rewind(fp);
        for (int i = 0; i < m; i++) {
            fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
            p[i].sum = 0;
            for (int j = 0; j < n; j++) {
                fscanf(fp, "%d", &p[i].grade[j]);
                p[i].sum += p[i].grade[j];
            }
        }


        for (int i = 0; i < m; i++) {
            int min = i;
            for (int j = i + 1; j < m; j++) {
                if (p[min].sum > p[j].sum) {
                    min = j;
                }
            }

            {
                Stu temp = p[i];
                p[i] = p[min];
                p[min] = temp;
            }
        }

        PRINTF(p);

//------------------------------------�ļ�д��------------------------------------------------
        FILE *fp1;
        fp1 = fopen("Students' scores.txt", "w");
        for (int i = 0; i < m; i++) {
            fprintf(fp1, "%s %s %s %s\n", p[i].name, p[i].gender, p[i].className, p[i].num);
            for (int j = 0; j < n; j++) {
                if (j != n - 1)
                    fprintf(fp1, "%d ", p[i].grade[j]);
                else
                    fprintf(fp1, "%d\n", p[i].grade[j]);
            }
        }
        fclose(fp1);
        free(p);
    }

//------------------------------------�ļ�д��------------------------------------------------
}


void SortNum_Min_Max(FILE *fp) {
    printf("�Ƿ�����Y/N\n");
    char ch;
    if (ch = getchar() == 'Y') {
        printf("������������ſ�����:\n");
        for (int k = 0; k < n; k++) {
            printf("�γ�%d ", k + 1);
        }
        printf("\n");
//------------------------------------------------------------
        int num;
        scanf("%d", &num);
        num = num - 1;


        Stu *p;
        p = (Stu *) malloc(sizeof(Stu) * m);
        rewind(fp);
        for (int i = 0; i < m; i++) {
            fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
            for (int j = 0; j < n; j++) {
                fscanf(fp, "%d", &p[i].grade[j]);
            }
        }

        for (int i = 0; i < m; i++) {
            int min = i;
            for (int j = i + 1; j < m; j++) {
                if (p[min].grade[num] > p[j].grade[num]) {
                    min = j;
                }
            }

            {
                Stu temp = p[i];
                p[i] = p[min];
                p[min] = temp;
            }
        }
        PRINTF(p);

//------------------------------------�ļ�д��------------------------------------------------
        FILE *fp1;
        fp1 = fopen("Students' scores.txt", "w");
        for (int i = 0; i < m; i++) {
            fprintf(fp1, "%s %s %s %s\n", p[i].name, p[i].gender, p[i].className, p[i].num);
            for (int j = 0; j < n; j++) {
                if (j != n - 1)
                    fprintf(fp1, "%d ", p[i].grade[j]);
                else
                    fprintf(fp1, "%d\n", p[i].grade[j]);
            }
        }
        fclose(fp1);
        free(p);
    }

//------------------------------------�ļ�д��------------------------------------------------

}


void SortNum_Max_Min(FILE *fp) {
    printf("�Ƿ�����Y/N\n");
    char ch;
    if (ch = getchar() == 'Y') {
        printf("������������ſ�����:\n");
        for (int k = 0; k < n; k++) {
            printf("�γ�%d ", k + 1);
        }
        printf("\n");
//------------------------------------------------------------
        int num;
        scanf("%d", &num);
        num = num - 1;


        Stu *p;
        p = (Stu *) malloc(sizeof(Stu) * m);
        rewind(fp);
        for (int i = 0; i < m; i++) {
            fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
            for (int j = 0; j < n; j++) {
                fscanf(fp, "%d", &p[i].grade[j]);
            }
        }

        for (int i = 0; i < m; i++) {
            int max = i;
            for (int j = i + 1; j < m; j++) {
                if (p[max].grade[num] < p[j].grade[num]) {
                    max = j;
                }
            }

            {
                Stu temp = p[i];
                p[i] = p[max];
                p[max] = temp;
            }
        }

        PRINTF(p);
//------------------------------------�ļ�д��------------------------------------------------
        FILE *fp1;
        fp1 = fopen("Students' scores.txt", "w");
        for (int i = 0; i < m; i++) {
            fprintf(fp1, "%s %s %s %s\n", p[i].name, p[i].gender, p[i].className, p[i].num);
            for (int j = 0; j < n; j++) {
                if (j != n - 1)
                    fprintf(fp1, "%d ", p[i].grade[j]);
                else
                    fprintf(fp1, "%d\n", p[i].grade[j]);
            }
        }
        fclose(fp1);
        free(p);
    }

//------------------------------------�ļ�д��------------------------------------------------

}


void Write_char(FILE *fp) {
    Stu *p;
    p = (Stu *) malloc(sizeof(Stu) * m);
    rewind(fp);
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &p[i].grade[j]);
        }
    }

    //------------------------------------------------------------
    while (1) {
        printf("������ѧ������(����ΪEXIT�˳�������):\n");
        char stn[30];
        scanf("%s", stn);
        getchar();
        if (strcmp("EXIT", stn) == 0) {
            printf("�˳��ɹ���\n");
            break;
        }

        printf("�����ַ�(1)����ɾ���ַ�(0):\n");
        char c;
        scanf("%c", &c);
        getchar();
        switch (c) {
            case '1': {
                {
                    printf("\n�����������ʲô�ַ���ѧ�����ֺ���(�������볬�������ַ�)\n");
                    char ch[3];
                    scanf("%s", ch);
                    int mid = 1;
                    for (int i = 0; i < m; i++) {
                        if (strcmp(stn, p[i].name) == 0) {
                            printf("�Ѿ������ַ���%s\n", p[i].name);
                            strcat(p[i].name, ch);
                            mid = 0;
                        }
                    }
                    if (mid) printf("ѧ��δ�ҵ���\n");
                }
                break;
            }
            case '0': {

                {
                    printf("\n��������ɾ��ʲô�ַ���ѧ�����ֺ���(�������볬�������ַ�)\n");
                    char sub[3];
                    scanf("%s", sub);
                    int mid = 1;
                    for (int i = 0; i < m; i++) {
                        if (strcmp(stn, p[i].name) == 0) {
                            printf("�Ѿ�ɾ���ַ���%s\n", p[i].name);


                            int len = strlen(sub);
                            char *match;
                            while ((match = strstr(p[i].name, sub))) {
                                memmove(match, match + len, strlen(match + len) + 1);
                            }
                            mid = 0;
                        }
                    }
                    if (mid) printf("ѧ��δ�ҵ���\n");
                }

                break;
            }
            default: {
                printf("��Ч�ַ���\n");
                break;
            }
        }

    }
    //----------------------------------------------------------------------------------

    PRINTF(p);
//------------------------------------�ļ�д��------------------------------------------------
    FILE *fp1;
    fp1 = fopen("Students' scores.txt", "w");
    for (int i = 0; i < m; i++) {
        fprintf(fp1, "%s %s %s %s\n", p[i].name, p[i].gender, p[i].className, p[i].num);
        for (int j = 0; j < n; j++) {
            if (j != n - 1)
                fprintf(fp1, "%d ", p[i].grade[j]);
            else
                fprintf(fp1, "%d\n", p[i].grade[j]);
        }
    }
    fclose(fp1);
    free(p);
    //-----------------------------------------------------------------
}


void Looking_all(FILE *fp) {
    Stu *p;
    p = (Stu *) malloc(sizeof(Stu) * m);
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &p[i].grade[j]);
        }
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------------
    PRINT_ALL(p);

    //----------------------------------------------------------------------------------------------------------------------------------
    free(p);
}


void Sortbygender(FILE *fp) {
    printf("�Ƿ�����Ů������Y/N\n");
    char ch;
    if (ch = getchar() == 'Y') {

        Stu *p;
        p = (Stu *) malloc(sizeof(Stu) * m);
        rewind(fp);
        for (int i = 0; i < m; i++) {
            fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
            p[i].sum = 0;
            for (int j = 0; j < n; j++) {
                fscanf(fp, "%d", &p[i].grade[j]);
                p[i].sum += p[i].grade[j];
            }
        }

        char sex[10] = {"��"};


        for (int i = 0; i < m; i++) {

            if (strcmp(sex, p[i].gender) != 0) {
                for (int j = i + 1; j < m; j++) {
                    if (strcmp(sex, p[j].gender) == 0) {
                        {
                            Stu temp = p[i];
                            p[i] = p[j];
                            p[j] = temp;
                        }
                        break;
                    }
                }
            }


        }
//-------------------------------------------------------------------------------------------------------
        PRINTF(p);

//------------------------------------�ļ�д��------------------------------------------------
        FILE *fp1;
        fp1 = fopen("Students' scores.txt", "w");
        for (int i = 0; i < m; i++) {
            fprintf(fp1, "%s %s %s %s\n", p[i].name, p[i].gender, p[i].className, p[i].num);
            for (int j = 0; j < n; j++) {
                if (j != n - 1)
                    fprintf(fp1, "%d ", p[i].grade[j]);
                else
                    fprintf(fp1, "%d\n", p[i].grade[j]);
            }
        }
        fclose(fp1);
        free(p);

    }
//------------------------------------�ļ�д��------------------------------------------------

}


//-----------####################################################################################
void Randomsort(FILE *fp) {
    //-------------------------------------------------------------
    printf("��ѡ��ģʽ\n1.˳������\n2.�������\n3.����ϵͳ\n~~~~~~~~~~~~~~~~\n��ѡ��:");
    char moshi;
    scanf("%d", &moshi);
    getchar();
    switch (moshi) {
        case 1: {
            system("CLS");
            Stu *p;
            p = (Stu *) malloc(sizeof(Stu) * m);
            rewind(fp);
            for (int i = 0; i < m; i++) {
                fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
                p[i].sum = 0;
                for (int j = 0; j < n; j++) {
                    fscanf(fp, "%d", &p[i].grade[j]);
                    p[i].sum += p[i].grade[j];
                }
            }
            moshi1(p);
            free(p);
            break;
        }
        case 2: {
            system("CLS");
            Stu *p;
            p = (Stu *) malloc(sizeof(Stu) * m);
            rewind(fp);
            for (int i = 0; i < m; i++) {
                fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
                p[i].sum = 0;
                for (int j = 0; j < n; j++) {
                    fscanf(fp, "%d", &p[i].grade[j]);
                    p[i].sum += p[i].grade[j];
                }
            }
            moshi2(p);
            free(p);
            break;
        }
        case 3: {
            system("CLS");
            Stu *p;
            p = (Stu *) malloc(sizeof(Stu) * m);
            rewind(fp);
            for (int i = 0; i < m; i++) {
                fscanf(fp, "%s %s %s %s", p[i].name, p[i].gender, p[i].className, p[i].num);
                p[i].sum = 0;
                for (int j = 0; j < n; j++) {
                    fscanf(fp, "%d", &p[i].grade[j]);
                    p[i].sum += p[i].grade[j];
                }
            }
            moshi3(p);
            free(p);
            break;
        }
        default : {
            system("CLS");
            printf("��Ч�ַ������˳�������\n");
        }
    }
}

//##########################################################################################################
void moshi1(Stu *p) {

    printf("�����������õ�һ��ѧ������ţ�����˳���ӡ,�������볬��8λ������\n");
    long long int xuhao = 0;
    scanf("%lld", &xuhao);
    getchar();
    //---------------------------------------------------------
    srand(time(NULL));
    // �����һ��Ԫ�ؿ�ʼ����������λ�õ�Ԫ�ؽ���
    for (int i = m - 1; i > 0; i--) {
        // �����������
        int j = rand() % (i + 1);
        // ����λ��
        Stu temp = p[i];
        p[i] = p[j];
        p[j] = temp;
    }
    printf(FG_1"��ǰѧ���ܱ���Ϣ��\n"RESET);
    for (int i = 0; i < m; i++) {
        if (strcmp("��", p[i].gender) == 0) {
            printf("���:%lld:", xuhao + i);
            printf(FG_1 "%10s %6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
            printf("\n");
        } else {
            printf("���:%lld:", xuhao + i);
            printf(FG_5 "%10s %6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
            printf("\n");
        }
    }
    FILE *fp1;
    fp1 = fopen("ѧ������.txt", "w");
    for (int i = 0; i < m; i++) {
        fprintf(fp1, "��ţ�%lld\t ������%10s �Ա�%6s �༶%10s ѧ��%10s\n", xuhao + i, p[i].name, p[i].gender,
                p[i].className, p[i].num);
    }
    fclose(fp1);
    printf("\n~~~~~~~~~~~\n�ļ�����ɹ�����\n");
}

//############################################################################
void moshi2(Stu *p) {
    FILE *fp1;
    fp1 = fopen("ѧ������.txt", "w");
    printf("�������봴������ų���\n");
    int k = 0;
    scanf("%d", &k);
    getchar();
    srand(time(NULL));
    printf(FG_1"��ǰѧ���ܱ���Ϣ��\n"RESET);
    for (int i = 0; i < m; i++) {

        fprintf(fp1, "���:");
        printf("���:");
        for (int j = 0; j < k; j++) {
            int x = rand() % 10;
            fprintf(fp1, "%d", x);
            printf("%d", x);
        }
        printf(FG_1 " %10s\t%6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
        printf("\n");
        fprintf(fp1, " ������%10s\t��ϸ��Ϣ:�Ա�%6s �༶��%10s ѧ�ţ�%10s\n", p[i].name, p[i].gender, p[i].className,
                p[i].num);
    }
    printf("\n~~~~~~~~~~~\n�ļ�����ɹ�����\n");
    fclose(fp1);
}

//####################################################################################
void moshi3(Stu *p) {
    printf("����������Ҫ����ѧ��\n");
    int a = 0;
    scanf("%d", &a);
    getchar();
    srand(time(NULL));

    for (int i = 0; i < m; i++) {
        {
            if (strcmp("��", p[i].gender) == 0) {
                printf("������....\n");
                printf(FG_1 "%10s %6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
                printf("\n");
            } else {
                printf("������....\n");
                printf(FG_5 "%10s %6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
                printf("\n");
            }
        }
        usleep(50000);
        if (i % 10 == 0) system("CLS");
    }
    system("CLS");
    int *q;
    q = (int *) malloc(sizeof(int) * a);
    int i = 0;

    while (i != a) {
        int x;
        q[i] = -1;
        x = rand() % m;
        int mid = 1;
        for (int j = i - 1; j >= 0; j--) {
            if (x == q[j]) {
                mid = 0;
            }
        }
        if (mid) {
            q[i] = x;
            i++;
        }
    }

    for (int i = 0; i < a; i++) {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n��������,��%d�����˶�:%s\n", i + 1, p[q[i]].name);
    }
}

//###########################################################################
void PRINTF(Stu *p) {
    printf(FG_1"��ǰѧ���ܱ���Ϣ��\n"RESET);
    for (int i = 0; i < m; i++) {

        if (strcmp("��", p[i].gender)) {
            printf("��%4d��ѧ��:", i + 1);
            printf(FG_1 "%10s %6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
            for (int j = 0; j < n; j++) {
                printf(FG_1 "%d\t"RESET, p[i].grade[j]);
            }
            printf("\n");
        } else {
            printf("��%4d��ѧ��:", i + 1);
            printf(FG_5 "%10s %6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
            for (int j = 0; j < n; j++) {
                printf(FG_5 "%d\t"RESET, p[i].grade[j]);
            }
            printf("\n");
        }
    }

}


void PRINT_ALL(Stu *p) {
    for (int i = 0; i < m; i++) {
        printf("*----------����:%10s----------------* \n�༶:%s �Ա�:%s ѧ��%s \n�ɼ�:\n", p[i].name, p[i].className,
               p[i].gender, p[i].num);
        int sum = 0;
        int max = p[i].grade[0];
        int min = p[i].grade[0];
        printf(FG_8 BG_WHITE"_________________________    "RESET);
        printf("\n");
        for (int j = 0; j < n; j++) {
            printf(FG_8 BG_WHITE"|�γ�%4d:%5d             |"RESET, j + 1, p[i].grade[j]);
            printf("\n");
            if (max < p[i].grade[j]) {
                max = p[i].grade[j];
            }
            if (min > p[i].grade[j]) {
                min = p[i].grade[j];
            }
            sum += p[i].grade[j];
        }
        printf(FG_8 BG_WHITE"-------------------------    "RESET);
        printf("\n");
        double average = sum / n;
        printf(FG_5 "��߷�:%d\n"RESET, max);
        printf(FG_1 "��ͷ�:%d\n"RESET, min);
        printf(FG_2 "ƽ��ֵ:%.2f\n"RESET, average);
        printf(FG_3 "�ܳɼ�:%d\n"RESET, sum);

    }

}

