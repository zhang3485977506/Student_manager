#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
//-------------------------------------------------------------------------------------------------------------
#define FG_BLACK          "\033[30m"    //黑色
#define FG_1  "\033[38;2;246;129;10m"   // 金黄色
#define FG_2  "\033[38;2;243;100;13m"   // 深金黄色
#define FG_3  "\033[38;2;219;88;31m"    // 橙黄色
#define FG_4  "\033[38;2;195;76;49m"    // 浅橙色
#define FG_5  "\033[38;2;171;63;67m"    // 橙红色
#define FG_6  "\033[38;2;0;90;0m"       // 更深的绿色
#define FG_7  "\033[38;2;0;80;0m"       // 极深的绿色
#define FG_8  "\033[38;2;0;64;0m"       // 十分深绿的颜色
#define FG_9  "\033[38;2;0;51;0m"       // 最深的绿色
#define YELLOW "\033[38;2;255;255;0m"
#define BG_WHITE   "\033[48;2;255;255;255m"
#define RESET      "\033[0m"
#define WHITE   "\033[47m"
#define BLINK_1 "\033[38;2;255;69;0m\033[5m"      // 橙红色闪烁
#define BLINK_2 "\033[38;2;255;0;0m\033[5m"       // 红色闪烁
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

int Read_m(FILE *fp);//学生数量初始化
int Read_n(FILE *fp); //课程数量初始化
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
        printf("请输入用户名:");
        scanf("%s", USERNAME);
        getchar();
        printf("----------------------\n");
        printf("请输入密码:");
        scanf("%s", USERNUM);
        getchar();
        if (strcmp(USERNAME, "张应胜") == 0 && strcmp(USERNUM, "zhangyingsheng") == 0) {
            FILE *user;
            user = fopen("User.txt", "a");
            system("CLS");
            printf("--------------------------------\n");
            printf("你好,管理者\n请输入增加的用户名和密码:\n");
            char aaa[100];
            char bbb[100];
            scanf("%s %s", aaa, bbb);
            getchar();
            fprintf(user, "%s %s\n", aaa, bbb);
            userpower = 1;
            k = 11;
            system("CLS");
            printf("密码正确\n~~~~~~~~~~欢迎~~~~~~~~~~\n");
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
                    printf("~~~~~~~~~~~~~~~~\n用户名或密码有误！！！\n");
                } else {
                    userpower = 1;
                    k = 11;
                    printf("密码正确\n~~~~~~~~~~欢迎~~~~~~~~~~\n");
                    sleep(1);
                }
            }


        }
        if (k == 3) {
            system("CLS");
            printf("\n输入用户名和密码错误3次,可退出,获得查看权限或继续输入,最多输错10次!!!\n");
            printf("1.退出\n");
            printf("2.继续输入,最多输错10次!!!\n");
            printf("3.获得查看权限(默认)\n");
            printf("~~~~~~~~~~~~~~~~\n");
            printf("请选择:\n");
            int choice = 0;
            scanf("%d", &choice);
            getchar();
            switch (choice) {
                case 1: {
                    printf("退出\n");
                    return 0;
                    break;
                }
                case 2: {
                    printf("继续输入,最多输错10次!!!\n");
                    k = 4;
                    break;
                }
                case 3: {
                    printf("######################\n已经获得查看权限(默认)\n");
                    getchar();
                    k = 11;
                    userpower = 0;
                    break;
                }
                default: {
                    printf("######################\n已经获得查看权限(默认)\n");
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
    //初始化模块1------------------------------------------------------------------------------------------------------
    FILE *fp;
    fp = fopen("Students' scores.txt", "a");
    fseek(fp, 0L, SEEK_END);// 移动指针到末尾
    if (ftell(fp) == 0)//如果为0，初始化
    {
        Inilial_Write(fp);
        fclose(fp);
        printf(BG_WHITE BLINK_1"欢迎进入Management for Students' scores系统\n"RESET);
    } else
        //初始化模块2-------------------------------------------------------------------------------------------
    {
        FILE *fp1;
        fp1 = fopen("Students' scores.txt", "r");
        m = Read_m(fp1);//学生数量初始化
        rewind(fp1);
        n = Read_n(fp1);//课程数量初始化
        fclose(fp1);
    }
//-------------------------------------------------------------
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            system("CLS");
            printf("进入系统中");
        }
        for (int j = 0; j < 3; j++) {
            printf(".");
            usleep(43000);
        }
    }
    system("CLS");
    printf("进入系统成功！！！");
    sleep(1);
    //----------------------------------------------------------------------------------------------
    int choice = 0;
    int menuSize = 12; // 菜单的大小
    char menu[12][100] = {
            "1. Append record             (添加记录)                               ",
            "2. List record               (查看记录)                               ",
            "3. Delete record             (删除记录)                               ",
            "4. Modify record             (修改记录)                               ",
            "5. Search record             (搜索记录)                               ",
            "6. Sort by sum               (按总和排序)                             ",
            "7. Sort by course            (按课程排序)                             ",
            "8. Sort by male and female students (按学生男女排序)                  ",
            "9. Random sort               (随机排序)                               ",
            "W. Write to a File            (可按下后添加字符在目标学生中，方便查找)",
            "R. Read from a File                           (文件进行查看，快捷全部)",
            "0. Exit                      (退出)                                   ",
    }; // 菜单选项

    while (1) {
        if (caozuo) {
            system("CLS");
            caozuo = 0;
        }
        if (m == 0) return 0;
        printf("\033[0;0H");
        printf(WHITE FG_BLACK"提示:已经操作"RESET);
        printf(WHITE RED"%5d"RESET, caozuoshu);
        printf(WHITE FG_BLACK"次                                                    \n"RESET);
        {
            FILE *fp1;
            fp1 = fopen("Students' scores.txt", "r");
            m = Read_m(fp1);//学生数量初始化
            rewind(fp1);
            n = Read_n(fp1);//课程数量初始化
            fclose(fp1);
            printf(WHITE FG_BLACK"提示:从文件中已经读取学生"RESET);
            printf(WHITE RED"%5d"RESET, m);
            printf(WHITE FG_BLACK"人，课程"RESET);
            printf(WHITE RED"%5d"RESET, n);
            printf(WHITE FG_BLACK"门                           \n"RESET);
        }

        int mid = 0;
        printf(BG_WHITE YELLOW"########################################################################\n"RESET);
        printf(BG_WHITE BLINK_1);
        printf("欢迎进入Management for Students' scores系统                             \n                                                            版本号 V3.0 \n"RESET);
        printf(BG_WHITE   FG_BLACK "Management for Students' scores                           (学生成绩管理)\n"RESET);
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
        printf(WHITE FG_BLACK"提示:选择了                                                             \n"RESET);
        printf(WHITE RED"%s  "RESET, menu[mid]);
        char key = getch();
        switch (key) {
            case 13: // 回车键
                system("cls");
                CHOICE(choice);
                caozuoshu++;
                getchar();
                getchar();
                break;
            case 72: // 上箭头键
                choice = (choice - 1 + menuSize) % menuSize;
                break;
            case 80: // 下箭头键
                choice = (choice + 1) % menuSize;
                break;
            default:
                // 其他键
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
                    printf("退出程序中");
                }
                for (int j = 0; j < 3; j++) {
                    printf(".");
                    usleep(40000);
                }
            }
            system("CLS");
            printf("安全退出程序成功！！！");
            sleep(1);
            exit(0);
            break;
        }
        case 0: {
            system("cls");
            printf(BG_WHITE   FG_1  "1.Append record                                             (添加记录)\n"RESET);
            //---------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\n没有权限使用！！！\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "a");
                Append(fp);
                fclose(fp);
            }
            //---------------------------------------------
            printf("\n回车三次后刷新");
            getchar();
            getchar();
            break;
        }
        case 1: {
            system("cls");
            printf(BG_WHITE   FG_2  "2.List record                                               (查看记录)\n"RESET);
            FILE *fp;
            fp = fopen("Students' scores.txt", "r");
            //--------------------------
            Looking(fp);
            //------------------------------
            fclose(fp);
            int c;
            printf("\n回车三次后刷新");
            while ((c = getchar()) != '\n' && c != EOF);
            break;
        }
        case 2: {
            system("cls");
            printf(BG_WHITE   FG_3  "3.Delete record                                             (删除记录)\n"RESET);
            //-------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\n没有权限使用！！！\n"RESET);
            }
            if (userpower) {
                printf("0.删除所有记录\n任意键进入普通模式\n");
                char aaa;
                scanf("%c", &aaa);
                getchar();
                switch (aaa) {
                    case '0': {
                        printf("确定吗?Y/N\n");
                        char ch = getchar();
                        if (ch == 'Y') {
                            printf("已经清除所有记录！！！");
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
            printf("\n回车俩次后刷新");
            while ((c = getchar()) != '\n' && c != EOF);
            break;
        }
        case 3: {
            system("cls");
            printf(BG_WHITE   FG_4  "4.Modify record                                             (修改记录)\n"RESET);
            //-------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\n没有权限使用！！！\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                Modify(fp);
                fclose(fp);
            }
            //---------------------------------------------------------------------
            printf("\n回车三次后刷新");
            getchar();
            getchar();
            break;
        }
        case 4: {
            system("cls");
            printf(BG_WHITE   FG_5  "5.Search record                                             (搜索记录)\n"RESET);
            FILE *fp;
            fp = fopen("Students' scores.txt", "r");
            Mearch(fp);
            fclose(fp);
            printf("\n回车三次后刷新");
            getchar();
            getchar();
            break;
        }
        case 5: {
            system("cls");
            printf(BG_WHITE   FG_6  "6.Sort by sum                                             (按总和排序)\n"RESET);

            //-----------------------------------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\n没有权限使用！！！\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                printf("0.降序\n1.升序\n");
                char c = getchar();

                getchar();
                switch (c) {
                    case '0': {
                        printf(BG_WHITE   FG_6  "Sort in descending order by sum                       (按总和降序排序)\n"RESET);
                        Sort_Max_Min(fp);
                        break;
                    }
                    case '1': {
                        printf(BG_WHITE   FG_7  "Sort in ascending order by sum                        (按总和升序排序)\n"RESET);
                        Sort_Min_Max(fp);
                        break;
                    }
                    default: {
                        printf("无效字符！！！\n");
                        break;
                    }
                }
                fclose(fp);
            }
            //-------------------------------------------------------------------------------
            printf("\n回车三次后刷新");
            getchar();
            getchar();
            break;
        }
        case 6: {
            system("cls");

            printf(BG_WHITE   FG_7  "7.Sort by course                                          (按课程排序)\n"RESET);
            //------------------------------------------------------------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\n没有权限使用！！！\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                printf("0.课程降序\n1.课程升序\n");

                char c = getchar();

                getchar();
                switch (c) {
                    case '0': {
                        printf(BG_WHITE   FG_8  "Sort in descending order by course                   (按课程降序排序)\n"RESET);
                        SortNum_Max_Min(fp);
                        break;
                    }
                    case '1': {
                        printf(BG_WHITE   FG_9  "Sort in ascending order by course                     (按课程升序排序)\n"RESET);
                        SortNum_Min_Max(fp);
                        break;
                    }
                    default: {
                        printf("无效字符！！！\n");
                        break;
                    }
                }
                fclose(fp);
            }
            //-----------
            printf("\n回车三次后刷新");
            getchar();
            getchar();
            break;
        }
        case 7: {
            system("cls");
            printf(BG_WHITE   FG_8  "8.Sort by male and female students                    (按学生男女排序)\n"RESET);
            //--------------------------------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\n没有权限使用！！！\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                Sortbygender(fp);
                fclose(fp);
            }
            //-------------------------------------------
            printf("\n回车三次后刷新");
            getchar();
            getchar();
            break;
        }
        case 8: {
            system("cls");
            printf(BG_WHITE   FG_9  "9.Random sort                                               (随机排序)\n"RESET);
            //--------------------------------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\n没有权限使用！！！\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                Randomsort(fp);
                fclose(fp);
            }
            //---------------------------------------
            printf("\n回车三次后刷新");
            getchar();
            getchar();
            break;
        }
        case 9: {
            system("cls");
            printf(BG_WHITE BLINK_1 "W. Write to a File             (可按下后添加字符在目标学生中，方便查找)\n"RESET);

            //--------------------------------------------------------------------------------------------------
            if (userpower == 0) {
                printf(BLINK_2"\n没有权限使用！！！\n"RESET);
            }
            if (userpower) {
                FILE *fp;
                fp = fopen("Students' scores.txt", "r");
                Write_char(fp);
                fclose(fp);
            }
            //------------------------------------------------------------------------------------
            printf("\n回车三次后刷新");
            getchar();
            getchar();
            break;
        }
        case 10: {
            printf(BG_WHITE BLINK_2 "R. Read from a File                           (文件进行查看，快捷全部)\n"RESET);
            //-------------------------------------------------------------------------------------------------------------
            FILE *fp;
            fp = fopen("Students' scores.txt", "r");
            Looking_all(fp);
            fclose(fp);
            //--------------------------------------------------------------------------------
            printf("\n回车三次后刷新");
            getchar();
            getchar();
            break;
        }
        default: {
            printf("\n回车俩次后刷新");
            break;
        }
    }
    caozuo = 1;
}


