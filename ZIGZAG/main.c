#include <stdio.h>

int DATA_M;
char DATA_A[500];
char DATA_B[500];
int CALCULATOR[501][500][10][3][2];
int length_x;
int ANSWER;


int solve(int A__digits,int B__remnant,int C__number,int D__updown,int E__match,char data_X[]){
    //printf("\nIn");
    if (A__digits == length_x) {
        
        //printf("size = %d",length_x);
        
        //printf("\nmd     = %d  [%d][%d][%d][%d][%d]",B__remnant,A__digits,B__remnant,C__number,D__updown,E__match);
        if (B__remnant >= 1) {
            return 0;
        } else {
            return 1;
        }
    }
    
    if(CALCULATOR[A__digits][B__remnant][C__number][D__updown][E__match] >= 0){
        //printf("\nreturn = %d  [%d][%d][%d][%d][%d] すでに計算済みです",CALCULATOR[A__digits][B__remnant][C__number][D__updown][E__match],A__digits,B__remnant,C__number,D__updown,E__match);
        return CALCULATOR[A__digits][B__remnant][C__number][D__updown][E__match];
    }
    
    int REMNANT = 0;
    for (int i = 0; i <= ((E__match)?9:(int)(data_X[A__digits]-'0')); i ++) {
        if (D__updown == 0 && C__number <= i) {
            //ジグザグではありません
        } else {
            if (D__updown == 1 && C__number >= i){
                //ジグザグではありません
            } else {
                if (D__updown == 2 && C__number != 0 && C__number == i) {
                    //二文字目と一文字目が被っても、ジグザグではありません。
                } else {
                    int provisional_D__updown;
                    if (D__updown == 2) {
                        //上下がまだ定まっていません。決めてあげましょう。
                        if(C__number == 0){
                            //0000...の連続で、未だに決定できません。
                            provisional_D__updown = 2;
                        } else if (C__number > i) {
                            //減少しています。Downとして記録します。
                            provisional_D__updown = 1;
                        } else {
                            //増加しています。Upとして記録します。
                            provisional_D__updown = 0;
                        }
                    } else {
                        //すでにジグザグきてるので、入れ替えてあげましょう。
                        provisional_D__updown = 1 - D__updown;
                    }
                    
                    int provisional_E__match;//文字が今まで一致してきているかを検証します。
                    if (E__match == 1 || i != (int)(data_X[A__digits]-'0')) {
                        provisional_E__match = 1;
                    } else {
                        provisional_E__match = 0;
                    }
                    
                    REMNANT = REMNANT + solve(A__digits + 1,//処理を一つ進めます。
                                              (B__remnant * 10 + i) % DATA_M,//あまりを十倍して、今回の数を足して、Mで割ります。
                                              i,//このまま伝えてあげます。
                                              provisional_D__updown,//先ほど指定したupdownを使用します。
                                              provisional_E__match,//先ほど指定したmatchを使用します。
                                              data_X);
                    
                }
            }
        }
    }
    
    CALCULATOR[A__digits][B__remnant][C__number][D__updown][E__match] = REMNANT % 10000;
    //printf("\nreturn = %d  [%d][%d][%d][%d][%d]",REMNANT%10000,A__digits,B__remnant,C__number,D__updown,E__match);
    return CALCULATOR[A__digits][B__remnant][C__number][D__updown][E__match];
    
}


void reset(){
    for (int A__digits = 0; A__digits < 501; A__digits ++) {
        for (int B__remnant = 0; B__remnant < 500; B__remnant ++) {
            for (int C__number = 0; C__number < 10; C__number ++) {
                for (int D__updown = 0; D__updown < 3; D__updown ++) {
                    for (int E__match = 0; E__match < 2; E__match ++) {
                        CALCULATOR[A__digits][B__remnant][C__number][D__updown][E__match] = -1;
                    }
                }
            }
        }
    }
}


int main() {
    
    char c;
    int i_scan;
    
    for(i_scan = 0; i_scan < 100; i_scan++){
        scanf("%c", &c);
        if ( c == '\n'){
            /* もし'\n'だったらヌル文字を書いてループを抜ける */
            DATA_A[i_scan] = '\0';
            break;
        }
        else
            DATA_A[i_scan] = c;
    }
    for(i_scan = 0; i_scan < 100; i_scan++){
        scanf("%c", &c);
        if ( c == '\n'){
            /* もし'\n'だったらヌル文字を書いてループを抜ける */
            DATA_B[i_scan] = '\0';
            break;
        }
        else
            DATA_B[i_scan] = c;
    }
    
    
    
    
    scanf("%d",&DATA_M);

    int length_of_DATA_A;
    int length_of_DATA_B;
    
    length_of_DATA_A = strlen(DATA_A);
    length_of_DATA_B = strlen(DATA_B);

    for(int i = length_of_DATA_A-1; i >= 0; i--){
        if(DATA_A[i] == '0'){
            DATA_A[i] = '9';
        }else{
            DATA_A[i]--;
            break;
        }
    }
    
    //printf("%s",DATA_A);
    reset();
    length_x = length_of_DATA_A;
    int ans_a;
    ans_a = solve(0, 0, 0, 2, 0, DATA_A);
    printf("\na = %d",ans_a);
    
    
    //printf("\n\n\n\n\n");

    
    //printf("%s",DATA_B);
    reset();
    length_x = length_of_DATA_B;
    int ans_b;
    ans_b = solve(0, 0, 0, 2, 0, DATA_B);
    printf("\nb = %d",ans_b);
    
    ANSWER = (ans_b + 10000 - ans_a)%10000;
    
    printf("\n\n計算結果 = %d\n\n",ANSWER);
    
    return 0;
}
