%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [I , Pr] = Nonlinear3()

Pr = 0;
J = 0; %luu tong so lan duyet
N = 1000;
O = ones(1,100);
E = 0;

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
	
    %them nhieu
    ran_mat = round(unifrnd(1, 1000, 100, 1));
    
    for p = 1:100
        y(ran_mat(p)) = -y(ran_mat(p));
    end
    
    %tinh gia tri trong so
	w = pinv(X)*y';

    %tao 1000 diem kiem thu
    tx = unifrnd(-1,1,1000,2);
    tx = [ones(1000,1) tx tx(:,1).*tx(:,2) tx.*tx];
    
    %gan nhan cho 1000 diem
    signf = [];
    for p=1:N,
		if(tx(p,2)*tx(p,2) + tx(p,3)*tx(p,3) - 0.6 >= 0),
			signf = [signf 1];
        else
			signf = [signf -1];
        end
    end
    
    %them nhieu
    ran_mat = round(unifrnd(1, 1000, 100, 1));
    
    for p = 1:100
        signf(ran_mat(p)) = 1 - signf(ran_mat(p));
    end
    
    %kiem thu voi 1000 diem cua tap test
    signh = (tx(:,:) * w);
    
    count = signh' .* signf;
    
    t_count = 0;
    
    for i = 1:1000
        if(count(i) < 0)
             t_count = t_count + 1;
        end
    end
    
    E = E + t_count;
end

Pr = E / 1000 / 1000;
I = J/1000; %tinh trung binh so lan duyet
end