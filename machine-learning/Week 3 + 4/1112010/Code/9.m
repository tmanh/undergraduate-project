%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [I , W, P] = Nonlinear2()

Pr = 0;
J = 0; %luu tong so lan duyet
N = 1000;
O = ones(1,100);
E = 0;
%khai bao cac hypothesis dap an
w2 = [-1; -0.05; 0.08; 0.13; 1.5; 1.5];
w3 = [-1; -0.05; 0.08; 0.13; 1.5; 15];
w4 = [-1; -0.05; 0.08; 0.13; 15; 1.5];
w5 = [-1; -1.5; 0.08; 0.13; 0.05; 0.05];
w6 = [-1; -0.5; 0.08; 1.5; 0.15; 0.15];
wk = [w2 w3 w4 w5 w6];

%khai bao ma tran chua xac suat giong cac hypothesis lan luot theo de bai
P = [0 0 0 0 0];

for i=1:1000,
	%create ten random point
	X = unifrnd(-1, 1, N, 2);
	X = [ones(N,1) X X(:,1).*X(:,2) X.*X];
	
	%initialize output label matrix
	y = [];
	for p=1:N,
		if(X(p,2)*X(p,2) + X(p,3)*X(p,3) - 0.6 >= 0),
			y = [y 1];
        else
			y = [y -1];
        end
    end
	
	%lay ngau nhien 100 diem nhieu
    ran_mat = round(unifrnd(1, 1000, 100, 1));
    
    for p = 1:100
        y(ran_mat(p)) = - y(ran_mat(p));
    end
    
    %tinh gia tri trong so
	w = pinv(X)*y';

    index = round(unifrnd(1,1000));

    %kiem thu voi 1 diem bat ky cua tap huan luyen
    sign1 = X(index,:) * w;
    
    for p=1:5
        signk = sign1 * (X(index,:) * wk(:,p));
        if(signk >= 0)
            P(p) = P(p) + 1;
        end
    end   
end

[value, iter] = max(P);

W = wk(:,iter);
Pr = E / N / 1000;
I = J/1000; %tinh trung binh so lan duyet
end