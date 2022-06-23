/*
    0 means its black
    king -> 1(0)
    queen -> 2(0)
    rook -> 3(0)
    bishop -> 4(0)
    knight -> 5(0)
    pawn -> 6(0)

*/
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "obscure.cpp"
#define __X 128
#define __Y 128
bool turn = 1; //0 black, 1 white
bool hold;

void renderTable(sf::RenderWindow&);
void drawFrame(sf::RenderWindow&);
void debugTable();
void debugAttackTable();

std::vector<std::vector<int>> homePos= {
    {0,  0,  0,  0,  0,  0,  0,  0,  0, 0},
    {0, 30, 50, 40, 20, 10, 40, 50, 30, 0},
    {0, 60, 60, 60, 60, 60, 60, 60, 60, 0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0, 0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0, 0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0, 0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0, 0},
    {0,  6,  6,  6,  6,  6,  6,  6,  6, 0},
    {0,  3,  5,  4,  2,  1,  4,  5,  3, 0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0, 0}

};

sf::Texture allPices;
sf::Mouse mouse;

std::vector<std::vector<int>> table = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
std::unordered_map<int, sf::Sprite> pices = {
    {1, sf::Sprite(allPices, sf::IntRect(5*__X, __Y, __X, __Y))},
    {10, sf::Sprite(allPices, sf::IntRect(5* __X, 0, __X, __Y))},
    {2, sf::Sprite(allPices, sf::IntRect(__X*4,   __Y, __X, __Y))},
    {20, sf::Sprite(allPices, sf::IntRect(__X*4,    0, __X, __Y))},
    {3, sf::Sprite(allPices, sf::IntRect(__X*3, __Y, __X, __Y))},
    {30, sf::Sprite(allPices, sf::IntRect(__X*3,    0, __X, __Y))},
    {4, sf::Sprite(allPices, sf::IntRect(__X*2, __Y, __X, __Y))},
    {40, sf::Sprite(allPices, sf::IntRect(__X*2,    0, __X, __Y))},
    {5, sf::Sprite(allPices, sf::IntRect(__X*1, __Y, __X, __Y))},
    {50, sf::Sprite(allPices, sf::IntRect(__X*1,    0, __X, __Y))},
    {6, sf::Sprite(allPices, sf::IntRect(0, __Y, __X, __Y))},
    {60, sf::Sprite(allPices, sf::IntRect(0,    0, __X, __Y))}
};

int xStart, xEnd, yStart, yEnd;

bool WKmove, BKmove;
bool WR1move, WR2move, BR1move, BR2move;
 

