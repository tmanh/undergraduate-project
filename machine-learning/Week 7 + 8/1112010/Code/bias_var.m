%
% Author: Truong Minh Anh
% Email: truongminhanh93.it@gmail.com
%

function [slope bias var] = bias_var(N)
%khoi tao N lan thu nghiem X, Y theo de bai va ma tran 1 kich thuoc 1x1000
[X Y O] = initialize(N);

%tinh slope cua N lan thu nghiem
a = getAllSlope(X,Y);

%tinh slope g_bar
slope = (O * a) / N;

%tinh bias (tuong doi tren 1000 diem du lieu)
bias = getBias(X,Y,O,N,slope);

%tinh var (tuong doi tren 1000 diem du lieu)
var = getVariance(X,O,N,slope,a);

end

%N: so luong lan thu nghiem can khoi tao
%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%Y: gia tri y cac diem trong cac lan thu nghiem duoc khoi tao
%O: ma tran 1
function [X Y O] = initialize(N)
    X = unifrnd(-1, 1, N, 2);
    Y = sin(pi*X);
    O = ones(1,N);
end

%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%Y: gia tri y cac diem trong cac lan thu nghiem duoc khoi tao
%slope: he so goc duoc tinh cho cac lan thu nghiem
function [slope] = getAllSlope(X,Y)
    a1 = X(:,1).*Y(:,1) + X(:,2).*Y(:,2);
    a2 = X(:,1).*X(:,1) + X(:,2).*X(:,2);
    slope = a1./a2;
end

%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%Y: gia tri y cac diem trong cac lan thu nghiem duoc khoi tao
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%slope: he so goc duoc tinh cho cac lan thu nghiem
function [bias] = getBias(X,Y,O,N,slope)
    G = slope*X(:,1);
    D = Y(:,1)-G;
    D = D.*D;
    bias = (O * D) / N;
end

%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%slope: he so goc duoc tinh cua g_bar
%a: he so goc duoc tinh cho cac lan thu nghiem
function [var] = getVariance(X,O,N,slope,a)
    var = 0;
    for i=1:N
        G = slope*X(:,1);
        H = a(i)*X(:,1);
        D = H - G;
        D = D.*D;
        var = var + O*D;
    end
    var = var / (N * N);
end