void Inilial_Write(FILE *p) {
    {
        printf("请先初始化增加学生信息:\n");
        printf("先输入学生的数量:\n");
        scanf("%d", &m);
        printf("课程数目:\n");
        scanf("%d", &n);
        getchar();
    }
    for (int i = 1; i <= m; i++) {

        char name[30];
        char gender[10];
        char className[30];
        char num[30];

        printf("第%d个学生\n\n", i);
        {

            printf("姓名:");
            scanf("%s", name);
            fprintf(p, "%s", name);
            fputc(' ', p);
        }
        {

            printf("性别:");
            scanf("%s", gender);
            fprintf(p, "%s", gender);
            fputc(' ', p);
        }

        {
            printf("班级:");
            scanf("%s", className);
            fprintf(p, "%s", className);
            fputc(' ', p);
        }

        {
            printf("学号:");
            scanf("%s", num);
            fprintf(p, "%s", num);
            fputc('\n', p);
        }

        {
            for (int j = 1; j <= n; j++) {
                printf("课程%d:", j);
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


void Append(FILE *p)//n为课程数量
{
    int a = 0;
    printf("请问您要输入几组数据:\n");
    scanf("%d", &a);
    int mid = m;
    m = m + a;
    for (int i = 1; i <= a; i++) {

        char name[30];
        char gender[10];
        char className[30];
        char num[30];
        printf("第%d个学生\n\n", mid + i);
        {
            printf("姓名:");
            scanf("%s", name);
            fprintf(p, "%s", name);
            fputc(' ', p);
        }
        {

            printf("性别:");
            scanf("%s", gender);
            fprintf(p, "%s", gender);
            fputc(' ', p);
        }

        {
            printf("班级:");
            scanf("%s", className);
            fprintf(p, "%s", className);
            fputc(' ', p);
        }

        {
            printf("学号:");
            scanf("%s", num);
            fprintf(p, "%s", num);
            fputc('\n', p);
        }

        {
            for (int j = 1; j <= n; j++) {
                printf("课程%d:", j);
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
            printf("第%d个学生:  ", i / 2 + 1);
        }

        printf("%s", line);
        i++;
    }
}

int Read_m(FILE *fp)//学生数量初始化
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
    printf("学生姓名总表:\n");
    for (int i = 0; i < m; i++) {
        printf("第%4d个学生:%s\n", i + 1, p_old[i].name);
    }


    //-------------------------------
    printf("请输入你要删除学生数量:");
    int a = 0;
    scanf("%d", &a);
    char **p_delete = (char **) malloc(sizeof(char *) * 30 * a);
    for (int i = 0; i < a; i++) {
        p_delete[i] = (char *) malloc(sizeof(char) * 30);
        printf("请输入删除第%d个学生姓名:\n", i + 1);
        scanf("%s", p_delete[i]);
    }
    system("cls");
    for (int i = 0; i < a; i++) {
        printf("%10s----- 准备删除中...\n", p_delete[i]);
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
    printf("当前学生总表及信息:\n");
    for (int i = 0; i < k; i++) {
        printf("%s\t%s\t%s\t%s\n", p_new[i].name, p_new[i].gender, p_new[i].className, p_new[i].num);
        for (int j = 0; j < n; j++) {
            printf("%d ", p_new[i].grade[j]);
        }
        printf("\n");
    }
//------------------------------------文件写入------------------------------------------------
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
    printf("\n删除成功!");
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
    printf("当前学生总表及信息:\n");
    for (int i = 0; i < m; i++) {
        printf("%s\t%s\t%s\t%s\n", p_new[i].name, p_new[i].gender, p_new[i].className, p_new[i].num);
        for (int j = 0; j < n; j++) {
            printf("%d ", p_new[i].grade[j]);
        }
        printf("\n");
    }
    //--------------------------------------------------------------------------------------------------
    printf("请输入你要修改学生数量:\n");
    int a;
    scanf("%d", &a);

    for (int i = 0; i < a; i++) {
        char temp_name[30];
        int mid = 1;
        printf("输入第%d个学生姓名:\n", i + 1);
        scanf("%s", temp_name);
        for (int j = 0; j < m; j++) {
            if (strcmp(temp_name, p_old[j].name) == 0) {
                mid = 0;
                strcpy(p_new[j].name, temp_name);
                printf("找到该学生！！！\n请输入该学生更改后信息:\n");
                printf("学生");
                printf("%s", p_new[j].name);
                printf("修改信息\n");

                printf("班级:\n");
                scanf("%s", p_new[j].className);
                printf("性别:\n");
                scanf("%s", p_new[j].gender);
                printf("学号:\n");
                scanf("%s", p_new[j].num);
                for (int u = 0; u < n; u++) {
                    printf("课程%d:\n", u + 1);
                    scanf("%d", &p_new[j].grade[u]);
                }
            }
        }
        if (mid) {
            printf("无效的学生信息请重新输入:\n");
            getchar();
            i--;
        }
    }
    system("cls");
    printf("\033[5;31;1m当前学生总表及信息：\n\033[0m");
    for (int i = 0; i < m; i++) {
        printf("第%d个学生:", i + 1);
        printf("%s\t%s\t%s\t%s\t", p_new[i].name, p_new[i].gender, p_new[i].className, p_new[i].num);
        for (int j = 0; j < n; j++) {
            printf("%d\t", p_new[i].grade[j]);
        }
        printf("\n");
    }



//------------------------------------文件写入------------------------------------------------

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
    printf("\n修改成功!");
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
    printf("0.退出\n");
    printf("1.按班级查找\n");
    printf("2.按成绩查找\n");
    printf("3.按学号查找\n");
    printf("~任意键姓名查找~\n");
    char ch;
    scanf("%c", &ch);

    //-------------------------------------------------------------
    switch (ch) {
        case '0': {
            system("cls");
            printf("退出成功！！！");
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
    printf("请输入你要查找的学生学号:\n");
    char Num[30];
    scanf("%s", Num);
    int mid = 1;
    for (int i = 0; i < m; i++) {
        if (strcmp(Num, p[i].num) == 0) {
            printf("-------------------------------------------------------\n");
            printf("----------姓名:%s----------- \n班级:%s 性别%s 学号%s \n成绩:\n", p[i].name, p[i].className,
                   p[i].gender, p[i].num);
            int sum = 0;
            int max = p[i].grade[0];
            int min = p[i].grade[0];
            for (int j = 0; j < n; j++) {
                printf("课程%d:%d\n", j + 1, p[i].grade[j]);
                if (max < p[i].grade[j]) {
                    max = p[i].grade[j];
                }
                if (min > p[i].grade[j]) {
                    min = p[i].grade[j];
                }
                sum += p[i].grade[j];
            }
            double average = sum / n;
            printf("最高分:%d\n", max);
            printf("最低分:%d\n", min);
            printf("平均值:%f\n", average);
            printf("总成绩:%d\n", sum);
            mid = 0;
        }
    }
    if (mid) {
        printf("未找到学生学号信息!!!\n");
    }

}

void Mearch_grade(Stu *p) {

    printf("请输入你要查找的课程:\n");
    printf("已有课程:");

    for (int i = 0; i < n; i++) {
        printf("课程%d ", i + 1);
    }
    printf("\n请选择课程:");
    int x;
    int up = 0, low = 0;
    scanf("%d", &x);
    x = x - 1;
    printf("\n请选择课程查找区间:\n");
    printf("最大值:\n");
    scanf("%d", &up);
    printf("最小值:\n");
    scanf("%d", &low);
    if (up < low) {
        int temp = low;
        low = up;
        up = temp;
        printf("最高值大于最低值，已经纠错！\n");
    }
    int mid = 1;
    for (int i = 0; i < m; i++) {
        if (p[i].grade[x] > low && p[i].grade[x] < up) {
            printf("课程%d  成绩:%d\t", x + 1, p[i].grade[x]);
            printf("      姓名:%s\t性别%s\t班级:%s\t学号%s\n", p[i].name, p[i].gender, p[i].className, p[i].num);
            mid = 0;
        }
    }
    if (mid) {
        printf("未找到课程信息!!!\n");
    }
}

void Mearch_name(Stu *p) {
    printf("请输入你要查找的学生姓名:\n");
    char Stu_name[30];
    scanf("%s", Stu_name);
    int mid = 1;
    for (int i = 0; i < m; i++) {
        if (strcmp(Stu_name, p[i].name) == 0) {
            printf("-----------------------------------------\n");
            printf("----------姓名:%s----------- \n班级:%s 性别%s 学号%s \n成绩:\n", p[i].name, p[i].className,
                   p[i].gender, p[i].num);
            int sum = 0;
            int max = p[i].grade[0];
            int min = p[i].grade[0];
            for (int j = 0; j < n; j++) {
                printf("课程%d:%d\n", j + 1, p[i].grade[j]);
                if (max < p[i].grade[j]) {
                    max = p[i].grade[j];
                }
                if (min > p[i].grade[j]) {
                    min = p[i].grade[j];
                }
                sum += p[i].grade[j];
            }
            double average = sum / n;
            printf("最高分:%d\n", max);
            printf("最低分:%d\n", min);
            printf("平均值:%f\n", average);
            printf("总成绩:%d\n", sum);
            mid = 0;
        }
    }
    if (mid) {
        printf("未找到学生信息!!!\n");
    }
}


void Mearch_class(Stu *p) {
    printf("请输入你要查找的班级:\n");
    char classname[30];
    scanf("%s", classname);
    int mid = 1;
    for (int i = 0; i < m; i++) {
        if (strcmp(classname, p[i].className) == 0) {
            printf("-----------------------------------------\n");
            printf("----------姓名:%s----------- \n班级:%s 性别:%s 学号%s \n成绩:\n", p[i].name, p[i].className,
                   p[i].gender, p[i].num);
            int sum = 0;
            int max = p[i].grade[0];
            int min = p[i].grade[0];
            for (int j = 0; j < n; j++) {
                printf("课程%d:%d\n", j + 1, p[i].grade[j]);
                if (max < p[i].grade[j]) {
                    max = p[i].grade[j];
                }
                if (min > p[i].grade[j]) {
                    min = p[i].grade[j];
                }
                sum += p[i].grade[j];
            }
            double average = sum / n;
            printf("最高分:%d\n", max);
            printf("最低分:%d\n", min);
            printf("平均值:%f\n", average);
            printf("总成绩:%d\n", sum);
            mid = 0;
        }
    }
    if (mid) {
        printf("未找到班级信息!!!\n");
    }
}


void Sort_Max_Min(FILE *fp) {
    printf("是否排序？Y/N\n");
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

//------------------------------------文件写入------------------------------------------------
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
//------------------------------------文件写入------------------------------------------------

}

void Sort_Min_Max(FILE *fp) {
    printf("是否排序？Y/N\n");
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

//------------------------------------文件写入------------------------------------------------
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

//------------------------------------文件写入------------------------------------------------
}


void SortNum_Min_Max(FILE *fp) {
    printf("是否排序？Y/N\n");
    char ch;
    if (ch = getchar() == 'Y') {
        printf("请输入根据哪门课排序:\n");
        for (int k = 0; k < n; k++) {
            printf("课程%d ", k + 1);
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

//------------------------------------文件写入------------------------------------------------
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

//------------------------------------文件写入------------------------------------------------

}


void SortNum_Max_Min(FILE *fp) {
    printf("是否排序？Y/N\n");
    char ch;
    if (ch = getchar() == 'Y') {
        printf("请输入根据哪门课排序:\n");
        for (int k = 0; k < n; k++) {
            printf("课程%d ", k + 1);
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
//------------------------------------文件写入------------------------------------------------
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

//------------------------------------文件写入------------------------------------------------

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
        printf("请输入学生姓名(姓名为EXIT退出并保存):\n");
        char stn[30];
        scanf("%s", stn);
        getchar();
        if (strcmp("EXIT", stn) == 0) {
            printf("退出成功！\n");
            break;
        }

        printf("增加字符(1)还是删除字符(0):\n");
        char c;
        scanf("%c", &c);
        getchar();
        switch (c) {
            case '1': {
                {
                    printf("\n请问你想插入什么字符在学生名字后面(请勿输入超过三个字符)\n");
                    char ch[3];
                    scanf("%s", ch);
                    int mid = 1;
                    for (int i = 0; i < m; i++) {
                        if (strcmp(stn, p[i].name) == 0) {
                            printf("已经增加字符到%s\n", p[i].name);
                            strcat(p[i].name, ch);
                            mid = 0;
                        }
                    }
                    if (mid) printf("学生未找到！\n");
                }
                break;
            }
            case '0': {

                {
                    printf("\n请问你想删除什么字符在学生名字后面(请勿输入超过三个字符)\n");
                    char sub[3];
                    scanf("%s", sub);
                    int mid = 1;
                    for (int i = 0; i < m; i++) {
                        if (strcmp(stn, p[i].name) == 0) {
                            printf("已经删除字符到%s\n", p[i].name);


                            int len = strlen(sub);
                            char *match;
                            while ((match = strstr(p[i].name, sub))) {
                                memmove(match, match + len, strlen(match + len) + 1);
                            }
                            mid = 0;
                        }
                    }
                    if (mid) printf("学生未找到！\n");
                }

                break;
            }
            default: {
                printf("无效字符！\n");
                break;
            }
        }

    }
    //----------------------------------------------------------------------------------

    PRINTF(p);
//------------------------------------文件写入------------------------------------------------
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
    printf("是否按照男女生排序？Y/N\n");
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

        char sex[10] = {"男"};


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

//------------------------------------文件写入------------------------------------------------
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
//------------------------------------文件写入------------------------------------------------

}


//-----------####################################################################################
void Randomsort(FILE *fp) {
    //-------------------------------------------------------------
    printf("请选择模式\n1.顺序排列\n2.随机排列\n3.点名系统\n~~~~~~~~~~~~~~~~\n请选择:");
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
            printf("无效字符，已退出！！！\n");
        }
    }
}

//##########################################################################################################
void moshi1(Stu *p) {

    printf("可输入你想让第一个学生的序号，将会顺序打印,请勿输入超过8位！！！\n");
    long long int xuhao = 0;
    scanf("%lld", &xuhao);
    getchar();
    //---------------------------------------------------------
    srand(time(NULL));
    // 从最后一个元素开始，逐个与随机位置的元素交换
    for (int i = m - 1; i > 0; i--) {
        // 生成随机索引
        int j = rand() % (i + 1);
        // 交换位置
        Stu temp = p[i];
        p[i] = p[j];
        p[j] = temp;
    }
    printf(FG_1"当前学生总表及信息：\n"RESET);
    for (int i = 0; i < m; i++) {
        if (strcmp("男", p[i].gender) == 0) {
            printf("序号:%lld:", xuhao + i);
            printf(FG_1 "%10s %6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
            printf("\n");
        } else {
            printf("序号:%lld:", xuhao + i);
            printf(FG_5 "%10s %6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
            printf("\n");
        }
    }
    FILE *fp1;
    fp1 = fopen("学生排序.txt", "w");
    for (int i = 0; i < m; i++) {
        fprintf(fp1, "序号：%lld\t 姓名：%10s 性别%6s 班级%10s 学号%10s\n", xuhao + i, p[i].name, p[i].gender,
                p[i].className, p[i].num);
    }
    fclose(fp1);
    printf("\n~~~~~~~~~~~\n文件保存成功！！\n");
}

//############################################################################
void moshi2(Stu *p) {
    FILE *fp1;
    fp1 = fopen("学生排序.txt", "w");
    printf("请输入想创建的序号长度\n");
    int k = 0;
    scanf("%d", &k);
    getchar();
    srand(time(NULL));
    printf(FG_1"当前学生总表及信息：\n"RESET);
    for (int i = 0; i < m; i++) {

        fprintf(fp1, "序号:");
        printf("序号:");
        for (int j = 0; j < k; j++) {
            int x = rand() % 10;
            fprintf(fp1, "%d", x);
            printf("%d", x);
        }
        printf(FG_1 " %10s\t%6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
        printf("\n");
        fprintf(fp1, " 姓名：%10s\t详细信息:性别：%6s 班级：%10s 学号：%10s\n", p[i].name, p[i].gender, p[i].className,
                p[i].num);
    }
    printf("\n~~~~~~~~~~~\n文件保存成功！！\n");
    fclose(fp1);
}

//####################################################################################
void moshi3(Stu *p) {
    printf("请输入你想要几个学生\n");
    int a = 0;
    scanf("%d", &a);
    getchar();
    srand(time(NULL));

    for (int i = 0; i < m; i++) {
        {
            if (strcmp("男", p[i].gender) == 0) {
                printf("点名中....\n");
                printf(FG_1 "%10s %6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
                printf("\n");
            } else {
                printf("点名中....\n");
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
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n就是你了,第%d个幸运儿:%s\n", i + 1, p[q[i]].name);
    }
}

//###########################################################################
void PRINTF(Stu *p) {
    printf(FG_1"当前学生总表及信息：\n"RESET);
    for (int i = 0; i < m; i++) {

        if (strcmp("男", p[i].gender)) {
            printf("第%4d个学生:", i + 1);
            printf(FG_1 "%10s %6s %10s %20s "RESET, p[i].name, p[i].gender, p[i].className, p[i].num);
            for (int j = 0; j < n; j++) {
                printf(FG_1 "%d\t"RESET, p[i].grade[j]);
            }
            printf("\n");
        } else {
            printf("第%4d个学生:", i + 1);
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
        printf("*----------姓名:%10s----------------* \n班级:%s 性别:%s 学号%s \n成绩:\n", p[i].name, p[i].className,
               p[i].gender, p[i].num);
        int sum = 0;
        int max = p[i].grade[0];
        int min = p[i].grade[0];
        printf(FG_8 BG_WHITE"_________________________    "RESET);
        printf("\n");
        for (int j = 0; j < n; j++) {
            printf(FG_8 BG_WHITE"|课程%4d:%5d             |"RESET, j + 1, p[i].grade[j]);
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
        printf(FG_5 "最高分:%d\n"RESET, max);
        printf(FG_1 "最低分:%d\n"RESET, min);
        printf(FG_2 "平均值:%.2f\n"RESET, average);
        printf(FG_3 "总成绩:%d\n"RESET, sum);

    }

}

