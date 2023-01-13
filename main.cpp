#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <bits/stdc++.h>
#include <cmath>
#include "picemove.cpp"

#define __X 128
#define __Y 128
bool turn = 1; //0 black, 1 white
bool hold;

PICES_ homePos[8][8] = {
	{b_rook, b_knight, b_bishop, b_queen, b_king, b_bishop, b_knight, b_rook},
	{b_pawn, b_pawn, b_pawn, b_pawn, b_pawn, b_pawn, b_pawn, b_pawn},
	{NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE},
	{NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE},
	{NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE},
	{NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE, NO_PICE},
	{w_pawn, w_pawn, w_pawn, w_pawn, w_pawn, w_pawn, w_pawn, w_pawn},
	{w_rook, w_knight, w_bishop, w_queen, w_king, w_bishop, w_knight, w_rook}

};

PICES_ board[8][8], selectedPice;

sf::Texture allPices;
sf::Sprite bPNG;
sf::Mouse mouse;

std::unordered_map<PICES_, sf::Sprite> pices;

int xStart, xEnd, yStart, yEnd;



void winRender(sf::RenderWindow&);

void MBpress(sf::RenderWindow& win){
	hold = 1;
	
	//snap!
	
	xStart = mouse.getPosition(win).x/80;
	yStart = mouse.getPosition(win).y/80;

	//std::cout<<char('h' - xStart + 1)<<(8 - yStart)<<'\n';

	selectedPice = board[yStart][xStart];

//	std::cout<<selectedPice<<'\n';
}

void MBrelease(sf::RenderWindow& win){
	if(!hold) return;
	hold = 0;

	int xP = mouse.getPosition(win).x/80, 
		yP = mouse.getPosition(win).y/80;
	
	if(xP == xStart && yP == yStart) return;
	

	switch(selectedPice){
	case b_pawn:
		if(pawnMove(board, {xStart, yStart}, {xP, yP}, 1)) goto _move;
	break;
	case w_pawn:
		if(pawnMove(board, {xStart, yStart}, {xP, yP}, 0)) goto _move;
	break;
	case b_rook:
		if(rookMove(board, {xStart, yStart}, {xP, yP}, 1)) goto _move;
	break;
	case w_rook:
		if(rookMove(board, {xStart, yStart}, {xP, yP}, 0)) goto _move;
	break;
	case b_bishop:
		if(bishopMove(board, {xStart, yStart}, {xP, yP}, 1)) goto _move;
	break;
	case w_bishop:
		if(bishopMove(board, {xStart, yStart}, {xP, yP}, 0)) goto _move;
	break;
	case b_knight:
		if(knightMove(board, {xStart, yStart}, {xP, yP}, 1)) goto _move;
	break;
	case w_knight:
		if(knightMove(board, {xStart, yStart}, {xP, yP}, 0)) goto _move;
	break;
	case b_queen:
		if(queenMove(board, {xStart, yStart}, {xP, yP}, 1)) goto _move;
	break;
	case w_queen:
		if(queenMove(board, {xStart, yStart}, {xP, yP}, 0)) goto _move;
	break;
	case b_king:
		if(kingMove(board, {xStart, yStart}, {xP, yP}, 1)) goto _move;
	break;
	case w_king:
		if(kingMove(board, {xStart, yStart}, {xP, yP}, 0)) goto _move;
	break;
	default:
		return;
	}
	
	return;
_move:
	board[yP][xP] = selectedPice;
	board[yStart][xStart] = NO_PICE;
}


int main(){
	
	for(int i = 0; i<8; i++){
		for(int j = 0; j<8; j++){
			board[i][j] = homePos[i][j];
		}
	}
	
// 	board[4][3] = w_king;

	sf::Texture __tx;
	__tx.loadFromFile("textures/board.png");

	bPNG.setTexture(__tx);

    allPices.loadFromFile("textures/chess.png");
    allPices.setSmooth(true);
    
	sf::RenderWindow win(sf::VideoMode(640, 640), "CHESS");
    //win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(1);


    pices = {
	{w_king,   sf::Sprite(allPices, sf::IntRect(5*__X, __Y, __X, __Y))},
    {b_king,   sf::Sprite(allPices, sf::IntRect(5*__X,   0, __X, __Y))},
    {w_queen,  sf::Sprite(allPices, sf::IntRect(__X*4, __Y, __X, __Y))},
    {b_queen,  sf::Sprite(allPices, sf::IntRect(__X*4,   0, __X, __Y))},
    {w_rook,   sf::Sprite(allPices, sf::IntRect(__X*3, __Y,  __X, __Y))},
    {b_rook,   sf::Sprite(allPices, sf::IntRect(__X*3,   0, __X, __Y))},
    {w_bishop, sf::Sprite(allPices, sf::IntRect(__X*2, __Y,  __X, __Y))},
    {b_bishop, sf::Sprite(allPices, sf::IntRect(__X*2,   0, __X, __Y))},
    {w_knight, sf::Sprite(allPices, sf::IntRect(__X*1, __Y,  __X, __Y))},
    {b_knight, sf::Sprite(allPices, sf::IntRect(__X*1,   0, __X, __Y))},
    {w_pawn,   sf::Sprite(allPices, sf::IntRect(    0, __Y, __X, __Y))},
    {b_pawn,   sf::Sprite(allPices, sf::IntRect(    0,   0, __X, __Y))}};


    while(win.isOpen()){
		sf::Event _e;
		while(win.pollEvent(_e)){
			switch(_e.type){
				case sf::Event::Closed: win.close(); break;
				case sf::Event::MouseButtonPressed: MBpress(win); break;
				case sf::Event::MouseButtonReleased: MBrelease(win); break;
				default: break;
			}
		}
		winRender(win);

		
		
	}
}

void winRender(sf::RenderWindow& win){
	win.clear();
	sf::RectangleShape square;
	square.setSize(sf::Vector2f(80, 80));

	//win.draw(bPNG);
	
	for(int i = 0; i<8; i++){
		for(int j = 0; j<8; j++){
			
			square.setPosition(j*80, i*80);

			if((i+j)%2 == 0) square.setFillColor(sf::Color(226, 226, 226));
			else 	 square.setFillColor(sf::Color(100, 148, 29));

			win.draw(square);
			

			if(board[i][j] == NO_PICE || (hold && (xStart == j && yStart == i))) continue;
			
			pices[board[i][j]].setOrigin((float)__X/2, (float)__Y/2);
			pices[board[i][j]].setPosition((j+1)*80-40, (i+1)*80-40);
			pices[board[i][j]].setScale(0.7, 0.7);

			win.draw(pices[board[i][j]]);
		}
	}

	if(hold){
		pices[board[yStart][xStart]].setPosition(mouse.getPosition(win).x, mouse.getPosition(win).y);
		win.draw(pices[board[yStart][xStart]]);
	}

	win.display();
}
