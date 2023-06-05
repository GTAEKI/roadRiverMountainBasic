
#include <time.h> //시간에 따른 srand변화를 위한 헤더
#include <stdlib.h>// random값 이용 헤더
#include <cstdlib> //system("clear");
#include <stdio.h>
#include <termios.h> // custom mygetch를 위한 헤더
#include <unistd.h> // custom mygetch를 위한 헤더

int mygetch(void);//windows getch()와 같은기능을 하는 함수
                  //사용하지 않은 함수입니다.

void start(void); //오프닝
void randomPlay(void); //길강산 게임 본체

//변수 선언
int maxHp = 50;
int randomPath, randomFight;
int count=1;
int trashMemory;
int monsterOffence, playerDeffence, playerHeal, finalDamage;
char gamePlay;

//게임 시작
int main(){

    srand(time(NULL));

    while(1)
    {
        start(); //인트로
        randomPlay(); //실제 게임

        printf("게임을 계속하시겠습니까? [Y/N]\n"); //게임 죽거나 이겼을경우
        scanf("%c",&gamePlay);

        //N을 눌렀을 경우에만 게임종료
        if(gamePlay == 'N' || gamePlay == 'n')
        {
            break;
        }
        count = 1;
    }

    
}//main

void start(void)
{
    printf("\n[안녕하세요. 길강산 게임에 오신것을 환영합니다.]\n\n");
    printf("길, 강, 산 세가지 경로가 있고, 당신은 길을 6번 가야 이길 수 있습니다.\n\n");
    printf("몬스터 공격력을 입력해주세요: ");
    scanf("%d",&monsterOffence);
    printf("당신의 방어력을 입력해주세요: ");
    scanf("%d",&playerDeffence);
    printf("당신의 회복량을 입력해주세요: ");
    scanf("%d",&playerHeal);

    printf("몬스터 공격력 = %d, 당신의 방어력 = %d, 회복량 = %d입니다.\n",monsterOffence,playerDeffence,playerHeal);
    
    finalDamage = monsterOffence - playerDeffence;
    printf("전투시 당신은 %d만큼 피해를 입습니다.\n",finalDamage);
    printf("================================================\n");
    printf("================================================\n");
    printf("=====게임을 시작합니다. 아무키나 눌러주세요======\n");

    trashMemory = getchar();
    trashMemory = getchar();
    system("clear");
}

void randomPlay(void)
{
    //길을 6번가면 
    for(int roadCount = 0; roadCount < 6; count +=1){
        
        printf("[%d번째] 세 갈래 길이 나왔다.\n",count);
        printf("[_길_] [_강_] [_산_]\n\n");
        
        printf("어디로 가지...?\n\n");
        printf("아무키나 입력하시면 진행됩니다.\n");
        trashMemory = getchar();//아무값 입력
        
        randomPath = (rand()%10)+1;//1~10 숫자 랜덤 대입
        if(randomPath <= 3)
        {
            roadCount += 1;
            printf("다행이다! 내가 찾던 길이야!!\n");
            printf("미션 진행도 [%d/6]",roadCount);
            trashMemory = getchar();
            system("clear");
        }//if 길
        else if(randomPath > 3 && randomPath <= 5)
        {
            printf("아쉽다.. 강이야. 물고기먹자\n");
            trashMemory = getchar();
            system("clear");
        }//else if 강
        else
        {
            printf("큰일났다. 여긴 산이야..\n");
            printf("몬스터가 나올지도 몰라 ㅠㅠ\n");

            printf(">>>>>>\n");
            printf(">>>>>>\n");
            randomFight = (rand()%10)+1;

            printf("몬스터를 만났습니다. 전투가 시작됩니다.\n");
            printf("몬스터 공격력 : %d, 내 방어력 :%d\n\n",monsterOffence, playerDeffence);

            if(randomFight <= 4)
            {
                printf("몬스터에게 공격당했습니다..");
                maxHp -= finalDamage;
                printf("데미지를 %d입습니다. 현재체력 [%d/50]\n",finalDamage, maxHp);

                if(maxHp <= 0)
                {
                    printf("[플레이어가 사망했습니다. 아무를 눌러 게임을 다시 시작하세요.]\n\n");
                    roadCount = 10;
                    trashMemory = getchar();
                    system("clear");
                }
                trashMemory = getchar();
                system("clear");

            }//if 몬스터 공격
            else if(randomFight > 4)
            {
                printf("몬스터를 회피했습니다. 회피보너스로 체력을 %d회복합니다.\n",playerHeal);
                maxHp += playerHeal;
                if(maxHp >= 50){
                    maxHp = 50;
                }
                printf("현재체력 [%d/50]\n", maxHp);
                trashMemory = getchar();
                system("clear");

            }//else if 회피
        } //else 산
    }//for
}//randomPlay함수

//사용하지 않은 함수입니다.
int mygetch(void)//windows getch와 같은기능을 하는 함수
{
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}