%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [E1 E2 E] = cau6()

e1 = unifrnd(0, 1, 10000, 1);
e2 = unifrnd(0, 1, 10000, 1);

e = min(e1, e2);

E = ones(1,10000) * e / 10000;
E1 = ones(1,10000) * e1 / 10000;
E2 = ones(1,10000) * e1 / 10000;

end