/* 1112010 - Truong Minh Anh */

/* A* Algorithm */

/*Chinh sua dinh dang xuat cua list*/
:- set_prolog_flag(toplevel_print_options,
             [quoted(true), portray(true), max_depth(0)]).


/* search(S,G,Path,Lenth).
 *
 + S trang thai bat dau.
 + G trang thai ket thuc.
 + Path duong dan tu trang thai bat dau den trang thai ket thuc
 + Length chi phi tu S den G.
 */
search(S,G,Path,Length) :- heuristic(S,G,Heu),
	                   astar([[S,0,Heu,[]]],Length,G,ReversedSolution),
			   reverse(ReversedSolution,Path).


/* astar(Open,Length,Goal,ReversedSolutionPath).
 *
 * Thuat toan A*
 * Neu da den duoc dich (node hien tai la node dich)
 * Nguoc lai lay phan tu dau tien trog Open (PP),
 *   dung ham succ sinh ra cac trang thai con
 *   tim va cap nhat lai gia tri cho cac node con
 *   cap nhat cac node con vao Open,
 *   tiep tuc astar voi Open vua cap nhat
 */

astar([],Length,_,_) :- Length is -1, !.

astar([[G,Len,_,RSol]|_],Length,G,RSol) :- Length is Len, !.

astar([[State,Len,_,Prev]|Others],Length,G,Rsol) :- succ([State,Len,_,Prev],NewL,G,[left,right,up,down]),
					       is_empty(NewL), !,
					       astar(Others,Length,G,Rsol).

astar([[State,Len,_,Prev]|Others],Length,G,Rsol) :- succ([State,Len,_,Prev],NewL,G,[left,right,up,down]),
					            insert_all(NewL,Others,NewOpen),
					            astar(NewOpen,Length,G,Rsol).

/*Kiem tra rong*/
is_empty([]).

/*
 * succ(State, Child, G).
 * success(State,Child, G, Dir).
 *
 * Dua vao trang thai hien tai, tim trang thai successor
 * Neu trang thai moi chua co trong duong di hien tai thi
 * cap nhat lai ham f(n)
 *
 */
succ([_,_,_,_], [], _, []).


succ([State,Len,_,CurrentPath], TailSucc, G, [H|T]) :-
     not(move(State,_,H)),
     succ([State,Len,_,CurrentPath], TailSucc, G, T).

succ([State,Len,_,CurrentPath], [HeadSucc|TailSucc], G, [H|T]) :-
     success([State,Len,_,CurrentPath], HeadSucc, G, H),
     succ([State,Len,_,CurrentPath], TailSucc, G, T).


success([State,Len,_,CurrentPath], [Child,Len2,Fn,[Dir|CurrentPath]], G, Dir) :-
	 /* trang thai ke tiep */
	 move(State,Child,Dir),
	 /* tinh g(n)    */
         Len2 is Len + 1,
	 /* tinh h(n)    */
         heuristic(Child,G,Hn),
	 /* tinh f(n)    */
         Fn is Hn + Len2.

%kiem tra trang thai dich
goal1([1,2,3,4,5,6,7,8,0]).
goal2([0,1,2,3,4,5,6,7,8]).

/*
 * Di chuyen puzzle
 *
 * ABC
 * DEF
 * GHI
 *
 * Voi 0 la o trong thi co cac phep di chuyen
 *   tuong voi vi tri cua o trong
 * +Sang trai: 0 tai B,C,E,F,H,I
 * +Sang phai: 0 tai A,B,D,E,G,H
 * +Len      : 0 tai D,E,F,G,H,I
 * +Xuong    : 0 tai A,B,C,D,E,F
 *
 */

left( [A,0,C,D,E,F,H,I,J] , [0,A,C,D,E,F,H,I,J] ).
left( [A,B,C,D,0,F,H,I,J] , [A,B,C,0,D,F,H,I,J] ).
left( [A,B,C,D,E,F,H,0,J] , [A,B,C,D,E,F,0,H,J] ).
left( [A,B,0,D,E,F,H,I,J] , [A,0,B,D,E,F,H,I,J] ).
left( [A,B,C,D,E,0,H,I,J] , [A,B,C,D,0,E,H,I,J] ).
left( [A,B,C,D,E,F,H,I,0] , [A,B,C,D,E,F,H,0,I] ).

