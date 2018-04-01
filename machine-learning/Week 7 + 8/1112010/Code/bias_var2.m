%
% Author: Anh Truong
% Email: truongminhanh93.it@gmail.com
%

%----------------------------------------
%HAM MAIN
%----------------------------------------
function [err1 err2 err3 err4 err5] = bias_var2(N)
%khoi tao N lan thu nghiem X, Y theo de bai va ma tran 1 kich thuoc 1x1000
[X Y O] = initialize(N);

%tinh slope cua N lan thu nghiem
b10 = getAll_b(X,Y);
a2 = getAllSlope_ax(X,Y);
[a3 b30] = getAllSlope_axb(X,Y);
a4 = getAllSlope_axx(X,Y);
[a5 b50] = getAllSlope_axxb(X,Y);

%tinh slope cua g_bar
b11 = getb_gbar_b(O,b10,N);
slope2 = getSlope_gbar_ax(O, a2, N);
[slope3 b31] = getSlope_gbar_axb(O, a3, b30, N);
slope4 = getSlope_gbar_axx(O, a4, N);
[slope5 b51] = getSlope_gbar_axxb(O, a5, b50, N);


%tinh cac diem du lieu gbar du doan
G1 = getAllG_b(X,O,b11);
G2 = getAllG_ax(X,slope2);
G3 = getAllG_axb(X,slope3,b31);
G4 = getAllG_axx(X,slope4);
G5 = getAllG_axxb(X,slope5,b51);

%tinh bias (tuong doi tren 1000 diem du lieu)
bias1 = getBias(Y,O,N,G1);
bias2 = getBias(Y,O,N,G2);
bias3 = getBias(Y,O,N,G3);
bias4 = getBias(Y,O,N,G4);
bias5 = getBias(Y,O,N,G5);

%tinh var (tuong doi tren 1000 diem du lieu)
var1 = getVariance_b(X,O,N,G1,b10);
var2 = getVariance_ax(X,O,N,G2,a2);
var3 = getVariance_axb(X,O,N,G3,a3,b30);
var4 = getVariance_axx(X,O,N,G2,a4);
var5 = getVariance_axxb(X,O,N,G5,a5,b50);

%tinh eout cua cac dang hypothesis
err1 = bias1 + var1;
err2 = bias2 + var2;
err3 = bias3 + var3;
err4 = bias4 + var4;
err5 = bias5 + var5;
end


%----------------------------------------
%TINH CAC THONG SO KHOI TAO
%----------------------------------------
%N: so luong lan thu nghiem can khoi tao
%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%Y: gia tri y cac diem trong cac lan thu nghiem duoc khoi tao
%O: ma tran 1
function [X Y O] = initialize(N)
    X = unifrnd(-1, 1, N, 2);
    Y = sin(pi*X);
    O = ones(1,N);
end

%----------------------------------------
%TINH CAC THONG SO CUA CAC PHEP THU DUOC PHAT SINH
%----------------------------------------
%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%Y: gia tri y cac diem trong cac lan thu nghiem duoc khoi tao
%b: he so b tinh cho cac lan thu nghiem
function [b] = getAll_b(X,Y)
    b = (Y(:,1) + Y(:,2))./2;
end

%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%Y: gia tri y cac diem trong cac lan thu nghiem duoc khoi tao
%slope: he so goc duoc tinh cho cac lan thu nghiem
function [slope] = getAllSlope_ax(X,Y)
    a1 = X(:,1).*Y(:,1) + X(:,2).*Y(:,2);
    a2 = X(:,1).*X(:,1) + X(:,2).*X(:,2);
    slope = a1./a2;
end

%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%Y: gia tri y cac diem trong cac lan thu nghiem duoc khoi tao
%slope: he so goc duoc tinh cho cac lan thu nghiem
%b: he so b tinh cho cac lan thu nghiem
function [slope b] = getAllSlope_axb(X,Y)
    a1 = Y(:,1) - Y(:,2);
    b1 = X(:,1).*Y(:,2) - X(:,2).*Y(:,1);
    a2 = X(:,1) - X(:,2);
    slope = a1./a2;
    b = b1./a2;
end

%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%Y: gia tri y cac diem trong cac lan thu nghiem duoc khoi tao
%slope: he so goc duoc tinh cho cac lan thu nghiem
function [slope] = getAllSlope_axx(X,Y)
    a1 = X(:,1).*X(:,1).*Y(:,1) + X(:,2).*X(:,2).*Y(:,2);
    a2 = X(:,1).*X(:,1).*X(:,1).*X(:,1) + X(:,2).*X(:,2).*X(:,2).*X(:,2);
    slope = a1./a2;
end

%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%Y: gia tri y cac diem trong cac lan thu nghiem duoc khoi tao
%slope: he so goc duoc tinh cho cac lan thu nghiem
%b: he so b tinh cho cac lan thu nghiem
function [slope b] = getAllSlope_axxb(X,Y)
    a1 = Y(:,1) - Y(:,2);
    b1 = X(:,1).*X(:,1).*Y(:,2) - X(:,2).*X(:,2).*Y(:,1);
    a2 = X(:,1).*X(:,1) - X(:,2).*X(:,2);
    slope = a1./a2;
    b = b1./a2;
