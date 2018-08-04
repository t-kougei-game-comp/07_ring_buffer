#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum{
    BUFFER_SIZE = 11,
};

typedef struct{
    int head;
    int tail;
    int buf[BUFFER_SIZE];
} ring_buffer;

// 初期化
void ring_buffer_initialize(ring_buffer *p){
    p->head = p->tail = 0;
}
// 値を追加(失敗したらfalse)
bool ring_buffer_write(ring_buffer *p, int n){
    int next = (p->head + 1) % BUFFER_SIZE;
    if(next == p->tail) return false;
    p->buf[p->head] = n;
    p->head = next;
    return true;
}
// データを取り出す（-1はデータがなかった場合）
int ring_buffer_read(ring_buffer *p){
    if(p->head == p->tail) return -1;
    int v = p->buf[p->tail];
    p->tail = (p->tail + 1) % BUFFER_SIZE;
    return v;
}
// リングバッファに追加された順にデータを参照する（-1はデータがなかった場合）
int ring_buffer_get(ring_buffer *p, int idx){
    int num = p->head + BUFFER_SIZE - p->tail; if(BUFFER_SIZE <= num) num -= BUFFER_SIZE;
    if(num <= idx) return -1;
    return p->buf[(p->tail + idx) % BUFFER_SIZE];
}


int main(int argc, char *argv[]) 
{
    char str[7];
    
    ring_buffer rb;
    ring_buffer_initialize(&rb);
    
    while(fgets(str, sizeof(str), stdin)){
        int v;
        int n = atoi(str);
        switch(n){
        default:
            // リングバッファに追加
            ring_buffer_write(&rb ,n);
            break;
        case -1:
            // スタックから取り出す
            v = ring_buffer_read(&rb);
            if(v != -1) printf("%d", v);
            printf("\n");
            break;
        case 0:
            // スタックを表示
            for(int i = 0; i < BUFFER_SIZE; i++){
                int v = ring_buffer_get(&rb, i);
                if(v == -1) break;
                if(i != 0) printf(",");
                printf("%d", v);
            }
            printf("\n");
            break;
        }
    }

    return 0;
}
