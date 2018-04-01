/* 1112010 - Truong Minh Anh */

/* A* Algorithm */

/* search(S,G,Path,Lenth).
 *
 + S trang thai bat dau.
 + G trang thai ket thuc.
 + Path duong dan tu trang thai bat dau den trang thai ket thuc
 + Length chi phi tu S den G.
 */
search(S,G,Path,Length) :- heuristic(S,G,Heu),
	                   astar([[S,0,Heu,[]]],Length,G,ReversedSolution),
			   reverse([G|ReversedSolution],Path).


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

astar([[State,_,_,_]|Others],Length,G,Rsol) :- succ(State,NewL),
					       is_empty(NewL), !,
					       astar(Others,Length,G,Rsol).

astar([[State,Len,_,Prev]|Others],Length,G,Rsol) :- succ(State,NewL),
					            getList(State,G,Len,Prev,NewL,[],L),
					            insert_all(L,Others,NewOpen),
					            astar(NewOpen,Length,G,Rsol).

is_empty([]).


/*lay danh sach*/
getList(_,_,_,_,[],L,L).
getList(S,G,Length,Prev,[H|T],[],NewL) :- leng(S,H,Len),
				          heuristic(H,G,Heu),
				          Nlen is Len+Heu+Length,
					  NLen2 is Len+Length,
				          getList(S,G,Length,Prev,T,[[H,NLen2,Nlen,[S|Prev]]],NewL).
getList(S,G,Length, Prev,[H|T],[TH|TT],NewL) :- leng(S,H,Len),
				                heuristic(H,G,Heu),
						NLen2 is Len+Length,
					        Nlen is Len+Heu+Length,
						getList(S,G,Length,Prev,T,[[H,NLen2,Nlen,[S|Prev]],TH|TT],NewL).


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
