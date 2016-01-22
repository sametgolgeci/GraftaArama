//
//  main.c
//  GraftaArama
//
//  Created by Samet Gölgeci on 02/01/16.
//  Copyright © 2016 SametGolgeci. All rights reserved.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    int N,M,K,i,j,a,b,tmp,secim,stackSayac,bul;
    int tablo[10][10],labirent[20][20],stack[100][2];
    int x[50],y[50];
    
    printf("N sayınısı giriniz\n");
    scanf("%d",&N);
    printf("Labirenti otomatik oluşturmak için 0 a, kendiniz oluşturmak için 1 e basınız\n");
    scanf("%d",&secim);
    
    if (secim==0) {
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                tmp=rand()%2;
                tablo[i][j]=tmp;
                printf("%d ",tmp);
            }
            printf("\n");
        }
        tablo[0][0]=0;
        printf("Labirent otomatik olarak oluşturuldu\n");
    }
    else{
        printf("Girilecek değer sayısını giriniz\n");
        scanf("%d",&K);
        printf("X dizisinin değerlerini giriniz\n");
        for (i=0; i<K; i++){
                scanf("%d",&x[i]);
        }
        printf("Y dizisinin değerlerini giriniz\n");
        for (i=0; i<K; i++){
            scanf("%d",&y[i]);
        }
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                tablo[i][j]=0;
            }
        }
        for (i=0; i<K; i++){
                tablo[x[i]][y[i]]=1;
        }
        
        for (i=0; i<N; i++){
            for (j=0; j<N; j++){
                printf("%d ",tablo[i][j]);
            }
            printf("\n");
        }

        
        printf("Labirent oluşturuluyor\n");
    }
    
    
    M=(2*N)+1;
    
    // 0 = boşluk " "
    // 1 = başlangıç "*"
    // 2 = izledi yol "I"
    // 3 = çıkış "X"
    // 4 = kısa duvar "-"
    // 5 = uzun duvar "|"
    // 6 = köşe "+"
    
    for (i=0; i<M; i++) {
        for (j=0; j<M; j++) {
            if ((i%2==0)&&(j%2==0)) {
                labirent[i][j]=6;
            }
            else{
                labirent[i][j]=0;
            }
        }
    }
    
    for (i=0; i<M; i++) {
        if (i%2==0) {
            labirent[i][0]=6;
            labirent[0][i]=6;
            labirent[i][M-1]=6;
            labirent[M-1][i]=6;
        }
        else{
            labirent[i][0]=5;
            labirent[0][i]=4;
            labirent[i][M-1]=5;
            labirent[M-1][i]=4;
        }
    }
    
    labirent[1][1]=1;
    
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            if (tablo[i][j]==1) {
                labirent[(2*i)+1][(2*j)+2]=5;
                labirent[(2*i)+1][(2*j)]=5;
                labirent[(2*i)+2][(2*j)+1]=4;
                labirent[(2*i)][(2*j)+1]=4;
            }
        }
    }

//  Labirent oluşturuldu.
    
    for (i=0; i<M; i++) {
        for (j=0; j<M; j++) {
            switch (labirent[i][j]) {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("*");
                    break;
                case 2:
                    printf("I");
                    break;
                case 3:
                    printf("X");
                    break;
                case 4:
                    printf("-");
                    break;
                case 5:
                    printf("|");
                    break;
                case 6:
                    printf("+");
                    break;
            }
        }
        printf("\n");
    }
    
//  Çıkış noktası labirentte ekleniyor.
    
    printf("Çıkış noktasını giriniz\n");
    scanf("%d",&a);
    scanf("%d",&b);
    
    labirent[(2*a)+1][(2*b)+1]=3;
    
    printf("Çıkış noktası labirente eklendi\n");
    
    for (i=0; i<M; i++) {
        for (j=0; j<M; j++) {
            switch (labirent[i][j]) {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("*");
                    break;
                case 2:
                    printf("I");
                    break;
                case 3:
                    printf("X");
                    break;
                case 4:
                    printf("-");
                    break;
                case 5:
                    printf("|");
                    break;
                case 6:
                    printf("+");
                    break;
            }
        }
        printf("\n");
    }
    
    bul=0;
    stackSayac=0;
    stack[0][0]=0;
    stack[0][1]=0;
    
    while ((stackSayac>=0)&&(bul==0)) {
        i=stack[stackSayac][0];
        j=stack[stackSayac][1];
        if ((i==a)&&(j==b)) {
            printf("Çıkış noktası bulundu:    %d    %d \n",i,j);
            bul=1;
        }else{
            if (tablo[i][j]==0) {
                tablo[i][j]=2;
                labirent[(2*i)+1][(2*j)+1]=2;
                printf("Labirentte %d,%d noktası I yapıldı\n",i,j);
                
                if ((tablo[i][j-1]==0)&&((j-1)>=0)) {
                    stackSayac++;
                    stack[stackSayac][0]=i;
                    stack[stackSayac][1]=j-1;
                    printf("Stackın %d. gözüne %d,%d noktası eklendi\n",stackSayac,i,j-1);
                }
                if ((tablo[i-1][j]==0)&&((i-1)>=0)) {
                    stackSayac++;
                    stack[stackSayac][0]=i-1;
                    stack[stackSayac][1]=j;
                    printf("Stackın %d. gözüne %d,%d noktası eklendi\n",stackSayac,i-1,j);
                }
                if ((tablo[i][j+1]==0)&&((j+1)<N)) {
                    stackSayac++;
                    stack[stackSayac][0]=i;
                    stack[stackSayac][1]=j+1;
                    printf("Stackın %d. gözüne %d,%d noktası eklendi\n",stackSayac,i,j+1);
                }
                if ((tablo[i+1][j]==0)&&((i+1)<N)) {
                    stackSayac++;
                    stack[stackSayac][0]=i+1;
                    stack[stackSayac][1]=j;
                    printf("Stackın %d. gözüne %d,%d noktası eklendi\n",stackSayac,i+1,j);
                }
                
                
                
                
            }
            else{
                stackSayac--;
                labirent[(2*i)+1][(2*j)+1]=0;
                printf("Labirentte %d,%d noktası boş olarak bırakıldı\n",i,j);
            }
        }
    }
    
    if (bul==0) {
        printf("Çıkış noktasına yol bulunamadı\n");
    }
    else{
        
        labirent[1][1]=1;
        
        for (i=0; i<M; i++) {
            for (j=0; j<M; j++) {
                switch (labirent[i][j]) {
                    case 0:
                        printf(" ");
                        break;
                    case 1:
                        printf("*");
                        break;
                    case 2:
                        printf("I");
                        break;
                    case 3:
                        printf("X");
                        break;
                    case 4:
                        printf("-");
                        break;
                    case 5:
                        printf("|");
                        break;
                    case 6:
                        printf("+");
                        break;
                }
            }
            printf("\n");
        }
    }
    
  

    
    
    return 0;
}

