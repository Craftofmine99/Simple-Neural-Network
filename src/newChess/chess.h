#include <cmath>

enum Piece {pawn,rook,knight,bishop,queen,king,empty};
enum Color {white,black,none};

struct Square
{
	Piece piece = empty;
	Color color = none;
};

struct Board
{
	Square places [8][8];
};

Board* makeBoard()
{
	Board *b = new Board;
	b->places[0][0].piece = rook;
	b->places[1][0].piece = knight;
	b->places[2][0].piece = bishop;
	b->places[3][0].piece = queen;
	b->places[4][0].piece = king;
	b->places[5][0].piece = bishop;
	b->places[6][0].piece = knight;
	b->places[7][0].piece = rook;
	b->places[0][7].piece = rook;
	b->places[1][7].piece = knight;
	b->places[2][7].piece = bishop;
	b->places[3][7].piece = queen;
	b->places[4][7].piece = king;
	b->places[5][7].piece = bishop;
	b->places[6][7].piece = knight;
	b->places[7][7].piece = rook;

	for(int i = 0 ; i != 8 ; ++i)
	{
		b->places[i][0].color = white;
		b->places[i][1].piece = pawn;
		b->places[i][1].color = white;

		b->places[i][7].color = black;
		b->places[i][6].piece = pawn;
		b->places[i][6].color = black;
	}

	return b;
}

bool isValidMove(Board *b,Color c,int sX,int sY,int dX,int dY)
{
	if(sX < 0 || sX > 7 || sY < 0 || sY > 7
		|| dX < 0 || dX > 7 || dY < 0 || dY > 7)
		return false;
	if(c == none) return false;

	Square s = b->places[sX][sY];
	Square d = b->places[dX][dY];
	if(s.color == none || s.piece == empty || s.color != c) return false;
	if(d.color == c) return false;
	if(sX == dX && sY == dY) return false;
	int incx,incy;

	// do the checks here
	switch(s.piece)
	{
		case pawn:
			if(s.color == white)
			{
				if(sY == dY)
				{
					if((dX - sX) == 1 && b->places[dX][dY].piece == empty) return true;
					else if((dX - sX) == 2 && sX == 1)
					{
						if(b->places[dX-1][dY].piece == empty && 
							b->places[dX][dY].piece == empty) return true;
					}
				}
				else if(std::abs((double) sY - dY) == 1.0 && (dX - sX) == 1 && b->places[dX][dY].color == black) return true;
			}
			else
			{
				if(sY == dY)
				{
					if((sX - dX) == 1 && b->places[dX][dY].piece == empty) return true;
					else if((sX - dX) == 2 && sX == 6)
					{
						if(b->places[dX+1][dY].piece == empty && 
							b->places[dX][dY].piece == empty) return true;
					}
				}
				else if(std::abs((double) sY - dY) == 1.0 && (sX - dX) == 1 && b->places[dX][dY].color == white) return true;
			}
			break;
		case rook:
			if(dX == sX && dY != sY)
			{
				int inc = (sY < dY) ? -1 : 1;
				for(int i = sY+=inc ; i != dY ; i += inc)
					if(b->places[dX][i].piece != empty) break;
			}
			else if (dY == sY && dX != sX)
			{
				int inc = (sX < dX) ? -1 : 1;
				for(int i = sX+=inc ; i != dX ; i += inc)
					if(b->places[i][dY].piece != empty) break;
			}
			if(b->places[dX][dY].color == c) break;
			return true;
		case knight:
			if(b->places[dX][dY].color == c) break;
			else if(abs((double)dX - sX) == 2 && abs((double)dY - sY) == 1) return true;
			else if(abs((double)dX - sX) == 1 && abs((double)dY - sY) == 2) return true;
			break;
		case bishop:
			if(abs((double)dX-sX) != abs((double)dY-sY)) break;
			incx = (dX < sX) ? -1 : 1;
			incy = (dY < sY) ? -1 : 1;
			for(int ix = sX,iy = sY ; ix != dX ; ++ix, ++iy)
				if(b->places[ix][iy].piece != empty) break;
			if(b->places[dX][dY].color == c) break;
			return true;
		case queen:
			if(abs((double)dX-sX) != abs((double)dY-sY)) break;
			incx = (dX < sX) ? -1 : 1;
			incy = (dY < sY) ? -1 : 1;
			for(int ix = sX,iy = sY ; ix != dX ; ++ix, ++iy)
				if(b->places[ix][iy].piece != empty) break;
			if(b->places[dX][dY].color == c) break;
			if(dX == sX && dY != sY)
			{
				int inc = (sY < dY) ? -1 : 1;
				for(int i = sY+=inc ; i != dY ; i += inc)
					if(b->places[dX][i].piece != empty) break;
			}
			else if (dY == sY && dX != sX)
			{
				int inc = (sX < dX) ? -1 : 1;
				for(int i = sX+=inc ; i != dX ; i += inc)
					if(b->places[i][dY].piece != empty) break;
			}
			if(b->places[dX][dY].color == c) break;
			return true;
		case king:
			if(abs((double) dX - sX) > 1) break;
			else if(abs((double) dY - sY) > 1) break;
			return true;
		case empty:
			break;
	}

	return false;
}

bool makeMove(Board* b,Color c,int sX,int sY,int dX,int dY)
{
	if(isValidMove(b,c,sX,sY,dX,dY))
	{
		b->places[dX][dY] = b->places[sX][sY];
		b->places[sX][sY].color = none;
		b->places[sX][sY].piece = empty;
		return true;
	}
	else return false;
}