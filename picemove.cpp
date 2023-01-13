#pragma once
#include<bits/stdc++.h>
#include <queue>

enum PICES_{
	NO_PICE,
	b_pawn, 	w_pawn,
	b_rook,		w_rook,
	b_knight,	w_knight,
	b_bishop,	w_bishop,
	b_queen,	w_queen,
	b_king,		w_king,
};

inline bool isEnemyPice(PICES_ a, PICES_ b){
	if(a == NO_PICE || b == NO_PICE) return 1;
	return (a % 2) != (b % 2);
}

inline PICES_ enemyPice(PICES_ pice, PICES_ sample){
	if(isEnemyPice(pice, sample)) return sample;


	return PICES_(sample + pice%2 == 0 ? 1 : (-1));
}
bool kingMove_(PICES_ board[8][8], std::pair<int, int> s, std::pair<int, int> e, bool flip){
	if(!isEnemyPice(board[s.second][s.second], board[e.second][e.first])) return 0;


	return(
		std::abs(s.first - e.first) <= 1 && std::abs(s.second - e.second) <= 1
	);

}

bool queenMove(PICES_[8][8], std::pair<int, int>, std::pair<int, int>, bool);
bool rookMove(PICES_[8][8], std::pair<int, int>, std::pair<int, int>, bool);
bool bishopMove(PICES_[8][8], std::pair<int, int>, std::pair<int, int>, bool);
bool pawnMove(PICES_[8][8], std::pair<int, int>, std::pair<int, int>, bool);
bool knightMove(PICES_[8][8], std::pair<int, int>, std::pair<int, int>, bool);




bool check(PICES_ board[8][8], std::pair<int, int> s, bool flip){


	if(board[s.second + (flip?1:-1)][s.first + 1] == 
			enemyPice(board[s.second][s.first], PICES_(flip + 1)) ||
	   board[s.second + (flip?1:-1)][s.first - 1] == 
	   		enemyPice(board[s.second][s.first], PICES_(flip + 1))
	  ) return 1;
	
	

	for(int i = 0; i<8; i++){
		for(int j = 0; j<8; j++){
			if(!isEnemyPice(board[i][j], (PICES_)(flip + 2)) || board[i][j] == NO_PICE)
					continue;

			if(board[i][j] == w_queen || board[i][j] == b_queen){

				if(queenMove(board, {j, i}, s, flip)) {
					std::cout<<"queen check\n";

					return 1;
				}

			} else if(board[i][j] == w_rook || board[i][j] == b_rook){

				if(rookMove(board, {j, i}, s, flip)){ 
					std::cout<<"rook check\n";
					return 1;
				}

			} else if(board[i][j] == w_bishop || board[i][j] == b_bishop){
			
				if(bishopMove(board, {j, i}, s, flip)) {
					std::cout<<"bishop check\n";
					
					return 1;
				}

			} else if(board[i][j] == w_knight || board[i][j] == w_knight){

				if(knightMove(board, {j, i}, s, flip)){
					std::cout<<"knight check\n";

					return 1;
				}

			} else if(board[i][j] == w_king || board[i][j] == b_king){
			
				if(kingMove_(board, {j, i}, s, flip)){
						std::cout<<"illegal move\n";

					return 1;
				}
			}
		}
	}

	return 0;

}

int enPW = -1, enPB = -1;