int main(){
    table = homePos;
    WKmove = BKmove = WR1move = WR2move = BR1move = BR2move = true;

    // table[4][4] = 2;

    allPices.loadFromFile("textures\\chess.png");
    allPices.setSmooth(true);
    sf::RenderWindow win(sf::VideoMode(640, 640), "CHESS");
    win.setFramerateLimit(120);


    while(win.isOpen()){
        sf::Event __e;
        while(win.pollEvent(__e)){
            if(__e.type == sf::Event::Closed)
                win.close();
            if(__e.type == sf::Event::MouseButtonPressed){ // if mouse is pressed memorize the pice
                if(__e.mouseButton.button == sf::Mouse::Left){
                    yStart = __e.mouseButton.x / 80 + 1;
                    xStart = __e.mouseButton.y / 80 + 1;
                    // std::cout<< xStart << " " << yStart << " Pressed!\n";
                }
                hold = 1;
            }
            else if(__e.type == sf::Event::MouseButtonReleased){ // if we release, memorise the end position and move the pice if the case
                if(__e.mouseButton.button == sf::Mouse::Left){
                    hold = 0;

                    if(__e.mouseButton.x > 640 || __e.mouseButton.y > 640 || __e.mouseButton.x < 0 || __e.mouseButton.y < 0)
                        break;
                    yEnd = __e.mouseButton.x / 80 + 1;
                    xEnd = __e.mouseButton.y / 80 + 1;
                    if(table[xStart][yStart] == 0)
                        break;
                    if(xStart == xEnd && yStart == yEnd)
                        break;

                    if(table[xStart][yStart]%10 == 0 && turn) break;
                    if(table[xStart][yStart]%10 != 0 && !turn) break;
                   
                    if(table[xStart][yStart]%10 == 0 && table[xEnd][yEnd]%10 == 0 && table[xEnd][yEnd] != 0) break;
                    if(table[xStart][yStart]%10 != 0 && table[xEnd][yEnd]%10 != 0) break;
                    
                    if(table[xStart][yStart] == 1 || table[xStart][yStart] == 10){//king pice
                        if((abs(xStart - xEnd) == 1 && abs(yStart - yEnd) == 1) ||
                            (abs(xStart - xEnd) == 0 && abs(yStart - yEnd) == 0) ||
                            (abs(xStart - xEnd) == 1 && abs(yStart - yEnd) == 0) ||
                            (abs(xStart - xEnd) == 0 && abs(yStart - yEnd) == 1)){
                            if(table[xStart][yStart]%10 == 0)
                                BKmove = false;
                            else
                                WKmove = false;
                            table[xEnd][yEnd] = table[xStart][yStart];
                            table[xStart][yStart] = 0;
                            turn = !turn;
                        }
                        //white casle
                        else if(yStart - yEnd == 2 && table[xStart][yStart] == 1 && WKmove && WR1move){
                            if(table[8][1] == 3){
                                if(table[8][2] == 0 && table[8][3] == 0 && table[8][4] == 0){
                                    table[8][3] = 1;
                                    table[8][4] = 3;
                                    table[8][5] = table[8][1] = 0;
                                    WKmove = false;
                                    WR1move = false;
                                    turn = !turn;
                                }
                            } else WR1move = 0;
                        }
                        else if(yStart - yEnd == -2 && table[xStart][yStart] == 1 && WKmove && WR2move){
                            if(table[8][8] == 3){
                                if(table[8][6] == 0 && table[8][7] == 0){
                                    table[8][7] = 1;
                                    table[8][6] = 3;
                                    table[8][5] = table[8][8] = 0;
                                    WKmove = false;
                                    WR2move = false;
                                    turn = !turn;
                                
                                }
                            } else WR2move = 0;
                        }
                        //black casle
                        else if(yStart - yEnd == 2 && table[xStart][yStart] == 10 && BKmove && BR1move){
                            if(table[1][1] == 30){
                                if(table[1][2] == 0 && table[1][3] == 0 && table[1][4] == 0){
                                    table[1][3] = 10;
                                    table[1][4] = 30;
                                    table[1][5] = table[1][1] = 0;
                                    BKmove = false;
                                    BR1move = false;
                                    turn = !turn;
                                }
                            } else BR1move = 0;
                        }
                        else if(yStart - yEnd == -2 && table[xStart][yStart] == 10 && BKmove && BR2move){
                            if(table[1][8] == 30){
                                if(table[1][6] == 0 && table[1][7] == 0){
                                    table[1][7] = 10;
                                    table[1][6] = 30;
                                    table[1][5] = table[1][8] = 0;
                                    BKmove = false;
                                    BR2move = false;
                                    turn = !turn;
                                
                                }
                            } else BR2move = 0;
                        }
                        
                        std::cout<<yStart-yEnd<<"\n";
                        
                    }

                    else if(table[xStart][yStart] == 2 || table[xStart][yStart] == 20){//queen pice
                        
                        if((xStart == xEnd || yStart == yEnd) ||
                            (abs(xStart - xEnd) == abs(yStart - yEnd))){
                            
                            if(rookCheck(xStart, yStart, xEnd, yEnd, table)){
                                table[xEnd][yEnd] = table[xStart][yStart];
                                table[xStart][yStart] = 0;
                                turn = !turn;

                            }else if(bishopCheck(xStart, yStart, xEnd, yEnd, table)){
                                table[xEnd][yEnd] = table[xStart][yStart];
                                table[xStart][yStart] = 0;
                                turn = !turn;

                            }

                        }  
                    }

                    else if(table[xStart][yStart] == 3 || table[xStart][yStart] == 30){//rook pice
                        if(xStart == xEnd || yStart == yEnd){
                            if(rookCheck(xStart, yStart, xEnd, yEnd, table)){
                                if(xStart == 8 && yStart == 1)
                                    WR1move = 0;
                                else if(xStart == 8 && yStart == 8)
                                    WR2move = 0;
                                else if(xStart == 1 && yStart == 1)
                                    BR2move = 0;
                                else if(xStart == 1 && yStart == 8)
                                    BR1move = 0;
                                
                                
                                table[xEnd][yEnd] = table[xStart][yStart];
                                table[xStart][yStart] = 0;
                                turn = !turn;

                            }
                        }
                    }

                    else if(table[xStart][yStart] == 4 || table[xStart][yStart] == 40){//bishop pice
                        if(abs(xStart - xEnd) == abs(yStart - yEnd)){
                            
                            if(bishopCheck(xStart, yStart, xEnd, yEnd, table)){
                                table[xEnd][yEnd] = table[xStart][yStart];
                                table[xStart][yStart] = 0;
                                turn = !turn;

                            }
                            
                        }
                        
                    }
                    
                    else if(table[xStart][yStart] == 5 || table[xStart][yStart] == 50){//knight pice
                        if((abs(xStart - xEnd) == 2 && abs(yStart - yEnd) == 1) ||
                            (abs(xStart - xEnd) == 1 && abs(yStart - yEnd) == 2)){
                                
                            table[xEnd][yEnd] = table[xStart][yStart];
                            table[xStart][yStart] = 0;
                            turn = !turn;
                        }
                    }
                    
                    else if(table[xStart][yStart] == 6){//white pawn pice
                        if(xEnd == xStart - 1 && yEnd == yStart){
                            if(table[xEnd][yEnd] != 0) break;
                            table[xEnd][yEnd] = table[xStart][yStart];
                            table[xStart][yStart] = 0;
                            turn = !turn;

                        }else if(xEnd == xStart - 1 && (yEnd == yStart + 1 || yEnd == yStart - 1)){

                            if(table[xEnd][yEnd] != 0 && table[xEnd][yEnd]%10 == 0){
                                table[xEnd][yEnd] = table[xStart][yStart];
                                table[xStart][yStart] = 0;
                                turn = !turn;
                            }
                        }
                        else if(xEnd == xStart - 2 && yEnd == yStart && table[xStart - 1][yStart] == 0 && xStart == 7){
                            if(table[xEnd][yEnd] != 0) break;
                            table[xEnd][yEnd] = table[xStart][yStart];
                            table[xStart][yStart] = 0;
                            turn = !turn;
                        }
                        

                    }
                    
                    else if(table[xStart][yStart] == 60){//black pawn pice
                        if(xEnd == xStart + 1 && yEnd == yStart){
                            if(table[xEnd][yEnd] != 0) break;
                            table[xEnd][yEnd] = table[xStart][yStart];
                            table[xStart][yStart] = 0;
                            turn = !turn;
                        }else if(xEnd == xStart + 1 && (yEnd == yStart + 1 || yEnd == yStart - 1)){
                            
                            if(table[xEnd][yEnd]%10 != 0){
                                table[xEnd][yEnd] = table[xStart][yStart];
                                table[xStart][yStart] = 0;
                                turn = !turn;
                            }
                            
                        }
                        else if(xEnd == xStart + 2 && yEnd == yStart && table[xStart + 1][yStart] == 0 && xStart == 2){
                            if(table[xEnd][yEnd] != 0) break;
                            table[xEnd][yEnd] = table[xStart][yStart];
                            table[xStart][yStart] = 0;
                            turn = !turn;
                        }
                        
                        
                    }
                    hold = 0;
                    Attacks(table);
                }
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            hold = 0;
            turn = 0;
            table = homePos;
            table = homePos;
            WKmove = BKmove = WR1move = WR2move = BR1move = BR2move = true;
        }
        drawFrame(win);
    }
}

void drawFrame(sf::RenderWindow& win){
    win.clear();
    renderTable(win);


    win.display();
    // debugTable();
    // debugAttackTable();
}

void renderTable(sf::RenderWindow& win){
    sf::RectangleShape square(sf::Vector2f(80, 80));
    square.setPosition(0, -80);
    for(int i = 1; i<=8; i++){
        square.setPosition(-80, square.getPosition().y + 80);
        for(int j = 1; j<=8; j++){
            square.setPosition(square.getPosition().x + 80, square.getPosition().y);
            if((i+j)%2 == 0)
                if(attacksB[i][j] == NEGRU) square.setFillColor(sf::Color(255, 100, 100));
                else square.setFillColor(sf::Color::White);
            else
                if(attacksB[i][j] == NEGRU) square.setFillColor(sf::Color(100, 80, 0, 255));
                else square.setFillColor(sf::Color(0, 124, 0, 255));
            
            win.draw(square);
            if(table[i][j] != 0){
                pices[table[i][j]].setScale(0.7, 0.7);
                if(hold == true && i == xStart && j == yStart){
                    //pices[table[i][j]].setPosition(mouse.getPosition(win).x, mouse.getPosition(win).y);
                }else{
                    pices[table[i][j]].setPosition(square.getPosition().x-5, square.getPosition().y-5);
                }

                win.draw(pices[table[i][j]]);
            }
        }
    }
    if(mouse.isButtonPressed(sf::Mouse::Left) && hold == true){
        pices[table[xStart][yStart]].setPosition(mouse.getPosition(win).x-40, mouse.getPosition(win).y-40);
        win.draw(pices[table[xStart][yStart]]);
    }
}

void debugTable(){
    system("cls");
    for(int i = 1; i<=8; i++){
        for(int j = 1; j<=8; j++){
            std::cout << table[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void debugAttackTable(){
    system("cls");
    for(int i = 1; i<=8; i++){
        for(int j = 1; j<=8; j++){
            std::cout << attacksW[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
