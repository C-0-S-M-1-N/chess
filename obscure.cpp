#pragma once
#include <bits/stdc++.h>
enum atacuri{
    LIBER,
    NEGRU,
    ALB
};
std::vector<std::vector<atacuri>> attacksW={
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER}
};
std::vector<std::vector<atacuri>> attacksB={
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER}
};
std::vector<std::vector<atacuri>> attacksLIBER={
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER},
    {LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER, LIBER}
};

bool rookCheck(int xStart, int yStart, int xEnd, int yEnd, std::vector<std::vector<int>> table){ //1 withe and 0 black
    if(xStart == xEnd){
        if(yStart > yEnd){
            for(int i = yStart - 1; i > yEnd; i--){
                if(table[xStart][i] != 0){
                    return 0;
                }
            }
        }
        else{
            for(int i = yStart + 1; i < yEnd; i++){
                if(table[xStart][i] != 0){
                    return 0;
                }
            }
        }
    }
    else{
        if(xStart > xEnd){
            for(int i = xStart - 1; i > xEnd; i--){
                if(table[i][yStart] != 0){
                    return 0;
                }
            }
        }
        else{
            for(int i = xStart + 1; i < xEnd; i++){
                if(table[i][yStart] != 0){
                    return 0;
                }
            }
        }
    }
    return 1;
}