//flip = 0 -> pawns advance from 6 to 0
//flip = 1 -> pawns advance from 1 to 7
//
// y x for pairs
bool pawnMove(PICES_ board[8][8], std::pair<int, int> s, std::pair<int, int> e, bool flip){

	if(std::abs(e.first - s.first) > 1) return 0;
	

	//captures
	if(std::abs(s.first - e.first) == 1){
		if(flip){
			if(e.second == 5 && enPW == e.first &&
			   (e.second - s.second) == 1 && 
			   isEnemyPice(board[s.second][s.first], board[e.second - 1][e.first])) {
				board[e.second - 1][e.first] = NO_PICE;
				enPB = -1;
				return 1;
			}
			
			if((e.second - s.second) == 1 &&
				board[e.second][e.first] != NO_PICE &&
				isEnemyPice(board[s.second][s.first], board[e.second][e.first])){
				board[e.second][e.first] = NO_PICE;
				enPB = -1;
				return 1;
			}
		}

		if(e.second == 2 && enPB == e.first &&
		  (s.second - e.second) == 1 &&
		   isEnemyPice(board[s.second][s.first], board[e.second + 1][e.first])){
			board[e.second + 1][e.first] = NO_PICE;
			enPW = -1;
			return 1;
		}

		if((s.second - e.second) == 1 &&
			board[e.second][e.first] != NO_PICE &&
			isEnemyPice(board[s.second][s.first], board[e.second][e.first])){
			board[e.second][e.first] = NO_PICE;
			return 1;
		}

		return 0;
	}

	//normal moves
	if(board[e.second][e.first] != NO_PICE) return 0;
	

	if(flip){
		if(s.second == 1 && 
		  ((e.second - s.second) == 1 || (e.second - s.second == 2)) &&
		  board[s.second + 1][s.first] == NO_PICE) {
			enPB = s.first;
			return 1;
		}
		if((e.second - s.second) == 1){
			enPB = -1;
			return 1;
		}
		return 0;
	}
	
	if(s.second == 6 &&
	  ((s.second - e.second) == 1 || (s.second - e.second) == 2)){
		enPW = s.first;
		return 1;
	}
	if(s.second - e.second == 1){
		enPW = -1;
		return 1;
	}
	return 0;
 }

bool rookMove(PICES_ board[8][8], std::pair<int, int> s, std::pair<int, int> e, bool flip){

	if(!((s.first == e.first) ^ (s.second == e.second))) return 0;

	if(s.first == e.first){
		for(int i = std::min(e.second, s.second) + 1; i < std::max(e.second, s.second); i++){
			if(board[i][s.first] != NO_PICE) return 0;
		}
	}

	if(s.second == e.second){
		for(int i = std::min(e.first, s.first) + 1; i < std::max(e.first, e.first); i++){
			if(board[s.second][i] != NO_PICE) return 0;
		}
	}

	if(flip) enPB = -1;
	else enPW = -1;
	return isEnemyPice(board[s.second][s.first], board[e.second][e.first]);
}

bool bishopMove(PICES_ board[8][8], std::pair<int, int> s, std::pair<int, int> e, bool flip){
	if(std::abs((1 + s.second) - (e.second + 1)) != 
	   std::abs((1 + s.first) - (e.first + 1))) return 0;
	

	for(int i = s.second + (s.second > e.second ? -1 : 1),
			j = s.first  + (s.first > e.first ? -1 : 1); 
			
			(s.second > e.second ? i > e.second : i < e.second);
	
			(s.second > e.second ? i-- : i++),
			(s.first > e.first ? j-- : j++)){
	
			if(board[i][j] != NO_PICE) return 0;
	}
	if(flip) enPB = -1;
	else enPW = -1;

	return isEnemyPice(board[s.second][s.first], board[e.second][e.first]);
}

bool knightMove(PICES_ board[8][8], std::pair<int, int> s, std::pair<int, int> e, bool flip){

	bool ret = (
	(std::abs(s.second - e.second) == 2 && std::abs(s.first - e.first) == 1) ||
	(std::abs(s.second - e.second) == 1 && std::abs(s.first - e.first) == 2)) &&
	isEnemyPice(board[e.second][e.first], board[s.second][s.first]);

	if(ret){
		if(flip) enPB = -1;
		else enPW = -1;
		std::cout<<"reseted enpassant\n";
	}

	return ret;
}

bool queenMove(PICES_ board[8][8], std::pair<int, int> s, std::pair<int, int> e, bool flip){
	return(
		rookMove(board, s, e, flip) ||
		bishopMove(board, s, e, flip)		
	);		
}

bool kingMove(PICES_ board[8][8], std::pair<int, int> s, std::pair<int, int> e, bool flip){
	if(!kingMove_(board, s, e, flip)) return 0;
	
//	PICES_ tmp = board[e.second][e.first];
//	board[e.second][e.first] = board[s.second][s.first];
//	board[s.second][s.first] = NO_PICE;
		
	PICES_ afterPice = board[s.second][s.first];
	board[s.second][s.first] = NO_PICE;


	bool ch = check(board, e, flip);
	board[s.second][s.first] = afterPice;
	return !ch;
}