up( [A,B,C,0,E,F,H,I,J] , [0,B,C,A,E,F,H,I,J] ).
up( [A,B,C,D,0,F,H,I,J] , [A,0,C,D,B,F,H,I,J] ).
up( [A,B,C,D,E,0,H,I,J] , [A,B,0,D,E,C,H,I,J] ).
up( [A,B,C,D,E,F,0,I,J] , [A,B,C,0,E,F,D,I,J] ).
up( [A,B,C,D,E,F,H,0,J] , [A,B,C,D,0,F,H,E,J] ).
up( [A,B,C,D,E,F,H,I,0] , [A,B,C,D,E,0,H,I,F] ).

right( [A,0,C,D,E,F,H,I,J] , [A,C,0,D,E,F,H,I,J] ).
right( [A,B,C,D,0,F,H,I,J] , [A,B,C,D,F,0,H,I,J] ).
right( [A,B,C,D,E,F,H,0,J] , [A,B,C,D,E,F,H,J,0] ).
right( [0,B,C,D,E,F,H,I,J] , [B,0,C,D,E,F,H,I,J] ).
right( [A,B,C,0,E,F,H,I,J] , [A,B,C,E,0,F,H,I,J] ).
right( [A,B,C,D,E,F,0,I,J] , [A,B,C,D,E,F,I,0,J] ).

down( [A,B,C,0,E,F,H,I,J] , [A,B,C,H,E,F,0,I,J] ).
down( [A,B,C,D,0,F,H,I,J] , [A,B,C,D,I,F,H,0,J] ).
down( [A,B,C,D,E,0,H,I,J] , [A,B,C,D,E,J,H,I,0] ).
down( [0,B,C,D,E,F,H,I,J] , [D,B,C,0,E,F,H,I,J] ).
down( [A,0,C,D,E,F,H,I,J] , [A,E,C,D,0,F,H,I,J] ).
down( [A,B,0,D,E,F,H,I,J] , [A,B,F,D,E,0,H,I,J] ).


/* move(State,ChildNode,Move).
 *
 * chuyen tu trang thai State sang trang thai ChidNode
 * bai toan 8puzzle co 4 cach di chuyen o trong tuong ung
 *  + left  : di chuyen o trong sang trai
 *  + right : di chuyen o trong sang phai
 *  + up    : di chuyen o trong len tren
 *  + down  : di chuyen o trong xuong duoi
 *
 */
move(P,C,left) :-  left(P,C).
move(P,C,right):-  right(P,C).
move(P,C,up)   :-  up(P,C).
move(P,C,down) :-  down(P,C).


/* heuristic(State,G,H).
 *
 * ham heuristic tinh gia tri heuristic cho node State
 * dua vao khoang cach manhattan
 *
 */
heuristic(State,G,F) :- goal1(G),
			manhattan1(State,F).

heuristic(State,G,F) :- goal2(G),
			manhattan2(State,F).

/* manhattan1(State,P). Dich la [1,2,3,4,5,6,7,8,0].
 * manhattan2(State,P). Dich la [0,1,2,3,4,5,6,7,8].
 * Tinh khoang cach manhattan cho trang thai hien tai State
 * gia tri tra ve cho bien P
 *
 */
manhattan1([A,B,C,D,E,F,G,H,I], P) :-
     a1(A,Pa), b1(B,Pb), c1(C,Pc),
     d1(D,Pd), e1(E,Pe), f1(F,Pf),
     g1(G,Pg), h1(H,Ph), i1(I,Pi),
     P is Pa+Pb+Pc+Pd+Pe+Pf+Pg+Ph+Pg+Pi.