bool bishopCheck(int xStart, int yStart, int xEnd, int yEnd, std::vector<std::vector<int>> table){ //1 withe and 0 black
    if(abs(xStart - xEnd) == abs(yStart - yEnd)){
        if(xStart > xEnd){
            if(yStart > yEnd){
                for(int i = xStart - 1, j = yStart - 1; i > xEnd; i--, j--){
                    if(table[i][j] != 0){
                        return 0;
                    }
                }
            }
            else{
                for(int i = xStart - 1, j = yStart + 1; i > xEnd; i--, j++){
                    if(table[i][j] != 0){
                        return 0;
                    }
                }
            }
        }
        else{
            if(yStart > yEnd){
                for(int i = xStart + 1, j = yStart - 1; i < xEnd; i++, j--){
                    if(table[i][j] != 0){
                        return 0;
                    }
                }
            }
            else{
                for(int i = xStart + 1, j = yStart + 1; i < xEnd; i++, j++){
                    if(table[i][j] != 0){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}


void Attacks(std::vector<std::vector<int>> table){
    attacksW = attacksLIBER;
    attacksB = attacksLIBER;
    for(int i = 1; i<=8; i++){
        for(int j = 1; j<=8; j++){
            //rege
            if(table[i][j] == 1){
                attacksW[i+1][j] = ALB;
                attacksW[i-1][j] = ALB;
                attacksW[i][j+1] = ALB;
                attacksW[i][j-1] = ALB;
                attacksW[i+1][j+1] = ALB;
                attacksW[i-1][j-1] = ALB;
                attacksW[i+1][j-1] = ALB;
                attacksW[i-1][j+1] = ALB;
            }else if(table[i][j] == 10){

                attacksB[i+1][j] = NEGRU;
                attacksB[i-1][j] = NEGRU;
                attacksB[i][j+1] = NEGRU;
                attacksB[i][j-1] = NEGRU;
                attacksB[i+1][j+1] = NEGRU;
                attacksB[i-1][j-1] = NEGRU;
                attacksB[i+1][j-1] = NEGRU;
                attacksB[i-1][j+1] = NEGRU;
            }
            //regina
            else if(table[i][j] == 2){
                //in forma de tura
                for(int k = i+1; k<9; k++){
                    attacksW[k][j] = ALB;
                    if(table[k][j] != 0) break;
                }
                for(int k = i-1; k>0; k--){
                    attacksW[k][j] = ALB;
                    if(table[k][j] != 0) break;
                }
                for(int k = j+1; k<9; k++){
                    attacksW[i][k] = ALB;
                    if(table[i][k] != 0) break;
                }
                for(int k = j-1; k>0; k--){
                    attacksW[i][k] = ALB;
                    if(table[i][k] != 0) break;
                }
                //in forma de nebun
                for(int k = i+1, l = j+1; k<9 && l<9; k++, l++){
                    attacksW[k][l] = ALB;
                    if(table[k][l] != 0) break;
                }
                for(int k = i-1, l = j-1; k>0 && l>0; k--, l--){
                    attacksW[k][l] = ALB;
                    if(table[k][l] != 0) break;
                }
                for(int k = i+1, l = j-1; k<9 && l>0; k++, l--){
                    attacksW[k][l] = ALB;
                    if(table[k][l] != 0) break;
                }
                for(int k = i-1, l = j+1; k>0 && l<9; k--, l++){
                    attacksW[k][l] = ALB;
                    if(table[k][l] != 0) break;
                }


            }else if(table[i][j] == 20){
                //in forma de tura
                for(int k = i+1; k<9; k++){
                    attacksB[k][j] = NEGRU;
                    if(table[k][j] != 0) break;
                }
                for(int k = i-1; k>0; k--){
                    attacksB[k][j] = NEGRU;
                    if(table[k][j] != 0) break;
                }
                for(int k = j+1; k<9; k++){
                    attacksB[i][k] = NEGRU;
                    if(table[i][k] != 0) break;
                }
                for(int k = j-1; k>0; k--){
                    attacksB[i][k] = NEGRU;
                    if(table[i][k] != 0) break;
                }
                //in forma de nebun
                for(int k = i+1, l = j+1; k<9 && l<9; k++, l++){
                    attacksB[k][l] = NEGRU;
                    if(table[k][l] != 0) break;
                }
                for(int k = i-1, l = j-1; k>0 && l>0; k--, l--){
                    attacksB[k][l] = NEGRU;
                    if(table[k][l] != 0) break;
                }
                for(int k = i+1, l = j-1; k<9 && l>0; k++, l--){
                    attacksB[k][l] = NEGRU;
                    if(table[k][l] != 0) break;
                }
                for(int k = i-1, l = j+1; k>0 && l<9; k--, l++){
                    attacksB[k][l] = NEGRU;
                    if(table[k][l] != 0) break;
                }

            }
            //tura
            else if(table[i][j] == 3){
                for(int k = i+1; k<9; k++){
                    attacksW[k][j] = ALB;
                    if(table[k][j] != 0) break;
                }
                for(int k = i-1; k>0; k--){
                    attacksW[k][j] = ALB;
                    if(table[k][j] != 0) break;
                }
                for(int k = j+1; k<9; k++){
                    attacksW[i][k] = ALB;
                    if(table[i][k] != 0) break;
                }
                for(int k = j-1; k>0; k--){
                    attacksW[i][k] = ALB;
                    if(table[i][k] != 0) break;
                }
            }
            else if(table[i][j] == 30){
                for(int k = i+1; k<9; k++){
                    attacksB[k][j] = NEGRU;
                    if(table[k][j] != 0) break;
                }
                for(int k = i-1; k>0; k--){
                    attacksB[k][j] = NEGRU;
                    if(table[k][j] != 0) break;
                }
                for(int k = j+1; k<9; k++){
                    attacksB[i][k] = NEGRU;
                    if(table[i][k] != 0) break;
                }
                for(int k = j-1; k>0; k--){
                    attacksB[i][k] = NEGRU;
                    if(table[i][k] != 0) break;
                }
            }
            //nebun
            else if(table[i][j] == 4){
                for(int k = i+1, l = j+1; k<9 && l<9; k++, l++){
                    attacksW[k][l] = ALB;
                    if(table[k][l] != 0) break;
                }
                for(int k = i-1, l = j-1; k>0 && l>0; k--, l--){
                    attacksW[k][l] = ALB;
                    if(table[k][l] != 0) break;
                }
                for(int k = i+1, l = j-1; k<9 && l>0; k++, l--){
                    attacksW[k][l] = ALB;
                    if(table[k][l] != 0) break;
                }
                for(int k = i-1, l = j+1; k>0 && l<9; k--, l++){
                    attacksW[k][l] = ALB;
                    if(table[k][l] != 0) break;
                }
            }
            else if(table[i][j] == 40){
                for(int k = i+1, l = j+1; k<9 && l<9; k++, l++){
                    attacksB[k][l] = NEGRU;
                    if(table[k][l] != 0) break;
                }
                for(int k = i-1, l = j-1; k>0 && l>0; k--, l--){
                    attacksB[k][l] = NEGRU;
                    if(table[k][l] != 0) break;
                }
                for(int k = i+1, l = j-1; k<9 && l>0; k++, l--){
                    attacksB[k][l] = NEGRU;
                    if(table[k][l] != 0) break;
                }
                for(int k = i-1, l = j+1; k>0 && l<9; k--, l++){
                    attacksB[k][l] = NEGRU;
                    if(table[k][l] != 0) break;
                }
            }
            //cal
            else if(table[i][j] == 5){
                if(i + 2 <= 8 && j + 1 <= 8)
                attacksW[i+2][j+1] = ALB;
                if(i + 2 <= 8 && j - 1 > 0)
                attacksW[i+2][j-1] = ALB;
                if(i - 2 > 0 && j + 1 <= 8)
                attacksW[i-2][j+1] = ALB;
                if(i - 2 > 0 && j - 1 > 0)
                attacksW[i-2][j-1] = ALB;

                if(i + 1 <= 8 && j + 2 <= 8)
                attacksW[i+1][j+2] = ALB;
                if(i - 1 > 0 && j + 2 <= 8)
                attacksW[i-1][j+2] = ALB;
                if(i + 1 <= 8 && j - 2 > 0)
                attacksW[i+1][j-2] = ALB;
                if(i - 1 > 0 && j - 2 > 0)
                attacksW[i-1][j-2] = ALB;
            }
            else if(table[i][j] == 50){
                if(i + 2 <= 8 && j + 1 <= 8)
                attacksB[i+2][j+1] = NEGRU;
                if(i + 2 <= 8 && j - 1 > 0)
                attacksB[i+2][j-1] = NEGRU;
                if(i - 2 > 0 && j + 1 <= 8)
                attacksB[i-2][j+1] = NEGRU;
                if(i - 2 > 0 && j - 1 > 0)
                attacksB[i-2][j-1] = NEGRU;

                if(i + 1 <= 8 && j + 2 <= 8)
                attacksB[i+1][j+2] = NEGRU;
                if(i - 1 > 0 && j + 2 <= 8)
                attacksB[i-1][j+2] = NEGRU;
                if(i + 1 <= 8 && j - 2 > 0)
                attacksB[i+1][j-2] = NEGRU;
                if(i - 1 > 0 && j - 2 > 0)
                attacksB[i-1][j-2] = NEGRU;
            }
            //pion
            else if(table[i][j] == 6){
                attacksW[i+1][j+1] = ALB;
                attacksW[i-1][j-1] = ALB;
            }
            else if(table[i][j] == 60){
                attacksB[i+1][j+1] = NEGRU;
                attacksB[i-1][j-1] = NEGRU;
            }
        }
    }
}