end

%----------------------------------------
%TINH CAC THONG SO CUA HAM GBAR
%----------------------------------------
%a: he so goc duoc tinh cho cac lan thu nghiem
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%slope: he so goc gbar
function [result] = getb_gbar_b(O, b, N)
    result = (O * b) / N;
end

%a: he so goc duoc tinh cho cac lan thu nghiem
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%slope: he so goc gbar
function [slope] = getSlope_gbar_ax(O, a, N)
    slope = (O * a) / N;
end

%a,b: he so duoc tinh cho cac lan thu nghiem
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%result1 result2: ket qua he so cua gbar
function [result1 result2] = getSlope_gbar_axb(O, a, b, N)
    result1 = (O * a) / N;
    result2 = (O * b) / N;
end

%a: he so goc duoc tinh cho cac lan thu nghiem
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%slope: he so goc gbar
function [slope] = getSlope_gbar_axx(O, a, N)
    slope = (O * a) / N;
end

%a,b: he so duoc tinh cho cac lan thu nghiem
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%result1 result2: ket qua he so cua gbar
function [result1 result2] = getSlope_gbar_axxb(O, a, b, N)
    result1 = (O * a) / N;
    result2 = (O * b) / N;
end

%----------------------------------------
%TINH CAC GIA TRI DU DOAN CUA HAM GBAR
%----------------------------------------
%tinh gia tri G_bar du doan cua ham y = b
%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%b: he so b
%G: ket qua toa do diem thu duoc
function [G] = getAllG_b(X,O,b)
    G = b.*O';
end

%tinh gia tri G_bar du doan cua ham y = ax
%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%slope: he so goc gbar
%G: ket qua toa do diem thu duoc
function [G] = getAllG_ax(X,slope)
    G = slope*X(:,1);
end

%tinh gia tri G_bar du doan cua ham y = ax + b
%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%slope,b: he so gbar
%G: ket qua toa do diem thu duoc
function [G] = getAllG_axb(X,slope,b)
    G = slope*X(:,1)+b;
end

%tinh gia tri G_bar du doan cua ham y = ax^2
%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%slope: he so goc gbar
%G: ket qua toa do diem thu duoc
function [G] = getAllG_axx(X,slope)
    G = slope*X(:,1).*X(:,1);
end

%tinh gia tri G_bar du doan cua ham y = ax^2 + b
%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%slope,b: he so gbar
%G: ket qua toa do diem thu duoc
function [G] = getAllG_axxb(X,slope,b)
    G = slope*X(:,1).*X(:,1)+b;
end
%----------------------------------------
%TINH BIAS CUA CAC DANG HYPOTHESIS
%----------------------------------------
%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%Y: gia tri y cac diem trong cac lan thu nghiem duoc khoi tao
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%slope: he so goc duoc tinh cho cac lan thu nghiem
function [bias] = getBias(Y,O,N,G)
    D = Y(:,1)-G;
    D = D.*D;
    bias = (O * D) / N;
end

%----------------------------------------
%TINH VARIANCE CUA CAC DANG HYPOTHESIS
%----------------------------------------
%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%G: cac diem du lieu duoc du doan boi gbar
%a: he so goc duoc tinh cho cac lan thu nghiem
function [var] = getVariance_b(X,O,N,G,b)
    var = 0;
    for i=1:N
        H = b(i)*O';
        D = H - G;
        D = D.*D;
        var = var + O*D;
    end
    var = var / (N * N);
end

%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%G: cac diem du lieu duoc du doan boi gbar
%a: he so goc duoc tinh cho cac lan thu nghiem
function [var] = getVariance_ax(X,O,N,G,a)
    var = 0;
    for i=1:N
        H = a(i)*X(:,1);
        D = H - G;
        D = D.*D;
        var = var + O*D;
    end
    var = var / (N * N);
end

%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%G: cac diem du lieu duoc du doan boi gbar
%a,b: he so goc duoc tinh cho cac lan thu nghiem
function [var] = getVariance_axb(X,O,N,G,a,b)
    var = 0;
    for i=1:N
        H = a(i)*X(:,1)+b(i);
        D = H - G;
        D = D.*D;
        var = var + O*D;
    end
    var = var / (N * N);
end



%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%G: cac diem du lieu duoc du doan boi gbar
%a,b: he so goc duoc tinh cho cac lan thu nghiem
function [var] = getVariance_axxb(X,O,N,G,a,b)
    var = 0;
    for i=1:N
        H = a(i)*X(:,1).*X(:,1)+b(i);
        D = H - G;
        D = D.*D;
        var = var + O*D;
    end
    var = var / (N * N);
end

%X: gia tri x cac diem trong cac lan thu nghiem duoc khoi tao
%O: ma tran 1
%N: so luong lan thu nghiem can khoi tao
%G: cac diem du lieu duoc du doan boi gbar
%a: he so goc duoc tinh cho cac lan thu nghiem
function [var] = getVariance_axx(X,O,N,G,a)
    var = 0;
    for i=1:N
        H = a(i)*X(:,1).*X(:,1);
        D = H - G;
        D = D.*D;
        var = var + O*D;
    end
    var = var / (N * N);
end