a1(0,4). a1(1,0). a1(2,1). a1(3,2). a1(4,1). a1(5,2). a1(6,3). a1(7,2). a1(8,3).
b1(0,3). b1(1,1). b1(2,0). b1(3,1). b1(4,2). b1(5,1). b1(6,2). b1(7,3). b1(8,2).
c1(0,2). c1(1,2). c1(2,1). c1(3,0). c1(4,3). c1(5,2). c1(6,1). c1(7,4). c1(8,3).
d1(0,3). d1(1,1). d1(2,2). d1(3,3). d1(4,0). d1(5,1). d1(6,2). d1(7,1). d1(8,2).
e1(0,2). e1(1,2). e1(2,1). e1(3,2). e1(4,1). e1(5,0). e1(6,1). e1(7,2). e1(8,1).
f1(0,1). f1(1,3). f1(2,2). f1(3,1). f1(4,2). f1(5,1). f1(6,0). f1(7,3). f1(8,2).
g1(0,2). g1(1,2). g1(2,3). g1(3,4). g1(4,1). g1(5,2). g1(6,3). g1(7,0). g1(8,1).
h1(0,1). h1(1,3). h1(2,2). h1(3,3). h1(4,2). h1(5,1). h1(6,2). h1(7,1). h1(8,0).
i1(0,0). i1(1,4). i1(2,3). i1(3,2). i1(4,3). i1(5,2). i1(6,1). i1(7,2). i1(8,1).


manhattan2([A,B,C,D,E,F,G,H,I], P) :-
     a2(A,Pa), b2(B,Pb), c2(C,Pc),
     d2(D,Pd), e2(E,Pe), f2(F,Pf),
     g2(G,Pg), h2(H,Ph), i2(I,Pi),
     P is Pa+Pb+Pc+Pd+Pe+Pf+Pg+Ph+Pg+Pi.


a2(0,0). a2(1,1). a2(2,2). a2(3,1). a2(4,2). a2(5,3). a2(6,2). a2(7,3). a2(8,4).
b2(0,1). b2(1,0). b2(2,1). b2(3,2). b2(4,1). b2(5,2). b2(6,3). b2(7,2). b2(8,3).
c2(0,2). c2(1,1). c2(2,0). c2(3,3). c2(4,2). c2(5,1). c2(6,4). c2(7,3). c2(8,2).
d2(0,1). d2(1,2). d2(2,3). d2(3,0). d2(4,1). d2(5,2). d2(6,1). d2(7,2). d2(8,3).
e2(0,2). e2(1,1). e2(2,2). e2(3,1). e2(4,0). e2(5,1). e2(6,2). e2(7,1). e2(8,2).
f2(0,3). f2(1,2). f2(2,1). f2(3,2). f2(4,1). f2(5,0). f2(6,3). f2(7,2). f2(8,1).
g2(0,2). g2(1,3). g2(2,4). g2(3,1). g2(4,2). g2(5,3). g2(6,0). g2(7,1). g2(8,2).
h2(0,3). h2(1,2). h2(2,3). h2(3,2). h2(4,1). h2(5,2). h2(6,1). h2(7,0). h2(8,1).
i2(0,4). i2(1,3). i2(2,2). i2(3,3). i2(4,2). i2(5,1). i2(6,2). i2(7,1). i2(8,0).


/*insert danh sach moi lay duoc vao danh sach cu*/


insert_all([F|R],Open1,Open3) :- insert(F,Open1,Open2),
                                 insert_all(R,Open2,Open3).
insert_all([],Open,Open).

/* insert(New,Open,NewOpen).
 *
 * thu tuc chen node New vao dung vi tri cua no
 * trong Open dua vao gia tri cua ham uoc luong
 * (1) chen vao cuoi cua Open neu Open rong
 * (2) chen vao dau cua Open khi
 *	f(NewPP)<f(phan tu dau cua Open)
 * (3) neu (2) sai, tim vi tri thich hop de chen vao Open
 */

insert(New,Open,Open) :- repeat_node(New,Open), ! .
insert(New,[PP|Others],[New,PP|Others]) :- lessthan(New,PP),!.
insert(New,[PP1|Others],[PP1|Merged]):- insert(New,Others,Merged).
insert(New,[],[New]).

repeat_node([P,_,F1,_], [[P,_,F2,_]|_]) :- F1 >= F2.

/* lessthan(PP1,PP2).
 *
 * ho tro cho thu tuc insert, tra ve true neu F1<F2
 *
 */
lessthan([_,_,F1,_], [_,_,F2,_]) :- F1 < F2.
